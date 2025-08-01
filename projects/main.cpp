#include <iostream>
#include "VectorDinamico.cpp"

using namespace std;

int main(){
    
vector<int> vec;

for(int i=0; i<5; i++)
        vec.add(i);

vec.add(3);
    
cout<<"Vector sin modificaciones\n";
for(int i=0; i<vec.getsize(); i++)
    cout<<"  "<<vec[i]<<"  ";
    cout<<endl;

vec.removeOcu2(3);

cout<<"Vector con modificaciones\n";
for(int i=0; i<vec.getsize(); i++)
    cout<<"  "<<vec[i]<<"  ";

    return 0;
}