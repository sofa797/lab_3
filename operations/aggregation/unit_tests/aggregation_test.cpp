#include <gtest/gtest.h>
#include <utility>
#include <vector>
#include "../AvgWithPartitioning.h"

class CacheTest : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

TEST_F(CacheTest, Simple) {
    std::vector<std::pair<int, int>> tmp;
    auto res = AvgWithPartitioning<int, int>(tmp).size();
    EXPECT_EQ(res, 0);
}

/*TODO*/