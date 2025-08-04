#include<iostream>


using namespace std;

template<class T>
class vector {
    private:
        T* data;
        size_t size;
        size_t capacity;
        void resize(size_t newcapacity);
        void remove(size_t pos);
    public:
        vector();
        ~vector() { delete[] data; }
        void add(T datos);
        bool removeinpos(size_t pos);
        bool removeOcu1(T datos);
        void removeOcu2(T datos);
        T& operator[](size_t pos);
        size_t getsize(){return this->size;}
        size_t  getcapacity(){return this->capacity;}
};

template<class T>
vector<T>::vector(){
    this->size = 0;
    this->capacity = 2; // Initial capacity
    this->data = new T[2];
}    

template<class T>
void vector<T>::add(T datos) {
    if (this->size == this->capacity) {
        this->resize(this->capacity*2);
    }
    this->data[this->size++] = datos;
}

template<class T>
void vector<T>::resize(size_t newcapacity){
    T* temp= new T[newcapacity];
    for (int i=0; i<this->capacity; i++){
        temp[i]=this->data[i];
    }
    delete[] this->data;
    this->data=temp;
    this->capacity= newcapacity;
}

template<class T>
void vector<T>::remove(size_t pos){
    for(int i=pos; i<this->size; i++)
        this->data[i]=this->data[i+1];

    this->size--;
}

template<class T>
bool vector<T>::removeinpos(size_t pos){
    if(!(pos<this->size))
        return false;
    remove(pos);
    return true;
}

template<class T>
void vector<T>::removeOcu2(T datos){
    for(int i=0; i<this->size; i++)
    while(this->data[i]==datos)
        remove(i);
}

template<class T>
bool vector<T>::removeOcu1(T datos){
    bool status=false;
    for (int i=0; i<this->size; i++)
        if(this->data[i]==datos){
        remove(i);
        status=true;
        }
    return status;
}

template<class T>
T& vector<T>::operator[](size_t pos){

    return this->data[pos];
}
