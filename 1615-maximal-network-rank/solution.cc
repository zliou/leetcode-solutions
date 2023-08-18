#import <queue>
#import <unordered_set>
#import <vector>


using CityRank = std::pair<int, int>;  // num_edges, city_number

int from(const std::vector<int>& road) { return road[0]; }
int to(const std::vector<int>& road) { return road[1]; }
int edges(const CityRank& city_rank) { return city_rank.first; }
int city(const CityRank& city_rank) { return city_rank.second; }

void ParseAdjacency(const std::vector<std::vector<int>>& roads,
        std::vector<std::unordered_set<int>>& adjacent) {
    for (const std::vector<int>& road : roads) {
        adjacent[from(road)].insert(to(road));
        adjacent[to(road)].insert(from(road));
    }
}

std::priority_queue<CityRank> CreateCityRanks(
        const std::vector<std::unordered_set<int>> adjacent) {
    std::vector<CityRank> max_heap;
    for (size_t i = 0; i < adjacent.size(); ++i) {
        max_heap.push_back(std::make_pair(adjacent[i].size(), i));
    }
    // Heapify is O(n).
    return std::priority_queue<CityRank>(max_heap.begin(), max_heap.end()); 
}

int GetMaxNetworkRank(
        std::priority_queue<CityRank>& city_ranks,
        const std::vector<std::unordered_set<int>>& adjacent) {
    int max_network_rank = 0;
    CityRank first = city_ranks.top();
    city_ranks.pop();
    CityRank second = city_ranks.top();
    city_ranks.pop();
    if (adjacent[city(first)].find(city(second)) == adjacent[city(first)].end()) {
        return edges(first) + edges(second);
    }
    if (edges(first) == edges(second)) {
        std::vector<int> equals = {city(first), city(second)};
        while (!city_ranks.empty() && edges(city_ranks.top()) == edges(second)) {
            equals.push_back(city(city_ranks.top()));
            city_ranks.pop();
        }
        for (int city1 : equals) {
            for (int city2 : equals) {
                if (city1 == city2) {
                    continue;
                }
                if (adjacent[city1].find(city2) == adjacent[city1].end()) {
                    return adjacent[city1].size() + adjacent[city2].size();
                }
            }
        }
    } else {
        std::vector<int> equals = {city(second)};
        while (!city_ranks.empty() && edges(city_ranks.top()) == edges(second)) {
            equals.push_back(city(city_ranks.top()));
            city_ranks.pop();
        }
        for (int other : equals) {
            if (adjacent[other].find(city(first)) == adjacent[other].end()) {
                return edges(first) + adjacent[other].size();
            }
        }
    }
    return edges(first) + edges(second) - 1;
}


class Solution {
  public:
    int maximalNetworkRank(int n, std::vector<std::vector<int>>& roads) {
        std::vector<std::unordered_set<int>> adjacent(n, std::unordered_set<int>());
        ParseAdjacency(roads, adjacent);
        std::priority_queue<CityRank> city_ranks = CreateCityRanks(adjacent);
        return GetMaxNetworkRank(city_ranks, adjacent);
    }
};
