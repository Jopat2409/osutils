#include <beatmap.h>
#include <iostream>

Osu::beatmap_t::~beatmap_t()
{
    // Ensure that each string exists (ie not nullptr) then free them
    FREE_STR(artistName);
	FREE_STR(artistNameUnicode);
	FREE_STR(songTitle);
	FREE_STR(songTitleUnicode);
	FREE_STR(creatorName);
	FREE_STR(difficultyName);
	FREE_STR(audioFileName);
	FREE_STR(md5Hash);
	FREE_STR(osuFileName);
	FREE_STR(songSource);
	FREE_STR(songTags);
	FREE_STR(folderName);
}

void Osu::beatmap_t::LoadFromDbStream(BinaryFile& file, int_t& dbVersion)
{
    if(dbVersion < 20191106)
        file.LoadType<int_t>(byteSize);
    // Load string metadata
    file.LoadString(artistName);
    file.LoadString(artistNameUnicode);
    file.LoadString(songTitle);
    file.LoadString(songTitleUnicode);
    file.LoadString(creatorName);
    file.LoadString(difficultyName);
    file.LoadString(audioFileName);
    file.LoadString(md5Hash);
    file.LoadString(osuFileName);

    file.LoadType<byte_t>(rankedStatus);
    file.LoadType<short_t>(numHitcircles);
    file.LoadType<short_t>(numSliders);
    file.LoadType<short_t>(numSpinners);
    file.LoadType<long_t>(lastModificationTimeWinTicks);

    if(dbVersion < 20140609)
    {
        file.LoadType<byte_t>(approachRateOld);
        file.LoadType<byte_t>(circleSizeOld);
        file.LoadType<byte_t>(hpDrainOld);
        file.LoadType<byte_t>(overallDifficultyOld);
    }else{
        file.LoadType<float_t>(approachRate);
        file.LoadType<float_t>(circleSize);
        file.LoadType<float_t>(hpDrain);
        file.LoadType<float_t>(overallDifficulty);
    }

    file.LoadType<double_t>(sliderVelocity);
    if(dbVersion > 20140609)
    {
        file.LoadIntDoublePair(stdStarRatings);
        file.LoadIntDoublePair(taikoStarRatings);
        file.LoadIntDoublePair(ctbStarRatings);
        file.LoadIntDoublePair(maniaStarRatings);
    }

    file.LoadType<int_t>(drainTime);
    file.LoadType<int_t>(totalLength);
    file.LoadType<int_t>(previewTime);

    int numTimingPoints = file.LoadType<int_t>();
    timingPoints = new timing_point_t[numTimingPoints]();
    for(int i = 0; i < numTimingPoints; i++)
    {
        timingPoints[i].bpm = file.LoadType<double_t>();
        timingPoints[i].offset = file.LoadType<double_t>();
        timingPoints[i].inherited = file.LoadType<byte_t>();
    }


    file.LoadType<int_t>(difficultyID);
    file.LoadType<int_t>(beatmapID);
    file.LoadType<int_t>(threadID);

    file.LoadType<byte_t>(stdGrade);
    file.LoadType<byte_t>(taikoGrade);
    file.LoadType<byte_t>(ctbGrade);
    file.LoadType<byte_t>(maniaGrade);

    file.LoadType<short_t>(localOffset);

    file.LoadType<float_t>(stackLeniency);
    file.LoadType<byte_t>(osuGameplayMode);

    file.LoadString(songSource);

    file.LoadString(songTags);

    file.LoadType<short_t>(onlineOffset);
    file.LoadString(fontUsed);
    file.LoadType<byte_t>(isUnplayed);
    file.LoadType<long_t>(lastTimePlayed);
    file.LoadType<byte_t>(isOsz2);
    file.LoadString(folderName);

    file.LoadType<long_t>(lastChecked);

    file.LoadType<byte_t>(ignoreBeatmapSound);
    file.LoadType<byte_t>(ignoreBeatmapSkin);
    file.LoadType<byte_t>(disableStoryboard);
    file.LoadType<byte_t>(disableVideo);
    file.LoadType<byte_t>(visualOverride);
    if(dbVersion < 20140609)
        file.LoadType<short_t>();
    file.LoadType<int_t>(lastModificationTime);
    file.LoadType<byte_t>(maniaScrollSpeed);
}
