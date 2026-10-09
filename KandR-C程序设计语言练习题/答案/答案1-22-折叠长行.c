/*
 * 答案1-22 折叠长行
 *
 * 提示：用数组 line 保存当前行（最多 MAXCOL 列），逐字符读入并跟踪 pos。当 pos 达到 MAXCOL 时，从后向前找最后一个空格作为折行点：有空格则把行折到该空格之后，无空格则在 MAXCOL 处硬折。折行后把剩余字符搬到行首继续处理。制表符先展开为空格再参与折叠。
 */
#include <stdio.h>

#define MAXCOL 10   /* maximum column of input */
#define TABINC 8    /* tab increment size */

char line[MAXCOL];  /* input line buffer */

int exptab(int pos);
int findblnk(int pos);
int newpos(int pos);
void printl(int pos);

/* fold long input lines into two or more shorter lines */
int main()
{
    int c, pos;

    pos = 0;
    while ((c = getchar()) != EOF) {
        line[pos] = c;              /* store current character */
        if (c == '\t')
            pos = exptab(pos);
        else if (c == '\n') {
            printl(pos);
            pos = 0;
        } else {
            ++pos;
        }
        if (pos >= MAXCOL) {        /* the line has reached the fold limit */
            pos = findblnk(pos);
            printl(pos);
            pos = newpos(pos);
        }
    }
    return 0;
}

/* exptab: expand tab to blanks */
int exptab(int pos)
{
    line[pos] = ' ';
    ++pos;
    while (pos < MAXCOL && pos % TABINC != 0) {
        line[pos] = ' ';
        ++pos;
    }
    return pos;
}

/* findblnk: find the last blank in line[0..pos-1]; return fold position */
int findblnk(int pos)
{
    int i;

    i = pos - 1;                /* start at the last stored character */
    while (i > 0 && line[i] != ' ')
        --i;
    if (i == 0 && line[0] != ' ')
        return MAXCOL;          /* no blanks found: fold at MAXCOL */
    else
        return i + 1;           /* fold after the blank */
}

/* printl: print line[0..pos-1] followed by a newline */
void printl(int pos)
{
    int i;

    for (i = 0; i < pos; ++i)
        putchar(line[i]);
    if (pos > 0)
        putchar('\n');
}

/* newpos: move the text from line[pos..] to the beginning; return new length */
int newpos(int pos)
{
    int i, j;

    if (pos <= 0 || pos >= MAXCOL)
        return 0;
    else {
        i = 0;
        for (j = pos; j < MAXCOL; ++j) {
            line[i] = line[j];
            ++i;
        }
        return i;
    }
}
