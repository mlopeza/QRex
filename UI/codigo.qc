sign int Pato(int);
 int Pato (int i){i=i+1;
print("Pato:",i,"\n");
return (i+1);} main(){int a;
a=1;
print("Main1:",a,"\n");
a=Pato(1);
print("Main2:",a,"\n");}