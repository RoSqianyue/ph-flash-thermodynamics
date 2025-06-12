/**
 * @file ph_flash.h
 * @brief P-H闪蒸计算的主要函数
 */

#ifndef PH_FLASH_H
#define PH_FLASH_H

#include "ph_defs.h"
#include "ph_eos.h"
#include "ph_enthalpy.h"
#include "ph_vle.h"

 /**
 * @brief 计算混合物的近似沸点
 * @param z 进料组成
 * @param P 压力 [Pa]
 * @param critical_props 临界性质数组
 * @return 估算的沸点 [K]
 */
/* estimate_boiling_point function is implemented in ph_flash.c */


/**
 * @brief 初始化组分的临界性质
 * @param critical_props 存储临界性质的数组
 * @return 错误代码
 */
PHErrorCode ph_flash_init_critical_props(CriticalProps critical_props[NC]);

/**
 * @brief 初始化默认闪蒸计算选项
 * @param options 选项结构的指针
 * @return 错误代码
 */
PHErrorCode ph_flash_init_options(FlashOptions *options);

/**
 * @brief 验证闪蒸计算的输入参数
 * @param z 进料组成
 * @param P 压力 [Pa]
 * @param H_spec 指定焓值 [J/mol]
 * @return 错误代码
 */
PHErrorCode ph_flash_validate_inputs(const double *z, double P, double H_spec);

/**
 * @brief 估计P-H闪蒸计算的初始温度
 * @param z 进料组成
 * @param P 压力 [Pa]
 * @param H_spec 指定焓值 [J/mol]
 * @param critical_props 临界性质数组
 * @param models 焓模型数组
 * @param T_init 存储初始温度的指针 [K]
 * @return 错误代码
 */
PHErrorCode ph_flash_estimate_init_temp(const double *z, double P, double H_spec,
                                       const CriticalProps critical_props[NC],
                                       const EnthalpyModel models[NC],
                                       double *T_init);

/**
 * @brief 执行主要P-H闪蒸计算
 * @param z 进料组成
 * @param P 压力 [Pa]
 * @param H_spec 指定焓值 [J/mol]
 * @param options 闪蒸计算选项
 * @param state 状态属性结构的指针
 * @return 错误代码
 */
PHErrorCode ph_flash_calculate(const double *z, double P, double H_spec,
                              const FlashOptions *options, StateProperties *state);

/**
 * @brief P-H闪蒸的温度迭代循环
 * @param z 进料组成
 * @param P 压力 [Pa]
 * @param H_spec 指定焓值 [J/mol]
 * @param T_init 初始温度猜测值 [K]
 * @param critical_props 临界性质数组
 * @param models 焓模型数组
 * @param options 闪蒸计算选项
 * @param state 状态属性结构的指针
 * @return 错误代码
 */
PHErrorCode ph_flash_temperature_iteration(const double *z, double P, double H_spec,
                                          double T_init,
                                          const CriticalProps critical_props[NC],
                                          const EnthalpyModel models[NC],
                                          const FlashOptions *options,
                                          StateProperties *state);

/**
 * @brief 应用线搜索改进温度更新
 * @param T_current 当前温度 [K]
 * @param direction 温度更新方向 [K]
 * @param z 进料组成
 * @param P 压力 [Pa]
 * @param H_target 目标焓值 [J/mol]
 * @param critical_props 临界性质数组
 * @param models 焓模型数组
 * @param options 闪蒸计算选项
 * @param T_new 存储新温度的指针 [K]
 * @return 错误代码
 */
PHErrorCode ph_flash_line_search(double T_current, double direction,
                                const double *z, double P, double H_target,
                                const CriticalProps critical_props[NC],
                                const EnthalpyModel models[NC],
                                const FlashOptions *options,
                                double *T_new);

/**
 * @brief 使用牛顿法计算温度更新
 * @param T 当前温度 [K]
 * @param H_error 焓误差 [J/mol]
 * @param dH_dT 焓导数 [J/(mol·K)]
 * @param T_new 存储更新温度的指针 [K]
 * @return 错误代码
 */
PHErrorCode ph_flash_newton_update(double T, double H_error, 
                                  double dH_dT, double *T_new);

/**
 * @brief 检查计算的解是否物理合理
 * @param state 当前状态属性
 * @return 错误代码（如果有效返回PH_OK，否则返回错误代码）
 */
PHErrorCode ph_flash_validate_solution(const StateProperties *state);

/**
 * @brief 格式化结果用于输出
 * @param state 状态属性结构
 * @param output_format 输出格式规范
 * @param output_file 输出文件指针（如为NULL则使用stdout）
 * @return 错误代码
 */
PHErrorCode ph_flash_output_results(const StateProperties *state, 
                                   int output_format, FILE *output_file);

/**
 * @brief 分类操作条件类型
 * @param T 温度 [K]
 * @param P 压力 [Pa]
 * @param z 组成
 * @return 操作条件类型
 */
OperatingCondition ph_flash_classify_operating_condition(double T, double P, const double *z);

/**
 * @brief 根据操作条件获取自适应容差
 * @param condition 操作条件类型
 * @param options 闪蒸选项
 * @return 焓容差 [J/mol]
 */
double ph_flash_get_adaptive_tolerance(OperatingCondition condition, const FlashOptions *options);

/**
 * @brief 根据操作条件更新容差设置
 * @param T 温度 [K]
 * @param P 压力 [Pa]
 * @param z 组成
 * @param options 闪蒸选项（会被修改）
 * @return 错误代码
 */
PHErrorCode ph_flash_update_tolerance_based_on_condition(double T, double P, const double *z, FlashOptions *options);

#endif /* PH_FLASH_H */