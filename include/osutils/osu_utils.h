#ifndef _EXTERNAL_UTILS_H
#define _EXTERNAL_UTILS_H

#include "type.h"
#include "db.h"
#include "beatmap.h"

#include <osutils_export.h>

namespace Osu
{
#ifdef __cplusplus
    extern "C" {
#endif
        OSU_API db_t* LoadDB(const char* path);
        OSU_API void FreeDB(db_t* db);

#ifdef __cplusplus
    }
#endif
}



#endif
