#ifndef _WATCH_DATA_H
#define _WATCH_DATA_H

#define WATCH_APP_CCID "898600D6991500012345"
#define WATCH_APP_CCID_LEN 20

#define NORDIC_SOFTWARE_VERSION "V1210"
#define NORDIC_SOFTWARE_VERSION_LEN 5

#define MT2621_SOFTWARE_VERSION "V1109"
#define MT2621_SOFTWARE_VERSION_LEN 5

extern void get_watch_device_ccid(unsigned char *ccid_buf);
extern void get_nordic_software_version(unsigned char *version_buf);
extern void get_mt2621_software_version(unsigned char *version_buf);
extern char get_watch_device_active_status(void);
extern void get_time_stamp(unsigned char *time_stamp);
extern unsigned char get_use_activity_type(void);
extern unsigned short get_use_activity_data_count(void);
extern unsigned int get_use_activity_start_time(void);
extern void get_gps_data(unsigned char *gps_buf);

#endif  //_WATCH_DATA_H