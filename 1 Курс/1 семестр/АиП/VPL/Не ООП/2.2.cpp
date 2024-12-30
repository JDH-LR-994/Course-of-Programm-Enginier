#include <iostream>
int main()
{
	int a;
	int b;
	int c;
	std::cin >> a >> b >> c;
	bool f1;
	bool f2;
	if ((a % 2 == 0) || (b % 2 == 0) || (c % 2 == 0))
	{
		f2 = true;
	}
	if ((a % 2 == 1) || (b % 2 == 1) || (c % 2 == 1))
	{
		f1 = true;
	}
	if (f1 && f2)
	{
		std::cout << "YES";
	}
	else
	{
		std::cout << "NO";
	}
}