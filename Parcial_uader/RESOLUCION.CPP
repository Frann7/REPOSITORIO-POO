#include <iostream>
#include <cstring>
#include <algorithm>
#include <fstream>
#include <vector>
#include <map>
#include <numeric> // para accumulate

using namespace std;

struct struAlumno
{
    int legajo;
    char nombre[200];
    char tipo;
};

struct struNota
{
    int legajo;
    int nota;
};

class Alumno
{
public:
    Alumno(int l, const char* n, char t);
    void agregarNota(int n);
    bool estaAprobado();
    int getLegajo();
    void setLegajo(int l);
    char* getNombre();
    void setNombre(const char* n);
    char getTipo();
    void setTipo(char t);
private:
    vector<int> vecN;
    int legajo;
    char* nombre;
    char tipo;
};

Alumno::Alumno(int l, const char* n, char t)
{
    this->legajo = l;
    this->nombre = new char[strlen(n)+1];
    strcpy(this->nombre, n);
    this->tipo = t;
}

void Alumno::agregarNota(int n)
{
    this->vecN.push_back(n);
}

bool Alumno::estaAprobado()
{
    if(this->vecN.empty())
    {
        return false;
    }

    if(this->tipo == 'L')
    {
        return(this->vecN.size() == 1 && vecN[0] > 70);
    }
    else if (this->tipo == 'R')
    {
        for(int n : this->vecN)
            if(n < 55)
                return false;
        
        float suma = accumulate(this->vecN.begin(), this->vecN.end(), 0.0);
        float promedio = suma / this->vecN.size();

        return(promedio >= 60);
    }
    return false;
}

int Alumno::getLegajo()
{
    return this->legajo;
}

void Alumno::setLegajo(int l)
{
    this->legajo = l;
}

char* Alumno::getNombre()
{
    return this->nombre;
}

void Alumno::setNombre(const char* n)
{
   this->nombre = new char[strlen(n)+1];
   strcpy(this->nombre, n);
}

char Alumno::getTipo()
{
   return this->tipo;
}

void Alumno::setTipo(char t)
{
    this->tipo = t;
}

class Curso
{
public:
    Curso();
    void leerAlumnos();
    void leerNotas();
private:
    vector<Alumno*> vecA;
};

Curso::Curso()
{
}

void Curso::leerAlumnos()
{
    ifstream archivo("Alumno.dat", ios::binary);
    if(archivo.fail()) return;

    struAlumno stru;
    while(archivo.read((char*)&stru,sizeof(stru)))
    {
        this->vecA.push_back(new Alumno(stru.legajo, stru.nombre, stru.tipo));
    }

    archivo.close();
}

void Curso::leerNotas()
{
    ifstream archivo("Notas.dat", ios::binary);
    if(archivo.fail()) return;
    struNota stru;
    while(archivo.read((char*)&stru,sizeof(stru)))
    {
        for(Alumno* a : this->vecA)
        {
            if(a->getLegajo() == stru.legajo)
            {
                a->agregarNota(stru.nota);
            }
        }
    }
    archivo.close();
}


