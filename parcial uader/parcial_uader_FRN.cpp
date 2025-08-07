#include <iostream>
#include "VectorDinamico.cpp"
#include <string.h>

class alumno{
public:
alumno(const char* nya, int dni);
    void add_nota(int nota);
    void reemplazar_nota(int nota_vieja, int nota_nueva);
    char* getestado();
    int getdni(){return this->dni;};
    int getnota(int pos){return this->notas[pos];};
    char* getnya(){return this->nya;};
    friend std::ostream& operator <<(std::ostream& os, alumno& p);
private:
    char* estado;
    char* nya;
    int dni;
    //int nota_parcial;
    int nota_recupertario;
    vector<int> notas; 
    char* copystr(const char* str);
    double getpromedio();
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
    if (p.notas.getsize() >= 1) os << p.getnota(0);
    if (p.notas.getsize() >= 2) os << " " << p.getnota(1);
    os << std::endl;
    os << "Estado: " << p.getestado() << std::endl;
    return os;
}

class Curso{
public:
    Curso(){};
    void add_alumno(alumno* newalumno);
    void mostrarDatos();
private:
    vector<alumno*> alumnos;
};

void Curso::add_alumno(alumno* newalumno){
    alumnos.add(newalumno);
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