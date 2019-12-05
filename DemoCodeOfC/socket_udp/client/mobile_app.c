#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "mobile_app.h"
#include "mobile_data.h"

unsigned char calc_check_sum(char *data_buf, int data_len)
{
    unsigned char check_sum = 0;
    int i = 0;
    
    for (i = 0; i < data_len; i++)
    {
        check_sum = (check_sum + data_buf[i]) & 0xff;
    }
    
    return check_sum;    
}

int one_complete_frame_check(char *data_buf, int data_len)
{
    int frame_check = -1;
    unsigned char check_sum = 0;
    
    if ( data_buf[0] == ((FRAME_START >> 8) & 0xff)
        && data_buf[1] == (FRAME_START & 0xff)
        && data_buf[data_len - 2] == ((FRAME_END >> 8) & 0xff)
        && data_buf[data_len - 1] == (FRAME_END & 0xff) )
    {
        check_sum = calc_check_sum(data_buf, data_len - 3);
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

int response_query_device_info(char *res_buf)
{
    short index = 0;
    char temp_data[20] = {0};
    
    res_buf[index++] = (FRAME_START >> 8) & 0xff;
    res_buf[index++] = FRAME_START & 0xff;
    
    res_buf[index++] = WATCH_APP_DEVICE;
    res_buf[index++] = MOBILE_APP_DEVICE;
    
    res_buf[index++] = RESERVED_DATA_BYTE;
    res_buf[index++] = RESERVED_DATA_BYTE;
    
    res_buf[index++] = WATCH_DEVICE_INFO_DATA;
    
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
    
    res_buf[index++] = calc_check_sum(res_buf, index);
    
    res_buf[4] = (index >> 8) & 0xff;
    res_buf[5] = index & 0xff;
    
    res_buf[index++] = (FRAME_END >> 8) & 0xff;
    res_buf[index++] = FRAME_END & 0xff;
                       
    return index;
}

int process_recv_cmd_info(char *data_buf, int data_len, char *res_buf)
{
    unsigned short cmd = 0;
    int res_data_len = 0;
    
    cmd = (data_buf[6] << 8) && data_buf[7];
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
        break;
    case NOTIFY_WATCH_REALTIME_DATA:
        break;
    case NOTIFY_WATCH_CLOCK_DATA:
        break;
    case NOTIFY_WATCH_SITLONG_DATA:
        break;
    case QUERY_WATCH_ACTIVE_STATUS: 
        break;
    case QUERY_WATCH_MOTION_DATA:
        break;
    case NOTIFY_WATCH_CALL_REMINDER:
        break;
    case NOTIFY_WATCH_MSG_REMINDER:
        break;
    case NOTIFY_WATCH_MOTION_RESULT:
        break;
    default:
        printf("Invalid command\n");
        break;
    }
    
    return res_data_len;
}
