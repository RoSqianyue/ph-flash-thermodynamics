/**
 * @file ph_anderson.h
 * @brief Anderson混合加速算法接口
 */

#ifndef PH_ANDERSON_H
#define PH_ANDERSON_H

#include "./ph_defs.h"

/**
 * @brief Anderson加速器状态信息
 */
typedef struct {
    int initialized;    /* 是否已初始化 */
    int iter_count;     /* 迭代计数 */
    int current_size;   /* 当前历史大小 */
    int max_size;       /* 最大历史大小 */
} AndersonInfo;

/**
 * @brief 初始化Anderson加速器
 * @param max_depth 最大混合深度（建议3-5）
 * @return 错误代码
 */
PHErrorCode ph_anderson_init(int max_depth);

/**
 * @brief 重置Anderson加速器
 */
void ph_anderson_reset(void);

/**
 * @brief Anderson混合加速更新
 * @param x_current 当前解向量 [NC]
 * @param f_current 当前残差向量 [NC]  
 * @param x_new 输出的加速解向量 [NC]
 * @return 错误代码
 */
PHErrorCode ph_anderson_update(const double *x_current, const double *f_current, 
                              double *x_new);

/**
 * @brief 获取Anderson加速器状态信息
 * @param info 输出状态信息结构
 */
void ph_anderson_get_info(AndersonInfo *info);

#endif /* PH_ANDERSON_H */