int getchar(){
	int i;
	__builtin_input i;
	return i;
}
void putchar(int i){
	__builtin_output i;
}

void print_str(char str[]){
	int cur;
	for(cur=0;str[cur]!=0;cur++){
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
int read_int () {
	int minus = 0;
	int result = 0;
	int ch = getchar();
	while (1) {
		if (ch == '-') break;
		if (ch >= '0' && ch <= '9') break;
		ch = getchar();
	}
	if (ch == '-') minus = 1; else result = ch-'0';
	while (1) {
		ch = getchar();
		if (ch < '0' || ch > '9') break;
		result = result*10 + (ch - '0');
	}
	if (minus)
		return -result;
	else
		return result;
}

int add_two_num(int a,int b){
	return a+b;
}

int sub_two_num(int a,int b){
	return a-b;
}



struct test_struct{
	int a,b,c;
};

void print_own_str(){
	char str[20];
	int cur;
	for(cur=0;cur<20;cur++){
		str[cur]= '0'+cur;
		putchar(str[cur]);
	}
}

int main()
{
	int a=3,b=5;
	int i,c=2,x=0;
	float f=3.5,s=3.2;
	struct test_struct ts;
	int hm[10],hm2[10],hm3[10];
	int xx=add_two_num(a,b);
	int yy=sub_two_num(a,b);
	char cc[4];
	cc[3]=0;
	for(i=0;i<3;i++)cc[i]='_';
	print_str(cc);
	print_int(read_int());
	hm2[b]=100;hm3[c]=2000;
	hm[a]=hm2[b]+hm3[c];
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
	print_int(hm[a]);
	putchar(' ');
	print_int(ts.a);
	print_own_str();
	print_str("fesipfjesronueigrewpofjegrebneojrefwifef  faweffw        freswager");

	
}
