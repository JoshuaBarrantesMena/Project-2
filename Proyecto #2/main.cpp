#include <iostream>
#include "MapEngine.h"

using namespace std;

int main(){

    //openMap();

    NodeRoute ruta1, ruta2, ruta3;

    ruta1.addCoords(10, 20, "r");
    ruta1.addCoords(120, 500, "b");

    ruta2.addCoords(78, 46, "g");
    ruta2.addCoords(1, 2, "y");

    ruta3.addCoords(8, 12, "m");
    ruta3.addCoords(20, 23, "c");

    NodeRouteList lista;

    lista.addRoute(ruta1);
    lista.addRoute(ruta2);
    lista.addRoute(ruta3);

    lista.printAll();

    return 0;
}
