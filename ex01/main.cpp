
#include "RPN.hpp"

int main(int ac, char **av)
{
    if (ac != 2)
    {
        std::cerr << "Error: Usage: ./RPN <rpn_expresion>\n";
        return 1;
    }
    try
    {
        RPN calcul;
        calcul.processCalculation(av[1]);
        calcul.print();
    }
    catch(const std::exception& e)
    {
        // std::cerr << "Error: " << e.what() << '\n';
        std::cerr << "Error\n";
    }
    return 0;
}