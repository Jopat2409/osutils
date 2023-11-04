#include <db.h>

#include <iostream>

Osu::db_t::~db_t()
{
    FREE_STR(playerName)
    if(beatmaps)
        delete[] beatmaps;
}

bool Osu::db_t::FromFile(const char* path)
{
    // Define the binfile used
    BinaryFile osuFile;
    if (!osuFile.Open(path))
    {
        std::cout << osuFile.GetLastError();
        return false;
    }

    // Load header metadata
    osuFile.LoadType<int_t>(osuVersion);
    osuFile.LoadType<int_t>(folderCount);
    osuFile.LoadType<byte_t>(isAccountUnlocked);
    osuFile.LoadType<long_t>(dateAccountUnlocked);
    osuFile.LoadString(playerName);
    osuFile.LoadType<int_t>(numBeatmaps);

    // Load and populate all beatmap
    beatmaps = new beatmap_t[numBeatmaps];
    for(int i = 0; i < numBeatmaps; i++)
    {
        beatmaps[i].LoadFromDbStream(osuFile, osuVersion);
    };


    // Load user permissions
    osuFile.LoadType<int_t>(userPerms);

    osuFile.Close();

    return true;
}
