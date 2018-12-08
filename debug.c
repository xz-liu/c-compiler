int putchar(int x);
int getchar(int x);
struct my_struct2{ int b; };
struct my_struct {
	int a, b, c, d;
	char ch[10];
	struct my_struct2 bb[10];
};
int test(int a,int b){
	int c=a,d=b;
	int ans=0;
	while(a!=b){
		ans+=c/d;
		a++;
	}
	a|=d&=c*=(b+c);
	return ans;
}
int main(){
	struct my_struct a;
	char str[100] = "this is a string!";
	double Pi = 3.1415926;int i;
	a.bb[5].b = Pi*(2 / 10 - 5);
	a.b=a.a=2;
	for(i=0;i<5;++i){
		if(a.a==2)	a.a--;
		else if(a.a==1){
			a.b++;
			a.a--;
		}else a.b+=a.a;
	}
	switch (test(4, 6)) {
	case 1:putchar('2');
		break;
	default:putchar('4');
		break;
	}
	return 0;
}

