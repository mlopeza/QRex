sign int Fibo(int);
int Fibo(int n){
	int f;
	if(n==1||n==2){f=1;}
	else{
		if(n<=0){f=0;}
		else{
			f=Fibo(1)+Fibo(2);
		}
	}
	return f;
}
main(){
int a;
	a=Fibo(6);
print("Fibo",a);

}
