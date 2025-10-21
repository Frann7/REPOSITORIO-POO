#include <iostream>
#include "VectorDinamico.cpp"

using namespace std;

int main(){
    
vector<int> vec;
bool existe;

for(int i=0; i<5; i++)
        vec.add(i);

vec.add(3);
vec.add(4);
existe=vec.existe(3);    
cout<<"Vector sin modificaciones\n";
for(int i=0; i<vec.getsize(); i++)
    cout<<"  "<<vec[i]<<"  ";

cout<<endl;

cout<<existe<<endl;

vec.removeOcu2(3);
vec.removeData(4);
existe=vec.existe(3);  
cout<<"Vector con modificaciones\n";
for(int i=0; i<vec.getsize(); i++)
    cout<<"  "<<vec[i]<<"  ";
cout<<endl;
cout<<existe;
    return 0;
}