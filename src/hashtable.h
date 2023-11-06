#pragma once

#include <forward_list>
#include <functional>
#include <iostream>
#include <memory>
#include <numeric>
#include <utility>

template <typename K, typename V>
class OpenHashMap {
private:

    struct HashtableEntry {
        std::forward_list<std::pair<K,V>> bucket;
        int bucketSize;
    };

    int size;
    int tableSize;
    std::function<int(K)> keyHash;

    std::unique_ptr<HashtableEntry[]> hashtable;

    int computeHash(K key) const {
        return std::abs(keyHash(key)) % tableSize;
    }

public:

    class KeyNotFoundException {};

    OpenHashMap(int tableSize,
                std::function<int(K)> keyHash = [](K key) { return std::hash<K>()(key); }) {
        this->size = 0;
        this->tableSize = tableSize;
        this->keyHash = keyHash;
        hashtable = std::make_unique<HashtableEntry[]>(tableSize);
        for (int i = 0; i < tableSize; i++) {
            hashtable[i].bucketSize = 0;
        }
    }

    bool exists(K key) const {
        int hash = computeHash(key);
        for (const auto& pair : hashtable[hash].bucket) {
            if (pair.first == key) {
                return true;
            }
        }
        return false;
    }

    const V& find(K key) const {
        for (const auto& pair : hashtable[computeHash(key)].bucket) {
            if (pair.first == key) {
                return pair.second;
            }
        }

        throw KeyNotFoundException();
    }

    void put(K key, V value) {
        auto& entry = hashtable[computeHash(key)];
        for (auto& pair : entry.bucket) {
            if (pair.first == key) {
                pair.second = value;
                return;
            }
        }
        entry.bucket.emplace_front(key, value);
        entry.bucketSize++;
        size++;
    }

    void erase(K key) {
        if (!exists(key)) {
            throw KeyNotFoundException();
        }

        auto& entry = hashtable[computeHash(key)];
        auto prev = entry.bucket.before_begin();
        for (auto i = entry.bucket.begin(); i != entry.bucket.end(); i++) {
            if (i->first == key) {
                entry.bucket.erase_after(prev);
                entry.bucketSize--;
                size--;
                break;
            }

            prev = i;
        }
    }

    int getSize() const {
        return size;
    }

    void printStats() const {
        int collisions = 0;
        int maxSize = 0;
        for (int i = 0; i < tableSize; i++) {
            if (hashtable[i].bucketSize > 0) {
                collisions += hashtable[i].bucketSize - 1;
            }
            if (hashtable[i].bucketSize > maxSize) {
                maxSize = hashtable[i].bucketSize;
            }
        }
        std::cout << "Table size     : " << tableSize << std::endl;
        std::cout << "Data size      : " << size << std::endl;
        std::cout << "Load factor    : " << (size / (float)tableSize) << std::endl;
        std::cout << "Collisions     : " << collisions << std::endl;
        std::cout << "Largest bucket : " << maxSize << std::endl;
    }

    void printGraph(int maxValue) const {
        const int MAX_WIDTH = 40;
        const int MAX_HEIGHT = 20;
        int height = std::min(tableSize, MAX_HEIGHT);
        auto values = std::make_unique<std::vector<int>[]>(height);
        for (int i = 0; i < tableSize; i++) {
            values[i * height / tableSize].push_back(hashtable[i].bucketSize);
        }
        std::cout << 0;
        for (int x = 0; x < MAX_WIDTH; x++) {
            std::cout << " ";
        }
        std::cout << maxValue << std::endl;
        std::cout << "┏";
        for (int x = 0; x < MAX_WIDTH; x++) {
            std::cout << "━";
        }
        std::cout << "┓" << std::endl;
        for (int y = 0; y < height; y++) {
            std::cout << "┃";
            float average = std::accumulate(values[y].begin(), values[y].end(), 0.0) / values[y].size();
            int barSize = std::round(average * MAX_WIDTH / maxValue);
            for (int i = 0; i < MAX_WIDTH; i++) {
                std::cout << (i < barSize ? "▇" : " ");
            }
            std::cout << "┃" << std::endl;
        }
        std::cout << "┗";
        for (int x = 0; x < MAX_WIDTH; x++) {
            std::cout << "━";
        }
        std::cout << "┛" << std::endl;
    }
};
