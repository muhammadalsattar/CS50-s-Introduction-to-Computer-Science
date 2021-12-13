#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main(void)
{
    // Prompting user for number
    long num = get_long("Number: \n");
    int length = 1; 

    // Looping over to get number length
    for (unsigned long long int i = 10; i *= 10;)
    {
        long j = num % i;
        length += 1;
        if (j == num)
        {
            break;
        }
    }

    // Checking if length in regular range
    if (length > 16 || length < 13)
    {
        printf("INVALID\n");
        exit(0);
    }

    // Getting sum of adding every other digit multiplied by 2, starting with second-to-last digit.
    int sum1 = 0;
    for (int n = 2; n <= length; n += 2)
    {
        unsigned long long int power = pow(10, n);
        int mydigit = (num % power) / (power / 10);

        // Checking if current number's digit has is greater than 9.
        if (mydigit * 2 > 9)
        {
            int mydig = (mydigit * 2) % 10;
            int mydig1 = ((mydigit * 2) % 100) / 10;
            sum1 = sum1 + mydig + mydig1;
        }
        else
        {
            sum1 = sum1 + (mydigit * 2);
        }
    }

    // Getting sum of adding number's digits that weren't multiplied.
    int sum2 = 0;
    for (int n = 1; n <= length; n += 2)
    {
        unsigned long long int power2 = pow(10, n);
        int mydigit2 = (num % power2) / (power2 / 10);
        sum2 = sum2 + mydigit2;
    }

    // adding both sums together to get final sum
    int sum3 = sum1 + sum2;
    int result = sum3 % 10;

    // Using Lunh's algorithm to figure out valid card numbers.
    if (result == 0)
    {
        // Checking if card is American express.
        if (length == 15)
        {
            unsigned long long int poweramex = pow(10, length - 1);
            int amex = (num % poweramex) / (poweramex / 10);
            if (amex == 4 || amex == 7)
            {
                printf("AMEX\n");
                exit(0);
            }
            else
            {
                printf("INVALID\n");
                exit(0);
            }

        }
        // Checking if number is Visa or Mastercard
        else if (length < 17 && length > 12)
        {
            unsigned long long int powervisa = pow(10, length);
            int visa = (num % powervisa) / (powervisa / 10);

            // Checking if number is visa.
            if (visa == 4)
            {
                printf("VISA\n");
                exit(0);
            }

            // Checking if number is Mastercard
            else
            {
                unsigned long long int powermcard = pow(10, length);
                int mcard = (num % powermcard) / (powermcard / 10);

                unsigned long long int powermcard1 = pow(10, length - 1);
                int mcard1 = (num % powermcard1) / (powermcard1 / 10);
                printf("mcard1: %i\n", mcard1);


                if (mcard == 5)
                {
                    if (mcard1 > 0 && mcard1 < 6)
                    {
                        printf("MASTERCARD\n");
                        exit(0);
                    }
                    else
                    {
                        printf("INVALID\n");
                        exit(0);
                    }
                }
            }
        }
    }

    // If number is not one of the above, so its INVALID!
    else
    {
        printf("INVALID\n");
        exit(0);
    }
}

