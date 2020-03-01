#include <iostream>
#include <fstream>
#include "bloomfilter.h"

BloomFilter::BloomFilter()
{
    initialBitFilter();
    import_CPP_KeyWords();
}

BloomFilter::~BloomFilter()
{

}

void BloomFilter::initialBitFilter()
{
    for(int i=0; i<MAXLEN; i++)
    {
        bitFilter[i]=0;
    }
}

void BloomFilter::refreshKeyWords()
{
    keyWords.clear();
}

void BloomFilter::refreshBitFilter()
{
    for (int i = 0; i < MAXLEN; i++)
        bitFilter[i] = 0;
}

void BloomFilter::import_CPP_KeyWords()
{
    refreshKeyWords();
    refreshBitFilter();
    readFileToArrays("CPP.txt");
    importKeyToBloomFilter();
}

void BloomFilter::import_Java_keyWords()
{
    refreshKeyWords();
    refreshBitFilter();
    readFileToArrays("Java.txt");
    importKeyToBloomFilter();
}

void BloomFilter::import_Python_keyWords()
{
    refreshKeyWords();
    refreshBitFilter();
    readFileToArrays("Python.txt");
    importKeyToBloomFilter();
}

void BloomFilter::readFileToArrays(const std::string str)
{
    std::ifstream in(str);
    if (!in)
    {
        std::cout << "error opening the file." << std::endl;
    }
    std::string line;
    while (in >> line)
        keyWords.push_back(line);
    in.close();
}

void BloomFilter::importKeyToBloomFilter()
{
    for (auto iter = keyWords.begin(); iter != keyWords.end(); iter++)
    {
        for (int i = 0; i < 3; i++)
        {
            auto bit = HashFunc((*iter), i);
            if(!((bitFilter[bit/8] >> bit%8) % 2))
            {
                bitFilter[bit/8] += 1 << bit % 8;
            }
        }
    }
}

bool BloomFilter::KeyExistInBitFilter(const std::string &str)
{
    for(int i=0; i<3; i++)
    {
        auto bit=HashFunc(str, i);
        if(!((bitFilter[bit/8] >> bit%8) % 2))
            return false;
    }
    return true;
}

int BloomFilter::HashFunc(const std::string &str, int i)
{
    switch(i)
    {
        case 0:
            return BKDRHash(str);
            break;
        case 1:
            return RSHash(str);
            break;
        case 2:
            return APHash(str);
            break;
        default:
            break;
    }
    return 0;
}

int BloomFilter::BKDRHash(const std::string &str)
{
    unsigned int seed = 131; // 31 131 1313 13131 131313 etc..
    unsigned int hash = 0;

    for (const auto &ch : str)
        hash = hash * seed + ch;

    return (hash & 0x7FFFFFFF)%7000;;
}

int BloomFilter::RSHash(const std::string &str)
{
	unsigned int hash = 0;
	unsigned magic = 63689;	
    for (const auto &ch : str)
	{
		hash = hash * magic + ch;
		magic *= 378551;
	}
	return hash % 7000;
}

int BloomFilter::APHash(const std::string &str)
{
    unsigned int hash = 0;
    int i = 0;

    for (const auto &ch : str)
    {
        if ((i & 1) == 0)
            hash ^= ((hash << 7) ^ (ch) ^ (hash >> 3));
        else
            hash ^= (~((hash << 11) ^ (ch) ^ (hash >> 5)));
        i++;
    }

    return (hash & 0x7FFFFFFF)%7000;
}