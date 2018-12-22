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

void print_str(char str[]){
	int cur;
	for(cur=0;str[cur]!=0;cur++){
		putchar(str[cur]);
	}
}
void print_own_str(){
	char str[20];
	int cur;
	for(cur=0;cur<20;cur++){
		str[cur]= '0'+cur;
		putchar(str[cur]);
	}
}
void print_int(int i){
	char cs[20];
	int cnt=0;
	if(i<0){
		i=-i;
		putchar('-');
	}
	if(i==0){
		putchar('0');
	}
	while(i){
		cs[cnt++]=i%10+'0';
		i/=10;
	}
	while(cnt>=0){
		putchar(cs[--cnt]);
	}
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
	int i,c=2,x=0;
	float f=3.5,s=3.2;
	struct test_struct ts;
	int fuck[10],fuck2[10],fuck3[10];
	int xx=add_two_num(a,b);
	int yy=sub_two_num(a,b);
	fuck2[b]=100;fuck3[c]=2000;
	fuck[a]=fuck2[b]+fuck3[c];
	ts.a=ts.b=ts.c=-345678;
	putchar('5');
	putchar(' ');
	print_int(234);

	f+=s;
	if(a>b)
		c=a-b;
	else 
		c=b-a;
	for(i=0;i<3;i++){
		int y=x;
		x+=20;
		putchar('-');
		print_int(y);
	
	}
	putchar(' ');
	print_int(x);
	putchar(' ');
	print_int(xx);
	putchar(' ');
	print_int(fuck[a]);
	putchar(' ');
	print_int(ts.a);
	print_own_str();
	print_str("fucK!!!!!!!!!!\n");

	
}
