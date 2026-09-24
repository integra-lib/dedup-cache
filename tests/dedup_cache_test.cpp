#include <gtest/gtest.h>

#include <hwlib/data_structures/dedup_cache.hpp>

namespace
{

TEST(DedupCacheTest, EmptyCacheContainsNothing)
{
    const hwlib::data_structures::DedupCache<4> cache;
    EXPECT_FALSE(cache.Contains(1U));
}

TEST(DedupCacheTest, RemembersInsertedIds)
{
    hwlib::data_structures::DedupCache<4> cache;
    cache.Insert(7U);
    cache.Insert(9U);

    EXPECT_TRUE(cache.Contains(7U));
    EXPECT_TRUE(cache.Contains(9U));
    EXPECT_FALSE(cache.Contains(8U));
}

TEST(DedupCacheTest, EvictsTheOldestOnceFull)
{
    hwlib::data_structures::DedupCache<3> cache;
    cache.Insert(1U);
    cache.Insert(2U);
    cache.Insert(3U);
    ASSERT_TRUE(cache.Contains(1U));

    cache.Insert(4U);
    EXPECT_FALSE(cache.Contains(1U));
    EXPECT_TRUE(cache.Contains(2U));
    EXPECT_TRUE(cache.Contains(3U));
    EXPECT_TRUE(cache.Contains(4U));
}

TEST(DedupCacheTest, SurvivesMoreInsertsThanCapacity)
{
    hwlib::data_structures::DedupCache<2> cache;
    for (std::uint32_t i = 0U; i < 100U; ++i)
    {
        cache.Insert(i);
    }
    EXPECT_TRUE(cache.Contains(99U));
    EXPECT_TRUE(cache.Contains(98U));
    EXPECT_FALSE(cache.Contains(97U));
}

TEST(DedupCacheTest, ACapacityOfOneKeepsOnlyTheLast)
{
    hwlib::data_structures::DedupCache<1> cache;
    cache.Insert(5U);
    EXPECT_TRUE(cache.Contains(5U));
    cache.Insert(6U);
    EXPECT_FALSE(cache.Contains(5U));
    EXPECT_TRUE(cache.Contains(6U));
}

} // namespace
