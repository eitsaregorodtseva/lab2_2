#ifndef MAPCOLLECTON_H
#define MAPCOLLECTON_H

#include <vector>
#include <string>

template<typename K, typename V> class MapCollection {
public:
    MapCollection();
    MapCollection(const MapCollection &other_);
    MapCollection& operator=(const MapCollection &other_) = default;
    MapCollection(MapCollection &&other_) = default;
    MapCollection& operator=(MapCollection &&other_) = default;
    void clear();
    size_t size() const;
    void readFromFile(std::string filename);
    void writeToFile(std::string filename) const;
    bool operator==(const MapCollection &other_);
    bool compareMaps(const MapCollection &other_);
    void insert(const K& key_, const V& value_);
    void erase(const K& key_);
    V &find(const K& key_);
    V &operator[](const K& key_);
    bool exist(const K& key_) const;
    std::vector<V> allValuesReturn(const MapCollection &other_);
    std::vector<K> allKeysReturn();
    bool compareKeys(const K& key_);
    bool operator>(const K& key_);
    ~MapCollection() = default;
private:
    std::vector<K> m_keys;
    std::vector <V> m_values;
    std::size_t m_size;
    void copyFromOther(const MapCollection &other_);
};

#endif // MAPCOLLECTON_H
