#include<iostream>
using namespace std;
float x1,y1,z1,x2,y2,z2,x3,y3,z3,c1,c2,c3,X=0,Y=0,Z=0,W=0;
int type=0;
void type2(){
    cout<<"your equations are of the type x1X + y1Y + z1Z = c1 "<<endl;
    cout<<"Enter  the values of the first equation 'x1,y1,z1,c1"<<endl;
    cin>>x1;
    cin>>y1;
    cin>>z1;
    cin>>c1;
    cout<<"Enter  the values of the second equation 'x2,y2,z2,c2"<<endl;
    cin>>x2;
    cin>>y2;
    cin>>z2;
    cin>>c2;
    cout<<"Enter  the values of the third equation 'x3,y3,z3,c3"<<endl;
    cin>>x3;
    cin>>y3;
    cin>>z3;
    cin>>c3;
    Y=((((-x1*z3)+(z1*x3))*((c2*z1)+(-z2*c1)))-(((-x1*z2)+(z1*x2))*((c3*z1)+(-z3*c1))))/(((((-x1*z3)+(z1*x3))*((-y1*z2)+(y2*z1)))-(((-x1*z2)+(z1*x2))*((-y1*z3)+(y3*z1)))));
    X=(((c2*z1)+(-z2*c1))-(((-y1*z2)+(y2*z1))*Y))/((-x1*z2)+(z1*x2));
    Z=(c1-(y1*Y)-(x1*X))/z1;    
}
void type1(){
    cout<<"Enter  the values of the first equation 'x1,y1,c1"<<endl;
cin>>x1;
cin>>y1;
cin>>c1;
cout<<"Enter  the values of the second equation 'x2,y2,c2"<<endl;
cin>>x2;
cin>>y2;
cin>>c2;
 Y=(((c1*x2)-(c2*x1))/((y1*x2)-(x1*y2)));
 X=(c1-(y1*Y))/x1;
}
int main(){
cout<<"which type of equation do you  want to sole 2 variables(1) or 3 variables(2)"<<endl;
cin>>type;
if(type==1){
type1();
cout<<"the values of X and Y are: "<<X<<" AND "<<Y<<endl;
}
if(type==2){
    type2();
    cout<<"the values of X,Y AND Z are: "<<X<<" "<<Y<<" AND "<<Z<<endl;
}
return 0;
}