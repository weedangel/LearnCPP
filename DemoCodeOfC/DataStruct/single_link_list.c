/*************************************************************************
	> FileName  : single_link_list.c
	> Author    : zhouzhijun
	> Mail      : snjzzjun@163.com
	> CreateTime: 2019年11月27日 星期三 16时16分12秒
*************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "single_link_list.h"

#if (USE_SINGLE_LINK_LIST)
int single_link_list_init(sg_list_head_t* list_head)
{
    if (list_head == NULL)
    {
        SINGLE_LINK_LIST_ERROR("Single link list invalid[init]\n");
        return SINGLE_LINK_LIST_OP_FAILURE;
    }
    list_head->list_len = 0;
    list_head->next = NULL;
    
    return SINGLE_LINK_LIST_OP_SUCCESS;
}

int single_link_list_destroy(sg_list_head_t* list_head)
{
    sg_list_node_t* temp_node = NULL;

    if (list_head == NULL)
    {
        SINGLE_LINK_LIST_ERROR("Single link list invalid[destroy]\n");
        return SINGLE_LINK_LIST_OP_FAILURE;
    }
    
    temp_node = list_head->next;
    while (temp_node != NULL)
    {
        list_head->next = temp_node->next;
        free(temp_node);
        temp_node = list_head->next;
    }
    list_head->list_len = 0;
    list_head->next = NULL;
    
    return SINGLE_LINK_LIST_OP_SUCCESS;
}

int single_link_list_node_insert(sg_list_head_t* list_head, int pos, data_t insert_data)
{
    int index = 0;
    sg_list_node_t* temp_node = NULL, read_node = NULL;
    
    if (list_head == NULL)
    {
        SINGLE_LINK_LIST_ERROR("Single link list invalid[insert]\n");
        return SINGLE_LINK_LIST_OP_FAILURE;
    }
    
    if (pos < 0)
    {
        SINGLE_LINK_LIST_ERROR("Single link list insert point invalid\n");
        return SINGLE_LINK_LIST_OP_FAILURE;
    }
    
    if (pos > list_head->list_len)
    {
        pos = list_head->list_len;
    }
    
    temp_node = (sg_list_node_t*)malloc(sizeof(sg_list_node_t));
    if (temp_node == NULL)
    {
        SINGLE_LINK_LIST_ERROR("Create link list node fail, no enough memory\n");
        return SINGLE_LINK_LIST_OP_FAILURE;
    }
    temp_node->data = insert_data;
    temp_node->next = NULL;
    
    read_node = list_head->next;
    if (pos == 0)
    {
        list_head->next = temp_node;
        list_head->list_len += 1;
    }
    else if(read_node != NULL)
    {
        for (index = 1; index < pos; index++) 
        {
            read_node = read_node->next;
            if (read_node == NULL)
            {
                SINGLE_LINK_LIST_ERROR("Single link list node error\n");
                return SINGLE_LINK_LIST_OP_FAILURE;
            }
        }
        temp_node->next = read_node->next;
        read_node->next = temp_node;
        list_head->list_len += 1;
    }
    else
    {
        SINGLE_LINK_LIST_ERROR("Single link list head error\n");
        return SINGLE_LINK_LIST_OP_FAILURE;
    }
    
    return SINGLE_LINK_LIST_OP_SUCCESS;
}

#endif //USE_SINGLE_LINK_LIST

#if (ENABLE_SINGLE_LINK_LSIT_TEST)
int main(int argc, char *argv[])
{    
    SEQUENCE_LIST_INFO("Start test single link list\n");

    SEQUENCE_LIST_INFO("Stop test single link list\n");
    
    return 0;
}
#endif //ENABLE_SINGLE_LINK_LSIT_TEST

