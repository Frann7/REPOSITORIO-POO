#include<iostream>

using namespace std;

template<class T>
class vector {
    private:
        T* data;
        size_t size;
        size_t capacity;
    public:
        vector(){};
        void add(T datos);

};

template<class T>
vector<T>::vector(){
    this->size = 0;
    this->capacity = 2; // Initial capacity
    this->data = new T[this->capacity];
}



template<class T>
void vector<T>::add(T datos) {
    if (this->size == this->capacity) {
        // Resize logic would go here
    }

    this->data[this->capacity++] = datos;
}


int main() {
    cout << "Hello, World!" << endl;
    return 0;
}