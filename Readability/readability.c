#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int main(void)
{
    // Setting an itial values for letters, words, sentences.
    int letters = 0;
    int words = 1;
    int sentences = 0;
    
    // Prompting user for text.
    string text = {get_string("Text: ")};
    
    // Getting length of the text.
    int length = strlen(text);
    
    // Looping over to get words, letters, and sentences.
    for (int i = 0; i < length; i++)
    {
        // Checking if current char is alphabet.
        if (isalpha(text[i]))
        {
            letters ++;
        }
        
        // Checking for spaces to detect end of words.
        if (text[i] == ' ')
        {
            words ++;
        }
        
        // Checking for end of sentences.
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences ++;
        }
    }
    
    float L = ((float) letters / words) * 100;
    float S = ((float) sentences / words) * 100;
    
    // Calculating Coleman-Liau index.
    int index = round(0.0588 * L - 0.296 * S - 15.8);
    
    
    if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }

}
