struct  my_struct2{ int b; };
struct my_struct {
	int a, b, c, d;
	char ch[10];
	struct my_struct2 bb[10];
};
union my_union{
	int i;
	double d;
	char c;
	long long int ll;
};
int test(int a,int b){
	int c=a,d=b;
	int ans=0;
	while(a!=b){
		int d;
		ans+=c/d;
		a++;
	}
	a|=d&=c*=(b+c);
	return ans;
}
int main(){

	struct my_struct a;
	char str[100] = "this is  not a string!";
	double Pi = 3.1415926;int i;
	int ar[45]={1,2,4,55};
	
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
	case 1:
		break;
	default:
		break;
	}
	return 0;
}