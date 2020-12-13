#include <QApplication>
#include <iostream>
#include <assert.h>
#include "mapcollection.h"
#include "mapcollection.cpp"
#include "mainwindow.h"

using namespace std;

void testConstructor() {
    MapCollection<size_t, string> map_collection;
    assert(0 == map_collection.size());
}

void testInsertSizeChanges() {
    MapCollection<size_t, string> map_collection;
    size_t tmp_int_1 = 0, tmp_int_2 = 1;
    string tmp_str_1 = "first", tmp_str_2 = "second";
    map_collection.insert(tmp_int_1, tmp_str_1);
    size_t buffer_size = map_collection.size();
    map_collection.insert(tmp_int_1, tmp_str_1);
    assert(buffer_size == map_collection.size());
    map_collection.insert(tmp_int_2, tmp_str_2);
    assert(buffer_size + 1 == map_collection.size());
}

void testExistKey() {
    MapCollection<size_t, string> map_collection;
    size_t tmp_int = 0;
    string tmp_str = "first";
    map_collection.insert(tmp_int, tmp_str);
    assert(true == map_collection.exist(tmp_int));
}

void testFindValue() {
    MapCollection<size_t, string> map_collection;
    size_t tmp_int = 0;
    string tmp_str = "first";
    map_collection.insert(tmp_int, tmp_str);
    assert(tmp_str == map_collection[tmp_int]);
    auto t = map_collection[tmp_int];
}

void testEraseSizeChanges() {
    MapCollection<size_t, string> map_collection;
    size_t tmp_int = 0, tmp_int_del = 1;
    string tmp_str = "first";
    map_collection.insert(tmp_int, tmp_str);
    size_t buffer_size = map_collection.size();
    map_collection.erase(tmp_int_del);
    assert(buffer_size == map_collection.size());
    map_collection.erase(tmp_int);
    assert(buffer_size - 1 == map_collection.size());
}

void testDeletedKey() {
    MapCollection<size_t, string> map_collection;
    size_t tmp_int = 0;
    string tmp_str = "first";
    map_collection.insert(tmp_int, tmp_str);
    map_collection.erase(tmp_int);
    assert(false == map_collection.exist(tmp_int));
}

void testClearMap() {
    MapCollection<size_t, string> map_collection_1, map_collection_2;
    size_t tmp_int = 0;
    string tmp_str = "first";
    map_collection_1.insert(tmp_int, tmp_str);
    map_collection_1.clear();
    assert(map_collection_1.size() == map_collection_2.size());
}

void testCopiedMap() {
    MapCollection<size_t, string> map_collection;
    size_t tmp_int = 0;
    string tmp_str_1 = "first", tmp_str_2 = "second";
    map_collection.insert(tmp_int, tmp_str_1);
    MapCollection<size_t, string> map_collection_copy(map_collection);
    auto result = (map_collection == map_collection_copy);
    assert(true == result);
    map_collection.insert(tmp_int, tmp_str_2);
    result = (map_collection == map_collection_copy);
    assert(true == result);
}

void testFileMethods() {
    MapCollection<size_t, string> map_collection_1, map_collection_2;
    string filename;
    map_collection_1.readFromFile(filename);
    map_collection_1.writeToFile(filename);
    map_collection_2.readFromFile(filename);
    auto result = map_collection_1 == map_collection_2;
    assert(true == result);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    testConstructor();
    testInsertSizeChanges();
    testEraseSizeChanges();
    testExistKey();
    testDeletedKey();
    testClearMap();
    testFindValue();
    testCopiedMap();
    testFileMethods();
    cout << "ALL TESTS WERE PASSED" << endl;
    return a.exec();
}
