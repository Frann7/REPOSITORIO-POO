#include <iostream>
#include <cstring>
#include <algorithm>
#include <fstream> 
#include <vector>
#include <numeric>
#include <map>

using namespace std;

struct struCatalogo
{
    int nro;
    char nombre[200];
    char tipo;
};

struct struVotacion
{
    int nro;
    int votacion;
};

class Catalogo
{
public:
    Catalogo(int nro, const char* nom, char tipo);
    void addVotacion(int v);
    size_t getCantVotos();
    double getValoracion();
    int getNro() const;
    void setNro(int n);
    const char* getNombre() const;
    void setNombre(const char* n);
    char getTipo() const;
    void setTipo(char t);
    
private:
    vector<int> vecVot; 
    int nro;
    char* nombre;
    char tipo;
};

Catalogo::Catalogo(int nro, const char* nom, char tipo)
{
    this->nro = nro;
    this->nombre = new char[strlen(nom)+1];
    strcpy(this->nombre, nom);
    this->tipo = tipo;
}

void Catalogo::addVotacion(int v)
{
    this->vecVot.push_back(v);
}

size_t Catalogo::getCantVotos()
{
    return this->vecVot.size();
}

double Catalogo::getValoracion()
{
    if(this->vecVot.empty()) return 0.0;
    double suma = accumulate(this->vecVot.begin(), this->vecVot.end(), 0);
    return suma / this->vecVot.size();
}

int Catalogo::getNro() const
{
    return this->nro;
}

void Catalogo::setNro(int n)
{
    this->nro = n;
}

const char* Catalogo::getNombre() const
{
    return this->nombre;
}

void Catalogo::setNombre(const char* n)
{
    this->nombre = new char[strlen(n)+1];
    strcpy(this->nombre, n);
}

char Catalogo::getTipo() const
{
    return this->tipo;
}

void Catalogo::setTipo(char t)
{
    this->tipo = t;
}

class Plataforma
{
public:
    Plataforma();
    void agregarCatalogo(Catalogo c);
    void leerDatos();
    void mostrarDatos();
    void escribirDatos();
    void mayorValoracion();
    void masVotadas();
    void cantVotos();
private:
    vector<Catalogo> vecCat;
};

Plataforma::Plataforma()
{
}

void Plataforma::agregarCatalogo(Catalogo c)
{
    this->vecCat.push_back(c);
}

void Plataforma::leerDatos()
{
    ifstream archivoCatalogo("Catalogo.dat", ios::binary);
    if(archivoCatalogo.fail()) return;

    struCatalogo struC;
    while(archivoCatalogo.read((char*)&struC,sizeof(struC)))
    {
        this->agregarCatalogo(Catalogo(struC.nro, struC.nombre, struC.tipo));
    }
    archivoCatalogo.close();

    ifstream archivoVotacion("Votaciones.dat", ios::binary);
    if(archivoVotacion.fail()) return;

    struVotacion struV;
    while(archivoVotacion.read((char*)&struV,sizeof(struV)))
    {
        for(Catalogo c : this->vecCat)
        {
            if(c.getNro() == struV.nro)
            {
                c.addVotacion(struV.votacion);
            }
        }
    }
}

void Plataforma::mostrarDatos()
{
    cout << "Catalogo de Plataforma:" << endl;
    for(Catalogo c : this->vecCat)
    {
        cout << "Nro: " << c.getNro() << ", Nombre: " << c.getNombre() 
             << ", Tipo: " << c.getTipo() << ", Cantidad de Votos: " << c.getCantVotos()
             << ", Valoracion Promedio: " << c.getValoracion() << endl;
    }
}

void Plataforma::escribirDatos()
{
    ofstream archivo("Datos.dat");
    if(archivo.fail()) return;

    for(Catalogo c : this->vecCat)
    {
    archivo << "Nombre: " << c.getNombre() << ".........Valoracion: " << c.getValoracion() << endl;
    }
}

void Plataforma::mayorValoracion()
{
    if(!this->vecCat.empty())
    {
        vector<double> vecValoracion;
        sort(this->vecCat.begin(), this->vecCat.end(), [](Catalogo c1, Catalogo c2)
                                { return c1.getValoracion() < c2.getValoracion(); });
        
        cout << "Series y/o Peliculas con mayor valoracion:\n"; 
        for(auto it = this->vecCat.begin(); it < this->vecCat.begin()+5; ++it)
        {
            cout << "Nombre: " << it->getNombre() << " Tipo: " << it->getTipo();
            cout << " Valoracion: " << it->getValoracion() << endl;
        }
    }
}

// Continuara... Proximamente solo en cines