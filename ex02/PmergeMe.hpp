
#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <cstdlib>
#include <climits>

class PmergeMe
{
private:
    std::vector<int> veArgs;
    std::deque<int>  deArgs;
public:
    PmergeMe(void);
    PmergeMe(const PmergeMe & other);
    PmergeMe & operator=(const PmergeMe & other);
    ~PmergeMe();

    void simpleParse(int ac, char **av);
    bool validNumber(std::string & in);
    void storeData(int ac, char **av);
    long long strToLong(std::string & str);

    void performSortDisplay(void);
    void display(std::string msg, std::vector<int> & ve);
    void displayFour(std::string msg, std::vector<int> & ve);

    void fordJohnsonSort(std::vector<int>& vec, int left, int right);    
    int binarySearchPos(const std::vector<int>& sorted, int value);
    void fordJohnsonSort(std::deque<int>& deq, int left, int right);
    int binarySearchPos(const std::deque<int>& sorted, int value);
    std::vector<std::size_t> getJacobsthalInsertionOrder(std::size_t n);

    std::vector<int> & getVec(void);
    std::deque<int> & getDeque(void);

};

#endif