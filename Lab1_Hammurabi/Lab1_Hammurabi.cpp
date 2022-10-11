#include <iostream>
#include "City.h"
#include <clocale>

int main()
{
    setlocale(LC_CTYPE, "rus");
    City *city = new City();
    city->run_game();
    std::cout << "Hello World!\n";
}