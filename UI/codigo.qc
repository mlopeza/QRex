sign int fibo(int);
 int fibo (int n){int ret,a,b;
if(n==1||n==2){
	ret=1;
}else{
	/*a=fibo(n-1);*/
	/*b=fibo(n-2)*/
	/*ret=a+b;*/
	ret=fibo(n-1)+fibo(n-2);
	print("A:",n-1," B:",n-2," RET:",ret,"\n");
}

return ret;} main(){int a,b;
read(b);
a=fibo(b);
print(a);}