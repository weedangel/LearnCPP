
/**
 *  Copyright (c) 2016 Cenon(Shanghai) Co.,Ltd.All rights reserved.
 * 
 * @file    cenon_api.h
 * @brief   cenon api head file
 * 
 * @author  fxjang (yong-qiang.li@cenon.com.cn)
 * @date    2018-04-17
 * 
 * @history
 */

#ifndef _RING_BUF_H
#define _RING_BUF_H

#define START_YEAR 1970
#define END_YEAR 2099
#define MIN_SEC (60)
#define HOUR_SEC (MIN_SEC * 60)
#define DAY_SEC (HOUR_SEC * 24)
#define LEAP_LEAY_DAY 366
#define AVG_YEAR_DAY 365
#define LEAP_YEAR_SEC (LEAP_LEAY_DAY * DAY_SEC)
#define AVG_YEAR_SEC (AVG_YEAR_DAY * DAY_SEC)
#define LEAP_YEAR_MON 29
#define AVG_YEAR_MON 28
#define WEEK_MASK 3
#define WEEK_START 4
#define ONE_WEEK 7
  
#define RING_BUF_STATUS_INVALID   0    
#define RING_BUF_STATUS_EMPTY     1
#define RING_BUF_STATUS_WORKABLE  2
#define RING_BUF_STATUS_FULL      3
#define RING_BUF_STATUS_OVERFLOW  4

#define RING_BUF_OVERFLOW_DISABLE 0
#define RING_BUF_OVERFLOW_ENABLE  1

#define RING_BUF_OPT_1BYTE        (1)
#define RING_BUF_ERR_EMPTY        (0)
#define RING_BUF_ERR_UNINIT       (-1)
#define RING_BUF_ERR_FULL         (-2)
#define RING_BUF_ERR_OVERFLOW     (-3)
#define RING_BUF_ERR_INVALID_DATA (-4)

typedef struct ring_buffer {
    short write_index;
    short read_index;
    char status;
    char overflow;
    short len;
    char *data;
}ring_buffer_t;

extern void ring_buffer_init(ring_buffer_t *rb, char *data, short len, char overflow);

extern int ring_buffer_write_char(ring_buffer_t *rb, char data);
extern int ring_buffer_write_block(ring_buffer_t *rb, char *buf, int len);
extern int ring_buffer_write_block_ensure(ring_buffer_t *rb, char *buf, int len);

extern int ring_buffer_read_char(ring_buffer_t *rb, char *data);
extern int ring_buffer_read_block(ring_buffer_t *rb, char *buf, int len);
extern int ring_buffer_peek(ring_buffer_t *rb, char *buf, int len);

extern int ring_buffer_read_offset(ring_buffer_t *rb, int offset);
extern int ring_buffer_clear(ring_buffer_t *rb);
extern int ring_buffer_is_empty(ring_buffer_t *rb);

extern int ring_buffer_strstr(ring_buffer_t *rb, char *str);
extern int ring_buffer_end(ring_buffer_t *rb, char *str);

extern int ring_buffer_print(ring_buffer_t *rb);

#endif /* _RING_BUF_H */
