
#include "PmergeMe.hpp"

int main(int ac, char **av)
{
    try
    {
        PmergeMe obj;
        obj.simpleParse(ac, av);
        obj.storeData(ac, av);
        obj.performSortDisplay();
    }
    catch( const std::exception & o)
    {
        // std::cerr << "Error: " << o.what() << '\n';
        std::cerr << "Error\n";
    }
    return 0;
}