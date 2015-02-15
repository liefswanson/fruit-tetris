#include "../rangeMap.hpp"

#include <iostream>

int main(int argc, char *argv[])
{
    std::cout << mapTo(0, 10, 0, 100, 50) << std::endl;
	std::cout << mapTo(0, 10, 0, 100, 1) << std::endl;
    std::cout << mapTo(5, 500, 25, 137, 25) << std::endl;
	std::cout << mapTo(0, 10, 10, 20, 5) << std::endl;

	std::cout << mapTo(0, 100, -1, 1, 50) << std::endl;
	std::cout << mapTo(0, 100, -1, 1, 25) << std::endl;
	std::cout << mapTo(0, 100, -1, 1, 75) << std::endl;
	std::cout << mapTo(0, 100, -1, 1, 10) << std::endl;
	std::cout << mapTo(0, 100, -1, 1, 1) << std::endl;
	std::cout << mapTo(0, 100, -1, 1, 100) << std::endl;
	std::cout << mapTo(0, 100, -1, 1, 0) << std::endl;
	return 0;
}
 
