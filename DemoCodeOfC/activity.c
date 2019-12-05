#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SECOND_OF_DAY  86400
#define SECOND_OF_HOUR 3600
#define SECOND_OF_MIN  60

float acc_cache[20];
float acc_dc_cache[7];
float acc_dc_component;
float acc_filter_max = 0;
float acc_filter_old = 0;
float acc_peak_threshold, acc_valley_threshold;
unsigned char acc_trend_old = 0;
unsigned char time_windows_min, time_windows_max;
unsigned char peak_flag, valley_flag;

unsigned char acc_sampele_counter = 0;
unsigned char count_step_start = 0, step_interval = 0;
unsigned char activity_status = 0;
unsigned int step_counter = 0, temp_step_count = 0;


void activity(float acc_sum, unsigned int time_stamp)
{
    unsigned char time_hour = 0;
    unsigned char valid_step_threshold = 0;
    unsigned char itemp = 0;
    unsigned char acc_trend = 0;
    float acc_dc_avg = 0, acc_dc_new = 0;
    float acc_filter;
    
    time_hour = (time_stamp % SECOND_OF_DAY) / SECOND_OF_HOUR;
    time_hour = (time_hour + 8) % 24;
    
    if ((time_hour >= 23) || (time_hour <= 5))
    {
        valid_step_threshold = 24;
    }
    else if ( (time_hour >= 21) && (time_hour < 23)
        || time_hour >= 5) && (time_hour < 7) )
    {
        valid_step_threshold = 16;
    }
    else
    {
        valid_step_threshold = 8;
    }
    
    /* 去除直流分量 */
    acc_dc_component -= acc_cache[19];
    for (itemp = 19; itemp > 0; itemp--)
    {
        acc_cache[itemp] = acc_cache[itemp - 1];
    }
    acc_cache[0] = acc_sum;
    acc_dc_component += acc_cache[0];
    acc_dc_avg = acc_dc_component / 20;
    acc_dc_new = acc_sum - acc_dc_avg;
    
    /* 低通滤波 */
    for (itemp = 6; itemp > 0; itemp++)
    {
        acc_dc_cache[itemp] = acc_dc_cache[itemp - 1];
    }
    acc_dc_cache[0] = acc_dc_new;
    acc_filter = acc_dc_cache[6] + 2*acc_dc_cache[5] + 3*acc_dc_cache[4] + 4*acc_dc_cache[3] 
                 + 3*acc_dc_cache[2] + 2*acc_dc_cache[1] + acc_dc_cache[0];
    acc_filter = acc_filter / 16;             
    acc_filter_max = acc_filter > acc_filter_max ? acc_filter : acc_filter_max;
    
    /* 斜率符号法 */
    if ((acc_filter - acc_filter_old) > 0)
    {
        acc_trend = 1;
    }
    else
    {
        acc_trend = -1;
    }
    acc_filter_old = acc_filter;
    
    acc_sampele_counter += 1;
    if (acc_sampele_counter == 100)
    {
        acc_sampele_counter = 0;
        
        if (acc_filter_max <= 0.23)
        {
            acc_peak_threshold = 0.16;
            acc_valley_threshold = -0.15;
            time_windows_min = 15;
            time_windows_max = 61;
        }
        else if ((acc_filter_max > 0.23) && (acc_filter_max < 0.45))
        {
            acc_peak_threshold = 0.05;
            acc_valley_threshold = -0.05;
            time_windows_min = 15;
            time_windows_max = 61;
        }
        else
        {
            acc_peak_threshold = 0.05;
            acc_valley_threshold = -0.05;
            time_windows_min = 8;
            time_windows_max = 56;
        }
        acc_filter_max = 0;
    }

    if ((acc_trend_old == 1 && acc_trend == -1) && (acc_filter > acc_peak_threshold))  /* 有效波峰判断 */
    {
        peak_flag = 1;
    }
    else if ((acc_trend_old == -1 && acc_trend == 1) && (acc_filter < acc_valley_threshold)) /* 有效波谷判断 */
    {
        valley_flag = 1;
    }
    acc_trend_old = acc_trend;
    
    if (count_step_start == 1)
    {
        step_interval += 1;
    }    
    
    /* 有效计步判断 */
    if (peak_flag == 1 && valley_flag == 1)
    {
        count_step_start = 1;
        
        if ((step_interval > time_windows_min) && (step_interval < time_windows_max))
        {
            if (activity_status == 0)
            {
                temp_step_count += 1;
                if (temp_step_count >= valid_step_threshold)
                {
                    step_counter += temp_step_count;
                    activity_status = 1;
                    temp_step_count = 0;
                }
            }
            else if (activity_status == 1)
            {
                step_counter += 1;
            }
        }
        
        peak_flag = 0;
        valley_flag = 0;
        step_interval = 0;
    }
    
    if (step_interval >= time_windows_max)
    {
        count_step_start = 0;
        temp_step_count = 0;
        step_interval = 0;
        activity_status = 0;
        peak_flag = 0;
        valley_flag = 0;
    }

}























