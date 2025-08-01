#include <iostream>
#include "VectorDinamico.cpp"

using namespace std;

int main(){
    int tam=0;
vector<int> vec;

for(int i=0; i<5; i++)
        vec.add(i);
    
cout<<"Vector sin modificaciones\n";
for(int i=0; i<5; i++)
    cout<<"  "<<vec[i]<<"  ";
    cout<<endl;

vec.removeOcu2(3);

cout<<"Vector con modificaciones\n";
for(int i=0; i<vec.getsize(); i++)
    cout<<"  "<<vec[i]<<"  ";

    return 0;
}