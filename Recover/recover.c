#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
 
int main(int argc, char *argv[])
{
    // checking for proper usage
    if (argc != 2)
    {
        return 1;
    }
    
    FILE *card = fopen(argv[1], "r");
    
    //check for valid card
    if (card == NULL)
    {
        return 1;
    }
    
    typedef uint8_t BYTE;
    
    BYTE buffer[512];
    FILE *image = fopen("000.jpg", "w");
    char filename[8];
    int counter = 1;
    int first = 0;
    
    //looping over card to recover images
    while (fread(buffer, sizeof(BYTE), 512, card))
    {
        //if first jpg is discovered
        if (first == 1)
        {
            //if start of a new jpg
            if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
            {
                fclose(image);
                sprintf(filename, "%03i.jpg", counter);
                counter++;
                image = fopen(filename, "w");
                fwrite(buffer, sizeof(BYTE), 512, image);
            }
            
            //if not a jpg start
            else
            {
                fwrite(buffer, sizeof(BYTE), 512, image);
            }
        }
        
        //if first jpg isnt discovered yet
        else
        {
            if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
            {
                first = 1;
                fwrite(buffer, sizeof(BYTE), 512, image);
            }
        }
    }
    fclose(image);
}