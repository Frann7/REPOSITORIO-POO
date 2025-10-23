#include <iostream>
#include "RESOLUCION.CPP" // Incluimos la resolución del parcial

using namespace std;

int main()
{
    // 1. Creamos un objeto Curso
    Curso miCurso;

    // 2. Generamos los archivos de prueba
    miCurso.generarEjemploArchivos();

     
    // 3. Leemos los archivos para cargar el vector vecA
    cout << "\nCargando datos desde archivos..." << endl;
    miCurso.leerAlumnos();
    miCurso.leerNotas();
    cout << "Datos cargados." << endl;

    // 4. ¡Probamos todas las funciones del parcial!
    cout << "\n--- Consigna 2: Estado de Alumnos ---" << endl;
    miCurso.escribirCondicion();
    cout << "(Archivo 'Condiciones.dat' generado)" << endl;

    cout << "\n--- Consigna 3a: Mayor Promedio ---" << endl;
    miCurso.mayorPromedio();

    cout << "\n--- Consigna 3b: Promedios Discriminados ---" << endl;
    miCurso.promedioTotal(); 

    cout << "\n--- Consigna 3c: Regulares con < Notas ---" << endl;
    miCurso.menoresNotas(); 

    return 0;
}