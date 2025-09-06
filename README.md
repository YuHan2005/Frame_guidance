# 项目名称

本项目用于目标识别与跟踪，目前主要实现了相机识别模块和目标相对位置的传递功能，后续将继续完善轨迹预测与决策逻辑。

---

## 开发日志

### [2025-09-06]
- 识别部分基本完工，已经可以给 **track** 模块传送相机和目标的相对位置  
- **track** 的卡尔曼滤波部分还未完成初始化和决策逻辑设计  

---

## 构建与运行

### 1. 配置与编译
```bash
cmake -S .. -DBUILD_TESTS=ON     # 重新配置（无则创建，有则复用并更新缓存）
cmake --build . -j              # 编译

ctest --test-dir . --output-on-failure   # 执行测试并显示失败详情


为了方便 clangd 在项目根目录找到编译数据库，可创建符号链接
ln -sf build/compile_commands.json compile_commands.json