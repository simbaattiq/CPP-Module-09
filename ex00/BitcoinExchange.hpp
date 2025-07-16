
#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <fstream>

class BitcoinExchange
{
private:
    std::map<std::string, float> dataBase;
public:
    BitcoinExchange(void);
    BitcoinExchange(const BitcoinExchange & other);
    BitcoinExchange& operator=(const BitcoinExchange & other);
    ~BitcoinExchange(void);

    void trimWhiteSpace(std::string & str);
    bool isValidDate(std::string date);
    bool isValidValue(std::string value, float & fv);
    bool processDataFile(std::string inFile);
    bool performOperation(std::string inFile);
    std::string closeYearSearch(std::string date);
};

#endif