#pragma once
#include <iostream>
#include <unordered_map>
#include <string>
#include <optional>
#include <vector>
#include <filesystem>
#include <queue>


template<typename T>
static std::vector<T> merge(const std::vector<std::vector<T>>& blocks){
    struct Node{
        T v;
        size_t blockindx;
        size_t elindx;
        bool operator>(const Node& other) const{
            return v > other.v;
        }
    };
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> prior_q;
    std::vector<T> result;
    for (size_t i=0; i < blocks.size(); ++i){
        if (!blocks[i].empty()) {
            prior_q.push(Node{blocks[i][0],i,0});
        }
    }
    while (!prior_q.empty()){
        Node node = prior_q.top();
        prior_q.pop();
        result.push_back(node.v);
        size_t nextindx = node.elindx+1;
        if (nextindx < blocks[node.blockindx].size()) {
            prior_q.push(Node{blocks[node.blockindx][nextindx],node.blockindx,nextindx});
        }
    }
    return result;
}

template<typename T>
std::vector<T> KwayMergeSort(const std::vector<T>& array
    , std::size_t k = 4
    , std::size_t block_size = 8)
{
    if (array.empty())
        return {};
    if (k == 1) {
        std::vector<T> result = array;
        std::sort(result.begin(), result.end());
        return result;
    }
    std::vector<std::vector<T>> blocks;
    for (size_t start=0; start < array.size(); start+=block_size) {
        size_t end=std::min(start+block_size, array.size());
        std::vector<T> block(array.begin()+start, array.begin()+end);
        std::sort(block.begin(), block.end());
        blocks.push_back(std::move(block));
    }
    while (blocks.size() > 1) {
        std::vector<std::vector<T>> newblocks;
        for (size_t i=0; i < blocks.size(); i+=k) {
            size_t end = std::min(i+k, blocks.size());
            std::vector<std::vector<T>> domerge(blocks.begin()+i, blocks.begin()+end);
            newblocks.push_back(merge(domerge));
        }
        blocks = std::move(newblocks);
    }
    return blocks[0];
}