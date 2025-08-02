#include <iostream>
#include <string.h>

class Viaje{
public:
    Viaje(const char * Nombre){
        this->nombre = new char[strlen(Nombre)+1];
        strcpy(this->nombre, Nombre);
    }
    virtual double getMonto() = 0;
    virtual char* getNombre(){
        return nombre;
    }

    friend std::ostream& operator<< (std::ostream& os, Viaje& v){
        os << "Destino: " << v.getNombre() << " Monto: " << v.getMonto();
        return os;
    }

protected:  
    char * nombre;
    double monto;
};

class ViajeComun: public Viaje{
public:
    ViajeComun(const char * Nombre, double Monto): Viaje(Nombre){
        this->monto = Monto;
    }
    double getMonto(){
        return this->monto;
    }
};

class ViajeDestino: public Viaje{
public:
    ViajeDestino(const char * Nombre, double MontoKm, double Km): Viaje(Nombre){
        this->monto = MontoKm;
        this->km = Km;
    }
    double getMonto(){
        return this->monto * this->km;
    }
private:
    double km;
};

class ViajeMixto: public Viaje{
private:
    Viaje ** viajes;
    int numViajes, maxViajes;
    void modVector(int newMax){
        Viaje ** nuevoVector = new Viaje*[newMax];
        for (int i = 0; i < this->numViajes; i++)
            nuevoVector[i] = this->viajes[i];
        delete[] this->viajes;
        this->viajes = nuevoVector;
        this->maxViajes = newMax;
    }
public:
    ViajeMixto(const char * Nombre): Viaje(Nombre), numViajes(0){
        // Iniciamos en 2, para arrancar con un vector de 2. (Porque pinto)
        this->maxViajes = 2;
        this->viajes = new Viaje*[maxViajes];
    }

    void addViaje(Viaje * newViaje){
        if (dynamic_cast<ViajeMixto*>(newViaje)){
            printf("No se puede guardar un viaje mixto dentro de un viaje mixto");
            return; // para no meter un viaje mixto dentro de un viaje mixto.
        }
            
        if (numViajes == maxViajes)
            modVector(this->maxViajes*2);
         viajes[numViajes++] = newViaje;
    }

    double getMonto(){
        this->monto = 0;
        for (int i = 0; i < this->numViajes; i++)
            this->monto += viajes[i]->getMonto();
        return this->monto;
    }
};

class GestorViajes{
private:
    Viaje * viajes[100];
    int numViaje;
public:
    GestorViajes(): numViaje(0) {}
    void addViaje(Viaje * newViaje){
        if (numViaje == 100)
            return; //para no meter mas de 100 viajes
        viajes[numViaje++] = newViaje;
    }

    // Getter de viaje, hecho con una terna. Pregunta si la pos
    // ingresada es menor a la cantidad de viajes cargados, si lo es
    // devuelve un puntero del array, y en caso contrario, 
    // devuelve un null ptr

    // Estructura de terna: 
    // return (condicion) ? ResultadoPorVerdadero : ResultadoPorFalso;
    Viaje * getViaje(int pos){
        return (pos < numViaje)? viajes[pos]: nullptr;
    }

    friend std::ostream& operator<< (std::ostream& os, GestorViajes& gv){
        for (int i = 0; i < gv.numViaje; i++)
            os << *(gv.viajes[i]) << std::endl;
        return os;
    }
};

int main(int argc, char const *argv[])
{
    ViajeMixto * viajelocura = new ViajeMixto("ViajeLocura");
    viajelocura->addViaje(new ViajeComun("trampa", 15.50));
    return 0;
}
