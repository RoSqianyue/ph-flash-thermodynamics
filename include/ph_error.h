/**
 * @file ph_error.h
 * @brief P-H Flash Calculator Enhanced Error Handling System
 * @description Comprehensive error management with diagnostics, recovery, and logging
 */

#ifndef PH_ERROR_H
#define PH_ERROR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>

/**
 * @brief 扩展的错误代码体系 - 分类化的错误处理
 */
typedef enum {
    /* 成功状态 */
    PH_OK = 0,                              /* 正常 */
    
    /* 输入验证错误 (100-199) */
    PH_ERROR_INPUT_NULL = -101,             /* 空指针输入 */
    PH_ERROR_INPUT_INVALID_COMPOSITION = -102, /* 无效组成 */
    PH_ERROR_INPUT_INVALID_PRESSURE = -103, /* 无效压力 */
    PH_ERROR_INPUT_INVALID_TEMPERATURE = -104, /* 无效温度 */
    PH_ERROR_INPUT_INVALID_ENTHALPY = -105, /* 无效焓值 */
    PH_ERROR_INPUT_OUT_OF_RANGE = -106,     /* 参数超出范围 */
    PH_ERROR_INPUT_INCONSISTENT = -107,     /* 输入参数不一致 */
    
    /* 数值计算错误 (200-299) */
    PH_ERROR_NUMERICAL_OVERFLOW = -201,     /* 数值溢出 */
    PH_ERROR_NUMERICAL_UNDERFLOW = -202,    /* 数值下溢 */
    PH_ERROR_NUMERICAL_DIVISION_BY_ZERO = -203, /* 除零错误 */
    PH_ERROR_NUMERICAL_INVALID_RESULT = -204, /* 无效计算结果 */
    PH_ERROR_NUMERICAL_PRECISION_LOSS = -205, /* 精度损失 */
    PH_ERROR_NUMERICAL_MATRIX_SINGULAR = -206, /* 矩阵奇异 */
    
    /* 收敛性错误 (300-399) */
    PH_ERROR_CONVERGENCE_MAX_ITERATIONS = -301, /* 超过最大迭代次数 */
    PH_ERROR_CONVERGENCE_SLOW = -302,       /* 收敛过慢 */
    PH_ERROR_CONVERGENCE_OSCILLATION = -303, /* 解振荡 */
    PH_ERROR_CONVERGENCE_DIVERGENCE = -304, /* 解发散 */
    PH_ERROR_CONVERGENCE_STAGNATION = -305, /* 解停滞 */
    PH_ERROR_CONVERGENCE_TOLERANCE = -306,  /* 无法达到容差要求 */
    
    /* 物理有效性错误 (400-499) */
    PH_ERROR_PHYSICAL_NEGATIVE_COMPOSITION = -401, /* 负组成 */
    PH_ERROR_PHYSICAL_INVALID_PHASE = -402,  /* 无效相状态 */
    PH_ERROR_PHYSICAL_UNSTABLE_SOLUTION = -403, /* 不稳定解 */
    PH_ERROR_PHYSICAL_IMPOSSIBLE_STATE = -404, /* 不可能的物理状态 */
    PH_ERROR_PHYSICAL_CRITICAL_REGION = -405, /* 临界区域问题 */
    PH_ERROR_PHYSICAL_FUGACITY_BALANCE = -406, /* 逸度平衡失败 */
    
    /* 内存管理错误 (500-599) */
    PH_ERROR_MEMORY_ALLOCATION = -501,      /* 内存分配失败 */
    PH_ERROR_MEMORY_DEALLOCATION = -502,    /* 内存释放失败 */
    PH_ERROR_MEMORY_CORRUPTION = -503,      /* 内存损坏 */
    PH_ERROR_MEMORY_LEAK = -504,           /* 内存泄露 */
    PH_ERROR_MEMORY_ACCESS_VIOLATION = -505, /* 内存访问违规 */
    
    /* 算法特定错误 (600-699) */
    PH_ERROR_ALGORITHM_TPD_FAILURE = -601,  /* TPD稳定性分析失败 */
    PH_ERROR_ALGORITHM_RACHFORD_RICE = -602, /* Rachford-Rice求解失败 */
    PH_ERROR_ALGORITHM_ANDERSON_FAILURE = -603, /* Anderson加速失败 */
    PH_ERROR_ALGORITHM_LINE_SEARCH_FAILURE = -604, /* 线搜索失败 */
    PH_ERROR_ALGORITHM_NEWTON_FAILURE = -605, /* Newton方法失败 */
    PH_ERROR_ALGORITHM_EOS_FAILURE = -606,  /* 状态方程求解失败 */
    
    /* 系统和配置错误 (700-799) */
    PH_ERROR_CONFIG_INVALID = -701,         /* 无效配置 */
    PH_ERROR_CONFIG_MISSING = -702,         /* 缺少配置 */
    PH_ERROR_FILE_IO = -703,               /* 文件读写错误 */
    PH_ERROR_SYSTEM_RESOURCE = -704,       /* 系统资源不足 */
    PH_ERROR_NOT_IMPLEMENTED = -705,       /* 功能未实现 */
    PH_ERROR_VERSION_INCOMPATIBLE = -706,  /* 版本不兼容 */
    
    /* 通用错误 (900-999) */
    PH_ERROR_UNKNOWN = -901,               /* 未知错误 */
    PH_ERROR_INTERNAL = -902,              /* 内部错误 */
    PH_ERROR_FATAL = -903,                 /* 致命错误 */
    
    /* 兼容性别名 - 保持向后兼容 */
    PH_ERROR_CONVERGENCE = PH_ERROR_CONVERGENCE_MAX_ITERATIONS,
    PH_ERROR_INPUT_VALIDATION = PH_ERROR_INPUT_NULL,
    PH_ERROR_NUMERICAL = PH_ERROR_NUMERICAL_INVALID_RESULT,
    PH_ERROR_UNSTABLE = PH_ERROR_PHYSICAL_UNSTABLE_SOLUTION,
    PH_ERROR_SOLUTION_VALIDATION = PH_ERROR_PHYSICAL_INVALID_PHASE,
    PH_ERROR_CALCULATION = PH_ERROR_NUMERICAL_INVALID_RESULT
} PHErrorCode;

/**
 * @brief 错误严重级别
 */
typedef enum {
    PH_SEVERITY_INFO = 0,       /* 信息级别 */
    PH_SEVERITY_WARNING = 1,    /* 警告级别 */
    PH_SEVERITY_ERROR = 2,      /* 错误级别 */
    PH_SEVERITY_CRITICAL = 3,   /* 严重错误 */
    PH_SEVERITY_FATAL = 4       /* 致命错误 */
} PHErrorSeverity;

/**
 * @brief 错误上下文信息
 */
typedef struct {
    const char* function_name;   /* 函数名 */
    const char* file_name;       /* 文件名 */
    int line_number;            /* 行号 */
    double timestamp;           /* 时间戳 */
    int iteration_count;        /* 迭代次数（如适用） */
    double error_magnitude;     /* 错误量级 */
    char additional_info[256];  /* 附加信息 */
} PHErrorContext;

/**
 * @brief 错误诊断信息（前向声明）
 */
typedef struct PHErrorInfo PHErrorInfo;

/**
 * @brief 错误诊断信息
 */
struct PHErrorInfo {
    PHErrorCode error_code;         /* 错误代码 */
    PHErrorSeverity severity;       /* 严重级别 */
    PHErrorContext context;         /* 错误上下文 */
    char message[512];             /* 错误消息 */
    char diagnostic_info[1024];    /* 诊断信息 */
    char suggested_action[512];    /* 建议操作 */
    PHErrorInfo* previous;  /* 错误链 */
};

/**
 * @brief 错误恢复策略
 */
typedef enum {
    PH_RECOVERY_NONE = 0,          /* 无恢复策略 */
    PH_RECOVERY_RETRY = 1,         /* 重试 */
    PH_RECOVERY_FALLBACK = 2,      /* 回退到备用方法 */
    PH_RECOVERY_ADJUST_PARAMETERS = 3, /* 调整参数 */
    PH_RECOVERY_SIMPLIFY_PROBLEM = 4,  /* 简化问题 */
    PH_RECOVERY_ABORT = 5          /* 终止操作 */
} PHRecoveryStrategy;

/**
 * @brief 错误统计信息
 */
typedef struct {
    int total_errors;              /* 总错误数 */
    int errors_by_category[10];    /* 按类别统计的错误数 */
    int recoverable_errors;        /* 可恢复错误数 */
    int fatal_errors;             /* 致命错误数 */
    double first_error_time;      /* 首次错误时间 */
    double last_error_time;       /* 最后错误时间 */
} PHErrorStats;

/* 全局错误管理器 */
extern PHErrorInfo* g_current_error;
extern PHErrorStats g_error_stats;
extern int g_error_logging_enabled;
extern FILE* g_error_log_file;

/**
 * @brief 宏定义：错误检查和处理
 */
#define PH_CHECK_ERROR(condition, error_code, message) \
    do { \
        if (!(condition)) { \
            return ph_error_detailed(error_code, __FUNCTION__, __FILE__, __LINE__, message); \
        } \
    } while(0)

#define PH_CHECK_NULL(ptr, message) \
    PH_CHECK_ERROR((ptr) != NULL, PH_ERROR_INPUT_NULL, message)

#define PH_CHECK_RANGE(value, min, max, message) \
    PH_CHECK_ERROR((value) >= (min) && (value) <= (max), PH_ERROR_INPUT_OUT_OF_RANGE, message)

#define PH_CHECK_POSITIVE(value, message) \
    PH_CHECK_ERROR((value) > 0.0, PH_ERROR_INPUT_INVALID_PRESSURE, message)

#define PH_TRY(expression) \
    do { \
        PHErrorCode __error_code = (expression); \
        if (__error_code != PH_OK) { \
            return __error_code; \
        } \
    } while(0)

/**
 * @brief 核心错误处理函数
 */
PHErrorCode ph_error_detailed(PHErrorCode code, const char* function, 
                             const char* file, int line, const char* message);
PHErrorCode ph_error_with_context(PHErrorCode code, const PHErrorContext* context, 
                                 const char* format, ...);
PHErrorCode ph_error_chain(PHErrorCode code, const char* message);

/**
 * @brief 错误信息和诊断
 */
const char* ph_error_code_to_string(PHErrorCode code);
PHErrorSeverity ph_error_get_severity(PHErrorCode code);
const char* ph_error_get_category(PHErrorCode code);
void ph_error_get_diagnostic_info(PHErrorCode code, char* buffer, size_t buffer_size);
void ph_error_get_suggested_action(PHErrorCode code, char* buffer, size_t buffer_size);

/**
 * @brief 错误恢复机制
 */
PHRecoveryStrategy ph_error_get_recovery_strategy(PHErrorCode code);
PHErrorCode ph_error_attempt_recovery(PHErrorCode code, void* context);
int ph_error_is_recoverable(PHErrorCode code);
int ph_error_is_fatal(PHErrorCode code);

/**
 * @brief 错误日志和追踪
 */
void ph_error_init_logging(const char* log_file_path);
void ph_error_cleanup_logging(void);
void ph_error_log(PHErrorCode code, const char* message);
void ph_error_dump_stats(FILE* output);
void ph_error_reset_stats(void);

/**
 * @brief 错误上下文管理
 */
void ph_error_push_context(const char* function, const char* operation);
void ph_error_pop_context(void);
void ph_error_set_iteration_info(int iteration, double error_magnitude);

/**
 * @brief 向后兼容的简化接口
 */
PHErrorCode ph_error(PHErrorCode code, const char* message);

#endif /* PH_ERROR_H */