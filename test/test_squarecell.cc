#include "../src/squarecell.h"
#include <iostream>


int main(){
    Squarecell testCell(8);
    //Test true
    testCell.test_validation_centered_square(1,1,0,1);
    //Test limit
    testCell.test_validation_centered_square(5,7,0,1);
    //Test fail
    testCell.test_validation_centered_square(8,8,0,1);
    //Test square true
    testCell.test_validation_centered_square(8,8,0,1);
    //Test square side to big
    testCell.test_validation_centered_square(8,8,0,1);
    //Test square
    testCell.test_validation_centered_square(8,8,0,1);
    //Test square
    testCell.test_validation_centered_square(8,8,0,1);

}
