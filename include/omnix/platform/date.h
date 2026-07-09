//
// Created by cakilgan on 4/10/26.
//

#ifndef OMNIX_DATE_H
#define OMNIX_DATE_H
#include "../platform/time.h"
#include "defines.h"
#include "types.h"

namespace ox {
    OX_USING(date_t, i32);
    struct date_default {
        date_t year;
        date_t month;
        date_t day;
        date_t hour;
        date_t minute;
    };
    struct date_detail {
        date_t second;
        date_t millisecond;
        date_t microsecond;
        date_t nanosecond;
    };
    struct date_absolute {
        date_default value{};
        date_detail detail{};
    };

    date_absolute date(const time &from);

    OX_FORCE_CONSTEXPR  time minutes(const time_t m) {
        return seconds(60) * m;
    }
    OX_FORCE_CONSTEXPR  timec_t minutes(const time &s) {
        return s.ns / seconds(60).ns;
    }
    OX_FORCE_CONSTEXPR  time hours(const time_t h) {
    return minutes(60) * h;
    }
    OX_FORCE_CONSTEXPR  timec_t hours(const time &h) {
    return h.ns / minutes(60).ns;
    }
} // namespace ox
#endif // OMNIX_DATE_H
