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

void bubbleSort(int arr[], int n) 
{ 
   int i, j; 
   for (i = 0; i < n-1; i++)        
       for (j = 0; j < n-i-1; j++)  
           if (arr[j] > arr[j+1]) {
			   int tmp= arr[j];
			   arr[j]=arr[j+1];
			   arr[j+1]=tmp;
		   } 
} 
  
void printArray(int arr[], int size) 
{ 
    int i; 
    for (i=0; i < size; i++){ 
		print_int(arr[i]);
		putchar(' ');
	}
} 
  

struct test_struct{
	int a,b,c;
};

int main()
{
	int sz=10;
	int arr[10];
	int i;
	print_str("Input 10 integers:");
	for(i =0;i<sz;i++){
		arr[i]=read_int();
	}
	bubbleSort(arr,sz);
	
	print_str("Array after sort():");
	printArray(arr,sz);
}
