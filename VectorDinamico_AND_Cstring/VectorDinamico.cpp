#include<iostream>

template<class T>
class vector {
    private:
        T* data;
        size_t size;
        size_t capacity;
        void resize(size_t newcapacity);
        
    public:
        vector();
        T get_in_pos(size_t pos){return this->data[pos];};
        void add(T datos);// agregar elemento;
        void remove(size_t pos);// remover un dato pasando la pos
        void removeOcu2(T datos);// remover ocurrencia de un dato
        void removeData(T datos);// remover un dato pasando el dato mismo
        bool existe(T datos);// saber si un elemento existe en el vector
        void reemplazar(T datoviejo, T datonuevo);// reemplaza un elemento por otro
        T& operator[](size_t pos);// similar a getinpos 
        size_t getsize(){return this->size;}// retorna la cantidad de elementos
};

template<class T>
vector<T>::vector(){
    this->size = 0;//cantidad de elementos del vector
    this->capacity = 2; // capacidad maxima(temporalmente) del vector
    this->data = new T[2];// vector dinamico
}    

template<class T>
void vector<T>::add(T datos) {
    if (this->size == this->capacity) {
        this->resize(this->capacity*2);
    }
    this->data[this->size++] = datos;// se incrementa post asignacion
}

template<class T>
void vector<T>::resize(size_t newcapacity){
    T* temp= new T[newcapacity];
    for (size_t i=0; i<this->size; i++){
        temp[i]=this->data[i];
    }
    delete[] this->data;
    this->data=temp;
    this->capacity= newcapacity;
}

template<class T>
void vector<T>::remove(size_t pos){
    for(size_t i=pos; i<this->size; i++)
        this->data[i]=this->data[i+1];// mueve todos los elementos hacia la izquierda

    this->size--;
}

template<class T>
void vector<T>::removeOcu2(T datos){
    for(size_t i=0; i<this->size; i++)
    while(this->data[i]==datos)//remueve todos los T datos del vector
        remove(i);
}

template<class T>
void vector<T>::removeData(T datos){
    for(size_t i=0; i<this->size; i++)
        if(this->data[i]==datos)//remueve solo el primer T dato que encuentre en el vector
          remove(i); 
}

template<class T>
bool vector<T>::existe(T datos){
    for (size_t i=0; i<this->size; i++)    
        if(this->data[i]==datos)
        return true;
    return false;
}

template<class T>
void vector<T>::reemplazar(T datoviejo,T datonuevo){
    for (size_t i=0; i<this->size; i++)
        if(this->data[i]==datoviejo)
            this->data[i]=datonuevo;    
}


template<class T>
T& vector<T>::operator[](size_t pos){// es lo mismo que un getter

    return this->data[pos];
}
