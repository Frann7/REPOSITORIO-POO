#include <iostream>
#include <string.h>
#include "VectorDinamico.cpp" 


class Productos{
public:
    Productos(const char* str, double precio);
    double getprecio();
    char* getcodigo();
    virtual void actualizar_precio()=0;
    friend std::ostream& operator <<(std::ostream& os, Productos& p);
protected:
   char* copystr(const char* str);
   char* codigo;
   double precio;
};

Productos::Productos(const char* str, double precio){
    this->codigo=copystr(str);
    this->precio=precio;
}

char* Productos::copystr(const char* str){
    char* newstr= new char[strlen(str)+1];
    strcpy(newstr, str);
    return newstr;
}

double Productos::getprecio(){
    return this->precio;
}

char* Productos::getcodigo(){
    return this->codigo;
}

std::ostream& operator <<(std::ostream& os, Productos& p){
    os << "Codigo " << p.getcodigo() << std::endl;
    os << "Precio "<< p.getprecio() << std::endl;
    return os; 
}

class Nacionales : public Productos{
public:
    Nacionales(char* codigo, double precio, float porcentaje) : Productos(codigo, precio) {this->porcentaje=porcentaje;}
    void actualizar_precio();
private:
    float porcentaje;
};

void Nacionales::actualizar_precio(){
    double newprecio;
    newprecio=(this->precio)+(this->precio*porcentaje);
    this->precio=newprecio;
}

class Extranjeros : public Productos{
public:
    Extranjeros(char* codigo, double precio, float cotizacion) : Productos(codigo, precio){this->cotizacion=cotizacion; this->cotizacion_nueva=cotizacion;}
    void actualizar_precio();
    void setcotizacion(float cotizacion_nueva){this->cotizacion_nueva=cotizacion_nueva;}
private:
    float cotizacion;
    float cotizacion_nueva;
};

void Extranjeros::actualizar_precio(){
    double newprecio=0;
    newprecio=(this->precio/this->cotizacion)*this->cotizacion_nueva;
    this->precio=newprecio;
}

class Ofertas : public Productos{
public:
    Ofertas(char* codigo) : Productos(codigo, 0.0){}
    void add_producto(Productos* newproducto);
    void remove_producto(Productos* producto);
    void actualizar_precio();
private:
    vector<Productos*> productos_ofertas;
};

void Ofertas::add_producto(Productos* newproducto){
    if(dynamic_cast<Ofertas*>(newproducto))
        return;

    productos_ofertas.add(newproducto);
}

void Ofertas::remove_producto(Productos* newproducto){
    productos_ofertas.removeData(newproducto);
}
void Ofertas::actualizar_precio(){
    double precio_=0;
    for(size_t i=0; i<productos_ofertas.getsize(); i++)
    precio_+=productos_ofertas[i]->getprecio();
    precio_=(precio_)-(precio_*0.10);
    this->precio=precio_;
}

class Gestora{
public:
    Gestora(){};
    void add(Productos* newprod);
    void mostrar();
    void actualizar();
private:
    vector<Productos*> datos;
};

void Gestora::add(Productos* newprod){
    if(datos.getsize()<100)
    datos.add(newprod);
}

void Gestora::mostrar(){
    for(size_t i=0; i<datos.getsize(); i++)
    std::cout<<*datos[i];
}

void Gestora::actualizar(){
    for(size_t i=0; i<datos.getsize(); i++)
        datos[i]->actualizar_precio();
}

int main(){
    Gestora Gestor;
    Productos* producto1= new Nacionales("00", 100000, 0.10);
    Productos* producto2= new Extranjeros("01", 100, 1000);
    Ofertas* producto_enoferta= new Ofertas("02");

    producto_enoferta->add_producto(producto1);

    Gestor.add(producto1);
    Gestor.add(producto2);
    Gestor.add(producto_enoferta);

    std::cout<<"Productos y precios iniciales \n";
    Gestor.mostrar();

    Extranjeros* ext = (Extranjeros*)producto2; // Cast simple Esto le dice al compilador: "Yo sé que producto2 apunta realmente a un objeto Extranjeros, así que tratalo como tal"
    ext->setcotizacion(1100);
    
    Gestor.actualizar();

    std::cout<<"Productos y precios actualizados \n";

    Gestor.mostrar();

    return 0;
}

