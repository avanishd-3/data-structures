#include "diagonal_matrix.hpp"

int main()
{
    int d;
    std::cout<<"Enter Dimensions: ";
    std::cin>>d;
    
    DiagonalMatrix<int> dm(d);
    int x;
    std::cout<<"Enter All Elements: ";
    for(int i=1;i<=d;i++)
    {
        std::cin >> x;
        dm[i-1] = x;
    }
    std::cout << dm << std::endl;
    return 0;
}