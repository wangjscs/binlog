#include <binlog/binlog.hpp>
#include <binlog/Range.hpp>
#include <binlog/adapt_struct.hpp> // Include the adapt_struct header
#include <iostream>
#include <string>
#include <tuple>
#include <utility> // pair
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <cstring> // For memcpy

struct MyCustomData1 {
    int id;
    float value;
    char name[32];
};
BINLOG_ADAPT_STRUCT(MyCustomData1, id, value, name) 
struct MyCustomData2 {
  int id;
  MyCustomData1 value;
};

// Use BINLOG_ADAPT_STRUCT to make MyCustomData serializable
BINLOG_ADAPT_STRUCT(MyCustomData2, id, value) 

int main()
{
    std::tuple<> empty;
    BINLOG_INFO("Empty tuple: {}", empty);

    std::pair<int, char> p{1, 'a'};
    std::tuple<std::string, bool, int> t{"foo", true, 2};
    BINLOG_INFO("Pair: {}, Tuple: {}", p, t);

    std::vector<int> vec = {1, 2, 3, 4, 5};
    BINLOG_INFO("Vector: {}", vec);

    std::map<int, std::string> myMap = {{1, "one"}, {2, "two"}, {3, "three"}};
    BINLOG_INFO("simple map: {}", myMap);

    std::map<std::string, std::vector<std::pair<int, std::tuple<std::string, double>>>> complexMap;
    complexMap["groupA"].emplace_back(1, std::make_tuple("alpha", 3.14));
    complexMap["groupA"].emplace_back(2, std::make_tuple("beta", 2.71));
    complexMap["groupB"].emplace_back(3, std::make_tuple("gamma", 1.61));
    complexMap["groupB"].emplace_back(4, std::make_tuple("delta", 0.577));
    BINLOG_INFO("complexMap: {}", complexMap);

    MyCustomData2 original_data{1,{123, 3.14f, "My Custom Object"}};
    BINLOG_INFO("original_data: {}", original_data);

    std::ofstream logfile("sample.blog", std::ofstream::out | std::ofstream::binary);
    binlog::consume(logfile);

    // Reading and deserialization would involve using binlog's reading API.
    // The data for MyCustomData will be serialized within the event.

    return 0;
}
