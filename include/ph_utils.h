/**
 * @file ph_utils.h
 * @brief P-H闪蒸计算的工具函数
 */

#ifndef PH_UTILS_H
#define PH_UTILS_H

#include "ph_defs.h"

/**
 * @brief 安全分配内存并进行错误处理
 * @param size 要分配的字节数
 * @return 分配的内存指针，如果失败则返回NULL
 */
void* ph_malloc(size_t size);

/**
 * @brief 释放内存并将指针设为NULL
 * @param ptr 要释放的内存指针的指针
 */
void ph_free(void** ptr);

/**
 * @brief 检查浮点数值是否接近零
 * @param value 待检查的值
 * @param tolerance 比较容差
 * @return 如果值接近零返回1，否则返回0
 */
int ph_is_zero(double value, double tolerance);

/**
 * @brief 计算双精度数组的和
 * @param array 双精度数组
 * @param size 数组大小
 * @return 数组元素的和
 */
double ph_sum(const double* array, int size);

/**
 * @brief 将值限制在最小值和最大值之间
 * @param value 要限制的值
 * @param min 允许的最小值
 * @param max 允许的最大值
 * @return 限制后的值
 */
double ph_clip(double value, double min, double max);

/**
 * @brief 复制双精度数组
 * @param dest 目标数组
 * @param src 源数组
 * @param size 数组大小
 */
void ph_copy_array(double* dest, const double* src, int size);

/**
 * @brief 计算数组中的最大绝对值
 * @param array 值数组
 * @param size 数组大小
 * @return 最大绝对值
 */
double ph_max_abs(const double* array, int size);

/**
 * @brief 计算两个值之间的相对误差
 * @param value 当前值
 * @param reference 参考值
 * @param min_denominator 防止除零的最小分母
 * @return 相对误差
 */
double ph_relative_error(double value, double reference, double min_denominator);

/**
 * @brief 计算两个数组之间的最大相对误差
 * @param array1 第一个数组
 * @param array2 第二个数组
 * @param size 数组大小
 * @param min_denominator 防止除零的最小分母
 * @return 最大相对误差
 */
double ph_max_relative_error(const double* array1, const double* array2, 
                            int size, double min_denominator);

/**
 * @brief 计算值的符号
 * @param value 要确定符号的值
 * @return 正数返回1，负数返回-1，零返回0
 */
int ph_sign(double value);

/**
 * @brief 基于迭代历史计算自适应阻尼因子
 * @param iteration 当前迭代次数
 * @param error_history 之前迭代的误差值数组
 * @param history_size 误差历史数组的大小
 * @return 0.1到0.8之间的阻尼因子
 */
double ph_adaptive_damping(int iteration, const double* error_history, int history_size);

/**
 * @brief 与Anderson加速协调的智能阻尼控制
 * @param iteration 当前迭代次数
 * @param error_history 误差历史数组
 * @param history_size 历史数组大小
 * @param anderson_failed Anderson加速是否失败
 * @param consecutive_anderson_failures 连续Anderson失败次数
 * @return 协调后的阻尼因子
 */
double ph_coordinated_damping(int iteration, const double* error_history, int history_size,
                             int anderson_failed, int consecutive_anderson_failures);

/**
 * @brief 在温度单位之间转换
 * @param value 要转换的温度值
 * @param from_unit 源单位('K', 'C'或'F')
 * @param to_unit 目标单位('K', 'C'或'F')
 * @return 转换后的温度值
 */
double ph_convert_temperature(double value, char from_unit, char to_unit);

/**
 * @brief 在不同压力单位之间转换
 * @param value 要转换的压力值
 * @param from_unit 源单位('Pa', 'bar', 'kPa', 'MPa', 'atm')
 * @param to_unit 目标单位('Pa', 'bar', 'kPa', 'MPa', 'atm')
 * @return 转换后的压力值
 */
double ph_convert_pressure(double value, const char* from_unit, const char* to_unit);

/**
 * @brief 在不同焓单位之间转换
 * @param value 焓值
 * @param from_unit 源单位('J/mol', 'kJ/mol', 'J/kg', 'kJ/kg')
 * @param to_unit 目标单位('J/mol', 'kJ/mol', 'J/kg', 'kJ/kg')
 * @param mw 分子量[g/mol]（质量基准单位需要）
 * @return 转换后的焓值
 */
double ph_convert_enthalpy(double value, const char* from_unit, 
                          const char* to_unit, double mw);

#endif /* PH_UTILS_H */