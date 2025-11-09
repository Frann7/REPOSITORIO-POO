#include <iostream>
#include <cstring>     // Para strcmp, strlen, strcpy
#include <vector>
#include <algorithm>   // Para sort, max_element, min_element
#include <numeric>     // Para accumulate
#include <fstream>     // Para ifstream, ofstream

using namespace std;

// --- ESTRUCTURAS DE ARCHIVOS ---
// Representación binaria de los datos en Empleados.dat
struct struEmpleados 
{
    char dni[8];
    char nombre[200];
    char apellido[200];
};

// Representación binaria de los datos en Horas.dat
struct struHorasT
{
    char dni[8];
    int horasT;
    char fecha[8]; // aaaammdd (No se usa en este parcial)
};

// -----------------------------------------------------------------
// --- CLASE EMPLEADO (Declaración) ---
// -----------------------------------------------------------------
// Representa a un empleado y su total de horas
class Empleado
{
public:
    // Constructor: crea el empleado y asigna memoria para los char*
    Empleado(char *dni, char *nombre, char *apellido);
    
    // Getters (funciones 'const' porque solo leen, no modifican)
    char* getDni() const { return dni; }
    char* getNombre() const { return nombre; }
    char* getApellido() const { return apellido; }
    
    // Métodos de lógica
    int getTotHoras(); // Devuelve la suma total de horas trabajadas
    void agregarHorasT(int h); // Añade un registro de horas al vector

private:
    vector<int> vecHorasT; // Almacena cada registro de horas
    char* dni;
    char* nombre;
    char* apellido; 
};

// -----------------------------------------------------------------
// --- CLASE EMPRESA (Declaración) ---
// -----------------------------------------------------------------
// Clase gestora: maneja los archivos y la lista de empleados
class Empresa
{
public:
    // Métodos de carga y escritura
    void leerArchivos(); // Consigna 1: Lee ambos .dat y carga el vector
    void escribir();     // Consigna 2: Escribe el reporte en .dat (texto)

    // Métodos de STL (Consigna 3)
    void cantHorasTrabajaronF1(); // Solución 3 con max_element / min_element
    void cantHorasTrabajaronF2(); // Solución 3 con sort

private:
    // (Helper) Añade un puntero de Empleado al vector
    void agregarEmpleado(Empleado* e);
    
    // Almacena punteros a Empleado (necesario para la POO)
    vector<Empleado*> vecEmpleado;
};


// -----------------------------------------------------------------
// --- EMPLEADO (Implementación) ---
// -----------------------------------------------------------------

// Constructor: Pide memoria dinámica para los C-Strings
Empleado::Empleado(char *dni, char *nombre, char *apellido)
{
    this->dni = new char[strlen(dni) + 1]; // +1 para el '\0'
    strcpy(this->dni, dni);
    
    this->nombre = new char[strlen(nombre) + 1];
    strcpy(this->nombre, nombre);
    
    this->apellido = new char[strlen(apellido) + 1];
    strcpy(this->apellido, apellido);
}

// Suma todas las horas del vector y devuelve el total
int Empleado::getTotHoras()
{
    // accumulate suma el vector. '0' es el valor inicial de la suma.
    return accumulate(this->vecHorasT.begin(), this->vecHorasT.end(), 0);
}

// Agrega un nuevo registro de horas (int) al vector
void Empleado::agregarHorasT(int h)
{
    this->vecHorasT.push_back(h);
}

// -----------------------------------------------------------------
// --- EMPRESA (Implementación) ---
// -----------------------------------------------------------------

// (Helper) Añade un puntero a Empleado al vector de la empresa
void Empresa::agregarEmpleado(Empleado* e)
{
    this->vecEmpleado.push_back(e);
}

// Consigna 1: Lee ambos archivos binarios y carga los datos en memoria
void Empresa::leerArchivos()
{
    // 1. Leer "Empleados.dat" y crear los objetos Empleado
    ifstream archivo1("Empleados.dat", ios::binary);
    if (archivo1.fail()) {
        cout << "Error al abrir Empleados.dat" << endl;
        return;
    }

    struEmpleados stru;
    while(archivo1.read((char*)&stru, sizeof(stru)))
    {
        // Crea el empleado en memoria (new) y lo agrega al vector
        agregarEmpleado(new Empleado(stru.dni, stru.nombre, stru.apellido));
    }
    archivo1.close();

    // 2. Leer "Horas.dat" y asignar las horas a cada empleado
    ifstream archivo2("Horas.dat", ios::binary);
    if (archivo2.fail()) {
        cout << "Error al abrir Horas.dat" << endl;
        return;
    }
    
    struHorasT stru2;
    while(archivo2.read((char*)&stru2, sizeof(stru2)))
    { 
        // Recorre el vector de punteros a Empleado
        for(Empleado* e : this->vecEmpleado)
        {
            // Se usa 'strcmp' (de <cstring>) para comparar el contenido
            // de los C-Strings. Devuelve 0 si son iguales.
            if(strcmp(e->getDni(), stru2.dni) == 0)
            {
                e->agregarHorasT(stru2.horasT);
                break; // Optimización: encontramos al empleado, salimos del 'for'
            }
        }
    }
    archivo2.close();
}

// Consigna 2: Escribe un archivo de texto con el reporte
void Empresa::escribir()
{
    ofstream archivo("Datos.dat"); // Archivo de texto
    if (archivo.fail()) return;

    // Recorre el vector de punteros
    for(Empleado* e : this->vecEmpleado)
    {
        // Llama a los getters de cada empleado
        archivo << "Nombre: " << e->getNombre() << " Apellido: " << e->getApellido();
        archivo << " : " << e->getTotHoras() << " hs" << endl;
    }
    archivo.close();
}

// Consigna 3 (Forma 1): Más/Menos horas usando max_element y min_element
void Empresa::cantHorasTrabajaronF1()
{
    // Chequeo de seguridad para evitar crasheos si el vector está vacío
    if(this->vecEmpleado.empty()) {
        cout << "No hay empleados cargados." << endl;
        return;
    }

    cout << "--- Empleado/s con MAS horas (Forma 1) ---" << endl;
    
    // 1. Encontrar al MÁXIMO
    // max_element necesita una lambda que le diga si a < b
    auto it_max = max_element(this->vecEmpleado.begin(), this->vecEmpleado.end(),
        [](Empleado* a, Empleado* b){
           return a->getTotHoras() < b->getTotHoras();
        });

    int maxHoras = (*it_max)->getTotHoras(); // Obtenemos el nro de horas

    // Recorremos el vector para buscar empates
    for(Empleado* e : this->vecEmpleado)
    {
        if(e->getTotHoras() == maxHoras)
        {
            cout << e->getNombre() << " (Horas: " << e->getTotHoras() << ")" << endl;
        }
    }

    cout << "\n--- Empleado/s con MENOS horas (Forma 1) ---" << endl;

    // 2. Encontrar al MÍNIMO
    // min_element usa la MISMA lambda (a < b) para encontrar al más chico
    auto it_min = min_element(this->vecEmpleado.begin(), this->vecEmpleado.end(),
        [](Empleado* a, Empleado* b){
           return a->getTotHoras() < b->getTotHoras();
        });

    int minHoras = (*it_min)->getTotHoras(); // Obtenemos el nro de horas

    // Recorremos el vector para buscar empates
    for(Empleado* e : this->vecEmpleado)
    {
        if(e->getTotHoras() == minHoras)
        {
            cout << e->getNombre() << " (Horas: " << e->getTotHoras() << ")" << endl;
        }
    }
}

// Consigna 3 (Forma 2): Más/Menos horas usando sort
void Empresa::cantHorasTrabajaronF2()
{
    // Chequeo de seguridad
    if(this->vecEmpleado.empty()) {
        cout << "No hay empleados cargados." << endl;
        return;
    }

    cout << "--- Empleado/s con MAS horas (Forma 2) ---" << endl;

    // 1. Encontrar al MÁXIMO
    // Ordenamos de MAYOR a MENOR (boquita '>')
    sort(this->vecEmpleado.begin(), this->vecEmpleado.end(),
        [](Empleado* e1, Empleado* e2){
            return e1->getTotHoras() > e2->getTotHoras();
        });

    // El máximo ahora está en la posición [0]
    int maxHoras = this->vecEmpleado[0]->getTotHoras();

    for(Empleado* e : this->vecEmpleado)
    {
        if(e->getTotHoras() == maxHoras)
        {
            cout << e->getNombre() << " (Horas: " << e->getTotHoras() << ")" << endl;
        } else {
            // Optimización: como está ordenado, si no es igual, ya no habrá más
            break; 
        }
    }

    cout << "\n--- Empleado/s con MENOS horas (Forma 2) ---" << endl;

    // 2. Encontrar al MÍNIMO
    // Volvemos a ordenar, pero de MENOR a MAYOR (boquita '<')
    sort(this->vecEmpleado.begin(), this->vecEmpleado.end(),
        [](Empleado* e1, Empleado* e2){
            return e1->getTotHoras() < e2->getTotHoras();
        });

    // El mínimo ahora está en la posición [0]
    int minHoras = this->vecEmpleado[0]->getTotHoras();

    for(Empleado* e : this->vecEmpleado)
    {
        if(e->getTotHoras() == minHoras)
        {
            cout << e->getNombre() << " (Horas: " << e->getTotHoras() << ")" << endl;
        } else {
            // Optimización: como está ordenado, si no es igual, ya no habrá más
            break; 
        }
    }
}