#include <iostream>
#include <string.h>
// archivo vectores dinamicos
#include "VectorDinamico.cpp"

//Clase Abstracta
class viaje{
public:
   viaje(char* tipo) {this->tipo=this->copystr(tipo);}; // guarda el tipo de viaje con la funcion de cstring, lo programas una vez y las hijas lo heredan  
   char* gettipo(){return this->tipo;};// nos sirve para mostrar el tipo de viaje en la sobrecarga
   virtual double getmonto()=0;// metodo abstracto
   friend std::ostream& operator << (std::ostream& os,viaje& p);//sobrecarga operador << sirve para mostrar la info como si fuera un main
protected: // protected por la herencia
   char* copystr(const char* str);
   char* tipo;
   double monto; 
};

//consigna b;
std::ostream& operator << (std::ostream& os, viaje& p){
   os <<"Tipo de Viaje "<<p.gettipo()<< std::endl;
   os <<"Monto a pagar ";
   os <<p.getmonto() << std::endl;
   return os;
}

char* viaje::copystr(const char* str){// funcion cstring (tambien se puede hacer directamente en el constructor de viaje y no como metodo aparte)
   char* temp=new char[strlen(str)+1];
   strcpy(temp, str);
   return temp;
}

class viaje_comun : public viaje{
public:
   viaje_comun(char* tipo, double monto): viaje(tipo){
      this->monto= monto;
   };
   double getmonto(); 
};

double viaje_comun::getmonto(){
   return this->monto;
}

class viaje_destino : public viaje{
public:
   viaje_destino(char* tipo, double monto, double km) : viaje(tipo){
      this->monto=monto;
      this->km=km;
   };
   double getmonto();
private:
   double km;
};

double viaje_destino::getmonto(){
   return this->monto*this->km;
}

class viaje_mixto : public viaje{
public:
   viaje_mixto(char* tipo): viaje(tipo){};
    
   void addviaje(viaje* newviaje);
   double getmonto();
private:
   vector<viaje*> vecviajes_mixtos;
};

void viaje_mixto::addviaje(viaje* newviaje){
   if(dynamic_cast<viaje_mixto*>(newviaje))// dynamic_cast es para que el vector de viaje_mixto no guarde viajes mixtos en si(solo debe guardar viajes comunes y viajes por destino)
      return;

   vecviajes_mixtos.add(newviaje);
   
}

double viaje_mixto::getmonto(){
   double monto=0;
   for (size_t i=0; i<vecviajes_mixtos.getsize(); i++)
      monto += vecviajes_mixtos[i]->getmonto();// recorre el vector y en cada posicion usa el metodo getmonto() de ese objeto viaje* con polimorfismo
                                               // ejemplo si vecviajes_mixtos[0] fuera un viaje* que tiene un new viaje_comun a su vez entonces implementa ese getmonto()
   return monto;
}

class gestora {
public:
   gestora(){};
   void addviaje(viaje* newviaje);
   void mostrardatos();
private:
   vector<viaje*> datos;// vector que guarda viajes comunes, por destino y mixtos
};

void gestora::addviaje(viaje* newviaje){
   if(datos.getsize()<100)// la empresa no va a contar con mas de 100 viajes
   datos.add(newviaje);// usar datos.add, no usar datos->add ya que la -> se usa para implementar metodos de los objetos que estan dentro del vector, no del vector mismo
    /*ejemplo pensar como si fuera una caja (vector) con direcciones (punteros) adentro: 
      caja.agregar_direccion() → Le decis a la caja que agregue una dirección
      caja[0]->tocar_timbre() → Vas a la dirección que está en la posición 0 de la caja y tocas el timbre*/
}

void gestora::mostrardatos(){
   for(int i=0; i<datos.getsize(); i++)
      std::cout<<*datos[i]<<std::endl;// puntero para desreferenciar sino muestra direcciones de memoria
}

int main(){
   gestora gestor;

   viaje* viaje1= new viaje_comun("Viaje comun", 3000);
   viaje* viaje2= new viaje_destino("Viaje destino", 100, 30);

   viaje_mixto* viaje3= new viaje_mixto("Viaje mixto");

   viaje3->addviaje(viaje1);
   viaje3->addviaje(viaje2);

   gestor.addviaje(viaje1);
   gestor.addviaje(viaje2);
   gestor.addviaje(viaje3);

   gestor.mostrardatos();

   return 0;
}