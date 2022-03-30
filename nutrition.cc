/****************************************************************!
 \file     nutrition.cc
 \author   Léo Brückl, Linus Crugnola
 \date     30.03.2022
 \brief    nutrition implementation
*****************************************************************/

#include "nutrition.h"
#include "message.h"


using namespace std;

Nutrition Nutrition::data_validation(istringstream& data){
    unsigned x_coor, y_coor;
    if(!(data >> x_coor >> y_coor)) cout << "reading error!" << endl;
    square_validation({x_coor,y_coor,3,1}); // throws error if invalid
    if(square_superposition({x_coor,y_coor,1,1})){
        cout << message::food_overlap(x_coor,y_coor) ;
        exit(EXIT_FAILURE);
    }
    Nutrition nutrition(x_coor, y_coor);
    return nutrition;
}


