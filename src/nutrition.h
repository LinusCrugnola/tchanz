/****************************************************************!
 \file     nutrition.h
 \author   Léo Brückl, Linus Crugnola
 \date     22.03.2022
 \brief    nutrition interface
*****************************************************************/
 #ifndef NUTRITION_H
 #define NUTRITION_H

 #include "squarecell.h"
 #include "message.h"
 #include "error_squarecell.h"

 class Nutrition
 {
     private:
        unsigned x,y;
        double val_food;
     public:
         static bool data_validation(unsigned x_coor, unsigned y_coor);
         Nutrition(unsigned x_coor, unsigned y_coor) : x(x_coor) , y(y_coor)
         {
             square_add({x,y,1,1});
         }
 };

#endif
 





 