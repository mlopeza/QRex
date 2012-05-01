global int globalMemory;
global float gg2;
global string gg3;
 main(){int a,b,c,d;
float x,y,z,w;
string cadena,f;
cadena="Hola ";
globalMemory=1000;
gg2=1.75;
gg3="Los Ramones";
a=1;
b=5;
c=3;
d=1;

x=1.5;
y=2.5;
z=2.5;
w=a+b;
f="parametros";
if(a>b){
print("Se imprimio A");
print(a);
}else{
print("Se imprimio B");
print(b);
}

print(a);
print(b);
print(c);
print(d);
print(x);
print(y);
print(z);
print(w);
read(a);
while(a<=105){
	print(a);
	a=a+1;
}
print(globalMemory,gg2,gg3);}