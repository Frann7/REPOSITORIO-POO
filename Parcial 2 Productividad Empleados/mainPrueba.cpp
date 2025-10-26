#include <iostream>
#include "Resolucion.cpp" 

using namespace std;


// --- FUNCIÓN HELPER: Generar Archivos de Ejemplo ---
// Esta funcion crea los .dat para que tu programa pueda leerlos
void generarArchivosDePrueba()
{
    // --- 1. Crear Empleados.dat ---
    ofstream arch1("Empleados.dat", ios::binary);
    if (arch1.fail()) {
        cout << "Error al crear Empleados.dat" << endl;
        return;
    }
    
    struEmpleados emp;

    // Empleado 1 (El que menos trabaja)
    strcpy(emp.dni, "111");
    strcpy(emp.nombre, "Juan");
    strcpy(emp.apellido, "Perez");
    arch1.write((char*)&emp, sizeof(struEmpleados));

    // Empleado 2 (El que mas trabaja)
    strcpy(emp.dni, "222");
    strcpy(emp.nombre, "Ana");
    strcpy(emp.apellido, "Gomez");
    arch1.write((char*)&emp, sizeof(struEmpleados));

    // Empleado 3 (Horas intermedias)
    strcpy(emp.dni, "333");
    strcpy(emp.nombre, "Luis");
    strcpy(emp.apellido, "Sosa");
    arch1.write((char*)&emp, sizeof(struEmpleados));
    
    arch1.close();
    cout << "Archivo 'Empleados.dat' generado con exito." << endl;

    // --- 2. Crear Horas.dat ---
    ofstream arch2("Horas.dat", ios::binary);
    if (arch2.fail()) {
        cout << "Error al crear Horas.dat" << endl;
        return;
    }

    struHorasT hora;

    // Horas para Juan (111) -> Total: 18 hs (El minimo)
    strcpy(hora.dni, "111"); hora.horasT = 10; strcpy(hora.fecha, "20251020");
    arch2.write((char*)&hora, sizeof(struHorasT));
    strcpy(hora.dni, "111"); hora.horasT = 8; strcpy(hora.fecha, "20251021");
    arch2.write((char*)&hora, sizeof(struHorasT));

    // Horas para Ana (222) -> Total: 120 hs (El maximo)
    strcpy(hora.dni, "222"); hora.horasT = 40; strcpy(hora.fecha, "20251020");
    arch2.write((char*)&hora, sizeof(struHorasT));
    strcpy(hora.dni, "222"); hora.horasT = 40; strcpy(hora.fecha, "20251021");
    arch2.write((char*)&hora, sizeof(struHorasT));
    strcpy(hora.dni, "222"); hora.horasT = 40; strcpy(hora.fecha, "20251022");
    arch2.write((char*)&hora, sizeof(struHorasT));

    // Horas para Luis (333) -> Total: 45 hs
    strcpy(hora.dni, "333"); hora.horasT = 20; strcpy(hora.fecha, "20251020");
    arch2.write((char*)&hora, sizeof(struHorasT));
    strcpy(hora.dni, "333"); hora.horasT = 25; strcpy(hora.fecha, "20251021");
    arch2.write((char*)&hora, sizeof(struHorasT));

    arch2.close();
    cout << "Archivo 'Horas.dat' generado con exito." << endl;
}


// --- FUNCIÓN PRINCIPAL MAIN ---
int main()
{
    cout << "--- Prueba Parcial 2: Empresa ---" << endl;
    
    // 1. Crear los archivos binarios de prueba
    generarArchivosDePrueba();
    
    // 2. Crear el objeto Empresa
    Empresa miEmpresa;
    
    // 3. Probar Consigna 1: Leer archivos y cargar memoria
    cout << "\n--- Consigna 1: Leyendo archivos... ---" << endl;
    miEmpresa.leerArchivos();
    cout << "Archivos leidos y cargados en memoria." << endl;
    
    // 4. Probar Consigna 2: Escribir reporte
    cout << "\n--- Consigna 2: Escribiendo reporte... ---" << endl;
    miEmpresa.escribir();
    cout << "Archivo 'Datos.dat' generado con exito." << endl;
    
    // 5. Probar Consigna 3 (Forma 1)
    cout << "\n--- Consigna 3 (Forma 1: max/min_element) ---" << endl;
    miEmpresa.cantHorasTrabajaronF1();
    
    // 6. Probar Consigna 3 (Forma 2)
    cout << "\n--- Consigna 3 (Forma 2: sort) ---" << endl;
    miEmpresa.cantHorasTrabajaronF2();
    
    cout << "\n--- Fin de la prueba ---" << endl;
    return 0;
}