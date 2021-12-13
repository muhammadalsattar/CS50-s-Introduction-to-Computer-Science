#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{
    // Defining a string to hold user key
    string argument;
    
    // Checking if user provides a key
    if (argc != 2)
    {
        // If not a key, program print error message and exit
        printf("Please provide 1 argument.\n");
        return 1;
    }
    else
    {
        // setting user key to a variable and getting its length
        argument = argv[1];
        int length = strlen(argument);

        // Checking if key composes of 26 letters
        if (length != 26)
        {
            printf("Argument must contain 26 letters.\n");
            return 1;
        }

        for (int i = 0; i < length; i++)
        {
            // Checking if key letters all alphabets
            if (isalpha(argument[i]) == false)
            {
                printf("Argument must be all alphabets.\n");
                return 1;
            }
            
            // Checking if key has to similar letters in it
            int count = 0;

            for (int j = 0; j < length; j++)
            {
                if (toupper(argument[j]) == toupper(argument[i]))
                {
                    count++;
                }
            }
            
            // Printing error message and exit program if there are 2 similar letters in user key
            if (count > 1)
            {
                printf("Argument must not have two similar letters.");
                return 1;
            }
        }
    }
    
    // Prompting user for plain text after all tests for key are over
    string text = get_string("plaintext: ");
    
    int textlen = strlen(text);
    
    string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    
    for (int r = 0; r < textlen; r++)
    {
        // Replacing lowercase letters in user text with cipher text
        if (text[r] >= 'a' && text[r] <= 'z')
        {
            for (int g = 0; g < 26; g++)
            {
                if (alphabet[g] == text[r])
                {
                    text[r] = tolower(argument[g]);
                    break;
                }
            }
        }
        
        // Replacing lowercase letters in user text with cipher text
        else if (text[r] >= 'A' && text[r] <= 'Z') 
        {
            for (int k = 0; k < 26; k++)
            {
                if (ALPHABET[k] == text[r])
                {
                    text[r] = toupper(argument[k]);
                    break;
                }
            }
        }
        
    }
    // Printing out plain text converted to cipher text
    printf("ciphertext: %s\n", text);
}