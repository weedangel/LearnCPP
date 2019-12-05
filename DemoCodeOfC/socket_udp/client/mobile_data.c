#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "mobile_data.h"

void get_watch_device_ccid(char *ccid_buf)
{
    memcpy(ccid_buf, WATCH_APP_CCID, WATCH_APP_CCID_LEN);    
}

void get_nordic_software_version(char *version_buf)
{
    memcpy(version_buf, NORDIC_SOFTWARE_VERSION, NORDIC_SOFTWARE_VERSION_LEN);
}

void get_mt2621_software_version(char *version_buf)
{
    memcpy(version_buf, MT2621_SOFTWARE_VERSION, MT2621_SOFTWARE_VERSION_LEN);
}

char get_watch_device_active_status(void)
{
    char active_status = 0x00;  //active: 0x00  not active: 0x01
    
    return active_status;  
}

void get_time_stamp(char *time_stamp)
{
    unsigned int cur_time = 0;
    
	cur_time = (unsigned int)time(NULL);
    printf("cur_time_stamp: %d\n", cur_time);
    
    time_stamp[0] = (cur_time >> 24) & 0xff;
    time_stamp[1] = (cur_time >> 16) & 0xff;
    time_stamp[2] = (cur_time >> 8) & 0xff;
    time_stamp[3] = cur_time & 0xff;    
}