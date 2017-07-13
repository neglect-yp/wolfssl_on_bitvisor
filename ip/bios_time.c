#include <core/timer.h>
#include <core/config.h>
#include <core/string.h>
#include "../core/asm.h"
#include "bios_time.h"

#define CMOS_ADDRESS    0x70
#define CMOS_DATA       0x71

struct datetime {
    u16 year;
    u8 month;
    u8 day;
    u8 hour;
    u8 minute;
    u8 second;
};

static const struct datetime UNIXTIME_REGION = {1970, 1, 1, 0, 0, 0};

static int get_update_in_progress_flag() {
    u8 data;
    
    asm_outb(CMOS_ADDRESS, 0x0A);
    asm_inb(CMOS_DATA, &data);

    return (data & 0x80);
}

static u8 get_rtc_register(int reg) {
    u8 data;

    asm_outb(CMOS_ADDRESS, reg);
    asm_inb(CMOS_DATA, &data);

    return data;
}

static bool is_equal(struct datetime *d1, struct datetime *d2) 
{
    return (d1->year == d2->year) && (d1->month == d2->month) && (d1->day == d2->day)
		&& (d1->hour == d2->hour) && (d1->minute == d2->minute) && (d1->second == d2->second);
}
	
static u32 leap_year_count(u32 year) {
    u32 leap_count = 0;

    // 97 times by 400 years
    leap_count += (year / 400) * 97;
    year = year % 400;
    // 24 times by 100 years
    leap_count += (year / 100) * 24;
    year = year % 100;
    // 1 time by 4 years;
    leap_count += (year / 4);

    return leap_count;
}

static u64 datetime_to_second(const struct datetime *datetime) {
    static const int day_count[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    u64 seconds = 0;
    u32 spend_days = 0;
    u32 i;

    for (i = 0; i < (datetime->month - 1); i++) {
	spend_days += day_count[i];
    }

    seconds +=  datetime->second;			// second
    seconds += (datetime->minute  * 60);		// minute -> second
    seconds += (datetime->hour    * 60 * 60);		// hour   -> second
    seconds += (datetime->day     * 60 * 60 * 24);	// day    -> second
    seconds += (spend_days * 60 * 60 * 24);		// month  -> spend_days -> second
    seconds += ((datetime->year * 365 + leap_year_count(datetime->year)) * 60 * 60 * 24);

    return seconds;
}

static void get_bios_datetime(struct datetime *getter) {

    struct datetime last_date;

    do {
	last_date = *getter;
    	// Make sure an update isn't in progress
    	while (get_update_in_progress_flag());

    	getter->second = get_rtc_register(0x00);
    	getter->minute = get_rtc_register(0x02);
        getter->hour   = get_rtc_register(0x04);
    	getter->day    = get_rtc_register(0x07);
    	getter->month  = get_rtc_register(0x08);
    	getter->year   = get_rtc_register(0x09);
    } while (is_equal(&last_date, getter));

    // Convert BCD to binary value if necessary
    if (!(get_rtc_register(0x0B) & 0x04)) {
	getter->second = (getter->second & 0x0F) + ((getter->second / 16) * 10);
	getter->minute = (getter->minute & 0x0F) + ((getter->minute / 16) * 10);
	getter->hour   = ((getter->hour  & 0x0F) + ((getter->hour & 0x70) / 16) * 10) | (getter->hour & 0x80);
	getter->day    = (getter->day    & 0x0F) + ((getter->day    / 16) * 10);
	getter->month  = (getter->month  & 0x0F) + ((getter->month  / 16) * 10);
	getter->year   = (getter->year   & 0x0F) + ((getter->year   / 16) * 10);
    }

    // bias to year
    getter->year += 2000;
}

time_t time(time_t *timer)
{
	struct datetime now;
    time_t result;

    get_bios_datetime(&now);
    result = datetime_to_second(&now) - datetime_to_second(&UNIXTIME_REGION);

    if (timer != NULL)
        *timer = result;

    return result;
}
