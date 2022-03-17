#include <vector>

class Squarecell
{
private :
    unsigned int g_max;
    unsigned int x,y;
    unsigned int side;
    vector<vector<bool>> grid(g_max,vector<bool>(g_max));
public  :
    void test_validation_square(x,y);
};