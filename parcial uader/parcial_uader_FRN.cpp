#include <iostream>
#include "VectorDinamico.cpp"
#include <string.h>// para strcpy()

class alumno{
public:
    alumno(const char* nya, int dni);// constructor
    void add_nota(int nota);// agregar nota al vec
    void reemplazar_nota(int nota_vieja, int nota_nueva);// nota del recuperatorio pisa la nota del parcial
    char* getestado();// consigna 2 permite saber el estado de los alumnos
    int getdni(){return this->dni;};// para mostrar datos
    int getnota(int pos){return this->notas[pos];};// getnota(0) contiene una nota, getnota(1) contiene la otra
    char* getnya(){return this->nya;};// para mostrar datos
    friend std::ostream& operator <<(std::ostream& os, alumno& p);// sobrecarga de operador << para mostrar datos
private:
    char* estado;
    char* nya;
    int dni;
    vector<int> notas;// vector dinamico que guarda la nota de los dos parciales 
    char* copystr(const char* str);// metodo para cstring
    double getpromedio();// metodo que calcula el promedio, esta en private porque no se necesita llamar desde afuera de la clase
};

alumno::alumno(const char* nya, int dni){
    this->dni=dni;
    this->nya=copystr(nya);
}

char* alumno::copystr(const char* str){
    char* newstr = new char[strlen(str)+1];
    strcpy(newstr, str);
    return newstr;
}

void alumno::add_nota(int nota){
    this->notas.add(nota);
}

void alumno::reemplazar_nota(int nota_vieja, int nota_nueva){
    this->notas.reemplazar(nota_vieja, nota_nueva);
}

double alumno::getpromedio(){

    double promedio=(this->notas[0]+this->notas[1]) / 2;
    return promedio; 
}

char* alumno::getestado(){
    //Segun el promedio y cuanta nota obtuvo en cada parcial tiene una condicion
    if(this->notas.getsize()<2){
        this->estado=copystr("Libre Ausente");
    }else if((this->getpromedio()<55) || (this->notas[0]<50) || (this->notas[1]<50)){
        this->estado=copystr("Libre");
    }else if((this->getpromedio()>=55) && (this->getpromedio()<75)){
        this->estado=copystr("Regular");
    }else if((this->getpromedio()>=75) && (this->notas[0])>=70 && (this->notas[1]>=70)){
        this->estado=copystr("Promocion");
    }

    return this->estado;
}

std::ostream& operator <<(std::ostream& os, alumno& p){
    os << "Nombre y Apellido: " << p.getnya() << std::endl;
    os << "Dni: " << p.getdni() << std::endl;
    os << "Notas: ";
    if (p.notas.getsize() >= 1) os << p.getnota(0);// estos if son para que si el estado es libre ausente no muestre basura
    if (p.notas.getsize() >= 2) os << " " << p.getnota(1);
    os << std::endl;
    os << "Estado: " << p.getestado() << std::endl;
    return os;
}

class Curso{// actua como una clase gestora
public:
    Curso(){};
    void add_alumno(alumno* newalumno);
    void mostrarDatos();
private:
    vector<alumno*> alumnos;
};

void Curso::add_alumno(alumno* newalumno){
    alumnos.add(newalumno);

    if(alumnos.getsize()==50)// un curso puede tener un maximo de 50 alumnos
        return;
}

void Curso::mostrarDatos(){
    for(size_t i=0; i<alumnos.getsize(); i++)
        std::cout<<*alumnos[i];
}

int main(){
    Curso CursoA;

    alumno* alumno1= new alumno("Jose Luis", 47175839);
    alumno1->add_nota(75);
    alumno1->add_nota(40);
    alumno1->reemplazar_nota(40, 80);
    
    alumno* alumno2= new alumno("Eduardo Gonzales (elgoat)", 44444444);
    alumno2->add_nota(30);
    alumno2->add_nota(30);
    alumno2->reemplazar_nota(30,40);

    alumno* alumno3= new alumno("Miriam Bregman", 23456095);
    alumno3->add_nota(60);
    
    CursoA.add_alumno(alumno1);
    CursoA.add_alumno(alumno2);
    CursoA.add_alumno(alumno3);

    CursoA.mostrarDatos();

    return 0;
}