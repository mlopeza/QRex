sign int Pato(int);
 int Pato (int i){int a;
i = i+1;
read(a);
print("Pato:",i,"\n");
return i+a;} main(){int a;
a=1;
print("Main1:",a,"\n");
a=a+1;
a=Pato(1);
print("Main2:",a,"\n");
}