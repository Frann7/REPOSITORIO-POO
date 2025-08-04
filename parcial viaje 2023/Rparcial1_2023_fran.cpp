#include <iostream>
#include <string.h>
#include "VectorDinamico.cpp"

class viaje{
public:
   viaje(char* tipo){this->tipo=this->copystr(tipo);};   
   char* gettipo(){return this->tipo;};
   virtual double getmonto()=0;
   friend std::ostream& operator << (std::ostream& os,viaje& p);
protected:
   char* copystr(const char* str);
   char* tipo;
   double monto; 
};

//consigna b;
std::ostream& operator << (std::ostream& os, viaje& p){
   os <<" Tipo de Viaje "<<p.gettipo()<< std::endl;
   os <<"Monto a pagar\n";
   os <<p.getmonto();
}

char* viaje::copystr(const char* str){
   char* temp=new char[strlen(str)+1];
   strcpy(temp, str);
   delete[] str;
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
   viaje_mixto(char* tipo, double monto):viaje(tipo, monto){};
   void addviaje(viaje* newviaje);
   double getmonto();
private:
   vector<viaje*> vecviajes_mixtos;
};

void viaje_mixto::addviaje(viaje* newviaje){
   if(dynamic_cast<viaje_mixto*>(newviaje))
      return;

   vecviajes_mixtos.add(newviaje);
   
}

double viaje_mixto::getmonto(){   
   for (int i=0; i<vecviajes_mixtos->getcapacity(); i++)
   double monto_+= vecviaje_mixtos[i]->getmonto();
   return monto_;
}

class gestora {
public:
   gestora(){};
   void addviaje(viaje* newviaje);
   void mostrardatos();
private:
   vector<viaje*> datos;
}

void gestora::addviaje(viaje* newviaje){
     datos->add(newviaje);
}

void mostrardatos(){
   for(int i=0; i<datos->getcapacity(); i++)
      std::cout<<*datos[i]<<std::endl;
}