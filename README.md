# P-H Flash Thermodynamics Library

一个基于C语言的综合热力学库，用于P-H（压力-焓）闪蒸计算，采用Peng-Robinson状态方程。

## 概述

该库为多组分系统提供精确的汽液平衡计算，特别支持化工过程中常见的含氢混合物系统。

## 特性

- **8个主要模块：**
  - `ph_defs`: 核心数据结构和常量
  - `ph_error`: 综合错误处理
  - `ph_eos`: Peng-Robinson状态方程
  - `ph_vle`: 汽液平衡计算
  - `ph_enthalpy`: 焓值计算（多种模型）
  - `ph_anderson`: Anderson加速收敛
  - `ph_utils`: 实用工具函数
  - `ph_flash`: 主要闪蒸计算例程

- **支持组分：** H₂, N₂, O₂, NH₃, H₂O
- **高级功能：**
  - 氢气的量子修正
  - Anderson加速改善收敛性
  - 不同操作条件下的自适应容差
  - 数值稳定性增强
  - 多种BIP（二元相互作用参数）来源

## 项目结构

```
ph-flash-thermodynamics/
├── src/                 # 源文件
│   ├── ph_anderson.c   # Anderson加速
│   ├── ph_eos.c        # 状态方程
│   ├── ph_enthalpy.c   # 焓值计算
│   ├── ph_error.c      # 错误处理
│   ├── ph_flash.c      # 主要闪蒸计算
│   ├── ph_stubs.c      # 函数存根
│   ├── ph_utils.c      # 实用工具
│   └── ph_vle.c        # VLE计算
├── include/            # 头文件
│   ├── ph_anderson.h
│   ├── ph_defs.h
│   ├── ph_enthalpy.h
│   ├── ph_eos.h
│   ├── ph_error.h
│   ├── ph_flash.h
│   ├── ph_utils.h
│   └── ph_vle.h
└── Makefile           # 构建配置
```

## 编译

### 前提条件
- GCC编译器
- Make工具
- 标准数学库

### 构建说明

```bash
# 编译库
make

# 清理构建文件
make clean

# 调试版本构建
make debug
```

### 手动编译

```bash
# 编译所有源文件
gcc -Wall -Wextra -O2 -Iinclude -c src/*.c

# 创建静态库
ar rcs libph_flash.a *.o

# 链接到您的应用程序
gcc -o your_app your_app.c -L. -lph_flash -lm
```

## 使用示例

```c
#include "ph_flash.h"

int main() {
    StateProperties state;
    FlashOptions options;
    
    // 初始化选项
    ph_flash_init_options(&options);
    
    // 设置条件
    state.P = 2000000.0;  // 20 bar
    state.H_spec = -45000.0;  // -45 kJ/mol
    
    // 设置组成（H2/N2混合物）
    state.z[IDX_H2] = 0.7;
    state.z[IDX_N2] = 0.3;
    
    // 执行闪蒸计算
    PHErrorCode result = ph_flash_PH(&state, &options);
    
    if (result == PH_OK) {
        printf("温度: %.2f K\\n", state.T);
        printf("气相分率: %.4f\\n", state.beta);
    }
    
    return 0;
}
```

## 技术细节

### 状态方程
- 带体积平移的Peng-Robinson (PR)
- 低温下氢气的量子修正
- 多种二元相互作用参数集

### 数值方法
- 外层温度循环的Anderson加速
- 基于操作条件的自适应容差
- 稳定性线搜索保护
- TPD（切平面距离）稳定性分析

### 操作条件
- **标准：** 1-10 atm, 250-400K
- **困难：** 高压或低温
- **极端：** 超高压或超低温

## GCC编译命令

适用于MSYS2/Mingw64环境：

```bash
# 基本编译
gcc -Wall -Wextra -O2 -Iinclude -c src/*.c
ar rcs libph_flash.a *.o

# 使用库的示例
gcc -o test_app test_app.c -Iinclude -L. -lph_flash -lm

# 完整的调试版本
gcc -Wall -Wextra -g -DDEBUG -Iinclude -c src/*.c
ar rcs libph_flash_debug.a *.o
```

## 许可证

本项目按原样提供，用于研究和教育目的。

## 贡献

欢迎贡献！确保代码遵循现有风格并包含适当的错误处理。