/*************************************************************************
	> FileName  : sequence_list.h
	> Author    : zhouzhijun
	> Mail      : snjzzjun@163.com
	> CreateTime: 2019年11月26日 星期二 15时24分34秒
*************************************************************************/
#ifndef _SEQUENCE_LIST_H
#define _SEQUENCE_LIST_H

#define USE_SEQUENCE_LIST         1
#define ENABLE_SEQUENCE_LSIT_TEST 1

#define SEQUENCE_LIST_OP_SUCCESS  0
#define SEQUENCE_LIST_OP_FAILURE  -1

#define SEQUENCE_LIST_ERROR(format,...) printf("<error> ["__FILE__":%d]: "format, __LINE__, ##__VA_ARGS__)
#define SEQUENCE_LIST_INFO(format, ...) printf(format, ##__VA_ARGS__)

#define SEQUENCE_MIN(a, b) ((a) < (b) ? (a) : (b))
#define SEQUENCE_MAX(a, b) ((a) > (b) ? (a) : (b))

#define true  1
#define false 0

typedef int sq_data_t;
typedef struct sequence_list 
{
    int sq_len;
    int sq_size;
    sq_data_t* data_buf;
}sq_list_t;

/*******************************************************************************
 * 功  能：初始化顺序表
 * 参  数：@sq_list: 待初始化的顺序表
 *         @sq_list_size: 预设顺序表的大小
 * 返回值：成功返回0(SEQUENCE_LIST_OP_SUCCESS)
 *         失败返回-1(SEQUENCE_LIST_OP_FAILURE)
 * 用例: ???
*******************************************************************************/
extern int sequence_list_init(sq_list_t* sq_list, int sq_list_size);

/*******************************************************************************
 * 功  能：销毁顺序表
 * 参  数：@sq_list: 待销毁的顺序表
 * 返回值：成功返回0(SEQUENCE_LIST_OP_SUCCESS)
 *         失败返回-1(SEQUENCE_LIST_OP_FAILURE)
 * 用例: ???
*******************************************************************************/
extern int sequence_list_destroy(sq_list_t* sq_list);

/*******************************************************************************
 * 功  能：清空顺序表
 * 参  数：@sq_list: 待清空的顺序表
 * 返回值：成功返回0(SEQUENCE_LIST_OP_SUCCESS)
 *         失败返回-1(SEQUENCE_LIST_OP_FAILURE)
 * 用例: ???
*******************************************************************************/
extern int sequence_list_clear(sq_list_t* sq_list);

/*******************************************************************************
 * 功  能：向顺序表插入元素
 * 参  数：@sq_list: 待插入的顺序表
 *         @pos: 插入的位置（索引值），若pos向后偏离了尾部，将以尾插插入
 *         @insert_data: 待插入的值
 * 返回值：成功返回0(SEQUENCE_LIST_OP_SUCCESS)
 *         失败返回-1(SEQUENCE_LIST_OP_FAILURE)
 * 用例: ???
*******************************************************************************/
extern int sequence_list_data_insert(sq_list_t* sq_list, int pos, sq_data_t insert_data);

/*******************************************************************************
 * 功  能：向顺序表头部插入元素
 * 参  数：@sq_list: 待插入的顺序表
 *         @insert_data: 待插入的值
 * 返回值：成功返回0(SEQUENCE_LIST_OP_SUCCESS)
 *         失败返回-1(SEQUENCE_LIST_OP_FAILURE)
 * 用例: ???
*******************************************************************************/
extern int sequence_list_data_insert_head(sq_list_t* sq_list, sq_data_t insert_data);

/*******************************************************************************
 * 功  能：向顺序表尾部插入元素
 * 参  数：@sq_list: 待插入的顺序表
 *         @insert_data: 待插入的值
 * 返回值：成功返回0(SEQUENCE_LIST_OP_SUCCESS)
 *         失败返回-1(SEQUENCE_LIST_OP_FAILURE)
 * 用例: ???
*******************************************************************************/
extern int sequence_list_data_insert_tail(sq_list_t* sq_list, sq_data_t insert_data);

/*******************************************************************************
 * 功  能：从顺序表中删除元素
 * 参  数：@sq_list: 待删除的顺序表
 *         @@pos: 删除的位置（索引值）
 * 返回值：成功返回0(SEQUENCE_LIST_OP_SUCCESS)
 *         失败返回-1(SEQUENCE_LIST_OP_FAILURE)
 * 用例: ???
*******************************************************************************/
extern int sequence_list_data_delete(sq_list_t* sq_list, int pos);

/*******************************************************************************
 * 功  能：从顺序表头部删除元素
 * 参  数：@sq_list: 待删除的顺序表
 * 返回值：成功返回0(SEQUENCE_LIST_OP_SUCCESS)
 *         失败返回-1(SEQUENCE_LIST_OP_FAILURE)
 * 用例: ???
*******************************************************************************/
extern int sequence_list_data_delete_head(sq_list_t* sq_list);

/*******************************************************************************
 * 功  能：从顺序表尾部删除元素
 * 参  数：@sq_list: 待删除的顺序表
 * 返回值：成功返回0(SEQUENCE_LIST_OP_SUCCESS)
 *         失败返回-1(SEQUENCE_LIST_OP_FAILURE)
 * 用例: ???
*******************************************************************************/
extern int sequence_list_data_delete_tail(sq_list_t* sq_list);

/*******************************************************************************
 * 功  能：修改顺序表中的元素
 * 参  数：@sq_list: 待修改的顺序表
 *         @pos: 修改的位置（索引值）
 *         @change_data: 待修改的值
 * 返回值：成功返回0(SEQUENCE_LIST_OP_SUCCESS)
 *         失败返回-1(SEQUENCE_LIST_OP_FAILURE)
 * 用例: ???
*******************************************************************************/
extern int sequence_list_data_change(sq_list_t* sq_list, int pos, sq_data_t change_data);

/*******************************************************************************
 * 功  能：修改顺序表头部的元素
 * 参  数：@sq_list: 待修改的顺序表
 *         @change_data: 待修改的值
 * 返回值：成功返回0(SEQUENCE_LIST_OP_SUCCESS)
 *         失败返回-1(SEQUENCE_LIST_OP_FAILURE)
 * 用例: ???
*******************************************************************************/
extern int sequence_list_data_change_head(sq_list_t* sq_list, sq_data_t change_data);

/*******************************************************************************
 * 功  能：修改顺序表尾部的元素
 * 参  数：@sq_list: 待修改的顺序表
 *         @change_data: 待修改的值
 * 返回值：成功返回0(SEQUENCE_LIST_OP_SUCCESS)
 *         失败返回-1(SEQUENCE_LIST_OP_FAILURE)
 * 用例: ???
*******************************************************************************/
extern int sequence_list_data_change_tail(sq_list_t* sq_list, sq_data_t change_data);

/*******************************************************************************
 * 功  能：从顺序表中查找元素
 * 参  数：@sq_list: 待查找的顺序表
 *         @find_data: 待查找的元素值
 * 返回值：成功返回当前元素在顺序表中的索引值
 *         失败返回-1(SEQUENCE_LIST_OP_FAILURE)
 * 用例: ???
*******************************************************************************/
extern int sequence_list_data_find(sq_list_t* sq_list, sq_data_t find_data);

/*******************************************************************************
 * 功  能：重置顺序表的空间，若重置之后比原来的表小，会丢弃超出部分的元素，
 *         若重置后空间变大，之前已有的元素将按原有的顺序存储
 * 参  数：@sq_list: 待重置的顺序表
 *         @reserve_size: 重置后的大小
 * 返回值：成功返回0(SEQUENCE_LIST_OP_SUCCESS)
 *         失败返回-1(SEQUENCE_LIST_OP_FAILURE)
 * 用例: ???
*******************************************************************************/
extern int sequence_list_reserve(sq_list_t* sq_list, int reserve_size);

/*******************************************************************************
 * 功  能：判断当前顺序表是否为空
 * 参  数：@sq_list: 待判断的顺序表
 * 返回值：为空返回true 不为空返回false
 * 用例: ???
*******************************************************************************/
extern int sequence_list_is_empty(sq_list_t* sq_list);

/*******************************************************************************
 * 功  能：判断当前顺序表是否已满
 * 参  数：@sq_list: 待判断的顺序表
 * 返回值：已满返回true 未满返回false
 * 用例: ???
*******************************************************************************/
extern int sequence_list_is_full(sq_list_t* sq_list);

/*******************************************************************************
 * 功  能：输出当前顺序表的信息
 * 参  数：@sq_list: 待输出的顺序表
 * 返回值：无
 * 用例: ???
*******************************************************************************/
extern void sequence_list_data_print(sq_list_t* sq_list);

#endif //_SEQUENCE_LIST_H


