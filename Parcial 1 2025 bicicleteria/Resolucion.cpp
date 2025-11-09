#include <iostream>
#include <cstring>

using namespace std;

template<class T>
class vector
{
public:
    vector();
    void push_back(T data); // A
    T& operator[](size_t pos); // B
    void remove(size_t pos);
    void removeOcu(T data); // C
    size_t getSize(){return this->size;};
private:
    T* data;
    size_t capacity; 
    size_t size;
    void resize(size_t newCapacity);
};

template<class T>
vector<T>::vector()
{
    this->capacity = 2;
    this->size = 0;
    this->data = new T[capacity];
}

template<class T>
void vector<T>::resize(size_t newCapacity)
{
    T* aux = new T[newCapacity];
    for(size_t i = 0; i<this->size; i++)
        aux[i] = this->data[i];
    
    delete[] this->data;
    this->data = aux;
    this->capacity = newCapacity;
}

template<class T>
void vector<T>::push_back(T data)
{
    if(this->size==this->capacity)
        resize(this->capacity*2);
    
    this->data[this->size++] = data;
}

template<class T>
T& vector<T>::operator[](size_t pos)
{
    return this->data[pos];
}

template<class T>
void vector<T>::remove(size_t pos)
{
    for(size_t i = pos; i < this->size-1; i++)
        this->data[i] = this->data[i+1];

    this->size--;
}

template<class T>
void vector<T>::removeOcu(T data)
{
    size_t i = 0;
    while(i < this->size)
    {
        if(this->data[i] == data)
        {
            remove(i);
        }else
        {
            i++;
        }
    } 
}      
    
// Comienzo consigna 2 Y 3

class Producto
{
public:
    Producto(int numero, char* descripcion, double precio);
    virtual ~Producto(){delete[] this->descripcion;};
    int getNumero(){return this->numero;};
    char* getDescripcion(){return this->descripcion;};
    virtual double getPrecio() = 0;
protected:
    int numero;
    char* descripcion;
    double precio;
};

Producto::Producto(int numero, char* descripcion, double precio)
{
    this->numero = numero;
    this->descripcion= new char[strlen(descripcion)+1];
    strcpy(this->descripcion,descripcion);
    this->precio = precio;
}

class Parte : public Producto
{
public:
    Parte(int numero, char* descripcion, double precio) : Producto(numero, descripcion, precio){}
    double getPrecio(){return this->precio;}
};

class Bicicleta : public Producto 
{
public:
    Bicicleta(int n, char* d, double p) : Producto(n, d, p){};
    void addParte(Parte* p) { partes.push_back(p);};
    double getPrecio();
private:
    vector<Parte*> partes;
};

double Bicicleta::getPrecio()
{
    double monto = 0;
    for(size_t i = 0; i < this->partes.getSize(); i++)
    {
        monto += this->partes[i]->getPrecio();
    }
    this->precio = monto;
    return this->precio;
}

class Oferta
{
public:
    Oferta(){}; 
    void addProducto(Producto* p) { this->vecProd.push_back(p); };
    double getPrecio();
    friend ostream& operator<<(ostream& os, Oferta& o);
private:
    vector<Producto*> vecProd;
    double precio;
}; 

ostream& operator<<(ostream& os, Oferta& o)
{
    os << "--- OFERTA ---" << endl;
    for(size_t i = 0; i < o.vecProd.getSize(); i++)
    {
       os << " Numero: " << o.vecProd[i]->getNumero() << " Descripcion: " << o.vecProd[i]->getDescripcion() << " Precio: " << o.vecProd[i]->getPrecio();
       os << endl;
    }
    os << "Precio Total de la oferta: " << o.getPrecio();
    return os;
}

double Oferta::getPrecio()
{
    double monto = 0.0;
    for(size_t i = 0; i < this->vecProd.getSize(); i++)
    {
        monto += vecProd[i]->getPrecio();
    }
    monto = monto - monto * 0.20;
    this->precio = monto;
    return this->precio;
}

class Bicicleteria
{
public:
    Bicicleteria(){};
    void addProducto(Producto* p);
    void addOferta(Oferta* o);
    void mostrarDatos();
private:
    vector<Producto*> vecProductos;
    vector<Oferta*> vecOfertas;
};

void Bicicleteria::addProducto(Producto* p)
{
   this->vecProductos.push_back(p);
}

void Bicicleteria::addOferta(Oferta* o)
{
   this->vecOfertas.push_back(o);
}

void Bicicleteria::mostrarDatos()
{
   for(size_t i = 0; i < vecOfertas.getSize(); i++)
   {
        cout<<*vecOfertas[i];
   }
}