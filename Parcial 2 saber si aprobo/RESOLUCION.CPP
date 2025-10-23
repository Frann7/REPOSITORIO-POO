#include <iostream>
#include <cstring>
#include <algorithm> // copy_if, transform
#include <fstream> 
#include <vector>
#include <numeric> // para accumulate

using namespace std;

// Estructura del archivo Alumnos.dat
struct struAlumno
{
    int legajo;
    char nombre[200];
    char tipo;
};

// Estructura del archivo Notas.dat
struct struNota
{
    int legajo;
    int nota;
};

// Clase Alumno
class Alumno
{
public:
    Alumno(int l, const char* n, char t); 

    void agregarNota(int n); // Agrega una nota al vector de notas
    bool estaAprobado(); // Retorna true si el alumno esta aprobado y false si esta desaprobado

    // Getters and Setters
    int getLegajo();
    void setLegajo(int l);
    char* getNombre();
    void setNombre(const char* n);
    char getTipo();
    void setTipo(char t);

    float getPromedio(); // Para consigna 3a y 3b
    size_t getCantNotas(); // Para consiga 3c
private:
    vector<int> vecN; // Vector de notas
    int legajo; // Identificador
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

    if(this->tipo == 'L') // Libre
    {
        return(this->vecN.size() == 1 && vecN[0] > 70); // Si las condiciones son verdaderas retorna true
    }
    else if (this->tipo == 'R') // Regular
    {
        for(int n : this->vecN)
            if(n < 55) 
                return false;
        
        float promedio = this->getPromedio();

        return(promedio >= 60); // Si la condicion es verdadera retorna true
    }
    return false;
}

float Alumno::getPromedio()
{
    if(this->vecN.empty())
    {
        return 0.0;
    }

    float suma = accumulate(this->vecN.begin(), this->vecN.end(), 0.0);
    return suma / this->vecN.size();
}

size_t Alumno::getCantNotas()
{
    return this->vecN.size();
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

// Clase gestora curso
class Curso
{
public:
    Curso();
    void agregarAlumno(Alumno* a); // Agrega alumno al vector
    void leerAlumnos(); // Pasa los datos del archivo Alumnos.dat a memoria
    void leerNotas(); // Pasa los datos del archivo Notas.dat a memoria
    void escribirCondicion(); // Consigna 2
    void mayorPromedio(); // Consigna 3a
    void promedioTotal(); // Consigna 3b
    void menoresNotas(); // Consigna 3c
    void generarEjemploArchivos(); // Metodo para generar archivos de ejemplo
    
private:
    vector<Alumno*> vecA; // Vector de alumnos
};

Curso::Curso()
{
}

void Curso::agregarAlumno(Alumno* a)
{
    this->vecA.push_back(a);
}

// Leer alumnos y notas puede hacerse en un mismo metodo
void Curso::leerAlumnos()
{
    ifstream archivo("Alumnos.dat", ios::binary);
    if(archivo.fail()) return;

    struAlumno stru;
    while(archivo.read((char*)&stru,sizeof(stru)))
    {
        agregarAlumno(new Alumno(stru.legajo, stru.nombre, stru.tipo));
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
            if(a->getLegajo() == stru.legajo) // Compara por el identificador si el alumno que esta en memoria es igual al del archivo
            {
                a->agregarNota(stru.nota);
            }
        }
    }
    archivo.close();
}

// Consigna 2
void Curso::escribirCondicion()
{
     if (this->vecA.empty())
    {
        cout << "No hay alumnos cargados." << endl;
        return;
    }

    ofstream archivo("Condiciones.dat");
    if(archivo.fail()) return;

    for (Alumno* a : this->vecA)
    {
        archivo << "Nombre: " << a->getNombre() << " ";
        if(a->estaAprobado())
        {
            archivo << "Aprobado";
        }
        else
        {
            archivo << "Desaprobado";
        }
        archivo << endl;
    }
}

void Curso::mayorPromedio()
{
    if (this->vecA.empty())
    {
        cout << "No hay alumnos cargados." << endl;
        return;
    }

    // Devuelve iterador apuntando al Alumno con mayor promedio
   auto it = max_element(this->vecA.begin(),this->vecA.end(), [](Alumno* a1, Alumno* a2)
                                { return a1->getPromedio() < a2->getPromedio(); }); 

    float promedioMax = (*it)->getPromedio(); // Es lo mismo que hacer Alumno* alum = *it y if(a->getPromedio() == alum->getPromedio())

    for(Alumno* a : this->vecA)
    {
        if(a->getPromedio() == promedioMax) // El o los alumnos con mayor promedio
        {
            cout << "Alumno " << a->getNombre() << " Promedio: " << a->getPromedio();
            cout << endl;
        }
    }
}

void Curso::promedioTotal()
{
    vector<Alumno*> vecAprobados;
    vector<Alumno*> vecDesaprobados;

    // Copia del vector de alumnos del curso a un vector de aprobados si el metodo estaAprobado() retorna true
    copy_if(this->vecA.begin(), this->vecA.end(), back_inserter(vecAprobados),[](Alumno* a)
                                                                { return a->estaAprobado(); });

    // Este if es para evitar dividir por 0 al calcular el promedio total 
    if(vecAprobados.size() != 0){
         // Copiar los promedios de los Aprobados a un nuevo vector
        vector<float> vecPromediosA(vecAprobados.size());
        transform(vecAprobados.begin(), vecAprobados.end(), vecPromediosA.begin(),[](Alumno* a)
                                                                { return a->getPromedio(); });

        // Suma de promedios de todo el vector
        float promediosA = accumulate(vecPromediosA.begin(), vecPromediosA.end(), 0.0);

        // Promedio Total
        float resultadoA = promediosA / vecPromediosA.size();

        cout << "Promedio Aprobados: " << resultadoA << endl;
    }else
    {
        cout << "Desaprobaron todos manga de burros" << endl;
    }

    // Copia del vector de alumnos del curso a un vector de desaprobados si  el metodo estaAprobado() retorna true(porque esta negado)
    copy_if(this->vecA.begin(), this->vecA.end(), back_inserter(vecDesaprobados), [](Alumno* a)
                                                                { return !a->estaAprobado();});

    // Este if es para evitar dividir por 0 al calcular el promedio total 
    if(vecDesaprobados.size() != 0){                                                          
        // Copiar los promedios de los Desaprobados a un nuevo vector
        vector<float> vecPromediosD(vecDesaprobados.size()); // Si le paso un size al vector no puedo usar back_inserter
        transform(vecDesaprobados.begin(), vecDesaprobados.end(), vecPromediosD.begin(),[](Alumno* a)
                                                                { return a->getPromedio(); });

        // Suma de promedios de todo el vector
        float promediosD = accumulate(vecPromediosD.begin(), vecPromediosD.end(), 0.0);

        // Promedio total
        float resultadoD = promediosD / vecPromediosD.size();

        cout << "Promedio Desprobados: " << resultadoD << endl;
    }else
    {
        cout << "Aprobaron todos altos capos " << endl;
    }
}

void Curso::menoresNotas()
{
    vector<Alumno*> regulares; // El vector no tiene un size fijo asi que puedo usar back_inserter
    
    // Toma del vector unicamente a los regulares
    copy_if(this->vecA.begin(), this->vecA.end(), back_inserter(regulares), [](Alumno* a)
                                                        { return a->getTipo() == 'R'; });
    if(!regulares.empty()){
        vector<size_t> vecCantnotas; /* Vector de cantidad de nota por alumno
         por ejemplo rindio 2 de 3 examenes su cantidad de notas va a ser 3 */

         // Pasa la cantidad de notas de cada alumno regular a un vector vecCantNotas
        transform(regulares.begin(), regulares.end(), back_inserter(vecCantnotas),[](Alumno* a)
                                                                { return a->getCantNotas(); });
        // Suma todas la cant notas del vector
        size_t cantNotas = accumulate(vecCantnotas.begin(), vecCantnotas.end(), 0);
        double promedioCantNotas = static_cast<double>(cantNotas) / vecCantnotas.size();

        cout << "El promedio de cantidad de notas para Regulares es: " << promedioCantNotas << endl;

        // Menos nota que el promedio
        vector<Alumno*> resultado;
        copy_if(regulares.begin(),regulares.end(),back_inserter(resultado), [promedioCantNotas](Alumno* a)
                                        { return a->getCantNotas() < promedioCantNotas; });

        cout << "Alumnos Regulares con menos notas que el promedio:" << endl;
        for(Alumno* a : resultado)
        {
            cout << a->getNombre() << " (Notas: " << a->getCantNotas() << ")" << endl;
        }
    } else
    {
        cout << "No hay alumnos regulares " << endl;
    }
}

void Curso::generarEjemploArchivos()
{
    // --- 1. Crear Alumnos.dat ---
    ofstream archAlumnos("Alumnos.dat", ios::binary);
    if (!archAlumnos) {
        cout << "Error al crear Alumnos.dat" << endl;
        return;
    }

    struAlumno alu;

    // Alumno 1 (Regular, debe aprobar)
    alu.legajo = 101;
    strcpy(alu.nombre, "Juan Perez");
    alu.tipo = 'R';
    archAlumnos.write((char*)&alu, sizeof(struAlumno));

    // Alumno 2 (Regular, debe reprobar por nota baja)
    alu.legajo = 102;
    strcpy(alu.nombre, "Ana Gomez");
    alu.tipo = 'R';
    archAlumnos.write((char*)&alu, sizeof(struAlumno));

    // Alumno 3 (Libre, debe aprobar)
    alu.legajo = 103;
    strcpy(alu.nombre, "Luis Rivas");
    alu.tipo = 'L';
    archAlumnos.write((char*)&alu, sizeof(struAlumno));

    // Alumno 4 (Regular, debe reprobar por promedio)
    alu.legajo = 104;
    strcpy(alu.nombre, "Maria Sol");
    alu.tipo = 'R';
    archAlumnos.write((char*)&alu, sizeof(struAlumno));

    // Alumno 5 (Libre, debe reprobar)
    alu.legajo = 105;
    strcpy(alu.nombre, "Carlos Paz");
    alu.tipo = 'L';
    archAlumnos.write((char*)&alu, sizeof(struAlumno));

    // Alumno 6 (Regular, sin notas, debe reprobar)
    alu.legajo = 106;
    strcpy(alu.nombre, "Laura Sinnotas");
    alu.tipo = 'R';
    archAlumnos.write((char*)&alu, sizeof(struAlumno));

    archAlumnos.close();


    // --- 2. Crear Notas.dat ---
    ofstream archNotas("Notas.dat", ios::binary);
    if (!archNotas) {
        cout << "Error al crear Notas.dat" << endl;
        return;
    }

    struNota nota;

    // Notas para Juan (101) -> Promedio 70, aprueba
    nota.legajo = 101; nota.nota = 60;
    archNotas.write((char*)&nota, sizeof(struNota));
    nota.legajo = 101; nota.nota = 80;
    archNotas.write((char*)&nota, sizeof(struNota));

    // Notas para Ana (102) -> Reprueba (un 50)
    nota.legajo = 102; nota.nota = 100;
    archNotas.write((char*)&nota, sizeof(struNota));
    nota.legajo = 102; nota.nota = 90;
    archNotas.write((char*)&nota, sizeof(struNota));
    nota.legajo = 102; nota.nota = 50; // <- Reprueba por esta
    archNotas.write((char*)&nota, sizeof(struNota));

    // Nota para Luis (103) -> Aprueba (es Libre, > 70)
    nota.legajo = 103; nota.nota = 75;
    archNotas.write((char*)&nota, sizeof(struNota));

    // Notas para Maria (104) -> Reprueba (Promedio 57.5)
    nota.legajo = 104; nota.nota = 60;
    archNotas.write((char*)&nota, sizeof(struNota));
    nota.legajo = 104; nota.nota = 55;
    archNotas.write((char*)&nota, sizeof(struNota));

    // Nota para Carlos (105) -> Reprueba (es Libre, <= 70)
    nota.legajo = 105; nota.nota = 70;
    archNotas.write((char*)&nota, sizeof(struNota));

    // (No hay notas para Laura 106)

    archNotas.close();

    cout << "Archivos 'Alumnos.dat' y 'Notas.dat' generados con exito." << endl;
}



