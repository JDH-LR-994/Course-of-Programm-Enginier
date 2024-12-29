#include <iostream>

char * string_for_unique_sym(char* new_string, char* my_string);

namespace lenght{
    const int LENGHT_FIRST_STRING = 33;
    const int LENGHT_OUTPUT_STRING = 50; 
}

int main(){
    char my_string[lenght::LENGHT_FIRST_STRING];
    std::cin.getline(my_string, lenght::LENGHT_FIRST_STRING);
    char new_string[lenght::LENGHT_OUTPUT_STRING] {'\0'};
    std::cout << string_for_unique_sym(new_string, my_string);
    
}

char * string_for_unique_sym(char* new_string, char* my_string){
    char ascii[128] {0};
    int counter = 0;
    for (int i = 0; i < lenght::LENGHT_FIRST_STRING; i++){
        if (my_string[i] == '\0'){
            break;
        }
        ascii[my_string[i]]++;
    }
    bool without_unique = true;
    for (int i = 0; i < 128; i++){

        if (ascii[i] == 1){
            new_string[counter] = i;            
            counter++;
            without_unique = false;
        }
        
    }
    if (without_unique){
        return (char *)"No unique symbols";
    }
    return new_string;
}
