#include <iostream>
int main()
{
	int a;
	int sum = 0;
	std::cin >> a;
	if (a <= 0) {
		std::cout << "ERROR:not a natural number";
		return 0;
	}
	for (int i = 1; i < a; i++) {
		if (a % i == 0) {
			sum += i;
		}
	}
	if (a == sum) {
		std::cout << "TRUE";
	}
	else {
		std::cout << "FALSE";
	}
}