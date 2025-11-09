#include <iostream>
#include <cstring>
#include "Resolucion.cpp"

using namespace std;

int main() {

    cout << "Armando la bicicleteria..." << endl;

    // 1. Creamos la gestora
    Bicicleteria miBicicleteria;

    // 2. Creamos los productos (¡con 'new' porque usamos punteros!)
    Producto* p1 = new Parte(1, "Manubrio Carbono", 150.00);
    Producto* p2 = new Parte(2, "Rueda Ruta", 200.00);
    Producto* b1 = new Bicicleta(10, "Bici Urbana", 500.00);
    
    // (A la bici le podríamos agregar partes)
    // Bicicleta* biciPtr = static_cast<Bicicleta*>(b1);
    // biciPtr->addParte(static_cast<Parte*>(p1));
    // biciPtr->addParte(static_cast<Parte*>(p2));

    // 3. Agregamos los productos a la lista "maestra" (opcional pero prolijo)
    miBicicleteria.addProducto(p1);
    miBicicleteria.addProducto(p2);
    miBicicleteria.addProducto(b1);

    // 4. Creamos una Oferta (¡con 'new'!)
    Oferta* o1 = new Oferta();
    
    // 5. Cargamos la Oferta
    o1->addProducto(p1); // Le agregamos el manubrio
    o1->addProducto(b1); // Le agregamos la bici entera

    // 6. Agregamos la Oferta a la Bicicleteria
    miBicicleteria.addOferta(o1);

    // 7. ¡Mostramos!
    miBicicleteria.mostrarDatos();


    // --- Limpieza (MUY importante ya que usamos 'new') ---
    cout << "\nLimpiando memoria..." << endl;
    delete p1;
    delete p2;
    delete b1;
    delete o1;

    return 0;
}