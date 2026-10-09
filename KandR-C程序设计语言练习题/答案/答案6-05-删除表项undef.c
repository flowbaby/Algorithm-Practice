/*
 * 答案6-05 删除表项undef
 *
 * 提示：undef 在 lookup 的哈希桶链表中查找名字，找到后从链表中摘除
 * 该节点并释放 name、defn 与节点本身。注意维护前驱指针：被删节点是
 * 链表头时更新 hashtab[h]，否则把前驱的 next 指向被删节点的 next。
 * main 演示 install 后 undef 再 lookup 验证删除生效。
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHSIZE 101

struct nlist {              /* 表项 */
    struct nlist *next;     /* 链表中下一项 */
    char *name;             /* 名字 */
    char *defn;             /* 替换文本 */
};

static struct nlist *hashtab[HASHSIZE];     /* 指针表 */

/* hash: 计算字符串的散列值 */
unsigned hash(char *s)
{
    unsigned hashval;

    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;
    return hashval % HASHSIZE;
}

/* lookup: 在表中查找名字 */
struct nlist *lookup(char *s)
{
    struct nlist *np;

    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
            return np;      /* 找到 */
    return NULL;            /* 未找到 */
}

/* install: 把 (name, defn) 放入表；已存在时更新 defn */
struct nlist *install(char *name, char *defn)
{
    struct nlist *np;
    unsigned hashval;

    if ((np = lookup(name)) == NULL) {      /* 不在表中 */
        np = (struct nlist *)malloc(sizeof(*np));
        if (np == NULL || (np->name = strdup(name)) == NULL)
            return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else                                  /* 已在表中 */
        free((void *)np->defn);             /* 释放旧定义 */
    if ((np->defn = strdup(defn)) == NULL)
        return NULL;
    return np;
}

/* undef: 从表中删除名字及其定义 */
void undef(char *name)
{
    unsigned h = hash(name);
    struct nlist *np, *prev = NULL;

    for (np = hashtab[h]; np != NULL; prev = np, np = np->next)
        if (strcmp(name, np->name) == 0) {
            if (prev == NULL)               /* 删的是链表头 */
                hashtab[h] = np->next;
            else
                prev->next = np->next;
            free(np->name);
            free(np->defn);
            free(np);
            return;
        }
}

int main(void)
{
    struct nlist *np;

    install("IN", "1");
    install("OUT", "0");
    install("MAX", "100");
    printf("删除前: IN=%s OUT=%s MAX=%s\n",
           lookup("IN")->defn, lookup("OUT")->defn, lookup("MAX")->defn);

    undef("OUT");
    np = lookup("OUT");
    printf("删除 OUT 后 lookup(\"OUT\") = %s\n", np ? np->defn : "(NULL)");
    printf("IN=%s MAX=%s 仍然存在\n", lookup("IN")->defn, lookup("MAX")->defn);
    return 0;
}
