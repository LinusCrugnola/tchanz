#ifndef SQUARECELL_H
#define SQUARECELL_H

#include <vector>

using namespace std;

class Squarecell
{
private:
    unsigned int g_max;
    unsigned int x,y;
    unsigned int side;
    vector<vector<bool>> grid;
public:
    Squarecell(unsigned int max)
    : g_max(max){
        vector<vector<bool>> __grid(g_max,vector<bool>(g_max, false));
        grid = __grid;
    }
    void test_validation_centered_square(unsigned x, unsigned y, unsigned side, bool centered);
};

#endif