#include <stdio.h>
#include <cs50.h>
int main(void)
{
    // Prompt user for name
    string name = get_string("whats your name?\n");
    // Saying hello to user
    printf("hello, %s\n", name);
}
