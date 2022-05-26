#include <iostream>

int main()
{
    int foo = 6;
    int *bar = &foo;
    
    *bar = 10;

    std::cout << "foo = " << foo << std::endl;
    std::cout << "bar = " << *bar << std::endl;

    return 0;
}