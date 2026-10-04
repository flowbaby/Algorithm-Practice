/*
 * 答案8-04 实现fgets
 *
 * 提示：fgets(s,n,fp) 最多读取 n-1 个字符存入 s，遇到换行符立即停止（换行符也存入），最后补 '\0'。
 * 逐字符使用本章的 getc 宏（内部调用 _fillbuf）即可，无需自己管理缓冲。返回 NULL 表示在存入任何
 * 字符之前就遇到 EOF。本文件给出私有 stdio 的最小框架（FILE 结构、_iob、_fillbuf、getc 宏、fopen）
 * 与 fgets 实现，演示程序用它逐行读取文件并打印行号。
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
    _READ = 01, _WRITE = 02, _UNBUF = 04, _EOF = 010, _ERR = 020
};

extern FILE _iob[OPEN_MAX];

#define stdin  (&_iob[0])
#define stdout (&_iob[1])
#define stderr (&_iob[2])

int _fillbuf(FILE *);
int _flushbuf(int, FILE *);

#define getc(p)   (--(p)->cnt >= 0 ? (unsigned char)*(p)->ptr++ : _fillbuf(p))
#define putc(x,p) (--(p)->cnt >= 0 ? *(p)->ptr++ = (x) : _flushbuf((x),p))
#define getchar() getc(stdin)
#define putchar(x) putc((x), stdout)

FILE _iob[OPEN_MAX] = {
    { 0, NULL, NULL, _READ, 0 },
    { 0, NULL, NULL, _WRITE, 1 },
    { 0, NULL, NULL, _WRITE | _UNBUF, 2 }
};

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
        if ((fp->flag & (_READ | _WRITE)) == 0)
            break;
    if (fp >= _iob + OPEN_MAX)
        return NULL;

    if (*mode == 'w')
        fd = creat(name, 0666);
    else if (*mode == 'a') {
        if ((fd = open(name, O_WRONLY, 0)) == -1)
            fd = creat(name, 0666);
        lseek(fd, 0L, 2);
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
    if (fp->base == NULL)
        if ((fp->base = (char *)malloc(bufsize)) == NULL)
            return EOF;
    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->ptr, bufsize);
    if (--fp->cnt < 0) {
        if (fp->cnt == -1)
            fp->flag |= _EOF;
        else
            fp->flag |= _ERR;
        fp->cnt = 0;
        return EOF;
    }
    return (unsigned char)*fp->ptr++;
}

/* _flushbuf: 把输出缓冲写出，并放入字符 c（供 putc 宏与演示使用） */
int _flushbuf(int c, FILE *fp)
{
    int bufsize, n;

    if ((fp->flag & (_WRITE | _ERR)) != _WRITE)
        return EOF;
    bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZE;
    if (fp->base == NULL) {
        if ((fp->base = (char *)malloc(bufsize)) == NULL) {
            fp->flag |= _ERR;
            return EOF;
        }
    } else {
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

/* fgets: 最多读 n-1 个字符，遇换行停止；返回 s，未读入任何字符即 EOF 时返回 NULL */
char *fgets(char *s, int n, FILE *fp)
{
    int c;
    char *cs = s;

    while (--n > 0 && (c = getc(fp)) != EOF) {
        *cs++ = c;
        if (c == '\n')
            break;
    }
    *cs = '\0';
    return (cs == s) ? NULL : s;
}

/* putdec: 把非负整数写到指定描述符（演示用，避免依赖标准库 printf） */
void putdec(int fd, long n)
{
    char buf[24];
    int i = 0;

    if (n == 0) {
        write(fd, "0", 1);
        return;
    }
    while (n > 0) {
        buf[i++] = '0' + (int)(n % 10);
        n /= 10;
    }
    while (i > 0)
        write(fd, &buf[--i], 1);
}

/* 演示：fgets 逐行读取命令行指定的文件，打印行号与行内容 */
int main(int argc, char *argv[])
{
    FILE *fp;
    char line[256];
    long lineno = 0;

    if (argc != 2) {
        errmsg("usage: program file\n");
        return 1;
    }
    if ((fp = fopen(argv[1], "r")) == NULL) {
        errmsg("fopen: can't open file\n");
        return 1;
    }
    while (fgets(line, sizeof line, fp) != NULL) {
        putdec(STDOUT_FILENO, ++lineno);
        write(STDOUT_FILENO, ": ", 2);
        {
            char *p = line;
            while (*p)
                write(STDOUT_FILENO, p++, 1);
        }
    }
    return 0;
}
