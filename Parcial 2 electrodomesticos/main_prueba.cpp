// ...existing code...
#include <iostream>
#include "RESOLUCION.CPP"

using namespace std;

int main()
{
    Empresa emp;

    cout << "1) Generando archivo de ejemplo (productos.dat)...\n";
    emp.generarEjemploArchivo();

    cout << "2) Configurando valor USD para importados y leyendo productos desde productos.dat...\n";
    emp.setValorUSD(12.5); // ejemplo: 12.5% aplicado a importados en actualizar_precio
    emp.leer();

    cout << "3) Generando listado ordenado (listado.dat)...\n";
    emp.listado();

    cout << "4) Escribiendo archivo con precios actualizados (Productos_actualizados.dat)...\n";
    emp.PreciosActualizados();

    cout << "5) Imprimiendo cantidad de productos por marca:\n";
    emp.prodXmarca();

    cout << "6) Mostrando producto más caro y más barato:\n";
    emp.masCaro();
    emp.masBarato();

    cout << "\nPrueba finalizada. Archivos generados/actualizados en el directorio del ejecutable:\n"
         << " - productos.dat\n - listado.dat\n - Productos_actualizados.dat\n";

    return 0;
}