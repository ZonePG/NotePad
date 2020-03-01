#ifndef BLOOMFILTER_H
#define BLOOMFILTER_H

#include <string>
#include <vector>

const int MAXLEN = 875;

class BloomFilter {
private:
    char bitFilter[MAXLEN];
    std::vector<std::string> keyWords;

    void initialBitFilter();
    void refreshKeyWords();
    void refreshBitFilter();

    void importKeyToBloomFilter();
    
    void readFileToArrays(const std::string str = "CPP.txt");

    // Hash Func
    int HashFunc(const std::string &str, int i);

    int BKDRHash(const std::string &str);
    int RSHash(const std::string &str);
    int APHash(const std::string &str);

public:
    BloomFilter();
    ~BloomFilter();

    
    void import_CPP_KeyWords();
    void import_Java_keyWords();
    void import_Python_keyWords();

    // user's control
    bool KeyExistInBitFilter(const std::string &str);
};

#endif