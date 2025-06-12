/**
 * @file ph_vle.h
 * @brief 气液平衡计算相关函数
 */

#ifndef PH_VLE_H
#define PH_VLE_H

#include "ph_defs.h"
#include "ph_eos.h"

#define MAX_TPD_TRIALS 7

 /**
 * @brief 在给定温度、压力下求解气液平衡
 * @param z 进料组成
 * @param T 温度 [K]
 * @param P 压力 [Pa]
 * @param options 闪蒸计算选项
 * @param state 存储状态属性的结构指针
 * @return 错误代码
 */
PHErrorCode ph_vle_solve(const double *z, double T, double P,
	const FlashOptions *options, StateProperties *state);

/**
 * @brief 使用Wilson关联式初始化K值
 * @param T 温度 [K]
 * @param P 压力 [Pa]
 * @param critical_props 组分临界性质
 * @param K 存储K值的数组
 * @return 错误代码
 */
PHErrorCode ph_vle_wilson_k_values(double T, double P, 
                                  const CriticalProps critical_props[NC],
                                  double K[NC]);

/**
 * @brief 求解Rachford-Rice方程，计算气相摩尔分数
 * @param z 进料组成
 * @param K K值
 * @param beta 存储气相摩尔分数的指针
 * @return 错误代码
 */
PHErrorCode ph_vle_solve_rachford_rice(const double *z, const double *K, double *beta);

/**
 * @brief 根据beta和K值计算液相和气相组成
 * @param z 进料组成
 * @param K K值
 * @param beta 气相摩尔分数
 * @param x 存储液相组成的数组
 * @param y 存储气相组成的数组
 * @return 错误代码
 */
PHErrorCode ph_vle_calc_compositions(const double *z, const double *K, 
                                    double beta, double *x, double *y);

/**
 * @brief 归一化组成数组，使其和为1.0
 * @param composition 组成值数组
 * @return 错误代码
 */
PHErrorCode ph_vle_normalize_composition(double *composition);

/**
 * @brief 进行切线平面距离(TPD)分析以检验相稳定性
 * @param T 温度 [K]
 * @param P 压力 [Pa]
 * @param z 进料组成
 * @param params PR状态方程参数
 * @param options 闪蒸计算选项
 * @param is_unstable 存储稳定性结果的指针（1表示不稳定，0表示稳定）
 * @param trial_comp 如不稳定，存储试验组成的数组
 * @return 错误代码
 */
PHErrorCode ph_vle_tpd_analysis(double T, double P, const double *z, 
                               const PREOSParams *params, const FlashOptions *options,
                               int *is_unstable, double *trial_comp);

/**
 * @brief 在给定T,P下进行等温闪蒸计算
 * @param T 温度 [K]
 * @param P 压力 [Pa]
 * @param z 进料组成
 * @param params PR状态方程参数
 * @param options 闪蒸计算选项
 * @param critical_props 临界性质数组
 * @param state 存储状态属性的结构指针
 * @return 错误代码
 */
PHErrorCode ph_vle_isothermal_flash(double T, double P, const double *z,
                                   PREOSParams *params, const FlashOptions *options,
                                   const CriticalProps critical_props[NC],
                                   StateProperties *state);

/**
 * @brief 检查组成是否为单相
 * @param T 温度 [K]
 * @param P 压力 [Pa]
 * @param z 组成
 * @param K K值
 * @param is_vapor 存储结果的指针（1表示气相，0表示液相）
 * @return 错误代码
 */
PHErrorCode ph_vle_check_single_phase(double T, double P, const double *z, 
                                     const double *K, int *is_vapor);

/**
 * @brief 根据TPD分析结果估计更好的K值
 * @param z 进料组成
 * @param trial_comp TPD分析的试验组成
 * @param K 存储改进K值的数组
 * @return 错误代码
 */
PHErrorCode ph_vle_estimate_k_from_tpd(const double *z, const double *trial_comp, double *K);

/**
 * @brief 对K值更新应用Anderson加速
 * @param k_history K值历史数组
 * @param residual_history 残差历史数组
 * @param k_size K值数组的大小
 * @param m 使用的前几次迭代数
 * @param iter 当前迭代次数
 * @param K_new 存储加速后K值的数组
 * @return 错误代码
 */
PHErrorCode ph_vle_anderson_acceleration(double **k_history, double **residual_history,
                                        int k_size, int m, int iter, double *K_new);

#endif /* PH_VLE_H */