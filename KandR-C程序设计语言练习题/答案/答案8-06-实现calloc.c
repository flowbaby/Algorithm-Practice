/*
 * 答案8-06 实现calloc
 *
 * 提示：calloc(n,size) 与 malloc 的区别在于：(1) 申请 n*size 字节并返回指向 n 个 size 大小对象的
 * 指针；(2) 存储必须初始化为全零。最直接的做法是"调用 malloc"：算出总字节数（注意检查 n 与 size
 * 的乘积溢出、以及 0 尺寸请求），malloc 成功后逐字节清零。本文件包含书中第8-7节的 malloc/free
 * 完整实现（首尾相接的空闲表 + sbrk 扩容），在其上实现 calloc。
 */
