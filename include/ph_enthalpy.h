/**
 * @file ph_enthalpy.h
 * @brief 焓计算相关函数
 */

#ifndef PH_ENTHALPY_H
#define PH_ENTHALPY_H

#include "ph_defs.h"
#include "ph_eos.h"

/**
 * @brief 初始化所有组分的焓模型
 * @param models 每个组分的焓模型数组
 * @return 错误代码
 */
PHErrorCode ph_enthalpy_init_models(EnthalpyModel models[NC]);

/**
 * @brief 使用NASA-7多项式计算组分的理想气体焓
 * @param T 温度 [K]
 * @param component 组分索引
 * @param model 组分的焓模型
 * @param H_ig 存储理想气体焓的指针 [J/mol]
 * @return 错误代码
 */
PHErrorCode ph_enthalpy_nasa7(double T, int component, const EnthalpyModel *model, double *H_ig);

/**
 * @brief 使用Shomate方程计算组分的理想气体焓
 * @param T 温度 [K]
 * @param component 组分索引
 * @param model 组分的焓模型
 * @param H_ig 存储理想气体焓的指针 [J/mol]
 * @return 错误代码
 */
PHErrorCode ph_enthalpy_shomate(double T, int component, const EnthalpyModel *model, double *H_ig);

/**
 * @brief 计算组分的理想气体焓
 * @param T 温度 [K]
 * @param component 组分索引
 * @param model 组分的焓模型
 * @param H_ig 存储理想气体焓的指针 [J/mol]
 * @return 错误代码
 */
PHErrorCode ph_enthalpy_ideal_gas(double T, int component, const EnthalpyModel *model, double *H_ig);

/**
 * @brief 计算混合物的理想气体焓
 * @param T 温度 [K]
 * @param composition 组分摩尔分数
 * @param models 每个组分的焓模型数组
 * @param H_ig_mix 存储混合物理想气体焓的指针 [J/mol]
 * @return 错误代码
 */
PHErrorCode ph_enthalpy_ideal_gas_mix(double T, const double *composition, 
                                     const EnthalpyModel models[NC], double *H_ig_mix);

/**
 * @brief 计算相的总焓
 * @param T 温度 [K]
 * @param P 压力 [Pa]
 * @param composition 组分摩尔分数
 * @param models 每个组分的焓模型数组
 * @param params PR状态方程参数
 * @param phase 相类型（液相/气相）
 * @param Z 压缩因子
 * @param H_phase 存储相焓的指针 [J/mol]
 * @return 错误代码
 */
PHErrorCode ph_enthalpy_phase_total(double T, double P, const double *composition,
                                   const EnthalpyModel models[NC], const PREOSParams *params,
                                   PhaseType phase, double Z, double *H_phase);

/**
 * @brief 计算混合物的总焓
 * @param state 当前状态属性
 * @param models 每个组分的焓模型数组
 * @param params PR状态方程参数
 * @return 错误代码
 */
PHErrorCode ph_enthalpy_mixture_total(StateProperties *state, 
                                     const EnthalpyModel models[NC],
                                     const PREOSParams *params);

/**
 * @brief 计算焓对温度的导数
 * @param T 温度 [K]
 * @param P 压力 [Pa]
 * @param beta 气相摩尔分数
 * @param x 液相组成
 * @param y 气相组成
 * @param models 每个组分的焓模型数组
 * @param params PR状态方程参数
 * @param options 闪蒸选项
 * @param dH_dT 存储焓导数的指针 [J/(mol·K)]
 * @return 错误代码
 */
PHErrorCode ph_enthalpy_derivative(double T, double P, double beta,
                                  const double *x, const double *y,
                                  const EnthalpyModel models[NC],
                                  const PREOSParams *params,
                                  const FlashOptions *options,
                                  double *dH_dT);

/**
 * @brief 确保温度边界处的多项式连续性
 * @param models 每个组分的焓模型数组
 * @return 错误代码
 */
PHErrorCode ph_enthalpy_ensure_continuity(EnthalpyModel models[NC]);

#endif /* PH_ENTHALPY_H */