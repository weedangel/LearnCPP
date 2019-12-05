#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "watch_data.h"

void get_watch_device_ccid(unsigned char *ccid_buf)
{
    memcpy(ccid_buf, WATCH_APP_CCID, WATCH_APP_CCID_LEN);    
}

void get_nordic_software_version(unsigned char *version_buf)
{
    memcpy(version_buf, NORDIC_SOFTWARE_VERSION, NORDIC_SOFTWARE_VERSION_LEN);
}

void get_mt2621_software_version(unsigned char *version_buf)
{
    memcpy(version_buf, MT2621_SOFTWARE_VERSION, MT2621_SOFTWARE_VERSION_LEN);
}

char get_watch_device_active_status(void)
{
    char active_status = 0x00;  //active: 0x00  not active: 0x01
    
    return active_status;  
}

void get_time_stamp(unsigned char *time_stamp)
{
    unsigned int cur_time = 0;
    
	cur_time = (unsigned int)time(NULL);
    //printf("cur_time_stamp: %d\n", cur_time);
    
    time_stamp[0] = (cur_time >> 24) & 0xff;
    time_stamp[1] = (cur_time >> 16) & 0xff;
    time_stamp[2] = (cur_time >> 8) & 0xff;
    time_stamp[3] = cur_time & 0xff;    
}

unsigned char get_use_activity_type(void)
{
    unsigned char act_type = 0;
    
    act_type = 0x02; //0x01: 室内运动  0x02:室外运动  0x03:健走
    
    return act_type;
}

unsigned short get_use_activity_data_count(void)
{
    unsigned short data_count = 18;
    
    return data_count;    
}

unsigned int get_use_activity_start_time(void)
{
    unsigned int start_time = 0;
    
    start_time = (unsigned int)time(NULL);
    
    return start_time;    
}

void get_gps_data(unsigned char *gps_buf)
{
    int i = 0;
    
    for (i = 0; i < 21; i++)
    {
        gps_buf[i] = 0x00;        
    }
}