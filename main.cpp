#include "sculptor.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>

using namespace std;

int main(void)
{
    Sculptor m(20,30,40);
    m.setColor(1,0,0,1);
    m.putBox(0,15,0,15,0,0);
    m.putBox(1,14,1,14,1,1);
    m.putBox(6,9,6,9,2,14);
    m.putSphere(8,8,15,7);
    m.writeOFF("teste.off");
    return 0;
}
