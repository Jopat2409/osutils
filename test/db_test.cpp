#include <gtest\gtest.h>
#include <osu_utils.h>
#include <string>


#define _(x) std::string(x)

TEST(DbTest, HeaderAssertions)
{
    EXPECT_EQ(2, 2);
    Osu::db_t* testDb = Osu::LoadDB("D:/osu!.db");

    EXPECT_EQ(testDb->isAccountUnlocked, 1);
    EXPECT_EQ(_(testDb->playerName), _("Jopat2409"));
    EXPECT_EQ(testDb->numBeatmaps, 16934);

    EXPECT_EQ(_(testDb->beatmaps[0].osuFileName), _("[Kyoro] - Mochio- (Snow Note) [Challenge].osu"));

    Osu::FreeDB(testDb);
}

TEST(DBTest, BeatmapArrayAssertions)
{

}
