

#include "PmergeMe.hpp"

PmergeMe::PmergeMe(void) {}

PmergeMe::~PmergeMe(void) {}

PmergeMe::PmergeMe(const PmergeMe & other) : veArgs(other.veArgs) , deArgs(other.deArgs) {}

PmergeMe & PmergeMe::operator=(const PmergeMe & other)
{
    if (this != &other)
    {
        veArgs = other.veArgs;
        deArgs = other.deArgs;
    }
    return *this;
}

void PmergeMe::simpleParse(int ac, char **av)
{
    if (ac < 2)
        throw std::runtime_error("usage: args count < minimum = 2");
    for (int i = 1; i < ac; i++)
    {
        std::string str  = av[i];
        if (!validNumber(str))
            throw std::runtime_error("not a valid number");
        str.clear();
    }
}

bool PmergeMe::validNumber(std::string & in)
{
    for (size_t i = 0; i < in.length(); i++)
        if (!std::isdigit(in[i]) && in[i] != '+')
            return false;
    return true;
}

void PmergeMe::storeData(int ac, char **av)
{
    for (int i = 1; i < ac; i++)
    {
        std::string s = av[i];
        long long tmp = strToLong(s);
        if (tmp < 0)
            throw std::runtime_error("a negative integer in the sequence");
        if (tmp > INT_MAX )
            throw std::runtime_error("value is bigger than 'MAX_INT'");
        int res = static_cast<int>(tmp);
        veArgs.push_back(res);
        deArgs.push_back(res);
    }
}

long long PmergeMe::strToLong(std::string & str)
{
    long long result = 0; 
    result = std::atoll(str.c_str());
    return result;
}

void PmergeMe::performSortDisplay(void)
{
    clock_t start;
    clock_t end;


    display("Before: ", getVec());

    /*managing vectore*/
    start = clock();
    std::vector<int> veCopy = this->getVec();
    fordJohnsonSort(veCopy, 0, veCopy.size() - 1);
    end = clock();
    double veTime = (double)(end - start) * 1e6 / CLOCKS_PER_SEC;

    /*managing deque*/
    start = clock();
    std::deque<int> deCopy = this->getDeque();
    fordJohnsonSort(deCopy, 0, deCopy.size() - 1);
    end = clock();
    double deTime = (double)(end - start) * 1e6 / CLOCKS_PER_SEC;

    display("After: ", veCopy);

    std::cout << "Time to process a range of " << veCopy.size();
    std::cout << " elements with std::vector<int> : " << veTime << " us\n";
    std::cout << "Time to process a range of " << deCopy.size();
    std::cout << " elements with std::deque<int> : " << deTime << " us\n";
    
}


int PmergeMe::binarySearchPos(const std::vector<int>& sorted, int value) 
{
    int low = 0, high = sorted.size();
    while (low < high)
    {
        int mid = (low + high) / 2;
        if (value < sorted[mid])
            high = mid;
        else
            low = mid + 1;
    }
    return low;
}

void PmergeMe::fordJohnsonSort(std::vector<int>& vec, int left, int right) 
{
    int size = right - left + 1;
    if (size <= 1)
        return;

    std::vector<int> mainList;
    std::vector<int> insertList;
    bool hasLeftover = (size % 2 != 0);
    int pairCount = size / 2;

    for (int i = 0; i < pairCount; ++i)
    {
        int a = vec[left + 2*i];
        int b = vec[left + 2*i + 1];
        if (a > b)
        {
            mainList.push_back(a);
            insertList.push_back(b);
        }
        else
        {
            mainList.push_back(b);
            insertList.push_back(a);
        }
    }

    int leftover = 0;
    if (hasLeftover)
        leftover = vec[left + size - 1];
    fordJohnsonSort(mainList, 0, mainList.size() - 1);
    std::vector<std::size_t> insertionOrder = getJacobsthalInsertionOrder(insertList.size());
    for (std::size_t i = 0; i < insertionOrder.size(); ++i)
    {
        std::size_t idx = insertionOrder[i];
        int pos = binarySearchPos(mainList, insertList[idx]);
        mainList.insert(mainList.begin() + pos, insertList[idx]);
    }

    if (hasLeftover)
    {
        int pos = binarySearchPos(mainList, leftover);
        mainList.insert(mainList.begin() + pos, leftover);
    }
    for (int i = 0; i < size; ++i)
        vec[left + i] = mainList[i];
}


int PmergeMe::binarySearchPos(const std::deque<int>& sorted, int value) 
{
    int low = 0, high = sorted.size();
    while (low < high) 
    {
        int mid = (low + high) / 2;
        if (value < sorted[mid])
            high = mid;
        else
            low = mid + 1;
    }
    return low;
}

void PmergeMe::fordJohnsonSort(std::deque<int>& dequ, int left, int right) 
{
    int size = right - left + 1;
    if (size <= 1)
        return;

    std::deque<int> mainList;
    std::deque<int> insertList;
    bool hasLeftover = (size % 2 != 0);
    int pairCount = size / 2;

    for (int i = 0; i < pairCount; ++i)
    {
        int a = dequ[left + 2*i];
        int b = dequ[left + 2*i + 1];
        if (a > b)
        {
            mainList.push_back(a);
            insertList.push_back(b);
        }
        else
        {
            mainList.push_back(b);
            insertList.push_back(a);
        }
    }
    int leftover = 0;
    if (hasLeftover)
        leftover = dequ[left + size - 1];
    fordJohnsonSort(mainList, 0, mainList.size() - 1);
    std::vector<std::size_t> insertionOrder = getJacobsthalInsertionOrder(insertList.size());
    for (std::size_t i = 0; i < insertionOrder.size(); ++i)
    {
        std::size_t idx = insertionOrder[i];
        int pos = binarySearchPos(mainList, insertList[idx]);
        mainList.insert(mainList.begin() + pos, insertList[idx]);
    }
    if (hasLeftover)
    {
        int pos = binarySearchPos(mainList, leftover);
        mainList.insert(mainList.begin() + pos, leftover);
    }
    for (int i = 0; i < size; ++i)
        dequ[left + i] = mainList[i];
}

/*
Jacobthal nums
J(0) = 0
J(1) = 1
J(n) = J(n-1) + 2 * J(n-2)
*/

std::vector<std::size_t> PmergeMe::getJacobsthalInsertionOrder(std::size_t n) 
{
    std::vector<std::size_t> jacobIdx;
    std::vector<bool> used(n, false);

    size_t j1 = 1;
    size_t j2 = 0;  // J(1), J(0)

    while (j1 < n) 
    {
        if (!used[j1]) 
        {
            jacobIdx.push_back(j1);
            used[j1] = true;
        }
        std::size_t next = j1 + 2 * j2;
        j2 = j1;
        j1 = next;
    }
    for (std::size_t i = 0; i < n; ++i) 
    {
        if (!used[i]) 
        {
            jacobIdx.push_back(i);
        }
    }
    return jacobIdx;
}

void PmergeMe::display(std::string msg, std::vector<int> & ve)
{
    if (ve.size() > 5)
    {
        displayFour(msg, ve);
        return;
    }
    std::cout << msg ;
    std::vector<int>::iterator it = ve.begin();
    for (; it != ve.end(); ++it)
    {
        std::cout << " " << *it;
    }
    std::cout << '\n';
}

void PmergeMe::displayFour(std::string msg, std::vector<int> & ve)
{
    std::cout << msg ;
    std::vector<int>::iterator it = ve.begin();
    for(int i = 0; i < 4; i++)
    {
        std::cout << " " << *it;
        ++it;
    }
    std::cout << " [...]\n";
}

std::vector<int> & PmergeMe::getVec(void) { return this->veArgs; }

std::deque<int> & PmergeMe::getDeque(void) { return this->deArgs; }