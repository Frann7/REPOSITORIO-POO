#include <iostream>
#include "Resolucion.cpp" 

using namespace std;

// --- FUNCIÓN HELPER: Generar Archivos de Ejemplo ---
void generarArchivosDePrueba()
{
    cout << "Generando archivos de prueba..." << endl;

    // --- 1. Crear Usuarios.dat (Clientes) ---
    ofstream archCli("Usuarios.dat", ios::binary);
    if (archCli.fail()) {
        cout << "Error al crear Usuarios.dat" << endl;
        return;
    }
    struCliente cli;

    // Cliente 1 (Basico, Uso alto)
    cli.id = 101; strcpy(cli.nombre, "Juan Perez"); cli.tipo = 'b'; cli.cantidad = 15;
    archCli.write((char*)&cli, sizeof(struCliente));

    // Cliente 2 (Medio, Uso medio)
    cli.id = 102; strcpy(cli.nombre, "Ana Gomez"); cli.tipo = 'm'; cli.cantidad = 8;
    archCli.write((char*)&cli, sizeof(struCliente));

    // Cliente 3 (Premium, Uso bajo)
    cli.id = 103; strcpy(cli.nombre, "Luis Sosa"); cli.tipo = 'p'; cli.cantidad = 3;
    archCli.write((char*)&cli, sizeof(struCliente));

    // Cliente 4 (Basico, Uso muy alto - Top 1)
    cli.id = 104; strcpy(cli.nombre, "Maria Rios"); cli.tipo = 'b'; cli.cantidad = 20;
    archCli.write((char*)&cli, sizeof(struCliente));

    // Cliente 5 (Premium, Uso medio)
    cli.id = 105; strcpy(cli.nombre, "Carlos Luna"); cli.tipo = 'p'; cli.cantidad = 9;
    archCli.write((char*)&cli, sizeof(struCliente));
    
    // Cliente 6 (Medio, Uso alto)
    cli.id = 106; strcpy(cli.nombre, "Laura Sol"); cli.tipo = 'm'; cli.cantidad = 16;
     archCli.write((char*)&cli, sizeof(struCliente));

    archCli.close();
    cout << "- Usuarios.dat generado." << endl;

    // --- 2. Crear Archivos de Prestaciones (Texto) ---
    ofstream archB("basica.txt");
    if(archB.fail()) return;
    archB << "Consulta Medica" << endl;
    archB << "Analisis Sangre" << endl; // Común
    archB << "Radiografia Simple" << endl;
    archB.close();
    cout << "- basica.txt generado." << endl;

    ofstream archM("medio.txt");
    if(archM.fail()) return;
    archM << "Consulta Medica" << endl;
    archM << "Analisis Sangre" << endl; // Común
    archM << "Ecografia" << endl;
    archM << "Kinesiologia" << endl;
    archM.close();
    cout << "- medio.txt generado." << endl;

    ofstream archP("premium.txt");
    if(archP.fail()) return;
    archP << "Consulta Medica" << endl;
    archP << "Analisis Sangre" << endl; // Común
    archP << "Resonancia Magnetica" << endl;
    archP << "Internacion" << endl;
    archP << "Cirugia Compleja" << endl;
    archP.close();
    cout << "- premium.txt generado." << endl;

    cout << "Archivos de prueba generados con exito." << endl;
}


// --- FUNCIÓN PRINCIPAL MAIN ---
int main()
{
    cout << "--- Prueba Parcial Obra Social ---" << endl;
    
    // 1. Crear los archivos binarios y de texto de prueba
    generarArchivosDePrueba();
    
    // 2. Crear el objeto ObraSocial
    ObraSocial miObraSocial;
    
    // 3. Cargar datos desde los archivos
    cout << "\n--- Cargando datos desde archivos... ---" << endl;
    miObraSocial.leerCliente();
    miObraSocial.leerPrestaciones();
    cout << "Datos cargados en memoria." << endl;
    
    // (Opcional) Mostrar datos cargados para verificar
    // miObraSocial.mostrarDatos(); // Necesitarías implementar esta función en ObraSocial

    // --- Pruebas de las Consignas ---

    // Prueba: Función esPrestada
    cout << "\n--- Prueba Funcion 'esPrestada' ---" << endl;
    cout << "Cliente 101 (Basico) tiene 'Consulta Medica'? " 
         << (miObraSocial.esPrestada(101, "Consulta Medica") ? "Si" : "No") << endl;
    cout << "Cliente 101 (Basico) tiene 'Ecografia'? " 
         << (miObraSocial.esPrestada(101, "Ecografia") ? "Si" : "No") << endl;
    cout << "Cliente 102 (Medio) tiene 'Ecografia'? " 
         << (miObraSocial.esPrestada(102, "Ecografia") ? "Si" : "No") << endl;
    cout << "Cliente 103 (Premium) tiene 'Cirugia Compleja'? " 
         << (miObraSocial.esPrestada(103, "Cirugia Compleja") ? "Si" : "No") << endl;
    cout << "Cliente 999 (Inexistente) tiene 'Consulta Medica'? " 
         << (miObraSocial.esPrestada(999, "Consulta Medica") ? "Si" : "No") << endl;

    // Consigna 1.A: Top 5 Usuarios por Uso
    cout << "\n--- Consigna 1.A: Top 5 Usuarios por Uso ---" << endl;
    miObraSocial.masUtilizaronServicio();
    
    // Consigna 1.B: Todas las Prestaciones
    cout << "\n--- Consigna 1.B: Lista Total de Prestaciones (Ordenada) ---" << endl;
    vector<string> todas = miObraSocial.getTotalPrestaciones();
    if (todas.empty()) {
        cout << "(No se cargaron prestaciones)" << endl;
    } else {
        for(const string& p : todas) {
            cout << "- " << p << endl;
        }
    }
    
    // Consigna 1.C: Cantidad de Usos por Plan
    cout << "\n--- Consigna 1.C: Total Usos por Tipo de Plan ---" << endl;
    miObraSocial.cantServicioxPlan();
    
    // Consigna 1.D: Prestaciones Comunes a Todos
    cout << "\n--- Consigna 1.D: Prestaciones Comunes a Todos los Planes ---" << endl;
    miObraSocial.prestacionesOcurrencia();
    
    cout << "\n--- Fin de la prueba ---" << endl;
    return 0;
}