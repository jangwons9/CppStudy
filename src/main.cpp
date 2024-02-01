#include <iostream>
#include "headertry.h"


int main(){
    const char* a = new char[5] {'h', 'a', 'h', 'a', '\0'};
    Log(a);
    
    delete[] a;
    int numbers[] = {1, 2, 3, 4, 5};
    std::cout << "C++11 feature: Range-based for loop - ";
    for (const auto& number : numbers) {
        std::cout << number << " ";
    }



    
}


void Log(const char* message){
    
    for (int i=0 ; i<=strlen(message) ; i++){

    std::cout << message[i] << std::endl;
    }
}