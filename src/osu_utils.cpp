#include "osu_utils.h"

Osu::db_t* Osu::LoadDB(const char* path)
{
    db_t* r_val = new db_t();
    bool success = r_val->FromFile(path);
    return success ? r_val : nullptr;
}

void Osu::FreeDB(db_t* db)
{
    if(db)
        delete db;
}
