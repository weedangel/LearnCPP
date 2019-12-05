/*************************************************************************
	> FileName  : sequence_list.c
	> Author    : zhouzhijun
	> Mail      : snjzzjun@163.com
	> CreateTime: 2019年11月26日 星期二 15时23分52秒
*************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sequence_list.h"

#if (USE_SEQUENCE_LIST)
/*******************************************************************************
 * 功  能：初始化顺序表
 * 参  数：@sq_list: 待初始化的顺序表
 *         @sq_list_size: 预设顺序表的大小
 * 返回值：成功返回0(SEQUENCE_LIST_OP_SUCCESS)
 *         失败返回-1(SEQUENCE_LIST_OP_FAILURE)
 * 用例: ???
*******************************************************************************/
int sequence_list_init(sq_list_t* sq_list, int sq_list_size)
{
    sq_data_t* temp_ptr = NULL;
    
    if (sq_list == NULL)
    {
        SEQUENCE_LIST_ERROR("Sequence list invalid[init]\n");
        return SEQUENCE_LIST_OP_FAILURE;
    }
    
    memset(sq_list, 0, sizeof(sq_list_t));
    temp_ptr = malloc(sizeof(sq_data_t)*sq_list_size);
    if(temp_ptr == NULL)
    {
        SEQUENCE_LIST_ERROR("Init sequence list fail, no enought memory\n");
        return SEQUENCE_LIST_OP_FAILURE;
    }
    sq_list->data_buf = temp_ptr;
    sq_list->sq_size = sq_list_size;
    sq_list->sq_len = 0;
    
    return SEQUENCE_LIST_OP_SUCCESS;
}

/*******************************************************************************
 * 功  能：销毁顺序表
 * 参  数：@sq_list: 待销毁的顺序表
 * 返回值：成功返回0(SEQUENCE_LIST_OP_SUCCESS)
 *         失败返回-1(SEQUENCE_LIST_OP_FAILURE)
 * 用例: ???
*******************************************************************************/
int sequence_list_destroy(sq_list_t* sq_list)
{
    if (sq_list == NULL || sq_list->data_buf == NULL)
    {
        SEQUENCE_LIST_ERROR("Sequence list invalid[destory]\n");
        return SEQUENCE_LIST_OP_FAILURE;
    }
    
    free(sq_list->data_buf);
    sq_list->sq_size = 0;
    sq_list->sq_len = 0;
    
    return SEQUENCE_LIST_OP_SUCCESS;
}

/*******************************************************************************
 * 功  能：清空顺序表
 * 参  数：@sq_list: 待清空的顺序表
 * 返回值：成功返回0(SEQUENCE_LIST_OP_SUCCESS)
 *         失败返回-1(SEQUENCE_LIST_OP_FAILURE)
 * 用例: ???
*******************************************************************************/
int sequence_list_clear(sq_list_t* sq_list)
{
    if (sq_list == NULL || sq_list->data_buf == NULL)
    {
        SEQUENCE_LIST_ERROR("Sequence list invalid[clear]\n");
        return SEQUENCE_LIST_OP_FAILURE;
    }
    
    memset(sq_list->data_buf, 0, sq_list->sq_size * sizeof(sq_data_t));
    sq_list->sq_len = 0;
    
    return SEQUENCE_LIST_OP_SUCCESS;
}

/*******************************************************************************
 * 功  能：向顺序表插入元素
 * 参  数：@sq_list: 待插入的顺序表
 *         @pos: 插入的位置（索引值），若pos向后偏离了尾部，将以尾插插入
 *         @insert_data: 待插入的值
 * 返回值：成功返回0(SEQUENCE_LIST_OP_SUCCESS)
 *         失败返回-1(SEQUENCE_LIST_OP_FAILURE)
 * 用例: ???
*******************************************************************************/
int sequence_list_data_insert(sq_list_t* sq_list, int pos, sq_data_t insert_data)
{
    int index = 0;
    
    if (sq_list == NULL || sq_list->data_buf == NULL)
    {
        SEQUENCE_LIST_ERROR("Sequence list invalid[insert]\n");
        return SEQUENCE_LIST_OP_FAILURE;
    }
    
    if (pos < 0 || pos > sq_list->sq_size)
    {
        SEQUENCE_LIST_ERROR("Sequence list insert point invalid\n");
        return SEQUENCE_LIST_OP_FAILURE;
    }
    
    if (sq_list->sq_len == sq_list->sq_size)
    {
        SEQUENCE_LIST_ERROR("Insert data error, sequence list is fulled\n");
        return SEQUENCE_LIST_OP_FAILURE;
    }

    /* 若pos向后偏离了尾部，直接调整到尾部位置插入 */
    if (pos > sq_list->sq_len)
    {
        pos = sq_list->sq_len;
    }
    
    /* 依次将元素后挪，腾出一个位置，直到找到pos位置 */
    for (index = sq_list->sq_len; index > pos; index--)
    {
        sq_list->data_buf[index] = sq_list->data_buf[index-1];
    }
    sq_list->data_buf[pos] = insert_data;
    sq_list->sq_len += 1;
    
    return SEQUENCE_LIST_OP_SUCCESS;
}

/*******************************************************************************
 * 功  能：向顺序表头部插入元素
 * 参  数：@sq_list: 待插入的顺序表
 *         @insert_data: 待插入的值
 * 返回值：成功返回0(SEQUENCE_LIST_OP_SUCCESS)
 *         失败返回-1(SEQUENCE_LIST_OP_FAILURE)
 * 用例: ???
*******************************************************************************/
int sequence_list_data_insert_head(sq_list_t* sq_list, sq_data_t insert_data)
{
    return sequence_list_data_insert(sq_list, 0, insert_data);
}

/*******************************************************************************
 * 功  能：向顺序表尾部插入元素
 * 参  数：@sq_list: 待插入的顺序表
 *         @insert_data: 待插入的值
 * 返回值：成功返回0(SEQUENCE_LIST_OP_SUCCESS)
 *         失败返回-1(SEQUENCE_LIST_OP_FAILURE)
 * 用例: ???
*******************************************************************************/
int sequence_list_data_insert_tail(sq_list_t* sq_list, sq_data_t insert_data)
{
    if (sq_list == NULL)
    {
        SEQUENCE_LIST_ERROR("Sequence list invalid[insert tail]\n");
        return SEQUENCE_LIST_OP_FAILURE;
    }
    
    return sequence_list_data_insert(sq_list, sq_list->sq_len, insert_data);
}

/*******************************************************************************
 * 功  能：从顺序表中删除元素
 * 参  数：@sq_list: 待删除的顺序表
 *         @@pos: 删除的位置（索引值）
 * 返回值：成功返回0(SEQUENCE_LIST_OP_SUCCESS)
 *         失败返回-1(SEQUENCE_LIST_OP_FAILURE)
 * 用例: ???
*******************************************************************************/
int sequence_list_data_delete(sq_list_t* sq_list, int pos)
{
    int index = 0;
    
    if (sq_list == NULL || sq_list->data_buf == NULL)
    {
        SEQUENCE_LIST_ERROR("Sequence list invalid[delete]\n");
        return SEQUENCE_LIST_OP_FAILURE;
    }
    
    if (pos < 0 || pos >= sq_list->sq_len)
    {
        SEQUENCE_LIST_ERROR("Sequence list delete point invalid\n");
        return SEQUENCE_LIST_OP_FAILURE;
    }
    
    for (index = pos; index < sq_list->sq_len - 1; index++)
    {
        sq_list->data_buf[index] = sq_list->data_buf[index+1];
    }
    sq_list->data_buf[sq_list->sq_len-1] = 0;
    sq_list->sq_len -= 1;
    
    return SEQUENCE_LIST_OP_SUCCESS;
}

/*******************************************************************************
 * 功  能：从顺序表头部删除元素
 * 参  数：@sq_list: 待删除的顺序表
 * 返回值：成功返回0(SEQUENCE_LIST_OP_SUCCESS)
 *         失败返回-1(SEQUENCE_LIST_OP_FAILURE)
 * 用例: ???
*******************************************************************************/
int sequence_list_data_delete_head(sq_list_t* sq_list)
{
    return sequence_list_data_delete(sq_list, 0);
}

/*******************************************************************************
 * 功  能：从顺序表尾部删除元素
 * 参  数：@sq_list: 待删除的顺序表
 * 返回值：成功返回0(SEQUENCE_LIST_OP_SUCCESS)
 *         失败返回-1(SEQUENCE_LIST_OP_FAILURE)
 * 用例: ???
*******************************************************************************/
int sequence_list_data_delete_tail(sq_list_t* sq_list)
{
    if (sq_list == NULL)
    {
        SEQUENCE_LIST_ERROR("Sequence list invalid[delete tail]\n");
        return SEQUENCE_LIST_OP_FAILURE;
    }
    
    return sequence_list_data_delete(sq_list, sq_list->sq_len-1);
}

/*******************************************************************************
 * 功  能：修改顺序表中的元素
 * 参  数：@sq_list: 待修改的顺序表
 *         @pos: 修改的位置（索引值）
 *         @change_data: 待修改的值
 * 返回值：成功返回0(SEQUENCE_LIST_OP_SUCCESS)
 *         失败返回-1(SEQUENCE_LIST_OP_FAILURE)
 * 用例: ???
*******************************************************************************/
int sequence_list_data_change(sq_list_t* sq_list, int pos, sq_data_t change_data)
{
    if (sq_list == NULL || sq_list->data_buf == NULL)
    {
        SEQUENCE_LIST_ERROR("Sequence list invalid[change]\n");
        return SEQUENCE_LIST_OP_FAILURE;
    }
    
    if (pos < 0 || pos >= sq_list->sq_len)
    {
        SEQUENCE_LIST_ERROR("Sequence list change point invalid\n");
        return SEQUENCE_LIST_OP_FAILURE;
    }

    sq_list->data_buf[pos] = change_data;

    return SEQUENCE_LIST_OP_SUCCESS;
}

/*******************************************************************************
 * 功  能：修改顺序表头部的元素
 * 参  数：@sq_list: 待修改的顺序表
 *         @change_data: 待修改的值
 * 返回值：成功返回0(SEQUENCE_LIST_OP_SUCCESS)
 *         失败返回-1(SEQUENCE_LIST_OP_FAILURE)
 * 用例: ???
*******************************************************************************/
int sequence_list_data_change_head(sq_list_t* sq_list, sq_data_t change_data)
{
    return sequence_list_data_change(sq_list, 0, change_data);
}

/*******************************************************************************
 * 功  能：修改顺序表尾部的元素
 * 参  数：@sq_list: 待修改的顺序表
 *         @change_data: 待修改的值
 * 返回值：成功返回0(SEQUENCE_LIST_OP_SUCCESS)
 *         失败返回-1(SEQUENCE_LIST_OP_FAILURE)
 * 用例: ???
*******************************************************************************/
int sequence_list_data_change_tail(sq_list_t* sq_list, sq_data_t change_data)
{
    if (sq_list == NULL)
    {
        SEQUENCE_LIST_ERROR("Sequence list invalid[change tail]\n");
        return SEQUENCE_LIST_OP_FAILURE;
    }
    
    return sequence_list_data_change(sq_list, sq_list->sq_len-1, change_data);
}

/*******************************************************************************
 * 功  能：从顺序表中查找元素
 * 参  数：@sq_list: 待查找的顺序表
 *         @find_data: 待查找的元素值
 * 返回值：成功返回当前元素在顺序表中的索引值
 *         失败返回-1(SEQUENCE_LIST_OP_FAILURE)
 * 用例: ???
*******************************************************************************/
int sequence_list_data_find(sq_list_t* sq_list, sq_data_t find_data)
{
    int index = 0;
    
    if (sq_list == NULL || sq_list->data_buf == NULL)
    {
        SEQUENCE_LIST_ERROR("Sequence list invalid[find]\n");
        return SEQUENCE_LIST_OP_FAILURE;
    }
    
    for (index = 0; index < sq_list->sq_len; index++)
    {
        if (sq_list->data_buf[index] == find_data)
        {
            return index;
        }
    }
    
    return SEQUENCE_LIST_OP_FAILURE;
}

/*******************************************************************************
 * 功  能：重置顺序表的空间，若重置之后比原来的表小，会丢弃超出部分的元素，
 *         若重置后空间变大，之前已有的元素将按原有的顺序存储
 * 参  数：@sq_list: 待重置的顺序表
 *         @reserve_size: 重置后的大小
 * 返回值：成功返回0(SEQUENCE_LIST_OP_SUCCESS)
 *         失败返回-1(SEQUENCE_LIST_OP_FAILURE)
 * 用例: ???
*******************************************************************************/
int sequence_list_reserve(sq_list_t* sq_list, int reserve_size)
{
    sq_data_t* temp_ptr = NULL;
    int temp_len = 0;
    
    if (sq_list == NULL || sq_list->data_buf == NULL)
    {
        SEQUENCE_LIST_ERROR("Sequence list invalid[reserve]\n");
        return SEQUENCE_LIST_OP_FAILURE;
    }
    
    temp_ptr = malloc(sizeof(sq_data_t) * reserve_size);
    if(temp_ptr == NULL)
    {
        SEQUENCE_LIST_ERROR("Reserve sequence list fail, no enought memory\n");
        return SEQUENCE_LIST_OP_FAILURE;
    }
    
    temp_len = SEQUENCE_MIN(sq_list->sq_len, reserve_size);
    memcpy(temp_ptr, sq_list->data_buf, sizeof(sq_data_t) * temp_len);
    free(sq_list->data_buf);
    
    sq_list->data_buf = temp_ptr;
    sq_list->sq_size = reserve_size;
    sq_list->sq_len = temp_len;
    
    return SEQUENCE_LIST_OP_SUCCESS;
}

/*******************************************************************************
 * 功  能：判断当前顺序表是否为空
 * 参  数：@sq_list: 待判断的顺序表
 * 返回值：为空返回true 不为空返回false
 * 用例: ???
*******************************************************************************/
int sequence_list_is_empty(sq_list_t* sq_list)
{
    int bool_ret = false;
    
    if (sq_list->sq_len == 0)
    {
        bool_ret = true;
    }
    else
    {
        bool_ret = false;
    }
    
    return bool_ret;
}

/*******************************************************************************
 * 功  能：判断当前顺序表是否已满
 * 参  数：@sq_list: 待判断的顺序表
 * 返回值：已满返回true 未满返回false
 * 用例: ???
*******************************************************************************/
int sequence_list_is_full(sq_list_t* sq_list)
{
    int bool_ret = false;
    
    if (sq_list->sq_len == sq_list->sq_size)
    {
        bool_ret = true;
    }
    else
    {
        bool_ret = false;
    }
    
    return bool_ret;
}

/*******************************************************************************
 * 功  能：输出当前顺序表的信息
 * 参  数：@sq_list: 待输出的顺序表
 * 返回值：无
 * 用例: ???
*******************************************************************************/
void sequence_list_data_print(sq_list_t* sq_list)
{
    int i = 0;
    
    SEQUENCE_LIST_INFO("\n********************************************************************\n");
    SEQUENCE_LIST_INFO(" * Sequence list size: %d\n", sq_list->sq_size);
    SEQUENCE_LIST_INFO(" * Sequence list len: %d\n", sq_list->sq_len);
    SEQUENCE_LIST_INFO(" * Sequence list data: \n");
    
    for (i = 0; i < sq_list->sq_len; i++)
    {
        
        if ((i+1) % 8 == 0)
        {
            SEQUENCE_LIST_INFO("%4d,\n", sq_list->data_buf[i]);
        }
        else if ((i+1) % 8 == 1)
        {
            SEQUENCE_LIST_INFO(" * %4d, ", sq_list->data_buf[i]);
        }
        else
        {
            SEQUENCE_LIST_INFO("%4d, ", sq_list->data_buf[i]);
        }
    }
    if (i%8 != 0)
    {
        SEQUENCE_LIST_INFO("\n********************************************************************\n");
    }
    else
    {
        SEQUENCE_LIST_INFO("********************************************************************\n");
    }
    
    return ;
}
#endif //USE_SEQUENCE_LIST

#if (ENABLE_SEQUENCE_LSIT_TEST)
int main(int argc, char *argv[])
{
    sq_list_t my_sq_list;
    int sq_list_size = 10;
    int i = 0;
    
    SEQUENCE_LIST_INFO("Start test sequence list\n");
    
    sequence_list_init(&my_sq_list, sq_list_size);
    for (i = 0; i < 5; i++)
    {
        sequence_list_data_insert_tail(&my_sq_list, (i+1)*4);
    }
    sequence_list_data_print(&my_sq_list);
    
    sequence_list_data_insert_head(&my_sq_list, 13);
    sequence_list_data_print(&my_sq_list);
    
    sequence_list_data_insert(&my_sq_list, 3, 27);
    sequence_list_data_print(&my_sq_list);
    
    sequence_list_data_insert(&my_sq_list, 9, 35);
    sequence_list_data_print(&my_sq_list);
    
    sq_list_size = 12;
    sequence_list_reserve(&my_sq_list, sq_list_size);
    sequence_list_data_print(&my_sq_list);
    
    sequence_list_data_insert(&my_sq_list, 19, 23);
    sequence_list_data_print(&my_sq_list);
    SEQUENCE_LIST_INFO("Sequence list is empty: %d\n", sequence_list_is_empty(&my_sq_list));
    SEQUENCE_LIST_INFO("Sequence list is full: %d\n", sequence_list_is_full(&my_sq_list));

    sequence_list_clear(&my_sq_list);
    sequence_list_data_print(&my_sq_list);
    SEQUENCE_LIST_INFO("Sequence list is empty: %d\n", sequence_list_is_empty(&my_sq_list));
    
    sequence_list_init(&my_sq_list, sq_list_size);
    for (i = 0; i < sq_list_size; i++)
    {
        sequence_list_data_insert_tail(&my_sq_list, (i+1)*4);
    }
    sequence_list_data_print(&my_sq_list);
    SEQUENCE_LIST_INFO("Sequence list is full: %d\n", sequence_list_is_full(&my_sq_list));
    
    sequence_list_data_change(&my_sq_list, 9, 123);
    sequence_list_data_print(&my_sq_list);
    
    sequence_list_data_change_tail(&my_sq_list, 333);
    sequence_list_data_print(&my_sq_list);
    
    sequence_list_data_change_head(&my_sq_list, 111);
    sequence_list_data_print(&my_sq_list);
    
    SEQUENCE_LIST_INFO("data point: %d\n", sequence_list_data_find(&my_sq_list, 123));

    SEQUENCE_LIST_INFO("Stop test sequence list\n");
    
    return 0;
}
#endif //ENABLE_SEQUENCE_LSIT_TEST

