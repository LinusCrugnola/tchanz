/******************************************************************************!
* @file     nutrition.cc
* @author   Léo Brückl, Linus Crugnola
* @version  1.0
*******************************************************************************/

#include "nutrition.h"
#include "message.h"

using namespace std;

//Verification if a food point fits in the grid and if it has a distance bigger than 1 
//from the border. Then it verifies if it overlaps with another entity.
Nutrition* Nutrition::data_validation(istringstream& data){
    Nutrition* ptr = nullptr;
    unsigned x_coor, y_coor;
    if(!(data >> x_coor >> y_coor)) cout << "reading error!" << endl;
    square_validation({x_coor,y_coor,3,1}); // throws error if invalid
    if(square_superposition({x_coor,y_coor,1,1})){
        cout << message::food_overlap(x_coor,y_coor) ;
        exit(EXIT_FAILURE);
    }
    ptr = new Nutrition(x_coor, y_coor);
    return ptr;
}


