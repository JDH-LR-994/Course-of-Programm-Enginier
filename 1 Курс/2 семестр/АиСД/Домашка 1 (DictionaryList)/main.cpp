#include "DictionaryList.hpp"

int main()
{
    std::cout << "DictionaryList Test\n";
    DictionaryList<int> dict;
    dict.insertItem(2);
    dict.insertItem(4);
    dict.insertItem(3);
    std::cout << "DictionaryList Test order: ";
    for (auto _ = dict.getHead(); _ != nullptr; _ = _->next_)
    {
        std::cout << _->key_ << " ";
    }
    std::cout << "\n";

    std::cout << "DictionaryList Test search (4 in list?): ";
    auto _ = dict.searchItem(4);
    if (_ != nullptr)
    {
        std::cout << "Found: " << _->key_ << "\n";
    }
    else
    {
        std::cout << "Not Found\n";
    }
    std::cout << "DictionaryList Test search (5 in list?): ";
    _ = dict.searchItem(5);
    if (_ != nullptr)
    {
        std::cout << "Found: " << _->key_ << "\n";
    }
    else
    {
        std::cout << "Not Found\n";
    }
    std::cout << "DictionaryList Test delete (2 in list?): ";
    dict.deleteItem(2);
    for (auto _ = dict.getHead(); _ != nullptr; _ = _->next_)
    {
        std::cout << _->key_ << " ";
    }
    std::cout << "\n";
    std::cout << "DictionaryList Test delete (5): ";
    dict.deleteItem(5);
    for (auto _ = dict.getHead(); _ != nullptr; _ = _->next_)
    {
        std::cout << _->key_ << " ";
    }
    std::cout << "\n";
    std::cout << "DictionaryList Test clear: ";
    dict.clear();
    for (auto _ = dict.getHead(); _ != nullptr; _ = _->next_)
    {
        std::cout << _->key_ << " ";
    }
    std::cout << "\n";
    dict.insertItem(2);
    dict.insertItem(3);
    dict.insertItem(4);
    dict.insertItem(5);
    DictionaryList<int> dict2;
    dict2.insertItem(1);
    dict2.insertItem(2);
    dict2.insertItem(3);

    DictionaryList<int> dict3 = getIntersection(dict, dict2);
    std::cout << "DictionaryList Test intersection: ";
    for (auto _ = dict3.getHead(); _ != nullptr; _ = _->next_)
    {
        std::cout << _->key_ << " ";
    }
}