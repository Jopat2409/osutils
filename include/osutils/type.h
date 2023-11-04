#ifndef _INTERNAL_TYPE_H
#define _INTERNAL_TYPE_H

#include <cstdint>
#include <unordered_map>

namespace Osu
{
    typedef unsigned char byte_t;
    typedef int16_t short_t;
    typedef int32_t int_t;
    typedef int64_t long_t;

    typedef float float_t;
    typedef double double_t;

    typedef std::unordered_map<int_t, double_t> int_double_t;
    struct timing_point_t
    {
        double_t bpm;
        double_t offset;
        byte_t inherited;
    };
}

#define OSU_STRING_PRESENT_BYTE 0x0b

#define OSU_MOD_NONE 0
#define OSU_MOD_NOFAIL (1<<0)
#define OSU_MOD_EASY (1<<1)
#define OSU_MOD_TOUCHSCREEN (1<<2)
#define OSU_MOD_HIDDEN (1<<3)
#define OSU_MOD_HARDROCK (1<<4)
#define OSU_MOD_SUDDENDEATH (1<<5)
#define OSU_MOD_DOUBLETIME (1<<6)
#define OSU_MOD_RELAX (1<<7)
#define OSU_MOD_HALFTIME (1<<8)
#define OSU_MOD_NIGHTCORE (1<<9)
#define OSU_MOD_FLASHLIGHT (1<<10)
#define OSU_MOD_AUTOPLAY (1<<11)
#define OSU_MOD_SPUNOUT (1<<12)


#endif
