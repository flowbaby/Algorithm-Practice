/*
 * 答案8-08 bfree释放任意块
 *
 * 提示：bfree(p,n) 让用户把一段静态或外部数组 p（n 字节）在运行时并入 malloc/free 维护的空闲表。
 * 要点：(1) 校验 n 至少能容纳一个 Header，且 p 按 Header 对齐（否则无法安全放置头部），不满足则
 * 置 errno=EINVAL 拒绝；(2) 把 p 强制转换为 Header*，填写 size = n/sizeof(Header)（向下取整到
 * Header 的整数倍）；(3) 该块并非来自 malloc，不能走带"已分配链验证"的 free()，应直接调用内部
 * free_block 完成相邻合并并入空闲表。本文件基于加强版 malloc/free（含已分配链检查）实现。
 */
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

#define NULL 0
#define NALLOC 1024
#define MAXBYTES (1U << 24)

typedef long Align;

union header {
    struct {
        union header *ptr;
        unsigned size;
    } s;
    Align x;
};

typedef union header Header;

static Header base;
static Header *freep = NULL;
static Header *alloc_head = NULL;

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
    free_block(up);
    return freep;
}

void *malloc(unsigned nbytes)
{
    Header *p, *prevp;
    unsigned nunits;

    if (nbytes == 0 || nbytes > MAXBYTES) {
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
            p->s.ptr = alloc_head;
            alloc_head = p;
            return (void *)(p + 1);
        }
        if (p == freep)
            if ((p = morecore(nunits)) == NULL)
                return NULL;
    }
}

void free(void *ap)
{
    Header *bp, **pp;

    if (ap == NULL)
        return;
    bp = (Header *)ap - 1;
    if (bp->s.size == 0) {
        errno = EINVAL;
        return;
    }
    for (pp = &alloc_head; *pp != NULL && *pp != bp; pp = &(*pp)->s.ptr)
        ;
    if (*pp == NULL) {
        errno = EINVAL;
        return;
    }
    *pp = bp->s.ptr;
    free_block(bp);
    errno = 0;
}

/* bfree: 把 p 开始的 n 字节任意块并入空闲表 */
void bfree(char *p, unsigned n)
{
    Header *hp;

    if (n < sizeof(Header)) {                          /* 放不下头部 */
        errno = EINVAL;
        return;
    }
    if ((unsigned long)p % sizeof(Header) != 0) {      /* 未按 Header 对齐 */
        errno = EINVAL;
        return;
    }
    hp = (Header *)p;
    hp->s.size = n / sizeof(Header);                   /* 取整为 Header 的整数倍 */
    free_block(hp);
    errno = 0;
}

static char userpool[10000];      /* 用户提供的静态数组 */

/* 演示：把静态数组并入空闲表，随后 malloc 应从中取得存储 */
int main(void)
{
    char *p;
    int i, inside = 1;

    bfree(userpool, sizeof userpool);
    if (errno != 0) {
        printf("bfree failed, errno=%d\n", errno);
        return 1;
    }
    printf("bfree ok: userpool=%p..%p\n",
           (void *)userpool, (void *)(userpool + sizeof userpool));

    for (i = 0; i < 5; i++) {
        p = (char *)malloc(100);
        if (p == NULL) {
            printf("malloc %d failed\n", i);
            return 1;
        }
        if (p < userpool || p >= userpool + sizeof userpool)
            inside = 0;
        free(p);
    }
    printf("malloc from user pool: %s\n",
           inside ? "all inside pool" : "NOT inside pool");
    return 0;
}
