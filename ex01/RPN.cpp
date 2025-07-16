
#include "RPN.hpp"


RPN::RPN(void) {}

RPN::~RPN(void) {}

RPN::RPN(const RPN & other) : stData(other.stData) {}

RPN & RPN::operator=(const RPN & other)
{
    if (this != &other)
    {
        stData = other.stData;
    }
    return *this;
}

void RPN::processCalculation(std::string input)
{
    if (!firstCheck(input))
        throw std::runtime_error("not a valid number");
    if (input.empty())
        throw std::runtime_error("empty argument list");
    while (!stData.empty())
        stData.pop();
    
    size_t i = 0;
    while (i < input.length())
    {
        if (std::isspace(input[i]))
        {
            i++;
            continue;
        }
        else if (std::isdigit(input[i]))
        {
            std::string strVal = input.substr(i, 1);
            long long num = std::atoll(strVal.c_str());
            stData.push(num);
        }
        else if (isOperator(input[i]))
        {
            if (stData.size() > 1)
            {                
                long long n2 = stData.top();
                stData.pop();
                long long n1 = stData.top();
                stData.pop();
                long long result = performOperation(n1, n2, input[i]);
                stData.push(result);
            }
            else
                throw std::runtime_error("can't Perform Operation: Stack_size < 2");
        }
        else if (!isValidToken(input[i]))
            throw std::runtime_error("Invalid Token");
        i++;
    }
}

long long  RPN::performOperation(long long n1, long long n2, char op)
{
    long long result ;
    bool done = false;

    if (op == '+')
    {
        result = n1 + n2;
        done = true;
    }
    else if (op == '-')
    {
        result = n1 - n2;
        done  = true;
    }
    else if (op == '*')
    {    
        result = n1 * n2;
        done = true;
    }
    else if (op == '/')
    {
        if (n2 < 1)
            throw std::runtime_error("devision by Zero is not allowed");
        result = n1 / n2;
        done = true;
    }
    if (!done)
        throw std::runtime_error("couldn't perform operation: token is not a valid operation " );
    return result;
}

void RPN::print(void)
{
    if (stData.size() == 1)
        std::cout << stData.top() << '\n';
    else if (stData.size() == 0)
        throw std::runtime_error("Printing failed: no Members");
    else if (stData.size() > 1)
        throw std::runtime_error("Printing failed: too many members");
}

bool RPN::firstCheck(std::string argv)
{
    size_t maxSize = countSpaces(argv);
    std::string result[maxSize];

    splitString(argv, result, maxSize);
    for (size_t i = 0; i < maxSize; i++)
    {
        if (!validNumTok(result[i]))
            return false;
    }
    return true;
}

bool RPN::validNumTok(std::string & input)
{
    if (input.length() > 1)
        return false;
    for (size_t i = 0; i < input.length(); i++)
    {
        if (!isValidToken(input[i]))
            return false;
    }
    return true;
}

bool RPN::isValidToken(char c)
{
    if (!isOperator(c) && !std::isdigit(c))
        return false;
    return true;
}

bool RPN::isOperator(char op)
{
    if (op == '+' || op == '-' || op == '*' || op == '/')
        return true;
    return false;
}

int RPN::countSpaces(std::string & input)
{
    int count = 0;

    for (size_t i = 0; i < input.length(); i++)
    {
        if (std::isspace(input[i]))
            count++;
    }
    if (count)
        count++;
    return count;
}

void RPN::splitString(std::string &input, std::string result[], size_t maxToken)
{
    std::string currentToken;
    size_t tokCount = 0;

    size_t i = 0;
    while (i < input.length())
    {
        if (!currentToken.empty() && tokCount < maxToken
            && (input[i] == 32 || input[i] == '\t'  || input[i] == '\r'))
        {
            result[tokCount] = currentToken;
            tokCount++;
            currentToken.clear();
        }
        else
            currentToken += input[i];
        i++;
    }
    if (!currentToken.empty() && tokCount < maxToken)
    {
        result[tokCount] = currentToken;
        tokCount++;
        currentToken.clear();
    }
}
