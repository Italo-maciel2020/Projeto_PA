#include "sculptor.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>

using namespace std;

int main(void)
{
    Sculptor m(20,30,40);
    m.setColor( 1, 1, 0, 1);
    m.putSphere(8,8,8,4);
    m.cutBox(0,15,0,15,0,7);
    m.cutBox(0,15,0,15,9,16);
    m.putBox(7,9,7,7,9,16);
    m.putBox(3,13,8,9,11,19);
    m.cutBox(4,12,9,9,12,18);
    m.writeOFF("monitor.off");
    return 0;
}
