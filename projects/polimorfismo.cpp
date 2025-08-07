#include <iostream>



class padre{
    public:
   virtual void hablar(){
       std::cout<<"Hola soy el padre "<< std::endl;
    }
};


class hija1 : public padre{
    void hablar(){
        std::cout<<"Hola soy la hija1";
    }
};

// en ambos casos falta el destructor en las clases para liberar la memoria q pedimos

int main(){

    padre* objeto= new padre();
    objeto->hablar();
    objeto= new hija1;
    objeto->hablar();

    return 0;
}