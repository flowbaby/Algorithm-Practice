/*
 * 答案8-07 malloc与free加强错误检查
 *
 * 提示：原版 malloc 不检查请求大小的合理性，free 也不验证要释放的指针是否真的是 malloc 给的。
 * 改进方案：(1) malloc 拒绝 0 字节与超过上限 MAXBYTES 的请求，置 errno=ENOMEM 后返回 NULL；
 * (2) 维护一条"已分配块链"（复用 Header 的 ptr 字段，仅对已分配块有效），malloc 成功时把块登记
 * 进去，free 时先在链中查找，找不到或 size 字段为 0 即判定非法释放，置 errno=EINVAL 并拒绝操作，
 * 找到才从链中移除并归还空闲表。morecore 直接调用内部 free_block 并入新块（新块不在已分配链上）。
 * 代价是每次 malloc/free 多一次链表操作，换来的是一般实现没有的健壮性。
 */
