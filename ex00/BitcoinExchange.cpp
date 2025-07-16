

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(void) {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &  other) 
: dataBase(other.dataBase)
{}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange &  other) 
{
    if (this != &other)
    {
        dataBase = other.dataBase;
    }
    return *this;
}

BitcoinExchange::~BitcoinExchange(void) {}


bool BitcoinExchange::processDataFile(std::string inFile)
{
    std::ifstream InputFile(inFile.c_str());
    if (!InputFile.is_open())
        return false;
 
    bool firstLine = true;
    std::string line;
    std::string date;
    std::string val;
    while(std::getline(InputFile, line))
    {
        if (firstLine)
        {
            firstLine = false; continue;
        }
        size_t commaPosition = line.find(',');
        if (commaPosition == std::string::npos)
            continue;
        date = line.substr(0, commaPosition);
        val = line.substr((commaPosition + 1), line.length());
        trimWhiteSpace(date);
        trimWhiteSpace(val);
        if (!isValidDate(date))
            continue;
        float digiVal = std::atof(val.c_str());
        dataBase[date] = digiVal;
    }
    return true;
}

bool BitcoinExchange::performOperation(std::string inFile)
{
    std::ifstream InputFile(inFile.c_str());
    if (!InputFile.is_open())
        return false;
    bool firstLine = true;
    std::string line;
    std::string dateStr;
    std::string valueStr;
    while (std::getline(InputFile, line))
    {
        if (firstLine && !std::isdigit(line[0]))
        {
            firstLine = false; continue;
        }
        size_t pipeIndex = line.find('|');
        dateStr = line.substr(0, pipeIndex);
        valueStr = line.substr((pipeIndex + 1), line.length());
        trimWhiteSpace(dateStr);
        trimWhiteSpace(valueStr);
        if (!isValidDate(dateStr))
        {    
            std::cout << "Error: bad input => " << dateStr << '\n'; continue;
        }
        if (dateStr == valueStr)
        {
            std::cout << "Error: bad input, missing '|' separator.\n"; continue;
        }
        float fv;
        std::string closeYear = closeYearSearch(dateStr);
        if (isValidValue(valueStr, fv))
        {
            float rate = dataBase[closeYear];
            float result = rate * fv;
            std::cout << dateStr << " => " << fv << " = " << result << '\n';
        }
    }
    return true;
}

bool BitcoinExchange::isValidDate(std::string date)
{
    if (date.empty())
        return false;

    if (date.length() != 10 || date[4] != '-' || date[7] != '-')
        return false;

    std::string yearStr = date.substr(0, 4);
    std::string monthStr = date.substr(5, 2);
    std::string dayStr = date.substr(8, 2);
        
    for(size_t i = 0; i < yearStr.length(); i++)
        if ( !(std::isdigit(yearStr[i])) )
            return false;
    
    for(size_t i = 0; i < monthStr.length(); i++)
        if ( !(std::isdigit(monthStr[i])) )
            return false;
    
    for(size_t i = 0; i < dayStr.length(); i++)
        if ( !(std::isdigit(dayStr[i])) )
            return false;

    int yr = std::atoi(yearStr.c_str());
    int mt = std::atoi(monthStr.c_str());
    int dy = std::atoi(dayStr.c_str());

    if (yr < 1001 || yr > 2025 || mt < 1 || mt > 12 || dy < 1 || dy > 31)
        return false;
    if (mt == 2 && dy > 29)
        return false;
    if ( (mt == 1 || mt == 3 || mt == 5 || mt == 7 || mt == 8 || mt || 10 || mt == 12) && dy > 31 )
        return false;
    if ( (mt == 4 || mt == 7 || mt == 9 || mt == 11) && dy > 30 )
        return false;
    return true;
}

bool BitcoinExchange::isValidValue(std::string value, float & fv)
{
        if (value.empty())
        {    
            std::cout << "Error: bad input, empty value string.\n" ; return false;
        }
        for (size_t i = 0; i < value.length(); i++)
        {
            if (!std::isdigit(value[i]) && value[i] != '.' && value[i] != '-' && value[i] != '+')
            {
                std::cout << "Error: bad input value ==> " << value << '\n'; return false;
            }
        }
        fv = std::atof(value.c_str());
        if (fv < 0)
        {
            std::cout << "Error: not a positive number.\n"; return false;
        }
        if (fv > 1000)
        {
            std::cout << "Error: too large a number.\n"; return false;
        }
        return true;
}

void BitcoinExchange::trimWhiteSpace(std::string & str)
{

    size_t start = str.find_first_not_of(" \t\n");
    if (start == std::string::npos)
    {
        str = "";
        return;
    }
    size_t end = str.find_last_not_of(" \t\n");
    str = str.substr(start, end - start + 1);
}

std::string  BitcoinExchange::closeYearSearch(std::string date)
{
    std::map<std::string, float>::iterator it = dataBase.upper_bound(date);
    if (it != dataBase.begin())
        --it;
    else
        return "";
    return it->first;
}