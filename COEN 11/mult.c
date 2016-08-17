#include <stdio.h>

int
main(void)

{
srand((int)time(NULL));

 int x;
        int y;
        int z;
        int counter;
	counter = 0;

int i;
for(i = 0;i < 10; i++)

{
	printf("Multiplication Test\n");
	printf("Answer the multiplication test ten times to get your percent correct\n");

	x = rand () % 13;

	y = rand () % 13;

	printf("%d * %d\n", x,y);

	scanf ("%d", &z);

		{
			if(z == x * y)
				counter ++;
		}

	printf("Your total correct answers:");
	printf("%d\n", counter);


	}

	return 1;
}
