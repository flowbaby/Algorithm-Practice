/*
 * 答案8-01 系统调用版cat
 *
 * 提示：用 open/read/write/close 四个系统调用重写第7章的 cat：无参数时把标准输入复制到标准输出，
 * 有参数时逐个打开、复制、关闭。read 返回 0 表示 EOF，返回 -1 表示出错；write 不保证一次写完，
 * 因此用循环确保把缓冲区全部写出。速度实验：对同一大文件分别运行第7章库函数版与本系统调用版，
 * 用 time 命令或 clock() 比较；结论通常是：带 BUFSIZ 缓冲的系统调用版与标准库版速度相当，
 * 而逐字节的 read/write 会明显慢于缓冲 I/O。
 */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

/* filecopy: 把 fd_in 复制到 fd_out */
void filecopy(int fd_in, int fd_out)
{
    char buf[BUFSIZ];
    int n;
    char *p;
    int left;

    while ((n = read(fd_in, buf, BUFSIZ)) > 0) {
        p = buf;
        left = n;
        while (left > 0) {              /* write 可能只写部分，循环写完 */
            int m = write(fd_out, p, left);
            if (m <= 0)
                return;
            p += m;
            left -= m;
        }
    }
}

int main(int argc, char *argv[])
{
    int fd;

    if (argc == 1) {
        filecopy(STDIN_FILENO, STDOUT_FILENO);
    } else {
        while (--argc > 0) {
            if ((fd = open(*++argv, O_RDONLY, 0)) == -1) {
                fprintf(stderr, "cat: can't open %s\n", *argv);
                return 1;
            }
            filecopy(fd, STDOUT_FILENO);
            close(fd);
        }
    }
    return 0;
}
