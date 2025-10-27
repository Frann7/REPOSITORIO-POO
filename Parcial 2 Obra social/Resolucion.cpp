#include <iostream>
#include <cstring>
#include <string>      // Para std::string
#include <vector>      // Para std::vector
#include <fstream>     // Para ifstream, ofstream
#include <numeric>     // Para std::accumulate
#include <algorithm>   // Para std::sort, std::find, std::min
#include <map>         // Para std::map

using namespace std;

// --- ESTRUCTURA DE ARCHIVO ---
// Representación binaria de los datos en Usuarios.dat
struct struCliente
{
    int id;
    char nombre[200];
    char tipo; // 'b': basico, 'm': medio, 'p': premium
    int cantidad; // Cantidad de veces que usó algún servicio en el mes
};

// -----------------------------------------------------------------
// --- CLASE CLIENTE (Declaración) ---
// -----------------------------------------------------------------
// Representa a un cliente/usuario de la obra social
class Cliente
{
public:
    // Constructor: recibe los datos leídos del struct
    Cliente(int id, char* nom, char tipo, int cant);

    // Getters (const: no modifican el objeto)
    int getId() const;
    string getNombre() const; // Devuelve std::string
    char getTipo() const;
    int getCantidad() const;

    // Setters (permiten modificar los datos si fuera necesario)
    void setId(int id);
    void setNombre(const string& nom); // Recibe std::string
    void setTipo(char tipo);
    void setCantidad(int cant);

private:
    int id;
    string nombre; // Usamos std::string para manejo automático de memoria
    char tipo;
    int cantidad;
};

// -----------------------------------------------------------------
// --- CLASE OBRA SOCIAL (Declaración) ---
// -----------------------------------------------------------------
// Clase gestora: maneja la lista de clientes y las prestaciones por plan
class ObraSocial
{
public:
    // Constructor
    ObraSocial();

    // Métodos de carga de datos
    void leerCliente();      // Lee Usuarios.dat
    void leerPrestaciones(); // Lee basica.txt, medio.txt, premium.txt

    // Funciones del enunciado y consignas
    bool esPrestada(int clienteId, const string& prestacion); // Verifica si una prestación está cubierta
    void masUtilizaronServicio();        // Consigna 1.A: Top 5 usuarios
    vector<string> getTotalPrestaciones(); // Consigna 1.B: Todas las prestaciones (con repetidas)
    void cantServicioxPlan();            // Consigna 1.C: Total usos por tipo de plan
    void prestacionesOcurrencia();       // Consigna 1.D: Prestaciones comunes a todos los planes

private:
    // (Helper) Añade un objeto Cliente al vector
    void agregarCliente(Cliente c);
    // (Helper) Busca un cliente por ID y devuelve un puntero (o nullptr si no lo encuentra)
    Cliente* buscarClientePorId(int id);

    // Almacenamiento de datos
    vector<Cliente> vecCliente;      // Lista de todos los clientes
    vector<string> vecPBasico;     // Prestaciones del plan Básico
    vector<string> vecPMedio;      // Prestaciones del plan Medio
    vector<string> vecPPremium;    // Prestaciones del plan Premium
};


// -----------------------------------------------------------------
// --- CLIENTE (Implementación) ---
// -----------------------------------------------------------------

// Constructor: Convierte char* a std::string
Cliente::Cliente(int id, char* nom, char tipo, int cant)
{
    this->id = id;
    this->nombre = nom; // std::string se inicializa directamente desde char*
    this->tipo = tipo;
    this->cantidad = cant;
}

// --- Getters ---
int Cliente::getId() const { return this->id; }
string Cliente::getNombre() const { return this->nombre; }
char Cliente::getTipo() const { return this->tipo; }
int Cliente::getCantidad() const { return this->cantidad; }

// --- Setters ---
void Cliente::setId(int id) { this->id = id; }
void Cliente::setNombre(const string& nom) { this->nombre = nom; } // Asignación directa de string
void Cliente::setTipo(char tipo) { this->tipo = tipo; }
void Cliente::setCantidad(int cant) { this->cantidad = cant; }


// -----------------------------------------------------------------
// --- OBRA SOCIAL (Implementación) ---
// -----------------------------------------------------------------

ObraSocial::ObraSocial() { } // Constructor vacío

// (Helper) Añade una copia del objeto Cliente al vector
void ObraSocial::agregarCliente(Cliente c)
{
    this->vecCliente.push_back(c);
}

// Lee el archivo binario de clientes y los carga en vecCliente
void ObraSocial::leerCliente()
{
    // Asume que el archivo se llama "Usuarios.dat" (¡Verificar!)
    ifstream archivo("Usuarios.dat", ios::binary);
    if(archivo.fail()) {
        cout << "Error al abrir Usuarios.dat" << endl;
        return;
    }

    struCliente stru;
    while(archivo.read((char*)&stru, sizeof(stru)))
    {
        // Llama al constructor de Cliente que convierte char* a string
        this->agregarCliente(Cliente(stru.id, stru.nombre, stru.tipo, stru.cantidad));
    }
    archivo.close(); // Cerrar el archivo
}

// Lee los tres archivos de texto de prestaciones
void ObraSocial::leerPrestaciones()
{
    string linea; // Variable reutilizable para leer cada línea

    // --- Leer basica.txt ---
    ifstream archivoB("basica.txt");
    if(archivoB.fail()) {
        cout << "Error al abrir basica.txt" << endl;
    } else {
        while(getline(archivoB, linea))
        {
            this->vecPBasico.push_back(linea);
        }
        archivoB.close(); // Cerrar el archivo
    }

    // --- Leer medio.txt ---
    ifstream archivoM("medio.txt");
    if(archivoM.fail()) {
        cout << "Error al abrir medio.txt" << endl;
    } else {
        while(getline(archivoM, linea))
        {
            this->vecPMedio.push_back(linea);
        }
        archivoM.close(); // Cerrar el archivo
    }
    
    // --- Leer premium.txt ---
    ifstream archivoP("premium.txt");
    if(archivoP.fail()) {
        cout << "Error al abrir premium.txt" << endl;
    } else {
        while(getline(archivoP, linea))
        {
            this->vecPPremium.push_back(linea);
        }
        archivoP.close(); // Cerrar el archivo
    }
}

// (Helper interno) Busca un cliente por su ID.
// Devuelve un puntero al cliente si lo encuentra, o nullptr si no.
// Es útil para la función esPrestada.
Cliente* ObraSocial::buscarClientePorId(int id) {
    for (Cliente& cliente : vecCliente) { // Usa referencia para eficiencia
        if (cliente.getId() == id) {
            return &cliente; // Devuelve la dirección de memoria del cliente encontrado
        }
    }
    return nullptr; // No se encontró el cliente
}


// Función del enunciado: Verifica si una prestación está cubierta para un cliente
// Modificada para recibir el ID del cliente en lugar del objeto completo
bool ObraSocial::esPrestada(int clienteId, const string& prestacion)
{
    // Busca al cliente por su ID
    Cliente* clientePtr = buscarClientePorId(clienteId);

    // Si no encontramos al cliente, no podemos verificar
    if (clientePtr == nullptr) {
         cout << "Cliente con ID " << clienteId << " no encontrado." << endl;
         return false;
    }
    
    // Obtenemos el tipo de plan del cliente encontrado
    char tipoPlan = clientePtr->getTipo();

    // Variable para guardar el resultado de la búsqueda
    bool encontrada = false;
    
    // Busca la prestación en el vector correspondiente al plan
    if(tipoPlan == 'b')
    {
        auto it = find(this->vecPBasico.begin(), this->vecPBasico.end(), prestacion);
        encontrada = (it != this->vecPBasico.end());
    }
    else if (tipoPlan == 'm')
    {
        auto it = find(this->vecPMedio.begin(), this->vecPMedio.end(), prestacion);
        encontrada = (it != this->vecPMedio.end());
    }
    else if (tipoPlan == 'p')
    {
        auto it = find(this->vecPPremium.begin(), this->vecPPremium.end(), prestacion);
        encontrada = (it != this->vecPPremium.end());
    }
    // Si el tipo no es 'b', 'm', ni 'p', 'encontrada' sigue siendo false

    return encontrada;
}

// Consigna 1.A: Obtiene los 5 usuarios que más utilizaron el servicio
void ObraSocial::masUtilizaronServicio()
{
    // Chequeo de seguridad
    if(this->vecCliente.empty()) {
        cout << "No hay clientes cargados." << endl;
        return;
    }

    // Ordena el vector de clientes de MAYOR a MENOR cantidad de usos
    // Se usa '&' en la lambda para eficiencia
    sort(this->vecCliente.begin(), this->vecCliente.end(),
        [](Cliente& c1, Cliente& c2) {
            return c1.getCantidad() > c2.getCantidad();
        });

    // Límite seguro: el menor entre 5 y el tamaño total
    size_t limite = min((size_t)5, this->vecCliente.size());

    cout << "--- Top 5 Clientes por Uso del Servicio ---" << endl; 
    for(size_t i = 0; i < limite; i++)
    {
        cout << "Nombre: " << this->vecCliente[i].getNombre();
        cout << " | Cantidad de Usos: " << this->vecCliente[i].getCantidad() << endl;
    }
}

// Consigna 1.B: Obtiene todas las prestaciones de todos los planes (ordenadas, con repetidas)
vector<string> ObraSocial::getTotalPrestaciones()
{
    vector<string> vecPrestacionesCat; // Vector resultado
    
    // Inserta todas las prestaciones de Básico
    vecPrestacionesCat.insert(vecPrestacionesCat.end(), 
                              this->vecPBasico.begin(), this->vecPBasico.end());
    // Inserta todas las de Medio
    vecPrestacionesCat.insert(vecPrestacionesCat.end(), 
                              this->vecPMedio.begin(), this->vecPMedio.end());
    // Inserta todas las de Premium
    vecPrestacionesCat.insert(vecPrestacionesCat.end(), 
                              this->vecPPremium.begin(), this->vecPPremium.end());

    // Ordena alfabéticamente el vector resultante
    sort(vecPrestacionesCat.begin(), vecPrestacionesCat.end());

    return vecPrestacionesCat; // Devuelve el vector completo
}

// Consigna 1.C: Obtiene la cantidad total de veces que se utilizó el servicio por tipo de plan
void ObraSocial::cantServicioxPlan()
{
    if(this->vecCliente.empty()) {
        cout << "No hay clientes cargados." << endl;
        return;
    }

    // Mapa para acumular: Clave = tipo de plan (char), Valor = suma de cantidades (int)
    map<char, int> cantXplan;

    // Recorre el vector de clientes (usando const& para eficiencia)
    for(const Cliente& c : this->vecCliente)
    {
        // Acumula la 'cantidad' del cliente en la entrada correspondiente a su 'tipo'
        cantXplan[c.getTipo()] += c.getCantidad();
    }

    cout << "--- Total de Usos del Servicio por Tipo de Plan ---" << endl;
    // Imprime el contenido del mapa
    for(auto const& par : cantXplan)
    {
        cout << "Tipo plan '" << par.first << "': " << par.second << " usos totales." << endl;
    }
}

// Consigna 1.D: Obtiene las prestaciones que se repiten en TODOS los planes
void ObraSocial::prestacionesOcurrencia()
{
    vector<string> prestacionesComunes; // Vector resultado

    // Recorre la lista del plan Básico (usualmente la más corta)
    for (const string& prestacion : vecPBasico) 
    {
        // Verifica si la prestación actual está en la lista del plan Medio
        bool estaEnMedio = (find(vecPMedio.begin(), vecPMedio.end(), prestacion) != vecPMedio.end());

        // Verifica si la prestación actual está en la lista del plan Premium
        bool estaEnPremium = (find(vecPPremium.begin(), vecPPremium.end(), prestacion) != vecPPremium.end());

        // Si está en AMBAS listas (&&), se considera común a los tres planes
        if (estaEnMedio && estaEnPremium) 
        {
            // Opcional: Antes de agregarla, podríamos verificar si YA está en 
            // 'prestacionesComunes' para evitar duplicados si 'prestacion'
            // aparecía varias veces en 'vecPBasico'.
            // Por simplicidad, aquí la agregamos directamente.
            prestacionesComunes.push_back(prestacion);
        }
    }

    // (Opcional Avanzado: Para eliminar duplicados si 'prestacion' estaba repetida
    //  en vecPBasico pero cumplía la condición):
    // sort(prestacionesComunes.begin(), prestacionesComunes.end());
    // prestacionesComunes.erase(unique(prestacionesComunes.begin(), prestacionesComunes.end()), prestacionesComunes.end());


    cout << "--- Prestaciones comunes a TODOS los planes ---" << endl;
    if (prestacionesComunes.empty()) {
        cout << "(Ninguna prestación encontrada en los tres planes)" << endl;
    } else {
        for (const string& p : prestacionesComunes) {
            cout << "- " << p << endl;
        } 
    }
}