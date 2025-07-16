#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <string>
#include <algorithm>
#include <stack>

class RPN
{
private:
    std::stack<long long> stData;
public:
    RPN(void);
    RPN(const RPN & other);
    RPN & operator=(const RPN & other);
    ~RPN(void);

    void processCalculation(std::string  input);
    long long performOperation(long long n1, long long n2, char op);
    void print(void);
    bool firstCheck(std::string argv);
    int countSpaces(std::string & input);
    void splitString(std::string &input, std::string result[], size_t maxToken);
    bool validNumTok(std::string & input);
    bool isOperator(char c);
    bool isValidToken(char c);

};

#endif