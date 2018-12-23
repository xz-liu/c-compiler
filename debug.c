int getchar(){
	int i;
	__builtin_input i;
	return i;
}
void putchar(int i){
	__builtin_output i;
}

void print_str(char str[])
{
	int cur;
	for (cur = 0; str[cur] != 0; cur++)putchar(str[cur]);
	
}
int read_str(char str[],int n){
	int i=0;
	while(i<n-1){
		int n= getchar();
		switch(n){
			case 10: break;
			case ' ':break;
			default:
			str[i++]=n;
		}
	}
	str[i]=0;
	return i;
}
void print_int(int i)
{
	char cs[20];
	int cnt = 0;
	if (i < 0){
		i = -i;
		putchar('-');
	}
	if (i == 0){
		putchar('0');
	}
	while (i){
		cs[cnt++] = i % 10 + '0';
		i /= 10;
	}
	while (cnt >= 0){
		putchar(cs[--cnt]);
	}
}
int read_int(){
	int minus = 0;
	int result = 0;
	int ch = getchar();
	while (1) {
		if (ch == '-')
			break;
		if (ch >= '0' && ch <= '9')
			break;
		ch = getchar();
	}
	if (ch == '-') minus = 1;
	else result = ch - '0';
	while (1){
		ch = getchar();
		if (ch < '0' || ch > '9') break;
		result = result * 10 + (ch - '0');
	}
	if (minus)
		return -result;
	else
		return result;
}

void bubbleSort(int arr[], int n)
{
	int i, j;
	for (i = 0; i < n - 1; i++)
		for (j = 0; j < n - i - 1; j++)
			if (arr[j] > arr[j + 1]) {
				int tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
}

void printArray(int arr[], int size)
{
	int i;
	for (i = 0; i < size; i++)
	{
		print_int(arr[i]);
		putchar(' ');
	}
}

int get_sum(int arr[],int n){
	int i,sum=0;
	for(i=0;i<n;++i){
		sum+=arr[i];
	}
	return sum;
}
struct my_inner_struct{
	int in;
};
struct my_struct{
	int a,b,c;
};

int main()
{
	int sz;
	int arr[1000];
	char str[1000];
	int str_sz;
	struct my_struct my;
	print_str("Input size:");
	while (sz = read_int()){
		int i;
		putchar(10);
		print_str("Input ");
		print_int(sz);
		print_str(" integers:");
		for (i = 0; i < sz; i++){
			arr[i] = read_int();
		}
		bubbleSort(arr, sz);
		print_str("Array after sort():");
		printArray(arr, sz);
		putchar(10);
		print_str("Array sum:");
		print_int(get_sum(arr,sz));
		putchar(10);
		print_str("Input size:");
	}

	print_str("Test struct");
	my.a=read_int();
	my.b=read_int();
	my.c=read_int();
	print_int(my.a);
	putchar(10);
	print_int(my.b);
	putchar(10);
	print_int(my.c);
	putchar(10);
	return 0;
}
