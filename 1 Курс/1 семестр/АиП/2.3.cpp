#include <iostream>
int main()
{
	bool f;
	int x;
	int y;
	f = false;
	std::cin >> x >> y;
	if (x >= 0 && y >= 0)
	{
		std::cout << "1";
		f = true;
	}
	if (x <= 0 && y >= 0)
	{
		if (f)
		{
			std::cout << ", 2";
		}
		else
		{
			std::cout << "2";
			f = true;
		}
	}
	if (x <= 0 && y <= 0)
	{
		if (f)
		{
			std::cout << ", 3";
		}
		else
		{
			std::cout << "3";
			f = true;
		}
	}
	if (x >= 0 && y <= 0)
	{
		if (f)
		{
			std::cout << ", 4";
		}
		else
		{
			std::cout << "4";
			f = true;
		}
	}
}