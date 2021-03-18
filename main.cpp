#include "sculptor.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>

using namespace std;

int main(void)
{
    Sculptor m(2,3,4);
    m.setColor(1,0,0,1);
    m.putBox(0,1,0,1,0,1);
    m.cutBox(0,0,0,0,0,0);
    m.writeOFF("PA.off");
    return 0;
}
