/******************************************************************************!
 * @file     nutrition.cc
 * @author   Léo Brückl <leo.bruckl@epfll.ch>            70 %
 *           Linus Crugnola <linus.crugnola@epfl.ch>     30 %
 * @version  1.0
 * @date     01.04.2022
 *******************************************************************************/

#include "nutrition.h"

#include <iostream>

#include "error_squarecell.h"
#include "message.h"

using namespace std;

Nutrition::Nutrition(unsigned x_coor, unsigned y_coor)
    : x(x_coor), y(y_coor) {
    square_add({x, y, 1, 1});
}

Nutrition* Nutrition::data_validation(istringstream& data) {
    Nutrition* ptr = nullptr;
    unsigned x_coor, y_coor;
    if (!(data >> x_coor >> y_coor)) cout << "reading error!" << endl;

    square_validation({x_coor, y_coor, 3, 1}); // throws error if invalid

    if (square_superposition({x_coor, y_coor, 1, 1})) {
        cout << message::food_overlap(x_coor, y_coor);
        exit(EXIT_FAILURE);
    }

    // Generate nutrition
    ptr = new Nutrition(x_coor, y_coor);
    return ptr;
}