#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark_all.hpp>

#include "hashtable.h"

using namespace std;

const int KEY_COUNT = 100000;
const int SEARCH_KEY = 20000;

TEST_CASE("Linear search")
{
    BENCHMARK_ADVANCED("Linear search of 100k keys")(Catch::Benchmark::Chronometer meter) {
        vector<int> vec;
        for (int i = 0; i < KEY_COUNT; i++) {
            vec.push_back(i);
        }
        meter.measure([&vec] {
            for (int i = 0; i < KEY_COUNT; i++) {
                if (vec[i] == SEARCH_KEY) {
                    return i;
                }
            }
            return -1;
        });
    };
}

bool binarySearch(const vector<int>& vec, int key)
{
    int left = 0;
    int right = vec.size() - 1;
    while (left <= right) {
        int middle = floor((left + right) / 2);
        if (vec[middle] < key) {
            left = middle + 1;
        } else if (vec[middle] > key) {
            right = middle - 1;
        } else {
            return true;
        }
    }

    return false;
}

TEST_CASE("Binary search")
{
    BENCHMARK_ADVANCED("Binary search of 100k keys")(Catch::Benchmark::Chronometer meter) {
        vector<int> vec;
        for (int i = 0; i < KEY_COUNT; i++) {
            vec.push_back(i);
        }
        meter.measure([&vec] {
            return binarySearch(vec, SEARCH_KEY);
        });
    };
}

TEST_CASE("Hash table search")
{
    BENCHMARK_ADVANCED("Hash table with 100k keys (1k table)")(Catch::Benchmark::Chronometer meter) {
        OpenHashMap<int,int> map(1000);
        for (int i = 0; i < KEY_COUNT; i++) {
            map.put(i, i);
        }
        meter.measure([&map] {
            return map.exists(SEARCH_KEY);
        });
    };

    BENCHMARK_ADVANCED("Hash table with 100k keys (5k table)")(Catch::Benchmark::Chronometer meter) {
        OpenHashMap<int,int> map(5000);
        for (int i = 0; i < KEY_COUNT; i++) {
            map.put(i, i);
        }
        meter.measure([&map] {
            return map.exists(SEARCH_KEY);
        });
    };

    BENCHMARK_ADVANCED("Hash table with 100k keys (10k table)")(Catch::Benchmark::Chronometer meter) {
        OpenHashMap<int,int> map(10000);
        for (int i = 0; i < KEY_COUNT; i++) {
            map.put(i, i);
        }
        meter.measure([&map] {
            return map.exists(SEARCH_KEY);
        });
    };

    BENCHMARK_ADVANCED("Hash table with 100k keys (50k table)")(Catch::Benchmark::Chronometer meter) {
        OpenHashMap<int,int> map(50000);
        for (int i = 0; i < KEY_COUNT; i++) {
            map.put(i, i);
        }
        meter.measure([&map] {
            return map.exists(SEARCH_KEY);
        });
    };

    BENCHMARK_ADVANCED("Hash table with 100k keys (100k table)")(Catch::Benchmark::Chronometer meter) {
        OpenHashMap<int,int> map(100000);
        for (int i = 0; i < KEY_COUNT; i++) {
            map.put(i, i);
        }
        meter.measure([&map] {
            return map.exists(SEARCH_KEY);
        });
    };
}
