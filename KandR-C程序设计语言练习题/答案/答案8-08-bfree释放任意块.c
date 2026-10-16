/*
 * 答案8-08 bfree释放任意块
 *
 * 提示：bfree(p,n) 让用户把一段静态或外部数组 p（n 字节）在运行时并入 malloc/free 维护的空闲表。
 * 要点：(1) 校验 n 至少能容纳一个 Header，且 p 按 Header 对齐（否则无法安全放置头部），不满足则
 * 置 errno=EINVAL 拒绝；(2) 把 p 强制转换为 Header*，填写 size = n/sizeof(Header)（向下取整到
 * Header 的整数倍）；(3) 该块并非来自 malloc，不能走带"已分配链验证"的 free()，应直接调用内部
 * free_block 完成相邻合并并入空闲表。本文件基于加强版 malloc/free（含已分配链检查）实现。
 */
