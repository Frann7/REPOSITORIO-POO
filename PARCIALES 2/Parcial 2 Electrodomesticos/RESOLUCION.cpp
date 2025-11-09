#include <iostream>
#include <cstring>
#include <string>
#include <vector> // Vector STL
#include <algorithm> // Para usar funcionalidades como Sort
#include <fstream> // Archivos
#include <map> // Mapa STL para el item D

// Estructura para el archivo binario
struct struct_producto
{
    int cod;
    char nombre[50];
    char marca[20];
    char tipo;
    double precio;
};

// Clase abstracta producto
class producto
{
    protected:
        int cod;
        char* nombre;
        char* marca;
        double precio;
    public:
        producto(int cod, char* nombre, char* marca, double precio);
        virtual void actualizar_precio() = 0;
        virtual char getTipo() = 0; // Sirve para identificar el tipo de producto para leer un archivo binario con esta estructura(ver metodo leer() en clase gestora)
        int getcod() const;
        void setcod(int cod);
        char* getnombre() const;
        void setnombre(char* nombre);
        char* getmarca() const;
        void setmarca(char* marca);
        double getprecio();
        void setprecio(double precio);
};

producto::producto(int cod, char* nombre, char* marca, double precio)
{
    this->cod = cod;
    this->nombre = new char[strlen(nombre)+1];
    strcpy(this->nombre, nombre);
    this->marca = new char[strlen(marca)+1];
    strcpy(this->marca, marca);
    this->precio = precio;
}

int producto::getcod() const
{
    return this->cod;
}

void producto::setcod(int cod)
{
    this->cod = cod;
}

char* producto::getnombre() const
{
    return this->nombre;
}

void producto::setnombre(char* nombre)
{
    this->nombre = nombre;
}

char* producto::getmarca() const
{
    return this->marca;
}

void producto::setmarca(char* marca)
{
    this->marca = marca;
}

double producto::getprecio(){
    return this->precio;
}

void producto::setprecio(double precio)
{
    this->precio = precio;
}

// Clase hija con productos nacionales
class nacional : public producto
{
    public:
        nacional(int cod, char* nombre, char* marca, double precio);
        void actualizar_precio();
        char getTipo();
};

nacional::nacional(int cod, char* nombre, char* marca, double precio) : producto(cod, nombre, marca, precio)
{
}

void nacional::actualizar_precio()
{
    this->precio= this->precio + this->precio * 0.02;
}

char nacional::getTipo()
{
    return 'N';
}

// Clase hija con productos importados
class importado : public producto
{
    private:
        double valor_dolar;// Atributo necesario para el actualizar precio
    public:
        importado(int cod, char* nombre, char* marca, double precio, double valor_dolar);
        void actualizar_precio();
        char getTipo();
        double getValor_dolar() const;
        void setValor_dolar(double valor);
};

importado::importado(int cod, char* nombre, char* marca, double precio, double valor_dolar) : producto(cod, nombre, marca, precio)
{
    this->valor_dolar = valor_dolar;
}

void importado::actualizar_precio()
{
    this->precio = this->precio + this->precio * (valor_dolar/100);
}

char importado::getTipo()
{
    return 'I';
}

double importado::getValor_dolar() const
{
    return valor_dolar;
}

void importado::setValor_dolar(double valor)
{
    this->valor_dolar = valor;
}

// Clase hija con productos de jardin
class jardin : public producto
{
    public:
        jardin(int cod, char* nombre, char* marca, double precio);
        void actualizar_precio();
        char getTipo();
};

jardin::jardin(int cod, char* nombre, char* marca, double precio) : producto(cod, nombre, marca, precio)
{
}

void jardin::actualizar_precio()
{
    this->precio = this->precio + this->precio * (0.10 /12);
}

char jardin::getTipo()
{
    return 'J';
}

// Gestor
class Empresa
{
public:
    Empresa();
    void leer();
    void PreciosActualizados();
    void listado();
    void prodXmarca();
    void masCaro();
    void masBarato();
    double getValorUSD() const;
    void setValorUSD(double valor);
    void generarEjemploArchivo(); // Metodo para generar un archivo de ejemplo
private:
    std::vector<producto*> vecProd;
    double valorUSD;
};

Empresa::Empresa()
{
}

double Empresa::getValorUSD() const
{
    return this->valorUSD;
}

void Empresa::setValorUSD(double valor)
{
    this->valorUSD = valor;
}

// Leer archivo y pasarlo a memoria
void Empresa::leer()
{
    std::ifstream archivo("productos.dat", std::ios::binary);
    if (archivo.fail())
    {
        std::cout<<" ERROR\n";
    }else
    {
        struct_producto struProd;
        while(archivo.read((char*)&struProd,sizeof(struProd))){
            switch (struProd.tipo)
            {
            case 'N':
                this->vecProd.push_back(new nacional(struProd.cod, struProd.nombre, struProd.marca, struProd.precio));
                break;
            case 'I':
                this->vecProd.push_back(new importado(struProd.cod, struProd.nombre, struProd.marca, struProd.precio, this->valorUSD));
                break;
            case 'J':
                this->vecProd.push_back(new jardin(struProd.cod, struProd.nombre, struProd.marca, struProd.precio));
                break;
            default:
                break;
            }
        }
    }
    archivo.close();
}

// Escribir archivo con precios actualizados (pasar de memoria al archivo)
 void Empresa::PreciosActualizados()
 {
    std::ofstream archivo("Productos_actualizados.dat", std::ios::binary);
    if(archivo.fail())
    {
        std::cout << " ERROR\n";;
    }else
    {
        struct_producto struProd;
        for(size_t i = 0; i<vecProd.size(); i++)
        {
            producto* prod = this->vecProd[i];

            prod->actualizar_precio();// Polimorfismo

            struProd.cod = prod->getcod();           
            strcpy(struProd.nombre, prod->getnombre());
            strcpy(struProd.marca, prod->getmarca());
            struProd.tipo = prod->getTipo();// Polimorfismo
            struProd.precio = prod->getprecio();

            archivo.write((char*)&struProd,sizeof(struProd));
        }
    }
    archivo.close();
 }

// Generar archivo txt con datos ordenados
void Empresa::listado()
{
    std::ofstream archivo("listado.dat");
    if(archivo.fail()) return;

    sort(this->vecProd.begin(), this->vecProd.end(), [](producto* a, producto* b)
                            { return strcmp(a->getnombre(),b->getnombre()) < 0; });

    for (producto* p : this->vecProd)
    {
        archivo << "Nombre: " << p->getnombre() << " Marca: " << p->getmarca() << ".........$ Precio: " << p->getprecio();
        archivo << std::endl;  
    }
}

void Empresa::prodXmarca()
{
    std::map <std::string, int> productos_marca;
    std::string marca;
   for (producto* prod : this->vecProd)
    {
    marca = prod->getmarca();
    productos_marca[marca] += 1;
    }
    for (auto it = productos_marca.begin(); it != productos_marca.end(); ++it)
    {
        std::cout << " Marca: " << it->first << " Cantidad: " << it->second;
        std::cout << std::endl;
    }
}

void Empresa::masBarato()
{
    auto it_barato = std::min_element(this->vecProd.begin(), this->vecProd.end(),[](producto* a, producto* b)
                                                                { return a->getprecio() < b->getprecio(); });
    producto* prod_masBarato = *it_barato; // el resultado es un iterator

    std::cout << "El producto mas barato es: " << prod_masBarato->getnombre();
    std::cout << std::endl;
}

void Empresa::masCaro()
{
    auto it_caro = std::max_element(this->vecProd.begin(), this->vecProd.end(),[](producto* a, producto* b)
                                                              { return a->getprecio() < b->getprecio(); });
    producto* prod_masCaro = *it_caro;

    std::cout << "El producto mas caro es: " << prod_masCaro->getnombre();
    std::cout << std::endl; 
}

// Metodo para generar un archivo de ejemplo
void Empresa::generarEjemploArchivo()
{
    std::ofstream archivo("productos.dat", std::ios::binary);
    if (archivo.fail())
    {
        std::cout<<" ERROR al crear el archivo\n";
    }else
    {
        struct_producto struProd;

        struProd.cod = 1;
        strcpy(struProd.nombre, "Heladera");
        strcpy(struProd.marca, "LG");
        struProd.tipo = 'N';
        struProd.precio = 50000.0;
        archivo.write((char*)&struProd,sizeof(struProd));

        struProd.cod = 2;
        strcpy(struProd.nombre, "Cortadora de cesped");
        strcpy(struProd.marca, "Honda");
        struProd.tipo = 'J';
        struProd.precio = 15000.0;
        archivo.write((char*)&struProd,sizeof(struProd));

        struProd.cod = 3;
        strcpy(struProd.nombre, "Microondas");
        strcpy(struProd.marca, "Samsung");
        struProd.tipo = 'I';
        struProd.precio = 20000.0;
        archivo.write((char*)&struProd,sizeof(struProd));
    }
    archivo.close();
}