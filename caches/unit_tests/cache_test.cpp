#include <gtest/gtest.h>
#include "../CacheImp.h"

class CacheTest : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

TEST_F(CacheTest, PutAndGet) {
    Clockcache<int, int> cache(3);
    EXPECT_EQ(cache.size(), 0);
    cache.set(99,100);
    EXPECT_EQ(cache.size(),1);
    EXPECT_EQ(cache.get(99),100);
    EXPECT_TRUE(cache.contains(99));
}

TEST_F(CacheTest, GetNotExistKey){
    Clockcache<int,int> cache(776);
    EXPECT_EQ(cache.get(777),0);
    EXPECT_FALSE(cache.contains(777));
}

TEST_F(CacheTest, UpdatingExistKey){
    Clockcache<int, std::pair<std::string,int>> cache(2);
    cache.set(0, {"now", 2025});
    EXPECT_EQ(cache.get(0), std::make_pair(std::string("now"), 2025));
    cache.set(0, {"soon", 2026});
    EXPECT_EQ(cache.size(), 1);
    EXPECT_EQ(cache.get(0), std::make_pair(std::string("soon"), 2026));
}

TEST_F(CacheTest, EvictionDueToFullness){
    Clockcache<int, int> cache(2);
    cache.set(0, 32);
    cache.set(1, 33);
    EXPECT_EQ(cache.size(), 2);
    EXPECT_TRUE(cache.contains(0));
    EXPECT_TRUE(cache.contains(1));
    cache.set(2, 34);
    EXPECT_EQ(cache.size(), 2);
    EXPECT_TRUE(cache.contains(2));
    bool el_zero = cache.contains(0);
    bool el_one = cache.contains(1);
    EXPECT_TRUE(el_zero || el_one);
    EXPECT_FALSE(el_zero && el_one);
}

TEST_F(CacheTest, CheckUsage){
    Clockcache<int, int> cache(3);
    cache.set(1, 1);
    cache.set(2, 2);
    for (int i=0; i<3; ++i){
        cache.get(1);
    }
    cache.set(3,3);
    cache.set(4,4);
    EXPECT_TRUE(cache.contains(1));
}

TEST_F(CacheTest, CheckClear){
    Clockcache<int,std::string> cache(3);
    cache.set(8, "august");
    cache.set(12, "december");
    cache.set(1, "january");
    EXPECT_EQ(cache.size(), 3);
    cache.clear();
    EXPECT_EQ(cache.size(), 0);
    EXPECT_FALSE(cache.contains(8));
    EXPECT_FALSE(cache.contains(12));
    EXPECT_FALSE(cache.contains(1));
    cache.set(4, "april");
    EXPECT_EQ(cache.size(),1);
    EXPECT_EQ(cache.get(4), "april");
}

TEST_F(CacheTest, EvictionOrder){
    Clockcache<int, int> cache(3);
    cache.set(3, 9);
    cache.set(25, 625);
    cache.set(10, 100);
    cache.get(3);
    cache.get(3);
    cache.get(10);
    cache.set(8, 64);
    EXPECT_FALSE(cache.contains(25));
    EXPECT_TRUE(cache.contains(3));
    EXPECT_TRUE(cache.contains(10));
    EXPECT_TRUE(cache.contains(8));
}