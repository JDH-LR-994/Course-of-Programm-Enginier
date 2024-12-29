#include <iostream>
bool isName(char* argument){
	int i = 0;
	int count_ = 0;
	int count = 0;
	while (argument[i] != '\0'){
		if ((((int)(argument[i]) >= 65) && ((int)(argument[i]) <= 90)) || (((int)(argument[i]) >= 97) && ((int)(argument[i]) <= 122)) || (((int)(argument[i]) >= 48) && ((int)(argument[i]) <= 57)) || ((int)(argument[i]) == 95)){
			if ((((int)(argument[i]) >= 48) && ((int)(argument[i]) <= 57)) && (i == 0)){
				return 0;
			}
			if ((int)(argument[i]) == 95){
				count_ += 1;
			}
		}
		else{
			return 0;	
		}
		count++;
		i++;
	}
	if (count_ == count){
		return 0;
	}
	else{
		return 1;
	}
}
int main()
{
	const int LENGTH_MAX = 25;
	char text[LENGTH_MAX];
	std::cin >> text;
	if (isName(text)){
	    std::cout << "true";
	}
	else{
	    std::cout << "false";
	}
}