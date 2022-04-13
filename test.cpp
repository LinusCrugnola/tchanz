#include "test/testfunctions.h"

#include <iostream>

int main(){
    std::cout << "\n------------------------- Start tests ------------------------------" << std::endl;
    std::cout << "\n------------------------- Test squarecell ------------------------------" << std::endl;
    test_squarecell();
    //test_simulation();
    //test_nutrition();
    std::cout << "\n------------------------- Test GUI ------------------------------" << std::endl;
    test_gui();
    std::cout << "------------------------- Finished tests ------------------------------\n" << std::endl;
}
