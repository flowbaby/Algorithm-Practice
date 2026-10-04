/*
 * 答案8-05 fsize打印inode全部信息
 *
 * 提示：在书中 fsize 程序基础上，把 printf 从只打印 st_size 扩展为打印 inode 条目的其余信息：
 * st_ino（inode 号）、st_mode（文件类型与权限位，按八进制打印）、st_nlink（链接数）、
 * st_uid/st_gid（属主与属组）、st_size（字节数）、st_atime/st_mtime/st_ctime（访问/修改/状态
 * 改变时间，按原始秒数打印）。目录仍通过 dirwalk 递归遍历，跳过 "." 与 ".."。
 */
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>

#define MAX_PATH 1024

void dirwalk(char *, void (*fcn)(char *));

/* fsize: 打印 name 的 inode 信息；若是目录则递归 */
void fsize(char *name)
{
    struct stat stbuf;

    if (stat(name, &stbuf) == -1) {
        fprintf(stderr, "fsize: can't access %s\n", name);
        return;
    }
    if ((stbuf.st_mode & S_IFMT) == S_IFDIR)
        dirwalk(name, fsize);
    printf("%10ld %7o %3ld %6ld %6ld %10ld %10ld %10ld %10ld %s\n",
           (long)stbuf.st_ino,
           (long)(stbuf.st_mode & 07777),   /* 类型与权限位 */
           (long)stbuf.st_nlink,
           (long)stbuf.st_uid,
           (long)stbuf.st_gid,
           (long)stbuf.st_size,
           (long)stbuf.st_atime,
           (long)stbuf.st_mtime,
           (long)stbuf.st_ctime,
           name);
}

/* dirwalk: 对 dir 中每个条目调用 fcn */
void dirwalk(char *dir, void (*fcn)(char *))
{
    char name[MAX_PATH];
    struct dirent *dp;
    DIR *dfd;

    if ((dfd = opendir(dir)) == NULL) {
        fprintf(stderr, "dirwalk: can't open %s\n", dir);
        return;
    }
    while ((dp = readdir(dfd)) != NULL) {
        if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0)
            continue;
        if (strlen(dir) + strlen(dp->d_name) + 2 > sizeof(name))
            fprintf(stderr, "dirwalk: name too long %s/%s\n", dir, dp->d_name);
        else {
            sprintf(name, "%s/%s", dir, dp->d_name);
            (*fcn)(name);
        }
    }
    closedir(dfd);
}

int main(int argc, char *argv[])
{
    printf("%10s %7s %3s %6s %6s %10s %10s %10s %10s %s\n",
           "ino", "mode", "nlink", "uid", "gid",
           "size", "atime", "mtime", "ctime", "name");
    if (argc == 1)
        fsize(".");
    else
        while (--argc > 0)
            fsize(*++argv);
    return 0;
}
