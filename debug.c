int getchar(){
	int i;
	__builtin_input i;
	return i;
}
void putchar(int i){
	__builtin_output i;
}

int add_two_num(int a,int b){
	return a+b;
}

int sub_two_num(int a,int b){
	return a-b;
}

int main()
{
	int a=3,b=5;
	int i,c,x=0;
	float f=3.5,s=3.2;
	int xx=add_two_num(a,b);
	int yy=sub_two_num(a,b);
	putchar('5');
	f+=s;
	if(a>b)
		c=a-b;
	else 
		c=b-a;
	for(i=0;i<3;i++)
		x+=20;
}
