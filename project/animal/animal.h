#pragma once

/**
 * @brief  动物属性
 * 
 */
typedef struct {
    char name[10];   ///< 名字
    char sound[10];  ///< 声音
} Animal_Attr;

/**
 * @brief 动物类接口
 * 
 * 提供面向对象风格的函数指针接口。
 */
typedef struct {
    /**
     * @brief 初始化函数
     * 
     * @param t    类对象指针
     * @param attr 动物属性
     * @return int 0 表示成功，其他为错误码
     */
    int (*init)(void* t, Animal_Attr attr);

    /**
     * @brief 获取动物名称
     * 
     * @param t    类对象指针
     * @param name 用于输出名称的缓冲区
     * @return int 0 表示成功，其他为错误码
     */
    int (*get_name)(void* t, char* name);

    /**
     * @brief 发出动物叫声
     * 
     * @param t 类对象指针
     * @return int 0 表示成功，其他为错误码
     */
    int (*speak)(void* t);
} ANIMAL_CLASS_IMPLEMENTS;

/**
 * @brief 动物类（基类）
 * 
 * 包含通用接口和属性。
 */
typedef struct {
    ANIMAL_CLASS_IMPLEMENTS api;  ///< 虚函数接口
    Animal_Attr attr;             ///< 动物属性
} ANIMAL_CLASS;

/**
 * @brief 狗的附加属性
 */
typedef struct {
    char name[10]; ///< 狗的名字
} Dog_Attr;

/**
 * @brief 狗类（继承自动物类）
 * 
 * 使用 Dog_Attr 扩展动物属性。
 */
typedef struct {
    ANIMAL_CLASS_IMPLEMENTS api; /*!< protected 继承 ANIMAL_CLASS 接口 */
    Dog_Attr attr;               ///< 狗的属性
} DOG_CLASS;

/**
 * @brief 猫的附加属性
 */
typedef struct {
    char name[10]; ///< 猫的名字
} Cat_Attr;

/**
 * @brief 猫类（继承自动物类）
 * 
 * 使用 Cat_Attr 扩展动物属性。
 */
typedef struct {
    ANIMAL_CLASS_IMPLEMENTS api; ///< 虚函数接口继承
    Cat_Attr attr;               ///< 猫的属性
} CAT_CLASS;

/**
 * @brief 构造 ANIMAL_CLASS 实例
 * 
 * @return ANIMAL_CLASS* 新分配并初始化的动物类指针
 */
ANIMAL_CLASS* ANIMAL_CLASS_CTOR(void);

/**
 * @brief 析构 ANIMAL_CLASS 实例
 * 
 * @param t 要释放的动物类实例
 */
void ANIMAL_CLASS_DTOR(ANIMAL_CLASS* t);

/**
 * @brief 构造 DOG_CLASS 实例
 * 
 * @param t 基类接口指针，可用于虚函数绑定
 * @return DOG_CLASS* 新分配并初始化的狗类指针
 */
DOG_CLASS* DOG_CLASS_CTOR(ANIMAL_CLASS_IMPLEMENTS* t);

/**
 * @brief 析构 DOG_CLASS 实例
 * 
 * @param t 要释放的狗类实例
 */
void DOG_CLASS_DTOR(DOG_CLASS* t);

/**
 * @brief 构造 CAT_CLASS 实例
 * 
 * @param t 基类接口指针，可用于虚函数绑定
 * @return CAT_CLASS* 新分配并初始化的猫类指针
 */
CAT_CLASS* CAT_CLASS_CTOR(ANIMAL_CLASS_IMPLEMENTS* t);

/**
 * @brief 析构 CAT_CLASS 实例
 * 
 * @param t 要释放的猫类实例
 */
void CAT_CLASS_DTOR(CAT_CLASS* t);
