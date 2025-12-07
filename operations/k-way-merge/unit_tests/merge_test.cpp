#include <gtest/gtest.h>
#include <vector>
#include "../KwayMerge.h"

class MergeTest : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

TEST_F(MergeTest, PutAndGet) {
    std::vector<int> tmp;
    EXPECT_EQ(KwayMergeSort(tmp).size(), 0);
}

/*TODO*/