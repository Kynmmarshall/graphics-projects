#include<iostream>
 
using namespace std;
int arra[32];
int i=0,j=0;
int main(){
   while(i<32){
      arra[i]=1+i;
      i++;
   }
   i=0;
 while(i<32){
   while(arra[i+j]<=32){
    arra[i+j]=-arra[i+j];
      j+=i;
   }
   j=0;
   i++;
 }
 i=0;
 while(i<32){
   cout<<arra[i]<<" ";
   i++;
 }
   return 0;
}