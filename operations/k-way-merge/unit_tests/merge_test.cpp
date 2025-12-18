#include <gtest/gtest.h>
#include <vector>
#include "../KwayMerge.h"
#include <algorithm>

class MergeTest : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

TEST_F(MergeTest, EmptyArray) {
    std::vector<int> tmp;
    EXPECT_EQ(KwayMergeSort(tmp).size(), 0);
}

TEST_F(MergeTest, OneEl){
    std::vector<int> tmp = {0};
    auto result = KwayMergeSort(tmp);
    std::vector<int> expected = {0};
    EXPECT_EQ(result, expected);
}

TEST_F(MergeTest, Repetitions){
    std::vector<int> tmp = {3, 5, 777, 5, 5, 777, 3, 3, 3, 777, 5};
    auto result = KwayMergeSort(tmp);
    std::vector<int> expected = {3, 3, 3, 3, 5, 5, 5, 5, 777, 777, 777};
    EXPECT_EQ(result, expected);
}

 TEST_F(MergeTest, OneBlock){
    std::vector<int> tmp = {4, 78, 1258, 345, 89, 456, 1};
    auto result = KwayMergeSort(tmp, 1);
    std::vector<int> expected= {1, 4, 78, 89, 345, 456, 1258};
    EXPECT_EQ(result, expected);
 }

TEST_F(MergeTest, KMoreThanNumOfBlocks){
    std::vector<int> tmp = {5, 32, 8, 10, 1};
    auto result = KwayMergeSort(tmp, 10, 2);
    std::vector<int> expected = {1, 5, 8, 10,32};
    EXPECT_EQ(result, expected);
}

TEST_F(MergeTest, ArrLessThanBlockSize){
    std::vector<int> tmp = {9, 8, 11, 6};
    auto result = KwayMergeSort(tmp, 4, 9);
    std::vector<int> expected = {6, 8, 9, 11};
    EXPECT_EQ(result, expected);
}

TEST_F(MergeTest, AscendArr_Sorted){
    std::vector<int> tmp = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto result = KwayMergeSort(tmp);
    std::vector<int> expected = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    EXPECT_EQ(result, expected);
}

TEST_F(MergeTest, DescendArr_ReversedSorted){
    std::vector<int> tmp = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    auto result = KwayMergeSort(tmp);
    std::vector<int> expected = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    EXPECT_EQ(result, expected);
}

TEST_F(MergeTest, ManyNumbers) {
    const size_t n = 100000;
    std::vector<int> tmp(n);
    for (size_t i=0; i<n; ++i) {
        tmp[i] = rand()%200000 - 100000;
    }
    auto result = KwayMergeSort(tmp);
    std::vector<int> expected = tmp;
    std::sort(expected.begin(), expected.end());
    EXPECT_EQ(result, expected);
}

TEST_F(MergeTest, Strings){
    std::vector<std::string> tmp = {"aaa", "a", "aaaaaaa", "aa"};
    auto result = KwayMergeSort(tmp);
    std::vector<std::string>expected = {"a", "aa", "aaa", "aaaaaaa"};
    EXPECT_EQ(result, expected);
}
TEST_F(MergeTest, DoublesAndNegatives){
    std::vector<double> tmp = {3.14, -1.0, 2.718, 0.0, -2.5};
    auto result = KwayMergeSort(tmp);
    std::vector<double> expected = {-2.5, -1.0, 0.0, 2.718, 3.14};
    EXPECT_EQ(result, expected);
}

TEST_F(MergeTest, Pairs){
    std::vector<std::pair<float, char>> tmp = {{3.1, 'b'}, {1.8, 'a'}, {3.1, 'a'}, {2.6, 'z'}};
    auto result = KwayMergeSort(tmp);
    std::vector<std::pair<float, char>> expected = {{1.8, 'a'}, {2.6, 'z'}, {3.1, 'a'}, {3.1, 'b'}};
    EXPECT_EQ(result, expected);
}

TEST_F(MergeTest, Bool){
    std::vector<bool> tmp = {true, false, true, false, true, false};
    auto result = KwayMergeSort(tmp, 2, 2);
    size_t false_count = std::count(result.begin(), result.end(), false);
    for (size_t i=0; i<false_count; ++i) {
        EXPECT_FALSE(result[i]);
    }
    for (size_t i = false_count; i < result.size(); ++i) {
        EXPECT_TRUE(result[i]);
    }
}