/*
 * 答案8-07 malloc与free加强错误检查
 *
 * 提示：原版 malloc 不检查请求大小的合理性，free 也不验证要释放的指针是否真的是 malloc 给的。
 * 改进方案：(1) malloc 拒绝 0 字节与超过上限 MAXBYTES 的请求，置 errno=ENOMEM 后返回 NULL；
 * (2) 维护一条"已分配块链"（复用 Header 的 ptr 字段，仅对已分配块有效），malloc 成功时把块登记
 * 进去，free 时先在链中查找，找不到或 size 字段为 0 即判定非法释放，置 errno=EINVAL 并拒绝操作，
 * 找到才从链中移除并归还空闲表。morecore 直接调用内部 free_block 并入新块（新块不在已分配链上）。
 * 代价是每次 malloc/free 多一次链表操作，换来的是一般实现没有的健壮性。
 */
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

#define NULL 0
#define NALLOC 1024            /* 每次 sbrk 的最小单位：Header 的个数 */
#define MAXBYTES (1U << 24)    /* 单次请求的合理上限：16MB */

typedef long Align;

union header {
    struct {
        union header *ptr;     /* 空闲块时指向下一空闲块；已分配块时指向下一已分配块 */
        unsigned size;         /* 本块大小（以 Header 为单位） */
    } s;
    Align x;
};

typedef union header Header;

static Header base;
static Header *freep = NULL;
static Header *alloc_head = NULL;   /* 已分配块链（按最近分配在前） */

/* free_block: 把块并入空闲表并做相邻合并（不检查来源） */
static void free_block(Header *bp)
{
    Header *p;

    for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
        if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
            break;
    if (bp + bp->s.size == p->s.ptr) {
        bp->s.size += p->s.ptr->s.size;
        bp->s.ptr = p->s.ptr->s.ptr;
    } else
        bp->s.ptr = p->s.ptr;
    if (p + p->s.size == bp) {
        p->s.size += bp->s.size;
        p->s.ptr = bp->s.ptr;
    } else
        p->s.ptr = bp;
    freep = p;
}

/* morecore: 向系统申请更多存储，并直接并入空闲表 */
static Header *morecore(unsigned nu)
{
    char *cp;
    Header *up;

    if (nu < NALLOC)
        nu = NALLOC;
    cp = sbrk(nu * sizeof(Header));
    if (cp == (char *)-1)
        return NULL;
    up = (Header *)cp;
    up->s.size = nu;
    free_block(up);                 /* up 不在已分配链上，不能走 free() */
    return freep;
}

/* malloc: 通用存储分配（带合理性检查） */
void *malloc(unsigned nbytes)
{
    Header *p, *prevp;
    unsigned nunits;

    if (nbytes == 0 || nbytes > MAXBYTES) {     /* 不合理的请求 */
        errno = ENOMEM;
        return NULL;
    }
    nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;
    if ((prevp = freep) == NULL) {
        base.s.ptr = freep = prevp = &base;
        base.s.size = 0;
    }
    for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr) {
        if (p->s.size >= nunits) {
            if (p->s.size == nunits)
                prevp->s.ptr = p->s.ptr;
            else {
                p->s.size -= nunits;
                p += p->s.size;
                p->s.size = nunits;
            }
            freep = prevp;
            p->s.ptr = alloc_head;              /* 登记到已分配链 */
            alloc_head = p;
            return (void *)(p + 1);
        }
        if (p == freep)
            if ((p = morecore(nunits)) == NULL)
                return NULL;
    }
}

/* free: 释放块；先验证其确在已分配链上 */
void free(void *ap)
{
    Header *bp, **pp;

    if (ap == NULL)
        return;
    bp = (Header *)ap - 1;
    if (bp->s.size == 0) {                      /* size 字段明显损坏 */
        errno = EINVAL;
        return;
    }
    for (pp = &alloc_head; *pp != NULL && *pp != bp; pp = &(*pp)->s.ptr)
        ;
    if (*pp == NULL) {                          /* 不在已分配链上：非法释放 */
        errno = EINVAL;
        return;
    }
    *pp = bp->s.ptr;                            /* 从已分配链移除 */
    free_block(bp);
    errno = 0;
}

/* 演示：正常分配/释放，以及两类非法操作 */
int main(void)
{
    char *p, *q;
    int saved;

    p = (char *)malloc(100);
    q = (char *)malloc(200);
    if (p == NULL || q == NULL) {
        printf("malloc failed (errno=%d)\n", errno);
        return 1;
    }
    printf("malloc ok: p=%p q=%p\n", (void *)p, (void *)q);

    free(p);
    printf("free(p) ok\n");

    errno = 0;
    free(q + 1);                                /* 非法：不是块起点 */
    saved = errno;
    printf("free(q+1) -> errno=%d (%s)\n", saved,
           saved == EINVAL ? "EINVAL, rejected" : "unexpected");

    errno = 0;
    p = (char *)malloc(0);                      /* 非法：0 尺寸 */
    saved = errno;
    printf("malloc(0) -> %s, errno=%d (%s)\n",
           p == NULL ? "NULL" : "non-NULL",
           saved, saved == ENOMEM ? "ENOMEM" : "unexpected");

    free(q);
    return 0;
}
