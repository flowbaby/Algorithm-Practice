/*
 * 答案8-03 实现_flushbuf-fflush-fclose
 *
 * 提示：_flushbuf 在输出缓冲已满（或无缓冲流每次 putc）时被调用：为流分配缓冲区（首次）并把已缓冲
 * 内容一次 write 出去，然后放入新字符；fflush 把流的剩余缓冲内容立即写出（传 NULL 时刷新全部输出流，
 * 这是标准库语义）；fclose 对可写流先 fflush，再 close 文件描述符、free 缓冲区，并把流槽位清空复用于
 * 下次 fopen。三者的错误都通过置 _ERR 标志并返回 EOF 报告。本文件给出完整的私有 stdio 框架（位标志版）
 * 及演示：用 putc 写文件、fflush 立即落盘、fclose 正常关闭。
 */
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define NULL 0
#define EOF (-1)
#define BUFSIZE 1024
#define OPEN_MAX 20

typedef struct _iobuf {
    int cnt;        /* 剩余字符数 */
    char *ptr;      /* 下一个字符位置 */
    char *base;     /* 缓冲区位置 */
    int flag;       /* 流状态标志 */
    int fd;         /* 文件描述符 */
} FILE;

enum _flags {
    _READ = 01,     /* 可读 */
    _WRITE = 02,    /* 可写 */
    _UNBUF = 04,    /* 无缓冲 */
    _EOF = 010,     /* 已到文件尾 */
    _ERR = 020      /* 出错 */
};

extern FILE _iob[OPEN_MAX];

#define stdin  (&_iob[0])
#define stdout (&_iob[1])
#define stderr (&_iob[2])

int _fillbuf(FILE *);
int _flushbuf(int, FILE *);
int fflush(FILE *);
int fclose(FILE *);

#define feof(p)   (((p)->flag & _EOF) != 0)
#define ferror(p) (((p)->flag & _ERR) != 0)
#define fileno(p) ((p)->fd)
#define getc(p)   (--(p)->cnt >= 0 ? (unsigned char)*(p)->ptr++ : _fillbuf(p))
#define putc(x,p) (--(p)->cnt >= 0 ? *(p)->ptr++ = (x) : _flushbuf((x),p))
#define getchar() getc(stdin)
#define putchar(x) putc((x), stdout)

FILE _iob[OPEN_MAX] = {
    { 0, NULL, NULL, _READ, 0 },
    { 0, NULL, NULL, _WRITE, 1 },
    { 0, NULL, NULL, _WRITE | _UNBUF, 2 }
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
        if ((fp->flag & (_READ | _WRITE)) == 0)   /* 空闲槽 */
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
        lseek(fd, 0L, 2);                         /* 定位到文件尾 */
    } else
        fd = open(name, O_RDONLY, 0);
    if (fd == -1)
        return NULL;

    fp->fd = fd;
    fp->cnt = 0;
    fp->base = NULL;
    fp->flag = (*mode == 'r') ? _READ : _WRITE;
    return fp;
}

/* _fillbuf: 分配并填充输入缓冲区 */
int _fillbuf(FILE *fp)
{
    int bufsize;

    if ((fp->flag & (_READ | _EOF | _ERR)) != _READ)
        return EOF;
    bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZE;
    if (fp->base == NULL)                          /* 尚无缓冲区 */
        if ((fp->base = (char *)malloc(bufsize)) == NULL)
            return EOF;
    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->ptr, bufsize);
    if (--fp->cnt < 0) {                           /* 读失败或已到 EOF */
        if (fp->cnt == -1)
            fp->flag |= _EOF;
        else
            fp->flag |= _ERR;
        fp->cnt = 0;
        return EOF;
    }
    return (unsigned char)*fp->ptr++;
}

/* _flushbuf: 把输出缓冲写出，并放入字符 c */
int _flushbuf(int c, FILE *fp)
{
    int bufsize, n;

    if ((fp->flag & (_WRITE | _ERR)) != _WRITE)
        return EOF;
    bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZE;
    if (fp->base == NULL) {                        /* 首次：分配缓冲区 */
        if ((fp->base = (char *)malloc(bufsize)) == NULL) {
            fp->flag |= _ERR;
            return EOF;
        }
    } else {                                       /* 已有缓冲：先写出 */
        n = fp->ptr - fp->base;
        if (write(fp->fd, fp->base, n) != n) {
            fp->flag |= _ERR;
            return EOF;
        }
    }
    fp->ptr = fp->base;
    fp->cnt = bufsize - 1;
    return (unsigned char)(*fp->ptr++ = c);
}

/* fflush: 把输出流剩余缓冲写出；fp 为 NULL 时刷新全部输出流 */
int fflush(FILE *fp)
{
    int rc = 0;

    if (fp == NULL) {
        for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
            if ((fp->flag & _WRITE) && fp->ptr > fp->base) {
                int n = fp->ptr - fp->base;
                if (write(fp->fd, fp->base, n) != n) {
                    fp->flag |= _ERR;
                    rc = EOF;
                } else {
                    fp->ptr = fp->base;
                    fp->cnt = (fp->flag & _UNBUF) ? 0 : BUFSIZE;
                }
            }
        return rc;
    }
    if ((fp->flag & _WRITE) == 0)                  /* 只读流不能刷新 */
        return EOF;
    if (fp->ptr > fp->base) {
        int n = fp->ptr - fp->base;
        if (write(fp->fd, fp->base, n) != n) {
            fp->flag |= _ERR;
            return EOF;
        }
    }
    fp->ptr = fp->base;
    fp->cnt = (fp->flag & _UNBUF) ? 0 : BUFSIZE;
    return rc;
}

/* fclose: 刷新（若可写）、关闭描述符、释放缓冲区并清空流槽 */
int fclose(FILE *fp)
{
    int rc = 0;

    if ((fp->flag & _WRITE) && fflush(fp) == EOF)
        rc = EOF;
    if (close(fp->fd) == -1)
        rc = EOF;
    if (fp->base != NULL)
        free(fp->base);
    fp->base = NULL;
    fp->ptr = NULL;
    fp->cnt = 0;
    fp->flag = 0;                                  /* 槽位恢复空闲 */
    return rc;
}

/* 演示：用 putc 写入文件，fflush 立即落盘，fclose 关闭 */
int main(int argc, char *argv[])
{
    FILE *fp;
    char *msg = "hello from private stdio\n";
    char *p;
    int c;

    if (argc != 2) {
        errmsg("usage: program outfile\n");
        return 1;
    }
    if ((fp = fopen(argv[1], "w")) == NULL) {
        errmsg("fopen: can't create file\n");
        return 1;
    }
    for (p = msg; *p; p++)
        putc(*p, fp);                 /* 写满缓冲才真正落盘 */
    if (fflush(fp) == EOF) {
        errmsg("fflush failed\n");
        fclose(fp);
        return 1;
    }
    errmsg("fflush ok, now closing\n");
    if (fclose(fp) == EOF) {
        errmsg("fclose failed\n");
        return 1;
    }

    /* 读回验证 */
    if ((fp = fopen(argv[1], "r")) == NULL) {
        errmsg("fopen: can't reopen file\n");
        return 1;
    }
    while ((c = getc(fp)) != EOF)
        putchar(c);
    fclose(fp);
    _flushbuf(0, stdout);
    return 0;
}
