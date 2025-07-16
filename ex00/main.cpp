
#include "BitcoinExchange.hpp"

int main(int ac, char **av)
{

    (void)av;
    if (ac != 2)
    {
        std::cerr << "Error: Usage: ./btc <input.txt>\n";
        return 1;
    }
    BitcoinExchange btc;
    if (!(btc.processDataFile("data.csv")))
    {
        std::cerr << "Error: Can't Process Database File\n";
        return 2;
    }
    if (!btc.performOperation(av[1]))
    {
        std::cerr << "Error: Can't process Input File\n"; return 3;
    }
    return 0;
}