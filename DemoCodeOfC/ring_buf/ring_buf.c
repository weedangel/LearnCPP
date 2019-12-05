/**
 *  Copyright (c) 2016 Cenon(Shanghai) Co.,Ltd.All rights reserved.
 * 
 * @file    cenon_app.c
 * @brief   cenon application
 * 
 * @author  fxjang (yong-qiang.li@cenon.com.cn)
 * @date    2018-04-20
 * 
 * @history
 */
#include <stdio.h>
#include <string.h>
#include <string.h>
#include <stdlib.h>

#include "ring_buf.h"

static const char mon_tb[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

void ring_buffer_init(ring_buffer_t *rb, char *data, short len, char overflow)
{
    rb->read_index = 0;
    rb->write_index = 0;
    rb->len = len;
    rb->data = data;
    if (overflow)
    {
        rb->overflow = RING_BUF_OVERFLOW_ENABLE;
    }
    else
    {
        rb->overflow = RING_BUF_OVERFLOW_DISABLE;
    }
    rb->status = RING_BUF_STATUS_EMPTY;
    memset(data, 0, len);
}

/* one data write to ring buffer, if write success return 1, otherwise return error code*/
int ring_buffer_write_char(ring_buffer_t *rb, char data)
{
    int ret = 0;
    
    if ((rb == NULL) || (rb->status == RING_BUF_STATUS_INVALID))
    {
        return RING_BUF_ERR_UNINIT;
    }
    
    if ((rb->status == RING_BUF_STATUS_EMPTY) || (rb->status == RING_BUF_STATUS_WORKABLE))
    {
        rb->data[rb->write_index] = data;
        rb->write_index = (rb->write_index + 1) % rb->len;
        if (rb->write_index == rb->read_index)
        {
            rb->status = RING_BUF_STATUS_FULL;
        }
        else
        {
            rb->status = RING_BUF_STATUS_WORKABLE;
        }
        
        ret = RING_BUF_OPT_1BYTE;
    }
    else if(rb->status == RING_BUF_STATUS_FULL)
    {
        if (rb->overflow == RING_BUF_OVERFLOW_ENABLE)
        {
            rb->data[rb->write_index] = data;
            rb->write_index = (rb->write_index + 1) % rb->len;
            rb->status = RING_BUF_STATUS_OVERFLOW;
            
            ret = RING_BUF_OPT_1BYTE;
        }
        else
        {
            ret = RING_BUF_ERR_FULL;
        }
    }
    else if (rb->status == RING_BUF_STATUS_OVERFLOW)
    {
        rb->data[rb->write_index] = data;
        rb->write_index = (rb->write_index + 1) % rb->len;
        rb->status = RING_BUF_STATUS_OVERFLOW;
        
        ret = RING_BUF_OPT_1BYTE;
    }
    else
    {
        ret = RING_BUF_ERR_UNINIT;
    }
    
    return ret;
}

/* write block data to ring buffer, if write success return write len, otherwise return error code */
int ring_buffer_write_block(ring_buffer_t *rb, char *buf, int len)
{
    int ret = 0, i = 0;
    int write_len = 0;

    if ((rb == NULL) || (rb->status == RING_BUF_STATUS_INVALID))
    {
        return RING_BUF_ERR_UNINIT;
    }
    
    if (buf == NULL || len == 0)
    {
        return RING_BUF_ERR_INVALID_DATA;
    }

    for (i = 0; i < len; i++)
    {
        ret = ring_buffer_write_char(rb, buf[i]);
        if (ret < 0)
        {
            write_len = ret;
            break;
        }
        write_len += 1;
    }

    return write_len;
}

/* ensure write all data, write success return len, otherwise return error code */
int ring_buffer_write_block_ensure(ring_buffer_t *rb, char *buf, int len)
{
    int ret = 0, i = 0;
    short temp_index = rb->write_index;
    short temp_status = rb->status;
    
    if ((rb == NULL) || (rb->status == RING_BUF_STATUS_INVALID))
    {
        return RING_BUF_ERR_UNINIT;
    }
    
    if (buf == NULL || len == 0)
    {
        return RING_BUF_ERR_INVALID_DATA;
    }

    for (i = 0; i < len; i++)
    {
        ret = ring_buffer_write_char(rb, buf[i]);
        if (ret < 0)
        {
            rb->write_index = temp_index;
            rb->status = temp_status;
            return ret;
        }
    }

    return len;
}

int ring_buffer_read_char(ring_buffer_t *rb, char *data)
{
    //int ret = 0;
    
    if ((rb == NULL) || (rb->status == RING_BUF_STATUS_INVALID))
    {
        return RING_BUF_ERR_UNINIT;
    }
    
    if (data == NULL)
    {
        return RING_BUF_ERR_INVALID_DATA;
    }
    
    if (rb->status == RING_BUF_STATUS_EMPTY)
    {
        return RING_BUF_ERR_EMPTY;
    }
    
    if (rb->status == RING_BUF_STATUS_OVERFLOW)
    {
        rb->read_index = rb->write_index;
        rb->status = RING_BUF_STATUS_FULL;
    }
    
    *data = rb->data[rb->read_index];
    rb->read_index = (rb->read_index + 1) % rb->len;
    if (rb->status == RING_BUF_STATUS_WORKABLE)
    {
        if (rb->read_index == rb->write_index)
        {
            rb->status = RING_BUF_STATUS_EMPTY;
        }
    }
    else if (rb->status == RING_BUF_STATUS_FULL)
    {
        rb->status = RING_BUF_STATUS_WORKABLE;
    }

    return RING_BUF_OPT_1BYTE;
}

int ring_buffer_read_block(ring_buffer_t *rb, char *buf, int len)
{
    int read_len = 0, i = 0;
    int ret = 0;

    if ((rb == NULL) || (rb->status == RING_BUF_STATUS_INVALID))
    {
        return RING_BUF_ERR_UNINIT;
    }
    
    if (buf == NULL || len == 0)
    {
        return RING_BUF_ERR_INVALID_DATA;
    }
    
    if (rb->status == RING_BUF_STATUS_EMPTY)
    {
        return RING_BUF_ERR_EMPTY;
    }
    
    for(i = 0; i < len; i++)
    {
        ret = ring_buffer_read_char(rb, &buf[i]);
        if (ret == RING_BUF_OPT_1BYTE)
        {
            read_len += 1;
        }
        else if (ret == RING_BUF_ERR_EMPTY)
        {
            break;
        }
        else
        {
            return ret;
        }
    }
		
    return read_len;
}

int ring_buffer_peek(ring_buffer_t *rb, char *buf, int len)
{
    int read_len = 0, i = 0;
    short temp_read_index = 0;
    short data_valid_len = 0;

    if ((rb == NULL) || (rb->status == RING_BUF_STATUS_INVALID))
    {
        return RING_BUF_ERR_UNINIT;
    }
    
    if (buf == NULL || len == 0)
    {
        return RING_BUF_ERR_INVALID_DATA;
    }
    
    if (rb->status == RING_BUF_STATUS_EMPTY)
    {
        return RING_BUF_ERR_EMPTY;
    }
    else if(rb->status == RING_BUF_STATUS_WORKABLE)
    {
        temp_read_index = rb->read_index;
        data_valid_len = (rb->read_index < rb->write_index) ? (rb->write_index - rb->read_index) : ((rb->write_index + rb->len) - rb->read_index);
    }
    else if ((rb->status == RING_BUF_STATUS_FULL) || (rb->status == RING_BUF_STATUS_OVERFLOW))
    {
        temp_read_index = rb->write_index;
        data_valid_len = rb->len;
    }
    
    for(i = 0; (i < len) && (i < data_valid_len); i++)
    {
        buf[i] = rb->data[temp_read_index];
        temp_read_index = (temp_read_index + 1) % rb->len;
    }
    read_len = i;
		
    return read_len;
}

int ring_buffer_read_offset(ring_buffer_t *rb, int offset)
{
    short data_valid_len = 0;
    short real_offset = 0;
    
    if ((rb == NULL) || (rb->status == RING_BUF_STATUS_INVALID))
    {
        return RING_BUF_ERR_UNINIT;
    }
    
    if (offset == 0)
    {
        return RING_BUF_ERR_EMPTY;
    }
    
    if (rb->status == RING_BUF_STATUS_EMPTY)
    {
        return RING_BUF_ERR_EMPTY;
    }
    else if (rb->status == RING_BUF_STATUS_WORKABLE)
    {
        data_valid_len = ((rb->read_index < rb->write_index) ? (rb->write_index - rb->read_index) : ((rb->write_index + rb->len) - rb->read_index));
        real_offset = (data_valid_len < offset ? data_valid_len : offset);
        rb->read_index = (rb->read_index + real_offset) % rb->len;
        if (rb->read_index == rb->write_index)
        {
            rb->status = RING_BUF_STATUS_EMPTY;
        }
    }
    else if (rb->status == RING_BUF_STATUS_FULL)
    {
        real_offset = (rb->len < offset ? rb->len : offset);
        rb->read_index = (rb->read_index + real_offset) % rb->len;
        if (rb->read_index == rb->write_index)
        {
            rb->status = RING_BUF_STATUS_EMPTY;
        }
        else
        {
            rb->status = RING_BUF_STATUS_WORKABLE;
        }
    }
    else if (rb->status == RING_BUF_STATUS_OVERFLOW)
    {
        data_valid_len = ((rb->read_index < rb->write_index) ? (rb->write_index - rb->read_index) : ((rb->write_index + rb->len) - rb->read_index));
        if (data_valid_len < offset)
        {
            real_offset = ((rb->len + data_valid_len) < offset ? (rb->len + data_valid_len) : offset);
            rb->read_index = (rb->read_index + real_offset) % rb->len;
            if (rb->read_index == rb->write_index)
            {
                rb->status = RING_BUF_STATUS_EMPTY;
            }
            else
            {
                rb->status = RING_BUF_STATUS_WORKABLE;
            }
        }
        else
        {
            real_offset = offset;
            rb->read_index = (rb->read_index + real_offset) % rb->len;
            if (rb->read_index == rb->write_index)
            {
                rb->status = RING_BUF_STATUS_FULL;
            }
        }
    }
    
    return real_offset;
}

int ring_buffer_clear(ring_buffer_t *rb)
{
    if ((rb == NULL) || (rb->status == RING_BUF_STATUS_INVALID))
    {
        return RING_BUF_ERR_UNINIT;
    }
    
    rb->read_index = 0;
    rb->write_index = 0;
    rb->status = RING_BUF_STATUS_EMPTY;
    
    return RING_BUF_ERR_EMPTY;
}

int ring_buffer_strstr(ring_buffer_t *rb, char *str)
{
    int i = 0, j = 0;
    int find_res = 0;
    short temp_read_index = 0;
    short data_valid_len = 0;

    if ((rb == NULL) || (rb->status == RING_BUF_STATUS_INVALID))
    {
        return RING_BUF_ERR_UNINIT;
    }
    
    if (str == NULL || str[0] == '\0')
    {
        return RING_BUF_ERR_INVALID_DATA;
    }
    
    if (rb->status == RING_BUF_STATUS_EMPTY)
    {
        return RING_BUF_ERR_EMPTY;
    }
    else if(rb->status == RING_BUF_STATUS_WORKABLE)
    {
        temp_read_index = rb->read_index;
        data_valid_len = (rb->read_index < rb->write_index) ? (rb->write_index - rb->read_index) : ((rb->write_index + rb->len) - rb->read_index);
    }
    else if ((rb->status == RING_BUF_STATUS_FULL) || (rb->status == RING_BUF_STATUS_OVERFLOW))
    {
        temp_read_index = rb->write_index;
        data_valid_len = rb->len;
    }
    
    for(i = 0, j = 0; i < data_valid_len; i++)
    {
        if (rb->data[temp_read_index] == str[j])
        {
            j += 1;
            if (str[j] == '\0')
            {
                find_res = 1;
                break;
            }
        }
        else
        {
            j = 0;
        }
        temp_read_index = (temp_read_index + 1) % rb->len;
    }
    
    return find_res;
}

int ring_buffer_end(ring_buffer_t *rb, char *str)
{
    int find_res = 0;
    short temp_read_index = 0;
    short data_valid_len = 0;
    short str_len = 0;

    if ((rb == NULL) || (rb->status == RING_BUF_STATUS_INVALID))
    {
        return RING_BUF_ERR_UNINIT;
    }
    
    if (str == NULL || str[0] == '\0')
    {
        return RING_BUF_ERR_INVALID_DATA;
    }
    
    if (rb->status == RING_BUF_STATUS_EMPTY)
    {
        return RING_BUF_ERR_EMPTY;
    }
    else if(rb->status == RING_BUF_STATUS_WORKABLE)
    {
        data_valid_len = (rb->read_index < rb->write_index) ? (rb->write_index - rb->read_index) : ((rb->write_index + rb->len) - rb->read_index);
    }
    else if ((rb->status == RING_BUF_STATUS_FULL) || (rb->status == RING_BUF_STATUS_OVERFLOW))
    {
        data_valid_len = rb->len;
    }
    
    str_len = strlen(str);
    if (data_valid_len < str_len)
    {
        find_res = 0;
    }
    else
    {
        temp_read_index = rb->write_index - str_len;
        if (memcmp(&rb->data[temp_read_index], str, str_len) == 0)
        {
            find_res = 1;
        }
        else
        {
            find_res = 0;
        }
    }
    
    return find_res;
}

int ring_buffer_print(ring_buffer_t *rb)
{
    int i = 0, temp_index = 0;
    short temp_read_index = 0;
    short data_valid_len = 0;
    unsigned char str_data[24] = {0};

    if ((rb == NULL) || (rb->status == RING_BUF_STATUS_INVALID))
    {
        return RING_BUF_ERR_UNINIT;
    }
    
    if (rb->status == RING_BUF_STATUS_EMPTY)
    {
        return RING_BUF_ERR_EMPTY;
    }
    else if(rb->status == RING_BUF_STATUS_WORKABLE)
    {
        temp_read_index = rb->read_index;
        data_valid_len = (rb->read_index < rb->write_index) ? (rb->write_index - rb->read_index) : ((rb->write_index + rb->len) - rb->read_index);
    }
    else if ((rb->status == RING_BUF_STATUS_FULL) || (rb->status == RING_BUF_STATUS_OVERFLOW))
    {
        temp_read_index = rb->write_index;
        data_valid_len = rb->len;
    }
    
    printf("ring buf remain data: %d\n", data_valid_len);
    for(i = 0, temp_index = 0; i < data_valid_len; i++)
    {
        sprintf(&str_data[temp_index], "%02x ", (unsigned char)rb->data[temp_read_index]);
        temp_index += 3;
        if (temp_index == sizeof(str_data))
        {
            temp_index = sizeof(str_data) - 1;
            str_data[temp_index] = '\0';
            printf("%s\n", str_data);
            memset(str_data, 0, sizeof(str_data));
            temp_index = 0;
        }
        temp_read_index = (temp_read_index + 1) % rb->len;
    }
    if (temp_index > 0)
    {
        str_data[temp_index - 1] = '\0';
        printf("%s\n", str_data);
    }
    
    return 0;
}

int ring_buffer_is_empty(ring_buffer_t *rb)
{
    if ((rb == NULL) || (rb->status == RING_BUF_STATUS_INVALID))
    {
        return RING_BUF_ERR_UNINIT;
    }
    
    if (rb->status == RING_BUF_STATUS_EMPTY)
    {
        return 1;
    }
    
    return 0;
}