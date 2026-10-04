/*
 * 答案8-02 字段版fopen与_fillbuf
 *
 * 提示：书中 fopen/_fillbuf 用一个整型 flag 配合显式位运算（_READ=01、_WRITE=02、_UNBUF=04、
 * _EOF=010、_ERR=020）记录流状态；本实现改用位字段（bit-field）声明 FILE 结构，每个状态位独立
 * 命名，读写直观、无需定义枚举常量，也免去 &、| 等位运算，代码更不易出错。代价是位字段访问通常
 * 比整型标志稍慢（编译生成掩码与移位），存储也略大，但对 OPEN_MAX 个流可忽略。getc/putc 宏、
 * _flushbuf/_fillbuf 的调用接口与缓冲逻辑保持与书中一致。
 */
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define NULL 0
#define EOF (-1)
#define BUFSIZE 1024
#define OPEN_MAX 20

typedef struct _iobuf {
    int cnt;                     /* 剩余字符数 */
    char *ptr;                   /* 下一个字符位置 */
    char *base;                  /* 缓冲区位置 */
    unsigned int flag_read : 1;  /* 可读 */
    unsigned int flag_write : 1; /* 可写 */
    unsigned int flag_unbuf : 1; /* 无缓冲 */
    unsigned int flag_eof : 1;   /* 已到文件尾 */
    unsigned int flag_err : 1;   /* 出错 */
    int fd;                      /* 文件描述符 */
} FILE;

extern FILE _iob[OPEN_MAX];

#define stdin  (&_iob[0])
#define stdout (&_iob[1])
#define stderr (&_iob[2])

int _fillbuf(FILE *);
int _flushbuf(int, FILE *);

#define feof(p)   ((p)->flag_eof)
#define ferror(p) ((p)->flag_err)
#define fileno(p) ((p)->fd)
#define getc(p)   (--(p)->cnt >= 0 ? (unsigned char)*(p)->ptr++ : _fillbuf(p))
#define putc(x,p) (--(p)->cnt >= 0 ? *(p)->ptr++ = (x) : _flushbuf((x),p))
#define getchar() getc(stdin)
#define putchar(x) putc((x), stdout)

FILE _iob[OPEN_MAX] = {
    { 0, NULL, NULL, 1, 0, 0, 0, 0, 0 },   /* stdin : 可读, fd 0 */
    { 0, NULL, NULL, 0, 1, 0, 0, 0, 1 },   /* stdout: 可写, fd 1 */
    { 0, NULL, NULL, 0, 1, 1, 0, 0, 2 }    /* stderr: 可写, 无缓冲, fd 2 */
};

/* errmsg: 向 stderr 写一条简单错误消息 */
void errmsg(char *s)
{
    while (*s)
        write(STDERR_FILENO, s++, 1);
}

/* fopen: 打开文件，返回流指针 */
FILE *fopen(char *name, char *mode)
{
    int fd;
    FILE *fp;

    if (*mode != 'r' && *mode != 'w' && *mode != 'a') {
        errmsg("fopen: illegal mode\n");
        return NULL;
    }
    for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
        if (!fp->flag_read && !fp->flag_write)   /* 找空闲槽 */
            break;
    if (fp >= _iob + OPEN_MAX) {
        errmsg("fopen: too many files\n");
        return NULL;
    }

    if (*mode == 'w')
        fd = creat(name, 0666);
    else if (*mode == 'a') {
        if ((fd = open(name, O_WRONLY, 0)) == -1)
            fd = creat(name, 0666);
        lseek(fd, 0L, 2);                        /* 定位到文件尾 */
    } else
        fd = open(name, O_RDONLY, 0);
    if (fd == -1)
        return NULL;

    fp->fd = fd;
    fp->cnt = 0;
    fp->base = NULL;
    fp->flag_read = (*mode == 'r');
    fp->flag_write = (*mode != 'r');
    fp->flag_unbuf = 0;
    fp->flag_eof = 0;
    fp->flag_err = 0;
    return fp;
}

/* _fillbuf: 分配并填充输入缓冲区 */
int _fillbuf(FILE *fp)
{
    int bufsize;

    if (!fp->flag_read || fp->flag_eof || fp->flag_err)
        return EOF;
    bufsize = fp->flag_unbuf ? 1 : BUFSIZE;
    if (fp->base == NULL)                        /* 尚无缓冲区 */
        if ((fp->base = (char *)malloc(bufsize)) == NULL)
            return EOF;
    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->ptr, bufsize);
    if (--fp->cnt < 0) {                         /* 读失败或已到 EOF */
        if (fp->cnt == -1)
            fp->flag_eof = 1;
        else
            fp->flag_err = 1;
        fp->cnt = 0;
        return EOF;
    }
    return (unsigned char)*fp->ptr++;
}

/* _flushbuf: 把输出缓冲写出，并放入字符 c */
int _flushbuf(int c, FILE *fp)
{
    int bufsize, n;

    if (!fp->flag_write || fp->flag_err)
        return EOF;
    bufsize = fp->flag_unbuf ? 1 : BUFSIZE;
    if (fp->base == NULL) {
        if ((fp->base = (char *)malloc(bufsize)) == NULL) {
            fp->flag_err = 1;
            return EOF;
        }
    } else {
        n = fp->ptr - fp->base;                  /* 已有内容先写出 */
        if (write(fp->fd, fp->base, n) != n) {
            fp->flag_err = 1;
            return EOF;
        }
    }
    fp->ptr = fp->base;
    fp->cnt = bufsize - 1;
    return (unsigned char)(*fp->ptr++ = c);
}

/* 演示：把命令行文件（或标准输入）复制到标准输出 */
int main(int argc, char *argv[])
{
    FILE *fp;
    int c;

    if (argc == 1) {
        while ((c = getchar()) != EOF)
            putchar(c);
    } else {
        if ((fp = fopen(argv[1], "r")) == NULL) {
            errmsg("fopen: can't open file\n");
            return 1;
        }
        while ((c = getc(fp)) != EOF)
            putchar(c);
    }
    _flushbuf(0, stdout);
    return 0;
}
