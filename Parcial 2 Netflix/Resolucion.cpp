#include <iostream>
#include <cstring>     // Para manejar char* (strlen, strcpy)
#include <algorithm>   // Para std::sort, std::min, std::max_element
#include <fstream>     // Para manejo de archivos (ifstream, ofstream)
#include <vector>      // Para std::vector
#include <numeric>     // Para std::accumulate
#include <map>         // Para std::map

using namespace std;

// --- ESTRUCTURAS DE ARCHIVOS ---
// Representación exacta de los datos en los archivos binarios

struct struCatalogo
{
    int nro;
    char nombre[200];
    char tipo; // 's' para serie, 'p' para película
};

struct struVotacion
{
    int nro;
    int votacion; // Calificación de 0 a 5
};

// --- CLASE CATALOGO ---
// Representa un solo ítem (película o serie) y sus votos
class Catalogo
{
public:
    // Constructor
    Catalogo(int nro, const char* nom, char tipo);

    // Métodos
    void addVotacion(int v); // Añade un voto (calificación) al vector

    // Getters
    // const al final "promete" que el método no modificará el objeto
    size_t getCantVotos() const;
    double getValoracion() const;
    int getNro() const;
    const char* getNombre() const;
    char getTipo() const;

    // Setters
    void setNro(int n);
    void setNombre(const char* n);
    void setTipo(char t);
    
private:
    vector<int> vecVot; // Vector de calificaciones (0-5)
    int nro;            // ID único
    char* nombre;       // Nombre (usando char* como pide el profe)
    char tipo;
};

// --- IMPLEMENTACIÓN CATALOGO ---

Catalogo::Catalogo(int nro, const char* nom, char tipo)
{
    this->nro = nro;
    // Asignación de memoria para el char*
    this->nombre = new char[strlen(nom) + 1]; // +1 para el caracter nulo '\0'
    strcpy(this->nombre, nom);
    this->tipo = tipo;
}

// Añade una calificación (int) al vector interno
void Catalogo::addVotacion(int v)
{
    this->vecVot.push_back(v);
}

// Devuelve cuántas calificaciones (votos) ha recibido
size_t Catalogo::getCantVotos() const
{
    return this->vecVot.size();
}

// Calcula y devuelve la valoración promedio (calificación)
double Catalogo::getValoracion() const
{
    // Chequeo de seguridad: Evita la división por cero si no hay votos
    if(this->vecVot.empty()) return 0.0;

    // Suma todas las calificaciones.
    // El '0.0' (double) es crucial para forzar una suma con decimales.
    double suma = accumulate(this->vecVot.begin(), this->vecVot.end(), 0.0);
    
    return suma / this->vecVot.size();
}

// --- Getters y Setters simples ---
int Catalogo::getNro() const { return this->nro; }
void Catalogo::setNro(int n) { this->nro = n; }
const char* Catalogo::getNombre() const { return this->nombre; }
char Catalogo::getTipo() const { return this->tipo; }
void Catalogo::setTipo(char t) { this->tipo = t; }

// Asigna un nuevo nombre
void Catalogo::setNombre(const char* n)
{
    // (Nota: Esto genera un 'memory leak' si no se borra el 'nombre'
    // anterior. Pero para el parcial en papel, está bien).
    this->nombre = new char[strlen(n) + 1];
    strcpy(this->nombre, n);
}


// --- CLASE PLATAFORMA ---
// Clase gestora: maneja la lista de todo el catálogo y los archivos
class Plataforma
{
public:
    Plataforma();
    
    // (Helper) Añade un objeto Catalogo al vector
    void agregarCatalogo(Catalogo c);

    // Métodos de carga y escritura
    void leerDatos();       // Carga Catalogo.dat y Votaciones.dat
    void escribirDatos();   // Consigna 2
    void mostrarDatos();    // (Helper) Muestra todo el catálogo
    
    // Métodos de consignas STL
    void mayorValoracion(); // Consigna 3a
    void masVotadasForma1(); // Consigna 3b (con max_element)
    void masVotadasForma2(); // Consigna 3b (con sort)
    void cantVotos();       // Consigna 3c (con map)

private:
    vector<Catalogo> vecCat; // Vector de OBJETOS Catalogo
};

// --- IMPLEMENTACIÓN PLATAFORMA ---

Plataforma::Plataforma() { } // Constructor vacío

// (Helper) Añade un objeto Catalogo al vector
void Plataforma::agregarCatalogo(Catalogo c)
{
    this->vecCat.push_back(c);
}

// Carga ambos archivos binarios en memoria
void Plataforma::leerDatos()
{
    // 1. Leer el catálogo de películas/series
    ifstream archivoCatalogo("Catalogo.dat", ios::binary);
    if(archivoCatalogo.fail()) {
        cout << "Error: No se pudo abrir Catalogo.dat" << endl;
        return;
    }

    struCatalogo struC;
    while(archivoCatalogo.read((char*)&struC, sizeof(struC)))
    {
        // Usa el método público 'agregarCatalogo'
        this->agregarCatalogo(Catalogo(struC.nro, struC.nombre, struC.tipo));
    }
    archivoCatalogo.close(); // Siempre cerrar los archivos

    // 2. Leer las votaciones y asignarlas
    ifstream archivoVotacion("Votaciones.dat", ios::binary);
    if(archivoVotacion.fail()) {
        cout << "Error: No se pudo abrir Votaciones.dat" << endl;
        return;
    }

    struVotacion struV;
    while(archivoVotacion.read((char*)&struV, sizeof(struV)))
    {
        // Se usa '&' (Referencia) para modificar el objeto ORIGINAL
        // dentro del vector, y no una copia temporal.
        for(Catalogo& c : this->vecCat)
        {
            if(c.getNro() == struV.nro)
            {
                c.addVotacion(struV.votacion);
                break; // Optimización: Si el ID es único, salimos del 'for'
            }
        }
    }
    archivoVotacion.close(); // Siempre cerrar los archivos
}

// (Helper) Muestra todos los datos cargados para depurar
void Plataforma::mostrarDatos()
{
    cout << "--- Catálogo Completo de la Plataforma ---" << endl;
    
    // Se usa 'const&' (Referencia Constante) para LEER.
    // Es rápido (no copia) y seguro (no deja modificar).
    for(const Catalogo& c : this->vecCat)
    {
        cout << "Nro: " << c.getNro() << ", Nombre: " << c.getNombre() 
             << ", Tipo: " << c.getTipo() << ", Votos: " << c.getCantVotos()
             << ", Valoracion: " << c.getValoracion() << endl;
    }
}

// Consigna 2: Escribe archivo de texto con Nombre y Valoración
void Plataforma::escribirDatos()
{
    ofstream archivo("Datos.dat"); // Archivo de texto
    if(archivo.fail()) {
        cout << "Error: No se pudo crear Datos.dat" << endl;
        return;
    }

    // Se usa 'const&' (rápido y seguro)
    for(const Catalogo& c : this->vecCat)
    {
        archivo << "Nombre: " << c.getNombre() << ".........Valoracion: " 
                << c.getValoracion() << endl;
    }
    archivo.close(); // Siempre cerrar los archivos
}

// Consigna 3a: Obtiene las 5 películas/series con mayor valoración
void Plataforma::mayorValoracion()
{
    // 1. Chequeo de seguridad
    if(this->vecCat.empty())
    {
        cout << "No hay películas o series en la plataforma." << endl;
        return;
    }

    // 2. Ordena el vector de MAYOR a MENOR valoración
    // Se usa '&' en la lambda para que sea más eficiente (evita copias)
    sort(this->vecCat.begin(), this->vecCat.end(),
         [](Catalogo& c1, Catalogo& c2) {
             // La "boquita >" ordena de mayor a menor
             return c1.getValoracion() > c2.getValoracion();
         });
    
    // 3. Límite seguro: el menor entre 5 y el tamaño total del vector
    // (size_t)5 es para comparar dos números del mismo tipo (size_t)
    size_t limite = std::min((size_t)5, this->vecCat.size());

    // 4. Imprime solo hasta ese límite
    cout << "--- 5 Series y/o Películas con mayor valoración ---" << endl; 
    for(size_t i = 0; i < limite; i++)
    {
        cout << "Nombre: " << this->vecCat[i].getNombre();
        cout << " | Valoracion: " << this->vecCat[i].getValoracion() << endl;
    }
}

// Consigna 3b (Forma 1): "Más votadas" usando max_element (más eficiente)
void Plataforma::masVotadasForma1()
{
    if(this->vecCat.empty())
    {
        cout << "No hay películas o series en la plataforma." << endl;
        return;
    }

    // 1. Encuentra un iterador al primer elemento con MÁS votos
    // La "boquita <" le dice a max_element cómo encontrar el "más grande"
    auto it_max = max_element(this->vecCat.begin(), this->vecCat.end(),
        [](Catalogo& c1, Catalogo& c2){
            return c1.getCantVotos() < c2.getCantVotos();
        });
    
    // 'it_max' es un iterador, se puede usar '->' como un puntero
    size_t maxVotos = it_max->getCantVotos();

    cout << "--- Película/s o Serie/s más votadas ---" << endl;
    // 2. Recorre el vector y muestra TODOS los que empaten
    for(const Catalogo& c : this->vecCat)
    {
        if(c.getCantVotos() == maxVotos)
        {
            if(c.getTipo() == 's')
                cout << "Serie: " << c.getNombre() << " (Votos: " << c.getCantVotos() << ")" << endl;
            else
                cout << "Pelicula: " << c.getNombre() << " (Votos: " << c.getCantVotos() << ")" << endl;
        }       
    }
}

// Consigna 3b (Forma 2): "Más votadas" usando sort
void Plataforma::masVotadasForma2()
{
    if(this->vecCat.empty())
    {
        cout << "No hay películas o series en la plataforma." << endl;
        return;
    }

    // 1. Ordena el vector de MAYOR a MENOR nro de votos
    sort(this->vecCat.begin(), this->vecCat.end(),
        [](Catalogo& c1, Catalogo& c2){
            return c1.getCantVotos() > c2.getCantVotos();
        });

    // 2. El nro máximo de votos está en el primer elemento
    size_t cantMax = this->vecCat[0].getCantVotos();

    cout << "--- Película/s o Serie/s más votadas ---" << endl;
    // 3. Recorre el vector e imprime TODOS los que empaten
    for(const Catalogo& c : this->vecCat)
    {
        if(cantMax == c.getCantVotos())
        {
            if(c.getTipo() == 's')
                cout << "Serie: " << c.getNombre() << " (Votos: " << c.getCantVotos() << ")" << endl;
            else
                cout << "Pelicula: " << c.getNombre() << " (Votos: " << c.getCantVotos() << ")" << endl;
        }
        else
        {
            // OPTIMIZACIÓN: Como el vector está ordenado,
            // si encontramos uno que no empata, ya no habrá más.
            break;
        }
    }
}

// Consigna 3c: Cantidad total de votos por tipo (Serie vs Película)
void Plataforma::cantVotos()
{
    if(this->vecCat.empty())
    {
        cout << "No hay películas o series en la plataforma." << endl;
        return;
    }
    
    // 1. Crea un mapa: la clave es el 'tipo' (char), el valor es el 'conteo' (size_t)
    map<char, size_t> votosPorTipo;

    // 2. Carga el mapa: recorre el vector y acumula los votos
    for(const Catalogo& c : this->vecCat)
    {
        // Si la clave (ej. 's') no existe, la crea con valor 0.
        // Luego, le SUMA la cantidad de votos de 'c'.
        votosPorTipo[c.getTipo()] += c.getCantVotos();
    }

    cout << "--- Votos totales por Tipo ---" << endl;
    // 3. Imprime el mapa (usando el 'for' moderno para mapas)
    for (auto const& par : votosPorTipo) 
    {
        // par.first es la Clave ('s' o 'p')
        // par.second es el Valor (el total de votos acumulado)
        cout << "Tipo: " << par.first << " | Cantidad total de votos: " << par.second << endl;
    }
}