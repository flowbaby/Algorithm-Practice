/*
 * 答案8-06 实现calloc
 *
 * 提示：calloc(n,size) 与 malloc 的区别在于：(1) 申请 n*size 字节并返回指向 n 个 size 大小对象的
 * 指针；(2) 存储必须初始化为全零。最直接的做法是"调用 malloc"：算出总字节数（注意检查 n 与 size
 * 的乘积溢出、以及 0 尺寸请求），malloc 成功后逐字节清零。本文件包含书中第8-7节的 malloc/free
 * 完整实现（首尾相接的空闲表 + sbrk 扩容），在其上实现 calloc。
 */
#include <stdio.h>
#include <unistd.h>

#define NULL 0
#define NALLOC 1024            /* 每次 sbrk 的最小单位：Header 的个数 */

typedef long Align;            /* 按最严格类型对齐 */

union header {                 /* 空闲块头部 */
    struct {
        union header *ptr;     /* 下一个空闲块 */
        unsigned size;         /* 本块大小（以 Header 为单位） */
    } s;
    Align x;                   /* 强制对齐 */
};

typedef union header Header;

static Header base;            /* 空表起点 */
static Header *freep = NULL;   /* 空闲表头 */

/* free: 把块放回空闲表 */
void free(void *ap)
{
    Header *bp, *p;

    bp = (Header *)ap - 1;
    for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
        if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
            break;
    if (bp + bp->s.size == p->s.ptr) {      /* 与后块合并 */
        bp->s.size += p->s.ptr->s.size;
        bp->s.ptr = p->s.ptr->s.ptr;
    } else
        bp->s.ptr = p->s.ptr;
    if (p + p->s.size == bp) {              /* 与前块合并 */
        p->s.size += bp->s.size;
        p->s.ptr = bp->s.ptr;
    } else
        p->s.ptr = bp;
    freep = p;
}

/* morecore: 向系统申请更多存储 */
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
    free((void *)(up + 1));
    return freep;
}

/* malloc: 通用存储分配 */
void *malloc(unsigned nbytes)
{
    Header *p, *prevp;
    unsigned nunits;

    nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;
    if ((prevp = freep) == NULL) {          /* 尚无空闲表：建立 */
        base.s.ptr = freep = prevp = &base;
        base.s.size = 0;
    }
    for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr) {
        if (p->s.size >= nunits) {          /* 足够大 */
            if (p->s.size == nunits)        /* 恰好 */
                prevp->s.ptr = p->s.ptr;
            else {                          /* 切出尾部一块 */
                p->s.size -= nunits;
                p += p->s.size;
                p->s.size = nunits;
            }
            freep = prevp;
            return (void *)(p + 1);
        }
        if (p == freep)                     /* 绕回：空闲表已空 */
            if ((p = morecore(nunits)) == NULL)
                return NULL;
    }
}

/* calloc: 分配 n*size 字节并清零 */
void *calloc(unsigned n, unsigned size)
{
    unsigned total;
    char *p, *q;

    if (n == 0 || size == 0)
        return NULL;
    if (n > (unsigned)-1 / size)            /* 乘积溢出检查 */
        return NULL;
    total = n * size;
    if ((p = (char *)malloc(total)) != NULL)
        for (q = p; q < p + total; q++)
            *q = 0;
    return p;
}

/* 演示：分配整数数组、校验清零、释放 */
int main(void)
{
    int *a;
    int n = 10, i, allzero = 1;

    a = (int *)calloc((unsigned)n, sizeof(int));
    if (a == NULL) {
        printf("calloc failed\n");
        return 1;
    }
    for (i = 0; i < n; i++)
        if (a[i] != 0)
            allzero = 0;
    printf("calloc(%d, %d) -> %s\n", n, (int)sizeof(int),
           allzero ? "all zero" : "NOT zero");
    a[3] = 42;
    free(a);
    printf("free ok\n");
    return 0;
}
