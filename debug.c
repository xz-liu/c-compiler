int function(int a)
{
	if (a == 1)
		return 1;
	else
		return a * function(a - 1);
}

int main()
{
	int a[3] = {2, 3, 6};
	int b[3];
	int i = 0;
	for (i = 0; i < 3; i++)
		b[i] = function(a[i]);
}