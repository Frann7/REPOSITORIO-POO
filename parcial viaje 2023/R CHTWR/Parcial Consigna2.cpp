#include <iostream>
#include <string.h>
class Viaje{
public:
    char * getNombre();
};

class ViajeMixto: public Viaje{
private:
    Viaje ** viajes;
    int numViajes, maxViajes;
public:
    friend std::ostream& operator<<(std::ostream& os, ViajeMixto &vm){
        os << "Viaje mixto: " << vm.getNombre() << std::endl;
        for (int i = 0; i < vm.numViajes; i++)
            os << "Destino " << i+1 << ": " << vm.viajes[i]->getNombre() 
            << " Costo: " << vm.viajes[i]->getMonto() << std::endl; 
        return os;
    }
};