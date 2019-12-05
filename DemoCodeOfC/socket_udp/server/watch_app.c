#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "watch_app.h"
#include "watch_data.h"

extern void send_data_func(int send_len, unsigned char *send_buf);

unsigned char calc_check_sum(unsigned char *data_buf, int data_len)
{
    unsigned char check_sum = 0;
    int i = 0;
    
    for (i = 0; i < data_len; i++)
    {
        check_sum = (check_sum + data_buf[i]) & 0xff;
    }
    
    return check_sum;    
}

int response_query_device_info(unsigned char *res_buf)
{
    short index = 0;
    unsigned char temp_data[20] = {0};
    
    res_buf[index++] = (FRAME_START >> 8) & 0xff;
    res_buf[index++] = FRAME_START & 0xff;
    
    res_buf[index++] = WATCH_APP_DEVICE;
    res_buf[index++] = MOBILE_APP_DEVICE;
    
    res_buf[index++] = RESERVED_DATA_BYTE;
    res_buf[index++] = RESERVED_DATA_BYTE;
    
    res_buf[index++] = (WATCH_DEVICE_INFO_DATA >> 8) & 0xff;
    res_buf[index++] = WATCH_DEVICE_INFO_DATA & 0xff;
    
    memset(temp_data, 0, 20);
    get_watch_device_ccid(temp_data);
    memcpy(&res_buf[index], temp_data, WATCH_APP_CCID_LEN);
    index += WATCH_APP_CCID_LEN;
    
    memset(temp_data, 0, 20);
    get_nordic_software_version(temp_data);
    memcpy(&res_buf[index], temp_data, NORDIC_SOFTWARE_VERSION_LEN);
    index += NORDIC_SOFTWARE_VERSION_LEN;
    
    memset(temp_data, 0, 20);
    get_mt2621_software_version(temp_data);
    memcpy(&res_buf[index], temp_data, MT2621_SOFTWARE_VERSION_LEN);
    index += MT2621_SOFTWARE_VERSION_LEN;
    
    res_buf[index++] = get_watch_device_active_status();
    
    memset(temp_data, 0, 20);
    get_time_stamp(temp_data);
    memcpy(&res_buf[index], temp_data, 4);
    index += 4;
    
    res_buf[4] = (index >> 8) & 0xff;
    res_buf[5] = index & 0xff;
    
    res_buf[index++] = calc_check_sum(res_buf, index);

    res_buf[index++] = (FRAME_END >> 8) & 0xff;
    res_buf[index++] = FRAME_END & 0xff;
    
    send_data_func(index, res_buf);
                       
    return index;
}

void show_recv_active_status_info(unsigned char *data_buf, int data_len)
{
    unsigned char temp_data[24] = {0};
    unsigned char temp_uchar = 0;
    unsigned int temp_uint = 0;
    short index = 8;
    short i = 0;
    
    memset(temp_data, 0, 24);
    memcpy(temp_data, &data_buf[index], 20);
    printf("device uuid: %s\n", temp_data);
    index += 20;
    
    temp_uchar = data_buf[index];
    printf("active status: %02x\n", temp_uchar);
    index += 1;
    
    temp_uchar = data_buf[index];
    printf("sex: %02x\n", temp_uchar);
    index += 1;
    
    temp_uchar = data_buf[index];
    printf("years: %d\n", temp_uchar);
    index += 1;
    
    temp_uchar = data_buf[index];
    printf("height: %d cm\n", temp_uchar);
    index += 1;
    
    temp_uchar = data_buf[index];
    printf("weight: %d kg\n", temp_uchar);
    index += 1;
    
    printf("emergency contact1:\n");
    for (i = 0; i < 16; i++)
    {
        printf("%02x ", data_buf[index]);
        index += 1;
    }
    printf("\n");
    
    printf("emergency contact2:\n");
    for (i = 0; i < 16; i++)
    {
        printf("%02x ", data_buf[index]);
        index += 1;
    }
    printf("\n");
    
    temp_uchar = data_buf[index];
    printf("Early warning coefficient: %d\n", temp_uchar);
    index += 1;
    
    temp_uchar = data_buf[index];
    printf("Reserved bytes1: %d\n", temp_uchar);
    index += 1;
    temp_uchar = data_buf[index];
    printf("Reserved bytes2: %d\n", temp_uchar);
    index += 1;
    
    for (i = 0; i < 4; i++)
    {
        temp_uint = (temp_uint << 8) | data_buf[index];
        index += 1;
    }
    printf("time stamp: %d\n", temp_uint);
}

int response_notify_device_active_status(unsigned char *res_buf)
{
    short index = 0;
    unsigned char temp_data[20] = {0};
    
    res_buf[index++] = (FRAME_START >> 8) & 0xff;
    res_buf[index++] = FRAME_START & 0xff;
    
    res_buf[index++] = WATCH_APP_DEVICE;
    res_buf[index++] = MOBILE_APP_DEVICE;
    
    res_buf[index++] = RESERVED_DATA_BYTE;
    res_buf[index++] = RESERVED_DATA_BYTE;
    
    res_buf[index++] = (WATCH_DEVCIE_ACTIVE_STATUS_DATA >> 8) & 0xff;
    res_buf[index++] = WATCH_DEVCIE_ACTIVE_STATUS_DATA & 0xff;
    
    memset(temp_data, 0, 20);
    get_watch_device_ccid(temp_data);
    memcpy(&res_buf[index], temp_data, WATCH_APP_CCID_LEN);
    index += WATCH_APP_CCID_LEN;
    
    res_buf[index++] = RECV_DATA_SUCCESS;
    
    memset(temp_data, 0, 20);
    get_time_stamp(temp_data);
    memcpy(&res_buf[index], temp_data, 4);
    index += 4;
    
    res_buf[4] = (index >> 8) & 0xff;
    res_buf[5] = index & 0xff;
    
    res_buf[index++] = calc_check_sum(res_buf, index);

    res_buf[index++] = (FRAME_END >> 8) & 0xff;
    res_buf[index++] = FRAME_END & 0xff;
    
    send_data_func(index, res_buf);
    
    return index;
}

void show_recv_clock_info(unsigned char *data_buf, int data_len)
{
    unsigned char temp_data[24] = {0};
    unsigned char clock_num = 0;
    unsigned char clock_hour = 0;
    unsigned char clock_min = 0;
    unsigned char clock_week = 0;
    unsigned int temp_uint = 0;
    short index = 8;
    short i = 0;
    
    memset(temp_data, 0, 24);
    memcpy(temp_data, &data_buf[index], 20);
    printf("device uuid: %s\n", temp_data);
    index += 20;
    
    clock_num = data_buf[index];
    printf("clock num: %d\n", clock_num);
    index += 1;
    
    for (i = 0; i < clock_num; i++)
    {
        clock_hour = data_buf[index];
        clock_min = data_buf[index+1];
        clock_week = data_buf[index+2];
        index += 3;
        printf("clock(%d): %d:%d week(%02x)\n", i+1, clock_hour, clock_min, clock_week);
    }
    
    for (i = 0; i < 4; i++)
    {
        temp_uint = (temp_uint << 8) | data_buf[index];
        index += 1;
    }
    printf("time stamp: %d\n", temp_uint);
}

int response_clock_info_msg(unsigned char *res_buf)
{
    short index = 0;
    short i = 0;
    unsigned char temp_data[20] = {0};
    
    res_buf[index++] = (FRAME_START >> 8) & 0xff;
    res_buf[index++] = FRAME_START & 0xff;
    
    res_buf[index++] = WATCH_APP_DEVICE;
    res_buf[index++] = MOBILE_APP_DEVICE;
    
    res_buf[index++] = RESERVED_DATA_BYTE;
    res_buf[index++] = RESERVED_DATA_BYTE;
    
    res_buf[index++] = (WATCH_DEVCIE_CLOCK_DATA >> 8) & 0xff;
    res_buf[index++] = WATCH_DEVCIE_CLOCK_DATA & 0xff;
    
    memset(temp_data, 0, 20);
    get_watch_device_ccid(temp_data);
    memcpy(&res_buf[index], temp_data, WATCH_APP_CCID_LEN);
    index += WATCH_APP_CCID_LEN;
    
    res_buf[index++] = RECV_DATA_SUCCESS;
    
    for (i = 0; i < 20; i++)
    {
        res_buf[index++] = RESERVED_DATA_BYTE;
    }
    
    memset(temp_data, 0, 20);
    get_time_stamp(temp_data);
    memcpy(&res_buf[index], temp_data, 4);
    index += 4;
    
    res_buf[4] = (index >> 8) & 0xff;
    res_buf[5] = index & 0xff;
    
    res_buf[index++] = calc_check_sum(res_buf, index);

    res_buf[index++] = (FRAME_END >> 8) & 0xff;
    res_buf[index++] = FRAME_END & 0xff;
    
    send_data_func(index, res_buf);
    
    return index;
}

void show_recv_sit_long_data(unsigned char *data_buf, int data_len)
{
    unsigned char temp_data[24] = {0};
    unsigned char time_hour = 0;
    unsigned char time_min = 0;
    unsigned char temp_uchar = 0;
    unsigned int temp_uint = 0;
    short index = 8;
    short i = 0;
    
    memset(temp_data, 0, 24);
    memcpy(temp_data, &data_buf[index], 20);
    printf("device uuid: %s\n", temp_data);
    index += 20;
    
    time_hour = data_buf[index];
    time_min = data_buf[index+1];
    printf("start time: %d:%d\n", time_hour, time_min);
    index += 2;
    
    time_hour = data_buf[index];
    time_min = data_buf[index+1];
    printf("end time: %d:%d\n", time_hour, time_min);
    index += 2;
    
    temp_uchar = data_buf[index];
    printf("noon time enable: %d\n", temp_uchar);
    index += 1;
    
    for (i = 0; i < 4; i++)
    {
        temp_uint = (temp_uint << 8) | data_buf[index];
        index += 1;
    }
    printf("time stamp: %d\n", temp_uint);
}

int response_sit_long_info_msg(unsigned char *res_buf)
{
    short index = 0;
    short i = 0;
    unsigned char temp_data[20] = {0};
    
    res_buf[index++] = (FRAME_START >> 8) & 0xff;
    res_buf[index++] = FRAME_START & 0xff;
    
    res_buf[index++] = WATCH_APP_DEVICE;
    res_buf[index++] = MOBILE_APP_DEVICE;
    
    res_buf[index++] = RESERVED_DATA_BYTE;
    res_buf[index++] = RESERVED_DATA_BYTE;
    
    res_buf[index++] = (WATCH_DEVCIE_SITLONG_DATA >> 8) & 0xff;
    res_buf[index++] = WATCH_DEVCIE_SITLONG_DATA & 0xff;
    
    memset(temp_data, 0, 20);
    get_watch_device_ccid(temp_data);
    memcpy(&res_buf[index], temp_data, WATCH_APP_CCID_LEN);
    index += WATCH_APP_CCID_LEN;
    
    res_buf[index++] = RECV_DATA_SUCCESS;
    
    for (i = 0; i < 20; i++)
    {
        res_buf[index++] = RESERVED_DATA_BYTE;
    }
    
    memset(temp_data, 0, 20);
    get_time_stamp(temp_data);
    memcpy(&res_buf[index], temp_data, 4);
    index += 4;
    
    res_buf[4] = (index >> 8) & 0xff;
    res_buf[5] = index & 0xff;
    
    res_buf[index++] = calc_check_sum(res_buf, index);

    res_buf[index++] = (FRAME_END >> 8) & 0xff;
    res_buf[index++] = FRAME_END & 0xff;
    
    send_data_func(index, res_buf);
    
    return index;
}

void show_recv_heart_rate_base_data(unsigned char *data_buf, int data_len)
{
    unsigned char temp_data[24] = {0};
    unsigned char temp_uchar = 0;
    unsigned int temp_uint = 0;
    short index = 8;
    short i = 0;
    
    memset(temp_data, 0, 24);
    memcpy(temp_data, &data_buf[index], 20);
    printf("device uuid: %s\n", temp_data);
    index += 20;
    
    printf("heart rate base: ");
    /* normal data is 800bytes, test only use 8bytes */
    for (i = 0; i < 8; i++)
    {
        temp_uchar = data_buf[index];
        printf("%02x ", temp_uchar);
        index += 1;
    }
    printf("\n");
    
    /* normal data have 20 reserved bytes, test not it */
    
    for (i = 0; i < 4; i++)
    {
        temp_uint = (temp_uint << 8) | data_buf[index];
        index += 1;
    }
    printf("time stamp: %d\n", temp_uint);
}

int response_heart_rate_base_msg(unsigned char *res_buf)
{
    short index = 0;
    short i = 0;
    unsigned char temp_data[20] = {0};
    
    res_buf[index++] = (FRAME_START >> 8) & 0xff;
    res_buf[index++] = FRAME_START & 0xff;
    
    res_buf[index++] = WATCH_APP_DEVICE;
    res_buf[index++] = MOBILE_APP_DEVICE;
    
    res_buf[index++] = RESERVED_DATA_BYTE;
    res_buf[index++] = RESERVED_DATA_BYTE;
    
    res_buf[index++] = (WATCH_DEVCIE_HEARTRATE_DATA >> 8) & 0xff;
    res_buf[index++] = WATCH_DEVCIE_HEARTRATE_DATA & 0xff;
    
    memset(temp_data, 0, 20);
    get_watch_device_ccid(temp_data);
    memcpy(&res_buf[index], temp_data, WATCH_APP_CCID_LEN);
    index += WATCH_APP_CCID_LEN;
    
    res_buf[index++] = RECV_DATA_SUCCESS;
    
    for (i = 0; i < 20; i++)
    {
        res_buf[index++] = RESERVED_DATA_BYTE;
    }
    
    memset(temp_data, 0, 20);
    get_time_stamp(temp_data);
    memcpy(&res_buf[index], temp_data, 4);
    index += 4;
    
    res_buf[4] = (index >> 8) & 0xff;
    res_buf[5] = index & 0xff;
    
    res_buf[index++] = calc_check_sum(res_buf, index);

    res_buf[index++] = (FRAME_END >> 8) & 0xff;
    res_buf[index++] = FRAME_END & 0xff;
    
    send_data_func(index, res_buf);
    
    return index;
}

void show_call_reminder_info(unsigned char *data_buf, int data_len)
{
    unsigned char temp_data[24] = {0};
    unsigned char temp_uchar = 0;
    unsigned int temp_uint = 0;
    short index = 8;
    short i = 0;
    
    memset(temp_data, 0, 24);
    memcpy(temp_data, &data_buf[index], 20);
    printf("device uuid: %s\n", temp_data);
    index += 20;
    
    printf("phone number: ");
    for (i = 0; i < 16; i++)
    {
        temp_uchar = data_buf[index];
        printf("%02x ", temp_uchar);
        index += 1;
    }
    printf("\n");
    
    temp_uchar = data_buf[index];
    printf("Phone status: %02x\n", temp_uchar);
    index += 1;
    
    for (i = 0; i < 4; i++)
    {
        temp_uint = (temp_uint << 8) | data_buf[index];
        index += 1;
    }
    printf("time stamp: %d\n", temp_uint);
}

int response_call_reminder_info(unsigned char *res_buf)
{
    short index = 0;
    short i = 0;
    unsigned char temp_data[20] = {0};
    
    res_buf[index++] = (FRAME_START >> 8) & 0xff;
    res_buf[index++] = FRAME_START & 0xff;
    
    res_buf[index++] = WATCH_APP_DEVICE;
    res_buf[index++] = MOBILE_APP_DEVICE;
    
    res_buf[index++] = RESERVED_DATA_BYTE;
    res_buf[index++] = RESERVED_DATA_BYTE;
    
    res_buf[index++] = (WATCH_DEVCIE_CALL_REMINDER_DATA >> 8) & 0xff;
    res_buf[index++] = WATCH_DEVCIE_CALL_REMINDER_DATA & 0xff;
    
    memset(temp_data, 0, 20);
    get_watch_device_ccid(temp_data);
    memcpy(&res_buf[index], temp_data, WATCH_APP_CCID_LEN);
    index += WATCH_APP_CCID_LEN;
    
    res_buf[index++] = 0x02;  //answer phone
    
    memset(temp_data, 0, 20);
    get_time_stamp(temp_data);
    memcpy(&res_buf[index], temp_data, 4);
    index += 4;
    
    res_buf[4] = (index >> 8) & 0xff;
    res_buf[5] = index & 0xff;
    
    res_buf[index++] = calc_check_sum(res_buf, index);

    res_buf[index++] = (FRAME_END >> 8) & 0xff;
    res_buf[index++] = FRAME_END & 0xff;
    
    send_data_func(index, res_buf);
    
    return index;
}

void show_recv_msg_info(unsigned char *data_buf, int data_len)
{
    unsigned char temp_data[152] = {0};
    unsigned char temp_uchar = 0;
    unsigned char msg_num = 0;
    unsigned int temp_uint = 0;
    short index = 8;
    short i = 0;
    
    memset(temp_data, 0, 24);
    memcpy(temp_data, &data_buf[index], 20);
    printf("device uuid: %s\n", temp_data);
    index += 20;
      
    msg_num = data_buf[index];
    printf("msg_num: %02x\n", temp_uchar);
    index += 1;
    
    for (i = 0; i < msg_num; i++)
    {
        memset(temp_data, 0, 152);
        memcpy(temp_data, &data_buf[index], 152);
        printf("device uuid: %s\n", temp_data);
        index += 150;
    }
    
    for (i = 0; i < 4; i++)
    {
        temp_uint = (temp_uint << 8) | data_buf[index];
        index += 1;
    }
    printf("time stamp: %d\n", temp_uint);
}

int response_msg_reminder_info(unsigned char *res_buf)
{
    short index = 0;
    short i = 0;
    unsigned char temp_data[20] = {0};
    
    res_buf[index++] = (FRAME_START >> 8) & 0xff;
    res_buf[index++] = FRAME_START & 0xff;
    
    res_buf[index++] = WATCH_APP_DEVICE;
    res_buf[index++] = MOBILE_APP_DEVICE;
    
    res_buf[index++] = RESERVED_DATA_BYTE;
    res_buf[index++] = RESERVED_DATA_BYTE;
    
    res_buf[index++] = (WATCH_DEVCIE_MSG_REMINDER_DATA >> 8) & 0xff;
    res_buf[index++] = WATCH_DEVCIE_MSG_REMINDER_DATA & 0xff;
    
    memset(temp_data, 0, 20);
    get_watch_device_ccid(temp_data);
    memcpy(&res_buf[index], temp_data, WATCH_APP_CCID_LEN);
    index += WATCH_APP_CCID_LEN;
    
    res_buf[index++] = 0x01;  //recieve mesage success
    
    memset(temp_data, 0, 20);
    get_time_stamp(temp_data);
    memcpy(&res_buf[index], temp_data, 4);
    index += 4;
    
    res_buf[4] = (index >> 8) & 0xff;
    res_buf[5] = index & 0xff;
    
    res_buf[index++] = calc_check_sum(res_buf, index);

    res_buf[index++] = (FRAME_END >> 8) & 0xff;
    res_buf[index++] = FRAME_END & 0xff;
    
    send_data_func(index, res_buf);
    
    return index;
}

int response_query_watch_motion_info(unsigned char *res_buf)
{
    short index = 0;
    short i = 0;
    unsigned char temp_data[20] = {0};
    unsigned short data_count = 0;
    unsigned int start_time = 0;
    
    res_buf[index++] = (FRAME_START >> 8) & 0xff;
    res_buf[index++] = FRAME_START & 0xff;
    
    res_buf[index++] = WATCH_APP_DEVICE;
    res_buf[index++] = MOBILE_APP_DEVICE;
    
    res_buf[index++] = RESERVED_DATA_BYTE;
    res_buf[index++] = RESERVED_DATA_BYTE;
    
    res_buf[index++] = (WATCH_DEVCIE_MOTION_INFO_DATA >> 8) & 0xff;
    res_buf[index++] = WATCH_DEVCIE_MOTION_INFO_DATA & 0xff;
    
    memset(temp_data, 0, 20);
    get_watch_device_ccid(temp_data);
    memcpy(&res_buf[index], temp_data, WATCH_APP_CCID_LEN);
    index += WATCH_APP_CCID_LEN;
    
    res_buf[index++] = get_use_activity_type();
    
    data_count = get_use_activity_data_count();
    res_buf[index++] = (data_count >> 8) & 0xff;
    res_buf[index++] = data_count & 0xff;
    
    start_time = get_use_activity_start_time();
    res_buf[index++] = (start_time >> 24) & 0xff;
    res_buf[index++] = (start_time >> 16) & 0xff;
    res_buf[index++] = (start_time >> 8) & 0xff;
    res_buf[index++] = start_time & 0xff; 
    
    memset(temp_data, 0, 20);
    get_time_stamp(temp_data);
    memcpy(&res_buf[index], temp_data, 4);
    index += 4;
    
    res_buf[4] = (index >> 8) & 0xff;
    res_buf[5] = index & 0xff;
    
    res_buf[index++] = calc_check_sum(res_buf, index);

    res_buf[index++] = (FRAME_END >> 8) & 0xff;
    res_buf[index++] = FRAME_END & 0xff;
    
    send_data_func(index, res_buf);
    
    return index;
}

int response_query_watch_motion_data(unsigned char *res_buf)
{
    short index = 0, group_index = 1;
    short i = 0;
    unsigned char temp_data[20] = {0};
    unsigned short data_count = 0;
    unsigned int data_stamp = 0;
    
    data_count = get_use_activity_data_count();
    
    while (group_index <= data_count)
    {
        index = 0;
        res_buf[index++] = (FRAME_START >> 8) & 0xff;
        res_buf[index++] = FRAME_START & 0xff;
        
        res_buf[index++] = WATCH_APP_DEVICE;
        res_buf[index++] = MOBILE_APP_DEVICE;
        
        res_buf[index++] = RESERVED_DATA_BYTE;
        res_buf[index++] = RESERVED_DATA_BYTE;
        
        res_buf[index++] = (WATCH_DEVCIE_MOTION_DATA >> 8) & 0xff;
        res_buf[index++] = WATCH_DEVCIE_MOTION_DATA & 0xff;
        
        memset(temp_data, 0, 20);
        get_watch_device_ccid(temp_data);
        memcpy(&res_buf[index], temp_data, WATCH_APP_CCID_LEN);
        index += WATCH_APP_CCID_LEN;
        
        for ( i = 0; i < 10 && group_index <= data_count; i++)
        {
            res_buf[index++] = (group_index >> 8) & 0xff;
            res_buf[index++] = group_index & 0xff;
            group_index += 1;
            
            res_buf[index++] = RESERVED_DATA_BYTE;
            res_buf[index++] = RESERVED_DATA_BYTE;
            
            res_buf[index++] = RESERVED_DATA_BYTE;
            
            res_buf[index++] = RESERVED_DATA_BYTE;
            res_buf[index++] = RESERVED_DATA_BYTE;
            
            get_gps_data(&res_buf[index]);
            index += 21;
            
            data_stamp = group_index * 2 + 1559533832;
            res_buf[index++] = (data_stamp >> 24) & 0xff;
            res_buf[index++] = (data_stamp >> 16) & 0xff;
            res_buf[index++] = (data_stamp >> 8) & 0xff;
            res_buf[index++] = data_stamp & 0xff;
        }
        
        memset(temp_data, 0, 20);
        get_time_stamp(temp_data);
        memcpy(&res_buf[index], temp_data, 4);
        index += 4;
        
        res_buf[4] = (index >> 8) & 0xff;
        res_buf[5] = index & 0xff;
        
        res_buf[index++] = calc_check_sum(res_buf, index);
        
        res_buf[index++] = (FRAME_END >> 8) & 0xff;
        res_buf[index++] = FRAME_END & 0xff;
        
        send_data_func(index, res_buf);
        printf("group_index: %d\n", group_index);
    }
    
    return index;
}

int response_query_watch_motion_result(unsigned char *res_buf)
{
    short index = 0;
    short i = 0;
    unsigned char temp_data[20] = {0};
    unsigned short ushort_temp = 0;
    unsigned int start_time = 0;
    
    res_buf[index++] = (FRAME_START >> 8) & 0xff;
    res_buf[index++] = FRAME_START & 0xff;
    
    res_buf[index++] = WATCH_APP_DEVICE;
    res_buf[index++] = MOBILE_APP_DEVICE;
    
    res_buf[index++] = RESERVED_DATA_BYTE;
    res_buf[index++] = RESERVED_DATA_BYTE;
    
    res_buf[index++] = (WATCH_DEVCIE_MOTION_RESULT_DATA >> 8) & 0xff;
    res_buf[index++] = WATCH_DEVCIE_MOTION_RESULT_DATA & 0xff;
    
    memset(temp_data, 0, 20);
    get_watch_device_ccid(temp_data);
    memcpy(&res_buf[index], temp_data, WATCH_APP_CCID_LEN);
    index += WATCH_APP_CCID_LEN;
    
    res_buf[index++] = get_use_activity_type();
    
    ushort_temp = 0x001e;  //Walking distance 0.1km
    res_buf[index++] = (ushort_temp >> 8) & 0xff;
    res_buf[index++] = ushort_temp & 0xff;
    
    ushort_temp = 0x0e10;  //use time(s)
    res_buf[index++] = (ushort_temp >> 8) & 0xff;
    res_buf[index++] = ushort_temp & 0xff;
    
    res_buf[index++] = 0x64;  //max heart rate 100
    res_buf[index++] = 0x3c;  //min heart rate 60
    res_buf[index++] = 0x4b;  //avr heart rate 75
    
    ushort_temp = 0x1234;  //cal
    res_buf[index++] = (ushort_temp >> 8) & 0xff;
    res_buf[index++] = ushort_temp & 0xff;
    
    ushort_temp = 0x5678;  //speed
    res_buf[index++] = (ushort_temp >> 8) & 0xff;
    res_buf[index++] = ushort_temp & 0xff;
    
    res_buf[index++] = 0x3c;   // 60 step/min
    res_buf[index++] = 0x20;   // 32 cm/step
    
    ushort_temp = 0x0110;  //rise (m)
    res_buf[index++] = (ushort_temp >> 8) & 0xff;
    res_buf[index++] = ushort_temp & 0xff;
    
    ushort_temp = 0x0220;  //down (m)
    res_buf[index++] = (ushort_temp >> 8) & 0xff;
    res_buf[index++] = ushort_temp & 0xff;
    
    res_buf[index++] = 0x00;  //no other motion data
    
    start_time = get_use_activity_start_time();
    res_buf[index++] = (start_time >> 24) & 0xff;
    res_buf[index++] = (start_time >> 16) & 0xff;
    res_buf[index++] = (start_time >> 8) & 0xff;
    res_buf[index++] = start_time & 0xff; 
      
    memset(temp_data, 0, 20);
    get_time_stamp(temp_data);
    memcpy(&res_buf[index], temp_data, 4);
    index += 4;
    
    res_buf[4] = (index >> 8) & 0xff;
    res_buf[5] = index & 0xff;
    
    res_buf[index++] = calc_check_sum(res_buf, index);

    res_buf[index++] = (FRAME_END >> 8) & 0xff;
    res_buf[index++] = FRAME_END & 0xff;
    
    send_data_func(index, res_buf);
    
    return index;
}

int process_recv_cmd_info(unsigned char *data_buf, int data_len)
{
    unsigned short cmd = 0;
    unsigned char res_buf[512] = {0};
    int res_data_len = 0;
    
    cmd = (data_buf[6] << 8) | data_buf[7];
    printf("cmd: %04x\n", cmd);
    switch(cmd)
    {
    case QUERY_WATCH_DEVICE_INFO:
        res_data_len = response_query_device_info(res_buf);
        break;
    case NOTIFY_WATCH_NORMAL_DATA:
        break;
    case UPGRADE_WATCH_APP_DATA:
        break;
    case NOTIFY_WATCH_SLEEP_DATA:
        break;
    case NOTIFY_WATCH_HEARTRATE_BASE:
        show_recv_heart_rate_base_data(data_buf, data_len);
        res_data_len = response_heart_rate_base_msg(res_buf);
        break;
    case NOTIFY_WATCH_REALTIME_DATA:
        break;
    case NOTIFY_WATCH_CLOCK_DATA:
        show_recv_clock_info(data_buf, data_len);
        res_data_len = response_clock_info_msg(res_buf);
        break;
    case NOTIFY_WATCH_SITLONG_DATA:
        show_recv_sit_long_data(data_buf, data_len);
        res_data_len = response_sit_long_info_msg(res_buf);
        break;
    case NOTIFY_WATCH_ACTIVE_STATUS: 
        show_recv_active_status_info(data_buf, data_len);
        res_data_len = response_notify_device_active_status(res_buf);
        break;
    case QUERY_WATCH_MOTION_INFO:
        res_data_len = response_query_watch_motion_info(res_buf);
        break;
    case QUERY_WATCH_MOTION_DATA:
        res_data_len = response_query_watch_motion_data(res_buf);
        break;
    case QUERY_WATCH_MOTION_RESULT:
        res_data_len = response_query_watch_motion_result(res_buf);
        break;
    case NOTIFY_WATCH_CALL_REMINDER:
        show_call_reminder_info(data_buf, data_len);
        res_data_len = response_call_reminder_info(res_buf);
        break;
    case NOTIFY_WATCH_MSG_REMINDER:
        show_recv_msg_info(data_buf, data_len);
        res_data_len = response_msg_reminder_info(res_buf);
        break;
    default:
        printf("Invalid command\n");
        break;
    }
    
    return res_data_len;
}

int one_complete_frame_check(unsigned char *data_buf, int data_len)
{
    int frame_check = -1;
    unsigned char check_sum = 0;
    
    if ( data_buf[0] == ((FRAME_START >> 8) & 0xff)
        && data_buf[1] == (FRAME_START & 0xff)
        && data_buf[data_len - 2] == ((FRAME_END >> 8) & 0xff)
        && data_buf[data_len - 1] == (FRAME_END & 0xff) )
    {
        check_sum = calc_check_sum(data_buf, data_len - 3);
        printf("check sum: %02x, recv sum: %02x\n", check_sum, data_buf[data_len - 3]);
        if (check_sum == data_buf[data_len - 3])
        {
            frame_check = 1;
        }
        else
        {
            printf("Frame check sum error!\n");
            frame_check = 0;
        }
    }
    else
    {
        printf("data frame is not complete!\n");
        frame_check = 0;
    }
    
    return frame_check;
}
