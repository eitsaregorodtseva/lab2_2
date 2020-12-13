#include "mapcollection.h"
#include <fstream>
#include <algorithm>

using namespace std;

template<typename K, typename V>
MapCollection<K, V>::MapCollection() {
    this->m_size = 0;
}

template<typename K, typename V>
MapCollection<K, V>::MapCollection(const MapCollection &other_) {
    copyFromOther(other_);
}

template<typename K, typename V>
void MapCollection<K, V>::clear() {
    this->m_size = 0;
    this->m_keys.clear();
    this->m_values.clear();
}

template<typename K, typename V>
size_t MapCollection<K, V>::size() const {
    return this->m_size;
}

template<typename K, typename V>
void MapCollection<K, V>::readFromFile(std::string filename) {
    ifstream file (filename);
    size_t n;
    size_t buffer_int;
    string buffer_str;
    if (file.is_open()) {
        file >> n;
        for (size_t i = 0; i < n; i++) {
            file >> buffer_int;
            file >> buffer_str;
            this->insert(buffer_int, buffer_str);
        }
    }
    file.close();
}

template<typename K, typename V>
void MapCollection<K, V>::writeToFile(std::string filename) const {
    ofstream file (filename);
    if (file.is_open()) {
        file << this->m_size << endl;
        auto iter_v = 0;
        for (auto iter = this->m_keys.begin(); iter != this->m_keys.end(); iter++) {
            file << *iter << endl;
            file << this->m_values[iter_v] << endl;
            iter_v++;
        }
    }
    file.close();
}

template<typename K, typename V>
bool MapCollection<K, V>::operator==(const MapCollection &other_) {
    return this->compareMaps(other_);
}

template<typename K, typename V>
bool MapCollection<K, V>::compareMaps(const MapCollection &other_) {
    if (this->m_size != other_.m_size)
        return false;
    else {
        auto m_keys_(this->m_keys);
        auto o_keys_(other_.m_keys);
        sort(m_keys_.begin(), m_keys_.end());
        sort(o_keys_.begin(), o_keys_.end());
        if (m_keys_ != o_keys_)
            return false;
        else {
            auto x = allValuesReturn(*this);
            auto y = allValuesReturn(other_);
            if (x == y)
                return true;
            else
                return false;
        }
    }
}

template<typename K, typename V>
void MapCollection<K, V>::insert(const K &key_, const V &value_) {
    for (auto iter = this->m_keys.begin(); iter != this->m_keys.end(); iter++) {
        if (*iter == key_) {
            this->m_values[iter - this->m_keys.begin()] = value_;
            return;
        }
    }
    this->m_keys.push_back(key_);
    this->m_values.push_back(value_);
    ++this->m_size;
}

template<typename K, typename V>
void MapCollection<K, V>::erase(const K &key_) {
    for (auto iter_k = this->m_keys.begin(); iter_k != this->m_keys.end(); iter_k++) {
        auto iter_v = this->m_values.begin();
        if (*iter_k == key_) {
            this->m_keys.erase(iter_k);
            this->m_values.erase(iter_v);
            this->m_size -= 1;
            return;
        }
        iter_v++;
    }
}

template<typename K, typename V>
V &MapCollection<K, V>::find(const K &key_) {
    for (auto iter = this->m_keys.begin(); iter != this->m_keys.end(); iter++) {
        if (*iter == key_) {
            auto value = this->m_values[iter - this->m_keys.begin()];
            return this->m_values[iter - this->m_keys.begin()];
        }
    }
}

template<typename K, typename V>
V &MapCollection<K, V>::operator[](const K &key_) {
    return this->find(key_);

}

template<typename K, typename V>
bool MapCollection<K, V>::exist(const K &key_) const {
    for (auto iter = this->m_keys.begin(); iter != this->m_keys.end(); iter++)
        if (*iter == key_)
            return true;
        else
            return false;
}


template<typename K, typename V>
bool MapCollection<K, V>::compareKeys(const K &key_) {
    if (this > key_)
        return true;
    else
        return false;
}

template<typename K, typename V>
bool MapCollection<K, V>::operator>(const K &key_) {
    return this->compareKeys(key_);
}

template<typename K, typename V>
void MapCollection<K, V>::copyFromOther(const MapCollection &other_) {
    this->m_size = other_.m_size;
    this->m_keys = other_.m_keys;
    this->m_values = other_.m_values;
}

template<typename K, typename V>
vector<V> MapCollection<K, V>::allValuesReturn(const MapCollection &other_) {
    vector<V> m_values_(other_.m_values);
    vector<K> m_keys_(other_.m_keys);
    for(size_t i = 0; i < other_.size(); i++) {
        for(size_t j = other_.size() - 1; j > i; j--)
            if (m_keys_[j-1] > m_keys_[j]) {
                m_values_.push_back(other_.m_values[j]);
                m_values_.push_back(other_.m_values[j - 1]);
                swap(m_keys_[j], m_keys_[j-1]);
            }
        m_values_.erase(m_values_.begin(), m_values_.begin() + other_.size());
    }
    return m_values_;
}

template<typename K, typename V>
std::vector<K> MapCollection<K, V>::allKeysReturn() {
    auto m_keys_(this->m_keys);
    sort(m_keys_.begin(), m_keys_.end());
    return m_keys_;
}
