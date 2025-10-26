#include <iostream>
#include <cstring>
#include <algorithm> // Para copy_if, transform, max_element, for_each
#include <fstream>   // Para leer/escribir archivos
#include <vector>    // Para std::vector
#include <numeric>   // Para std::accumulate (sumar vectores)

using namespace std;

// --- ESTRUCTURAS DE ARCHIVOS ---
// Representación exacta de cómo se leen los datos del archivo
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

// --- CLASE ALUMNO ---
// Representa a un solo alumno y su lógica interna
class Alumno
{
public:
    Alumno(int l, const char* n, char t); 

    void agregarNota(int n); // Agrega una nota al vector de notas
    bool estaAprobado();     // Retorna true si el alumno esta aprobado

    // Getters y Setters
    int getLegajo();
    void setLegajo(int l);
    char* getNombre();
    void setNombre(const char* n);
    char getTipo();
    void setTipo(char t);

    // Métodos para las consignas 3
    float getPromedio();   // Para consigna 3a y 3b
    size_t getCantNotas(); // Para consiga 3c

private:
    vector<int> vecN; // Vector de notas
    int legajo;
    char* nombre;
    char tipo;
};

// --- IMPLEMENTACIÓN ALUMNO ---

Alumno::Alumno(int l, const char* n, char t)
{
    this->legajo = l;
    this->nombre = new char[strlen(n)+1]; // Pedimos memoria para el nombre
    strcpy(this->nombre, n);
    this->tipo = t;
}

void Alumno::agregarNota(int n)
{
    this->vecN.push_back(n);
}

// Consigna 1: Lógica de aprobación
bool Alumno::estaAprobado()
{
    // Chequeo de seguridad: si no tiene notas, no puede aprobar
    if(this->vecN.empty())
    { 
        return false;
    }

    if(this->tipo == 'L') // Lógica para Libres
    {
        // Debe tener 1 sola nota Y esa nota ser MAYOR a 70
        return(this->vecN.size() == 1 && vecN[0] > 70); 
    }
    else if (this->tipo == 'R') // Lógica para Regulares
    {
        // 1. Chequea si tiene alguna nota desaprobada (< 55)
        for(int n : this->vecN)
            if(n < 55) 
                return false; // Si encuentra una, reprueba
        
        // 2. Si pasó el filtro, calcula el promedio
        float promedio = this->getPromedio();

        // 3. El promedio debe ser >= 60
        return(promedio >= 60);
    }
    return false; // Si no es ni 'L' ni 'R', reprueba
}

// Devuelve el promedio del alumno. Usado por Consignas 3
float Alumno::getPromedio()
{
    // Chequeo de seguridad: evita división por cero
    if(this->vecN.empty())
    {
        return 0.0;
    }

    // Suma todas las notas del vector
    float suma = accumulate(this->vecN.begin(), this->vecN.end(), 0.0);
    // Devuelve el promedio
    return suma / this->vecN.size();
}

// Devuelve cuántas notas tiene el alumno. Usado por Consigna 3c
size_t Alumno::getCantNotas()
{
    return this->vecN.size();
}

// --- Getters y Setters simples ---
int Alumno::getLegajo() { return this->legajo; }
void Alumno::setLegajo(int l) { this->legajo = l; }
char* Alumno::getNombre() { return this->nombre; }
void Alumno::setNombre(const char* n) { this->nombre = new char[strlen(n)+1]; strcpy(this->nombre, n); }
char Alumno::getTipo() { return this->tipo; }
void Alumno::setTipo(char t) { this->tipo = t; }


// --- CLASE CURSO ---
// Clase gestora. Maneja los archivos y la lista de todos los alumnos
class Curso
{
public:
    Curso();
    void agregarAlumno(Alumno* a); // Agrega alumno al vector
    void leerAlumnos(); // Pasa los datos del archivo Alumnos.dat a memoria
    void leerNotas(); // Pasa los datos del archivo Notas.dat a memoria
    
    // Consignas
    void escribirCondicion(); // Consigna 2
    void mayorPromedio(); // Consigna 3a
    void promedioTotal(); // Consigna 3b
    void menoresNotas(); // Consigna 3c

    // Método de prueba
    void generarEjemploArchivos(); 
    
private:
    vector<Alumno*> vecA; // Vector de punteros a Alumnos
};

// --- IMPLEMENTACIÓN CURSO ---

Curso::Curso() { }

void Curso::agregarAlumno(Alumno* a)
{
    this->vecA.push_back(a);
}

// Lee Alumnos.dat y llena el vector vecA
void Curso::leerAlumnos()
{
    // ** BUG FIX: El archivo es "Alumnos.dat" (con 's') **
    ifstream archivo("Alumnos.dat", ios::binary);
    if(archivo.fail()) {
        cout << "Error: No se pudo abrir Alumnos.dat" << endl;
        return;
    }

    struAlumno stru;
    while(archivo.read((char*)&stru, sizeof(stru)))
    {
        // Crea un Alumno en memoria dinámica (new) y lo guarda
        agregarAlumno(new Alumno(stru.legajo, stru.nombre, stru.tipo));
    }
    archivo.close();
}

// Lee Notas.dat y reparte las notas a cada alumno
void Curso::leerNotas()
{
    ifstream archivo("Notas.dat", ios::binary);
    if(archivo.fail()) {
        cout << "Error: No se pudo abrir Notas.dat" << endl;
        return;
    }
    
    struNota stru;
    while(archivo.read((char*)&stru, sizeof(stru)))
    {
        // Recorre el vector de alumnos en memoria
        for(Alumno* a : this->vecA)
        {
            // Si el legajo coincide, le da la nota
            if(a->getLegajo() == stru.legajo) 
            {
                a->agregarNota(stru.nota);
                break; // Optimización: pasa a la siguiente nota
            }
        }
    }
    archivo.close();
}

// --- CONSIGNAS ---

// Consigna 2: Escribe archivo de texto con Aprobados/Desaprobados
void Curso::escribirCondicion()
{
    // Chequeo de seguridad
    if (this->vecA.empty())
    {
        cout << "No hay alumnos cargados." << endl;
        return;
    }

    ofstream archivo("Condiciones.dat"); // Archivo de texto
    if(archivo.fail()) return;

    for (Alumno* a : this->vecA)
    {
        archivo << "Nombre: " << a->getNombre() << "....... ";
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
    archivo.close();
}

// Consigna 3a: Muestra el/los alumnos con mayor promedio
void Curso::mayorPromedio()
{
    // Chequeo de seguridad
    if (this->vecA.empty())
    {
        cout << "No hay alumnos cargados." << endl;
        return;
    }

    // 1. Encontrar el iterador al primer alumno con el max promedio
    auto it = max_element(this->vecA.begin(), this->vecA.end(), 
        [](Alumno* a1, Alumno* a2) { 
            return a1->getPromedio() < a2->getPromedio(); 
        }); 

    // 2. Obtener ese promedio máximo
    float promedioMax = (*it)->getPromedio(); 

    // 3. Recorrer y mostrar TODOS los que empaten con ese promedio
    for(Alumno* a : this->vecA)
    {
        if(a->getPromedio() == promedioMax) 
        {
            cout << "Alumno: " << a->getNombre() << " | Promedio: " << a->getPromedio() << endl;
        }
    }
}

// Consigna 3b (Optimizado): Promedio de Aprobados vs Desaprobados
void Curso::promedioTotal()
{
    vector<Alumno*> vecAprobados;
    vector<Alumno*> vecDesaprobados;

    // 1. Separa los alumnos en dos vectores (Aprobados y Desaprobados)
    copy_if(this->vecA.begin(), this->vecA.end(), back_inserter(vecAprobados),
        [](Alumno* a) { return a->estaAprobado(); });

    copy_if(this->vecA.begin(), this->vecA.end(), back_inserter(vecDesaprobados), 
        [](Alumno* a) { return !a->estaAprobado(); });

    // 2. Calcula promedio de APROBADOS
    if(!vecAprobados.empty()){
        // Suma los promedios de los aprobados sin crear un vector nuevo
        float promediosA = accumulate(vecAprobados.begin(), vecAprobados.end(), 0.0,
            [](float sumaActual, Alumno* a) {
                return sumaActual + a->getPromedio();
            }
        );
        float resultadoA = promediosA / vecAprobados.size();
        cout << "Promedio Aprobados: " << resultadoA << endl;
    } else {
        cout << "Desaprobaron todos manga de burros" << endl;
    }
    
    // 3. Calcula promedio de DESAPROBADOS
    if(!vecDesaprobados.empty()){ 
        // Suma los promedios de los desaprobados
        float promediosD = accumulate(vecDesaprobados.begin(), vecDesaprobados.end(), 0.0,
            [](float sumaActual, Alumno* a) {
                return sumaActual + a->getPromedio();
            }
        );
        float resultadoD = promediosD / vecDesaprobados.size();
        cout << "Promedio Desaprobados: " << resultadoD << endl;
    } else {
        cout << "Aprobaron todos altos capos " << endl;
    }
}


// Consigna 3c: Regulares con menos notas que el promedio de notas
void Curso::menoresNotas()
{
    vector<Alumno*> regulares; 
    
    // 1. Filtra y obtiene solo a los alumnos Regulares
    copy_if(this->vecA.begin(), this->vecA.end(), back_inserter(regulares), 
        [](Alumno* a) { return a->getTipo() == 'R'; });
    
    // Chequeo de seguridad
    if(!regulares.empty()){
        
        // 2. Crea un vector con la CANTIDAD de notas de cada regular
        vector<size_t> vecCantNotas; 
        transform(regulares.begin(), regulares.end(), back_inserter(vecCantNotas),
            [](Alumno* a) { return a->getCantNotas(); });

        // 3. Suma esas cantidades
        size_t sumaCantNotas = accumulate(vecCantNotas.begin(), vecCantNotas.end(), 0);
        
        // 4. Calcula el promedio de cantidad de notas
        // ** BUG FIX: Usamos static_cast para asegurar división con decimales **
        double promedioCantNotas = static_cast<double>(sumaCantNotas) / vecCantNotas.size();

        cout << "El promedio de cantidad de notas para Regulares es: " << promedioCantNotas << endl;

        // 5. Filtra a los regulares que tengan menos notas que ese promedio
        vector<Alumno*> resultado;
        copy_if(regulares.begin(), regulares.end(), back_inserter(resultado), 
            [promedioCantNotas](Alumno* a) { // [=] captura la variable
                return a->getCantNotas() < promedioCantNotas; 
            });

        // 6. Muestra los resultados
        cout << "Alumnos Regulares con menos notas que el promedio:" << endl;
        for(Alumno* a : resultado)
        {
            cout << a->getNombre() << " (Notas: " << a->getCantNotas() << ")" << endl;
        }
    } else {
        cout << "No hay alumnos regulares " << endl;
    }
}


// --- MÉTODO DE PRUEBA ---

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
    alu.legajo = 101; strcpy(alu.nombre, "Juan Perez"); alu.tipo = 'R';
    archAlumnos.write((char*)&alu, sizeof(struAlumno));

    // Alumno 2 (Regular, debe reprobar por nota baja)
    alu.legajo = 102; strcpy(alu.nombre, "Ana Gomez"); alu.tipo = 'R';
    archAlumnos.write((char*)&alu, sizeof(struAlumno));

    // Alumno 3 (Libre, debe aprobar)
    alu.legajo = 103; strcpy(alu.nombre, "Luis Rivas"); alu.tipo = 'L';
    archAlumnos.write((char*)&alu, sizeof(struAlumno));

    // Alumno 4 (Regular, debe reprobar por promedio)
    alu.legajo = 104; strcpy(alu.nombre, "Maria Sol"); alu.tipo = 'R';
    archAlumnos.write((char*)&alu, sizeof(struAlumno));

    // Alumno 5 (Libre, debe reprobar)
    alu.legajo = 105; strcpy(alu.nombre, "Carlos Paz"); alu.tipo = 'L';
    archAlumnos.write((char*)&alu, sizeof(struAlumno));

    // Alumno 6 (Regular, sin notas, debe reprobar)
    alu.legajo = 106; strcpy(alu.nombre, "Laura Sinnotas"); alu.tipo = 'R';
    archAlumnos.write((char*)&alu, sizeof(struAlumno));

    archAlumnos.close();


    // --- 2. Crear Notas.dat ---
    ofstream archNotas("Notas.dat", ios::binary);
    if (!archNotas) {
        cout << "Error al crear Notas.dat" << endl;
        return;
    }

    struNota nota;

    // Notas para Juan (101) -> Promedio 70, aprueba (2 notas)
    nota.legajo = 101; nota.nota = 60; archNotas.write((char*)&nota, sizeof(struNota));
    nota.legajo = 101; nota.nota = 80; archNotas.write((char*)&nota, sizeof(struNota));

    // Notas para Ana (102) -> Reprueba (un 50) (3 notas)
    nota.legajo = 102; nota.nota = 100; archNotas.write((char*)&nota, sizeof(struNota));
    nota.legajo = 102; nota.nota = 90; archNotas.write((char*)&nota, sizeof(struNota));
    nota.legajo = 102; nota.nota = 50; archNotas.write((char*)&nota, sizeof(struNota));

    // Nota para Luis (103) -> Aprueba (es Libre, > 70) (1 nota)
    nota.legajo = 103; nota.nota = 75; archNotas.write((char*)&nota, sizeof(struNota));

    // Notas para Maria (104) -> Reprueba (Promedio 57.5) (2 notas)
    nota.legajo = 104; nota.nota = 60; archNotas.write((char*)&nota, sizeof(struNota));
    nota.legajo = 104; nota.nota = 55; archNotas.write((char*)&nota, sizeof(struNota));

    // Nota para Carlos (105) -> Reprueba (es Libre, <= 70) (1 nota)
    nota.legajo = 105; nota.nota = 70; archNotas.write((char*)&nota, sizeof(struNota));

    // (No hay notas para Laura 106) (0 notas)

    archNotas.close();

    cout << "Archivos 'Alumnos.dat' y 'Notas.dat' generados con exito." << endl;
}
