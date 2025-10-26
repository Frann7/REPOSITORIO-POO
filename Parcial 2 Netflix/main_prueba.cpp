#include <iostream>
#include "Resolucion.cpp"

using namespace std;

// --- FUNCIÓN HELPER: Generar Archivos de Ejemplo ---
// (Esta funcion es necesaria para crear los archivos que tu Plataforma::leerDatos va a buscar)
void generarEjemploArchivos()
{
    // --- 1. Crear Catalogo.dat (Series y Peliculas) ---
    ofstream archCat("Catalogo.dat", ios::binary);
    if (!archCat) return;

    struCatalogo cat;

    // Item 1: Serie (S), Alta Valoracion, Muchos Votos
    cat.nro = 1001; strcpy(cat.nombre, "Serie A - Ganadora"); cat.tipo = 's';
    archCat.write((char*)&cat, sizeof(struCatalogo));

    // Item 2: Pelicula (P), Alta Valoracion, Muchos Votos (Empata con Serie A)
    cat.nro = 2002; strcpy(cat.nombre, "Peli B - El Empate"); cat.tipo = 'p';
    archCat.write((char*)&cat, sizeof(struCatalogo));

    // Item 3: Serie (S), Baja Valoracion, Votos Medios
    cat.nro = 1003; strcpy(cat.nombre, "Serie C - Promedio"); cat.tipo = 's';
    archCat.write((char*)&cat, sizeof(struCatalogo));

    // Item 4: Pelicula (P), Baja Valoracion, Pocos Votos
    cat.nro = 2004; strcpy(cat.nombre, "Peli D - Novoto"); cat.tipo = 'p';
    archCat.write((char*)&cat, sizeof(struCatalogo));
    
    // Item 5: Serie (S), Valoracion Perfecta, Votos Bajos (Estara entre las 5)
    cat.nro = 1005; strcpy(cat.nombre, "Serie E - Perfecta"); cat.tipo = 's';
    archCat.write((char*)&cat, sizeof(struCatalogo));
    
    // Item 6: Pelicula (P), Baja Valoracion, Muchos Votos (Para que quede sexta)
    cat.nro = 2006; strcpy(cat.nombre, "Peli F - Sexta"); cat.tipo = 'p';
    archCat.write((char*)&cat, sizeof(struCatalogo));

    archCat.close();
    cout << "Archivo 'Catalogo.dat' generado con 6 items." << endl;

    // --- 2. Crear Votaciones.dat ---
    ofstream archVot("Votaciones.dat", ios::binary);
    if (!archVot) return;

    struVotacion vot;

    // Votos para Serie A (1001) - TOTAL VOTOS: 6. VALORACION: (4+5+5+4)/4 = 4.5
    vot.nro = 1001; vot.votacion = 4; archVot.write((char*)&vot, sizeof(struVotacion));
    vot.nro = 1001; vot.votacion = 5; archVot.write((char*)&vot, sizeof(struVotacion));
    vot.nro = 1001; vot.votacion = 5; archVot.write((char*)&vot, sizeof(struVotacion));
    vot.nro = 1001; vot.votacion = 4; archVot.write((char*)&vot, sizeof(struVotacion));
    
    // Votos para Peli B (2002) - TOTAL VOTOS: 6. VALORACION: (5+5+5)/3 = 5.0 (¡Ganador Valoracion!)
    vot.nro = 2002; vot.votacion = 5; archVot.write((char*)&vot, sizeof(struVotacion));
    vot.nro = 2002; vot.votacion = 5; archVot.write((char*)&vot, sizeof(struVotacion));
    vot.nro = 2002; vot.votacion = 5; archVot.write((char*)&vot, sizeof(struVotacion));
    
    // Votos para Serie C (1003) - TOTAL VOTOS: 2. VALORACION: (3+4)/2 = 3.5
    vot.nro = 1003; vot.votacion = 3; archVot.write((char*)&vot, sizeof(struVotacion));
    vot.nro = 1003; vot.votacion = 4; archVot.write((char*)&vot, sizeof(struVotacion));

    // Votos para Peli F (2006) - TOTAL VOTOS: 6. VALORACION: (4+4)/2 = 4.0
    vot.nro = 2006; vot.votacion = 4; archVot.write((char*)&vot, sizeof(struVotacion));
    vot.nro = 2006; vot.votacion = 4; archVot.write((char*)&vot, sizeof(struVotacion));
    vot.nro = 2006; vot.votacion = 4; archVot.write((char*)&vot, sizeof(struVotacion));
    vot.nro = 2006; vot.votacion = 4; archVot.write((char*)&vot, sizeof(struVotacion));
    vot.nro = 2006; vot.votacion = 4; archVot.write((char*)&vot, sizeof(struVotacion));
    vot.nro = 2006; vot.votacion = 4; archVot.write((char*)&vot, sizeof(struVotacion)); // <- Maximo de votos
    
    // Votos para Serie E (1005) - TOTAL VOTOS: 1. VALORACION: 5.0 (Empata valoracion con Peli B)
    vot.nro = 1005; vot.votacion = 5; archVot.write((char*)&vot, sizeof(struVotacion));


    // Nota: Peli D (2004) no tiene votos. CantVotos=0, Valoracion=0.0
    
    archVot.close();
    cout << "Archivo 'Votaciones.dat' generado." << endl;
}


// --- FUNCIÓN PRINCIPAL MAIN ---
int main()
{
    cout << "--- INICIO DE PRUEBA DE PARCIAL NETFLIX ---" << endl;
    
    // 1. Generar los archivos binarios de prueba
    generarEjemploArchivos();

    // 2. Crear el objeto Plataforma
    Plataforma netflix;

    // 3. Cargar los datos a memoria (¡CRÍTICO!)
    cout << "\nCargando datos a memoria..." << endl;
    netflix.leerDatos();
    cout << "Datos cargados. (6 items)" << endl;
    
    // Helper: Mostrar catalogo completo
    netflix.mostrarDatos();

    // --- CONSIGNAS ---

    // Consigna 1 & 2: Archivo de texto
    cout << "\n--- CONSIGNAS 1 & 2: Archivo de Texto ---" << endl;
    netflix.escribirDatos();
    cout << "Archivo 'Datos.dat' generado con nombres y valoraciones." << endl;

    // Consigna 3a: Mayor Valoracion (Top 5)
    cout << "\n--- CONSIGNAS 3a: Mayor Valoracion (Top 5) ---" << endl;
    netflix.mayorValoracion();

    // Consigna 3b: Mas Votadas (Usando tu Forma 1 con max_element)
    cout << "\n--- CONSIGNAS 3b: Mas Votadas (Empates) ---" << endl;
    netflix.masVotadasForma1();
    
    // Consigna 3c: Votos Totales por Tipo (usando map)
    cout << "\n--- CONSIGNAS 3c: Votos por Tipo (MAP) ---" << endl;
    netflix.cantVotos();

    cout << "\n--- FIN DE PRUEBA ---" << endl;
    return 0;
}