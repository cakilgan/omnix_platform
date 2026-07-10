//
// Created by cakilgan on 7/10/26.
//

#ifndef OMNIX_PLATFORM_TIMER_H
#define OMNIX_PLATFORM_TIMER_H
#include "time.h"
namespace ox {
    template<typename Clock = clocks::monotonic>
    struct timer {
        timer(){reset();}
        time elapsed() const {return now<Clock>()-cursor;}
        time reset() {
            const auto temp = cursor;
            cursor = now<Clock>();
            return temp;
        }
    private:
        time cursor;
    };
}
#endif //OMNIX_PLATFORM_TIMER_H
