#include <iostream>
#include <string.h>

using namespace std;

char* copystr(const char* str){
    char* newstr= new char[strlen(str)+1];
    strcpy(newstr,str);
    return newstr;
}

char* append(char* & first, const char* second){
    char* suma= new char[strlen(first)+strlen(second)+1];
    strcpy(suma, first);
    strcat(suma, second);
    delete[] first;
    first=suma;
    return first;
}

int getlength(const char* str){
    return (strlen(str)+1);
}

int main(){

    char* p= new char[getlength("juan gomez")];
    p=copystr("juan");
    
    p=append(p,"gomez");
    
    for(int i=0; i<getlength(p); i++)
        cout<<p[i];

    return 0;
}