/**
 * @file ph_eos.h
 * @brief Peng-Robinson状态方程函数
 */

#ifndef PH_EOS_H
#define PH_EOS_H

#include "ph_defs.h"

/**
 * @brief 初始化PR状态方程组分参数
 * @param T 温度 [K]
 * @param params PR状态方程参数结构指针
 * @param options 闪蒸计算选项
 * @return 错误代码
 */
PHErrorCode ph_eos_init_params(double T, PREOSParams *params, const FlashOptions *options);

/**
 * @brief 计算混合物的PR状态方程参数
 * @param T 温度 [K]
 * @param composition 组分摩尔分数
 * @param params PR状态方程参数结构指针
 * @param phase 相类型（液相/气相）
 * @return 错误代码
 */
PHErrorCode ph_eos_calc_mixture_params(double T, const double *composition, 
                                      PREOSParams *params, PhaseType phase);

/**
 * @brief 使用PR状态方程计算压缩因子
 * @param T 温度 [K]
 * @param P 压力 [Pa]
 * @param params PR状态方程参数
 * @param phase 相类型（液相/气相）
 * @param Z 存储压缩因子的指针
 * @return 错误代码
 */
PHErrorCode ph_eos_calc_z_factor(double T, double P, const PREOSParams *params,
                                PhaseType phase, double *Z);

/**
 * @brief 使用PR状态方程计算逸度系数
 * @param T 温度 [K]
 * @param P 压力 [Pa]
 * @param composition 组分摩尔分数
 * @param params PR状态方程参数
 * @param phase 相类型（液相/气相）
 * @param phi 存储逸度系数的数组
 * @return 错误代码
 */
PHErrorCode ph_eos_calc_fugacity_coeffs(double T, double P, const double *composition,
                                       const PREOSParams *params, PhaseType phase,
                                       double *phi);

/**
 * @brief 使用PR状态方程计算焓偏差
 * @param T 温度 [K]
 * @param P 压力 [Pa]
 * @param composition 组分摩尔分数
 * @param params PR状态方程参数
 * @param Z 压缩因子
 * @param H_dep 存储焓偏差的指针 [J/mol]
 * @return 错误代码
 */
PHErrorCode ph_eos_calc_enthalpy_departure(double T, double P, const double *composition,
                                          const PREOSParams *params, double Z,
                                          double *H_dep);

/**
 * @brief 获取H2的量子修正临界参数
 * @param T 温度 [K]
 * @param Tc_eff 存储有效临界温度的指针 [K]
 * @param Pc_eff 存储有效临界压力的指针 [Pa]
 * @return 错误代码
 */
PHErrorCode ph_eos_h2_quantum_correction(double T, double *Tc_eff, double *Pc_eff);

/**
 * @brief 求解状态方程的三次方程
 * @param A 三次Z方程中的A系数
 * @param B 三次Z方程中的B系数
 * @param phase 相类型（液相/气相）
 * @param Z 存储压缩因子的指针
 * @return 错误代码
 */
PHErrorCode ph_eos_solve_cubic_eq(double A, double B, PhaseType phase, double *Z);

/**
* @brief 计算参数a的温度导数
* @param T 温度 [K]
* @param composition 组分摩尔分数
* @param params PR状态方程参数
* @return 错误代码
*/
PHErrorCode ph_eos_calc_da_dt(double T, const double *composition, PREOSParams *params);

/**
 * @brief 创建二元相互作用参数(BIP)矩阵
 * @param options 闪蒸计算选项
 * @param kij 存储BIP值的二维数组
 * @return 错误代码
 */
PHErrorCode ph_eos_init_bip_matrix(const FlashOptions *options, double kij[NC][NC]);

#endif /* PH_EOS_H */