int getchar(){
	int i;
	__builtin_input i;
	return i;
}
void putchar(int i){
	__builtin_output i;
}

struct test_struct{
	int a,b,c;
};
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
	struct test_struct ts;
	int fuck[3],fuck2[3],fuck3[3];
	int xx=add_two_num(a,b);
	int yy=sub_two_num(a,b);
	fuck[a]=fuck2[b]+fuck3[c];
	ts.a=ts.b=ts.c;
	putchar('5');
	f+=s;
	if(a>b)
		c=a-b;
	else 
		c=b-a;
	for(i=0;i<3;i++)
		x+=20;
}
