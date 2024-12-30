#include <iostream>
int main()
{
	int value;
	std::cin >> value;
	for (int i = 1; i < 100; i += 2) {
		std::cout << i;
	}
}