/**
 * @file ph_defs.h
 * @brief PR方程P-H闪蒸计算的通用定义、常量和数据结构
 */

#ifndef PH_DEFS_H
#define PH_DEFS_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ph_error.h"

/**
 * @brief 物理常数
 */
#define R_GAS_CONSTANT 8.314462618    /* 通用气体常数 [J/(mol·K)] */
#define P_STANDARD 101325.0           /* 标准压力 [Pa] */
#define T_STANDARD 273.15             /* 标准温度 [K] */
#define T_REFERENCE 298.15            /* 参考温度 [K] */

/**
 * @brief 数值设置
 */
#define MAX_ITER_OUTER 50             /* 温度循环最大迭代次数 */
#define MAX_ITER_VLE 100              /* VLE计算最大迭代次数 */
#define MAX_ITER_RR 30                /* Rachford-Rice最大迭代次数 */
#define MAX_ITER_TPD 20               /* TPD稳定性分析最大迭代次数 */
#define MAX_ITER_ANDERSON 10          /* Anderson加速最大迭代次数 */
#define MAX_TPD_TRIALS 7              /* TPD分析最大试探点数 */
#define MAX_ANDERSON_HISTORY 5        /* Anderson加速历史存储数量 */

/**
 * @brief 容差设置
 */
#define TOL_ENTHALPY 5.0          /* 焓平衡容差 [J/mol] */
#define TOL_K_VALUE 1.0e-6            /* K值相对容差 */
#define TOL_COMP_SUM 1.0e-8          /* 组成和容差 */
#define TOL_TEMP 1.0e-2               /* 温度绝对容差 [K] */
#define TOL_RR 1.0e-10               /* Rachford-Rice方程容差 */
#define TOL_TPD 1.0e-8                /* TPD稳定性判据容差 */
#define TOL_FUGACITY 1.0e-7          /* 逸度平衡容差 */

/**
 * @brief 自适应容差设置
 */
#define TOL_ENTHALPY_STANDARD 5.0     /* 标准条件焓容差 [J/mol] */
#define TOL_ENTHALPY_DIFFICULT 50.0   /* 困难条件焓容差 [J/mol] */
#define TOL_ENTHALPY_EXTREME 150.0    /* 极端条件焓容差 [J/mol] */

/**
 * @brief 操作条件分类枚举
 */
typedef enum {
    CONDITION_STANDARD = 0,           /* 标准条件 (1-10 atm, 250-400K) */
    CONDITION_DIFFICULT = 1,          /* 困难条件 (高压或低温) */
    CONDITION_EXTREME = 2             /* 极端条件 (超高压或超低温) */
} OperatingCondition;

/**
 * @brief BIP数据源常量
 */
#define BIP_RECOMMENDED     0         /* 工程推荐值(DIPPR验证) */
#define BIP_UNISIM          1         /* UniSim数据 */
#define BIP_CUSTOM          2         /* 自定义值 */

/**
 * @brief 组分索引
 */
#define NC 5                          /* 组分数量 */
#define IDX_H2 0                      /* H2索引 */
#define IDX_N2 1                      /* N2索引 */
#define IDX_O2 2                      /* O2索引 */
#define IDX_NH3 3                     /* NH3索引 */
#define IDX_H2O 4                     /* H2O索引 */

/**
 * @brief 相类型枚举
 */
typedef enum {
    PHASE_LIQUID = 0,                 /* 液相 */
    PHASE_VAPOR = 1,                  /* 气相 */
    PHASE_UNKNOWN = 2                 /* 未知相 */
} PhaseType;

/* Error handling is now defined in ph_error.h */

/**
 * @brief 组分临界性质
 */
typedef struct {
    double Tc;          /* 临界温度 [K] */
    double Pc;          /* 临界压力 [Pa] */
    double omega;       /* 偏心因子 */
    char name[10];      /* 组分名称 */
} CriticalProps;

/**
 * @brief 组分焓模型
 */
typedef struct {
    double shomate_coeffs[7];  /* Shomate方程系数 [A,B,C,D,E,F,H] */
    double nasa7_coeffs[7];    /* NASA-7系数 [a1-a7] */
    double T_min;              /* 最小有效温度 [K] */
    double T_max;              /* 最大有效温度 [K] */
} EnthalpyModel;

/**
 * @brief 状态性质
 */
typedef struct {
    double T;           /* 温度 [K] */
    double P;           /* 压力 [Pa] */
    double beta;        /* 气相摩尔分数 */
    double z[NC];       /* 总进料组成 */
    double x[NC];       /* 液相组成 */
    double y[NC];       /* 气相组成 */
    double K[NC];       /* K值 (y/x) */
    double H_spec;      /* 指定焓值 [J/mol] */
    double H_calc;      /* 计算焓值 [J/mol] */
    double H_L;         /* 液相焓值 [J/mol] */
    double H_V;         /* 气相焓值 [J/mol] */
    double Z_L;         /* 液相压缩因子 */
    double Z_V;         /* 气相压缩因子 */
    double phi_L[NC];   /* 液相逸度系数 */
    double phi_V[NC];   /* 气相逸度系数 */
    int iterations;     /* 所需迭代次数 */
    PHErrorCode status; /* 状态代码 */
} StateProperties;

/**
 * @brief PR状态方程参数
 */
typedef struct {
    double a_pure[NC];         /* 纯组分'a'参数 */
    double b_pure[NC];         /* 纯组分'b'参数 */
    double kij[NC][NC];        /* 二元相互作用参数 */
    double a_mix;              /* 混合物'a'参数 */
    double b_mix;              /* 混合物'b'参数 */
    double da_dT;              /* a_mix的温度导数 */
    double Tc_used[NC];        /* 实际使用的临界温度（含量子修正） [K] */
    double Pc_used[NC];        /* 实际使用的临界压力（含量子修正） [Pa] */
} PREOSParams;

/**
 * @brief 闪蒸计算参数
 */
typedef struct {
    double kij[NC][NC];        /* 使用的BIP矩阵 */
    int use_quantum_h2;        /* 是否对H2使用量子修正 */
    int bip_source;            /* BIP来源(0=推荐, 1=unisim, 2=自定义) */
    int eos_type;              /* 0=PR, 1=PR-CPA */
    int use_anderson;          /* 是否使用Anderson加速 */
    int use_line_search;       /* 是否使用线搜索保护机制 */
    int verbose;               /* 详细输出标志 */
    double damping;            /* 初始阻尼因子 */
    double tol_factor;         /* 困难案例的容差乘数 */
    int use_adaptive_tolerance; /* 是否使用自适应容差 */
    OperatingCondition condition_type; /* 操作条件类型 */
    double custom_enthalpy_tol; /* 自定义焓容差 [J/mol] */
    
    /* 数值稳定性增强 - 新增字段 */
    int use_adaptive_derivative; /* 是否使用自适应焓导数计算 */
    double derivative_perturbation; /* 焓导数温度扰动 [K] (0=自动) */
    int use_analytical_backup;  /* 数值失败时是否使用解析备用 */
    double max_reasonable_dhdt; /* 合理dH/dT上限 [J/(mol·K)] */
} FlashOptions;

/* ph_error function is now declared in ph_error.h */

#endif /* PH_DEFS_H */