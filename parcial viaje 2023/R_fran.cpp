#include <iostream>
#include <string.h>
#include "VectorDinamico.cpp"

class viaje_mixto{
public:
   viaje_mixto(char* tipo){this->tipo=this->copystr(tipo)};   
   char* gettipo();
   double getprecio();
   virtual double getmonto()=0;
   void setprecio(double precio){this->precio=precio};
protected:
   char* copystr(char* str);
   double precio=0;
   char* tipo; 
};

char* viaje_mixto::copystr(char* str){
   char* temp=new char[strlen(str)+1];
   strcpy(temp, str);
   delete[] str;
   return temp;
}

class viaje_comun : public viaje_mixto{
public:
   viaje_comun(char* tipo): viaje_mixto(tipo);
   
   

};

