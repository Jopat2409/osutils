#ifndef _INTERNAL_DB_H
#define _INTERNAL_DB_H

#include "beatmap.h"

namespace Osu
{
    struct db_t
    {
        int_t osuVersion;
        int_t folderCount;
        byte_t isAccountUnlocked;
        long_t dateAccountUnlocked;
        char* playerName;
        int_t numBeatmaps;
        int_t userPerms;

        beatmap_t* beatmaps;

        ~db_t();
        bool FromFile(const char* path);
    };
}


#endif