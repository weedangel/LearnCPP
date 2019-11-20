/*************************************************************************
	> FileName  : heap_function_demo.c
	> Author    : zhouzhijun
	> Mail      : snjzzjun@163.com
	> CreateTime: 2019年11月20日 星期三 14时42分52秒
*************************************************************************/

#include <stdio.h>

#define OPERATION_SUCCESS  0
#define OPERATION_FAILURE  -1

//#define DEBUG_ERROR(format,...) printf("FILE: "__FILE__", LINE: %d: "format"\n", __LINE__, ##__VA_ARGS__)
#define DEBUG_ERROR(format,...) printf("<error> ["__FILE__":%d]: "format, __LINE__, ##__VA_ARGS__)
#define DEBUG_INFO(format, ...) printf(format, ##__VA_ARGS__)

typedef int data_type_t;

/********************************************************************************************************
 * 功能：将传入的数组转换成大顶堆
 * 参数：
 *      @heap_buf: 原始数据位置（堆中的数据）
 *      @heap_size:需要转换的数据个数（堆的大小）
 * 返回值：构建成功返回OPERATION_SUCCESS，失败返回OPERATION_FAILURE
 * 用例：xxxxxx
********************************************************************************************************/
int create_max_heap(data_type_t* heap_buf, int heap_size)
{
    int index = 0, child_index = 0, grandson_index = 0;
    data_type_t temp_data = 0;
    
    if (heap_size <= 0) {
        DEBUG_ERROR("Invalid heap.\n");
        return OPERATION_FAILURE;
    }
    
    //从最后一个非叶子节点开始反向索引
    for (index = heap_size/2 - 1; index >= 0; index--) {
        //判断左孩子与父节点是否满足大顶堆规则
        child_index = index * 2 + 1;
        if ( (child_index < heap_size) && (heap_buf[index] < heap_buf[child_index]) ) {
            temp_data = heap_buf[index];
            heap_buf[index] = heap_buf[child_index];
            heap_buf[child_index] = temp_data;
            
            //判断交换后是否影响孙子节点
            grandson_index = child_index * 2 + 1;
            if ( (grandson_index < heap_size) && (heap_buf[child_index] < heap_buf[grandson_index])
                || ((grandson_index+1) < heap_size) && (heap_buf[child_index] < heap_buf[grandson_index+1]) ) {
                create_max_heap(heap_buf, heap_size);
            }
        }
        
        //判断右孩子与父节点是否满足大顶堆规则
        child_index = index * 2 + 2;
        if ( (child_index < heap_size) && (heap_buf[index] < heap_buf[child_index]) ) {
            temp_data = heap_buf[index];
            heap_buf[index] = heap_buf[child_index];
            heap_buf[child_index] = temp_data;
            
            //判断交换后是否影响孙子节点
            grandson_index = child_index * 2 + 1;
            if ( (grandson_index < heap_size) && (heap_buf[child_index] < heap_buf[grandson_index])
                || ((grandson_index+1) < heap_size) && (heap_buf[child_index] < heap_buf[grandson_index+1]) ) {
                create_max_heap(heap_buf, heap_size);
            }
        }
    }
    
    return OPERATION_SUCCESS;
}

/********************************************************************************************************
 * 功能：将传入的数组转换成小顶堆
 * 参数：
 *      @heap_buf: 原始数据位置（堆中的数据）
 *      @heap_size:需要转换的数据个数（堆的大小）
 * 返回值：构建成功返回OPERATION_SUCCESS，失败返回OPERATION_FAILURE
 * 用例：xxxxxx
********************************************************************************************************/
int create_min_heap(data_type_t* heap_buf, int heap_size)
{
    int index = 0, child_index = 0, grandson_index = 0;
    data_type_t temp_data = 0;
    
    if (heap_size <= 0) {
        DEBUG_ERROR("Invalid heap.\n");
        return OPERATION_FAILURE;
    }
    
    //从最后一个非叶子节点开始反向索引
    for (index = heap_size/2 - 1; index >= 0; index--) {
        //判断左孩子与父节点是否满足大顶堆规则
        child_index = index * 2 + 1;
        if ( (child_index < heap_size) && (heap_buf[index] > heap_buf[child_index]) ) {
            temp_data = heap_buf[index];
            heap_buf[index] = heap_buf[child_index];
            heap_buf[child_index] = temp_data;
            
            //判断交换后是否影响孙子节点
            grandson_index = child_index * 2 + 1;
            if ( (grandson_index < heap_size) && (heap_buf[child_index] > heap_buf[grandson_index])
                || ((grandson_index+1) < heap_size) && (heap_buf[child_index] > heap_buf[grandson_index+1]) ) {
                create_min_heap(heap_buf, heap_size);
            }
        }
        
        //判断右孩子与父节点是否满足大顶堆规则
        child_index = index * 2 + 2;
        if ( (child_index < heap_size) && (heap_buf[index] > heap_buf[child_index]) ) {
            temp_data = heap_buf[index];
            heap_buf[index] = heap_buf[child_index];
            heap_buf[child_index] = temp_data;
            
            //判断交换后是否影响孙子节点
            grandson_index = child_index * 2 + 1;
            if ( (grandson_index < heap_size) && (heap_buf[child_index] > heap_buf[grandson_index])
                || ((grandson_index+1) < heap_size) && (heap_buf[child_index] > heap_buf[grandson_index+1]) ) {
                create_min_heap(heap_buf, heap_size);
            }
        }
    }
    
    return OPERATION_SUCCESS;
}

/********************************************************************************************************
 * 功能：将传入的数组升序排序
 * 参数：
 *      @heap_buf: 需要排序的数据
 *      @heap_size:需要排序的数据的个数
 * 返回值：void
 * 用例：xxxxxx
********************************************************************************************************/
void heap_sort_up(data_type_t* data_buf, int data_len)
{
    int index = 0;
    data_type_t temp_data = 0;
    
    for (index = 0; index < data_len; index++) {
        create_max_heap(data_buf, data_len-index);
        temp_data = data_buf[0];
        data_buf[0] = data_buf[data_len-index-1];
        data_buf[data_len-index-1] = temp_data;
    }
    
    return ;
}

/********************************************************************************************************
 * 功能：将传入的数组降序排序
 * 参数：
 *      @heap_buf: 需要排序的数据
 *      @heap_size:需要排序的数据的个数
 * 返回值：void
 * 用例：xxxxxx
********************************************************************************************************/
void heap_sort_down(data_type_t* data_buf, int data_len)
{
    int index = 0;
    data_type_t temp_data = 0;
    
    for (index = 0; index < data_len; index++) {
        create_min_heap(data_buf, data_len-index);
        temp_data = data_buf[0];
        data_buf[0] = data_buf[data_len-index-1];
        data_buf[data_len-index-1] = temp_data;
    }
    
    return ;
}

void printf_heap_data(data_type_t* heap_buf, int heap_size)
{
    int index = 0;
    
    for (index = 0; index < heap_size; index++) {
        if ( index != (heap_size - 1) ) {
            DEBUG_INFO("%-4d, ", heap_buf[index]);
        }
        else {
            DEBUG_INFO("%-4d", heap_buf[index]);
        }
        
        if ( ((index + 1) % 8 == 0) || (index == (heap_size - 1)) ) {
            DEBUG_INFO("\n");
        }
    }
    
    return ;
}

int main(int argc, char *argv[])
{
    data_type_t heap_data[] = {765, 312, 9118, 15, 102, 2, 79, 43, 2, 17, 8, 6};
    
    create_max_heap(heap_data, sizeof(heap_data)/sizeof(heap_data[0]));
    DEBUG_INFO("Max heap data: \n");
    printf_heap_data(heap_data, sizeof(heap_data)/sizeof(heap_data[0]));
    
    create_min_heap(heap_data, sizeof(heap_data)/sizeof(heap_data[0]));
    DEBUG_INFO("Min heap data: \n");
    printf_heap_data(heap_data, sizeof(heap_data)/sizeof(heap_data[0]));
    
    heap_sort_up(heap_data, sizeof(heap_data)/sizeof(heap_data[0]));
    DEBUG_INFO("Sort up data: \n");
    printf_heap_data(heap_data, sizeof(heap_data)/sizeof(heap_data[0]));
    
    heap_sort_down(heap_data, sizeof(heap_data)/sizeof(heap_data[0]));
    DEBUG_INFO("Sort down data: \n");
    printf_heap_data(heap_data, sizeof(heap_data)/sizeof(heap_data[0]));
    
    return 0;
}
