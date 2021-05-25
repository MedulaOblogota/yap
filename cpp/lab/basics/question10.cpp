enum E1 { AA, BB, CC, DD };
enum E2 { TT, YY };

int main()
{
	int i;
	E1 e = CC;
	E2 temp;

	e = DD;
	temp = TT;
	i = e;
	++i;
}
