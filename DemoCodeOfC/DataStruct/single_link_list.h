/*************************************************************************
	> FileName  : single_link_list.h
	> Author    : zhouzhijun
	> Mail      : snjzzjun@163.com
	> CreateTime: 2019年11月27日 星期三 16时16分57秒
*************************************************************************/
#ifndef _SINGLE_LINK_LIST_H
#define _SINGLE_LINK_LIST_H

#define USE_SINGLE_LINK_LIST         1
#define ENABLE_SINGLE_LINK_LSIT_TEST 1

#define SINGLE_LINK_LIST_OP_SUCCESS  0
#define SINGLE_LINK_LIST_OP_FAILURE  -1

#define SINGLE_LINK_LIST_ERROR(format,...) printf("<error> ["__FILE__":%d]: "format, __LINE__, ##__VA_ARGS__)
#define SINGLE_LINK_LIST_INFO(format, ...) printf(format, ##__VA_ARGS__)

#define SINGLE_LINK_MIN(a, b) ((a) < (b) ? (a) : (b))
#define SINGLE_LINK_MAX(a, b) ((a) > (b) ? (a) : (b))

#define true  1
#define false 0

typedef int data_t;
typedef struct single_link_list_node 
{
    data_t data;
    struct single_link_list_node* next;
}sg_list_node_t;

typedef struct single_link_list_head
{
    int list_len;
    sg_list_node_t* next;
}sg_list_head_t;


#endif //_SINGLE_LINK_LIST_H


