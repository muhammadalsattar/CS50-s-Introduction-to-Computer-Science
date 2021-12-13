#include <cs50.h>
#include <stdio.h>

void build(int x);

int main(void)
{
    // Prompting user for integer
    int Height = get_int("Height:\n");

    // Checking if input between 1 - 8
    if (Height >= 1 && Height <= 8)
    {
        build(Height);
    }
    else
    {
        main();
    }
}
// Building function
void build(int x)
{
    for (int i = 1; i <= x; i++)
    {
        // adding space every new line corresponds to wide
        for (int n = x - i; n > 0; n--)
        {
            printf(" ");
        }

        // building left blocks corresponding to wide
        for (int j = 1; j <= i; j++)
        {
            printf("#");
        }

        // printing in between space
        printf("  ");

        // building left blocks corresponding to wide
        for (int k = 1; k <= i; k++)
        {
            printf("#");
        }

        printf("\n");
    }
}
