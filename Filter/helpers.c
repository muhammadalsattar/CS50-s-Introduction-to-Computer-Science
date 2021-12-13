#include <stdio.h>
#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // calculating average value of RGB
            float sum = image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue;
            float average = sum / 3;
            int value = round(average);

            image[i][j].rgbtBlue = value;
            image[i][j].rgbtGreen = value;
            image[i][j].rgbtRed = value;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // creating temp array
    RGBTRIPLE temparr[width];
    for (int i = 0; i < height; i++)
    {
        int counter = 0;
        for (int j = width - 1; j >= 0; j--)
        {
            temparr[counter] = image[i][j];
            counter++;
        }
        for (int k = 0; k < width; k++)
        {
            image[i][k] = temparr[k];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // creating temp array
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // top left corner pixel's algorithm
            if (i == 0 && j == 0)
            {
                // calculating new red value
                float sumRed = image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed;
                float avgRED = sumRed / 4;
                temp[i][j].rgbtRed = round(avgRED);
                
                // calculating new blue value
                float sumBlue = image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue;
                float avgBLUE = sumBlue / 4;
                temp[i][j].rgbtBlue = round(avgBLUE);
                
                //calculating new green value
                float sumGreen = image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen;
                float avgGREEN = sumGreen / 4;
                temp[i][j].rgbtGreen = round(avgGREEN);
            }
            
            // top right corner pixel's algorithm
            else if (i == 0 && j == (width - 1))
            {
                // calculating new red value
                float sumRed = image[i][j - 1].rgbtRed + image[i][j].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed;
                float avgRED = sumRed / 4;
                temp[i][j].rgbtRed = round(avgRED);
                
                // calculating new blue value
                float sumBlue = image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue;
                float avgBLUE = sumBlue / 4;
                temp[i][j].rgbtBlue = round(avgBLUE);
                
                // calculating new green value
                float sumGreen = image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen;
                float avgGREEN = sumGreen / 4;
                temp[i][j].rgbtGreen = round(avgGREEN);
            }
            // bottom left corner pixel's algorithm
            else if (j == 0 && i == (height - 1))
            {
                // calculating new red value
                float sumRed = image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i][j].rgbtRed + image[i][j + 1].rgbtRed;
                float avgRED = sumRed / 4;
                temp[i][j].rgbtRed = round(avgRED);
                
                // calculating new blue value
                float sumBlue = image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue;
                float avgBLUE = sumBlue / 4;
                temp[i][j].rgbtBlue = round(avgBLUE);
                
                // calculating new green value
                float sumGreen = image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen;
                float avgGREEN = sumGreen / 4;
                temp[i][j].rgbtGreen = round(avgGREEN);
            }
            
            // bottom right corner pixel's algorithm
            else if (j == (width - 1) && i == (height - 1))
            {
                // calculating new red value
                float sumRed = image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i][j - 1].rgbtRed + image[i][j].rgbtRed;
                float avgRED = sumRed / 4;
                temp[i][j].rgbtRed = round(avgRED);
                
                // calculating new blue value
                float sumBlue = image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue;
                float avgBLUE = sumBlue / 4;
                temp[i][j].rgbtBlue = round(avgBLUE);
                
                // calculating new green value
                float sumGreen = image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen;
                float avgGREEN = sumGreen / 4;
                temp[i][j].rgbtGreen = round(avgGREEN);
            }
            
            // 1st column pixel's algorithm 
            else if (j == 0 && (i != 0 || i != (height - 1)))
            {
                // calculating new red value
                float sumRed = image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i][j].rgbtRed + image[i][j + 1].rgbtRed + 
                               image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed;
                float avgRED = sumRed / 6;
                temp[i][j].rgbtRed = round(avgRED);
                
                // calculating new blue value
                float sumBlue = image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + 
                                image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue;
                float avgBLUE = sumBlue / 6;
                temp[i][j].rgbtBlue = round(avgBLUE);
                
                // calculating new green value
                float sumGreen = image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + 
                                 image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen;
                float avgGREEN = sumGreen / 6;
                temp[i][j].rgbtGreen = round(avgGREEN);
            }
            
            // 1st row pixel's algorithm
            else if (i == 0 && (j != 0 || j != (width - 1)))
            {
                // calculating new red value
                float sumRed = image[i][j - 1].rgbtRed + image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j - 1].rgbtRed +
                               image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed;
                float avgRED = sumRed / 6;
                temp[i][j].rgbtRed = round(avgRED);
                
                // calculating new blue value
                float sumBlue = image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue +
                                image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue;
                float avgBLUE = sumBlue / 6;
                temp[i][j].rgbtBlue = round(avgBLUE);
                
                // calculating new green value
                float sumGreen = image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen + 
                                 image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen;
                float avgGREEN = sumGreen / 6;
                temp[i][j].rgbtGreen = round(avgGREEN);
            }
            
            // last column pixel's algorithm
            else if (j == (width - 1) && (i != 0 || i != (height - 1)))
            {
                // calculating new red value
                float sumRed = image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i][j - 1].rgbtRed + image[i][j].rgbtRed +
                               image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed;
                float avgRED = sumRed / 6;
                temp[i][j].rgbtRed = round(avgRED);
                
                // calculating new blue value
                float sumBlue = image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue +
                                image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue;
                float avgBLUE = sumBlue / 6;
                temp[i][j].rgbtBlue = round(avgBLUE);
                
                // calculating new green value
                float sumGreen = image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen +
                                 image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen;
                float avgGREEN = sumGreen / 6;
                temp[i][j].rgbtGreen = round(avgGREEN);
            }
            
            // last row pixel's algorithm
            else if (i == (height - 1) && (j != 0 || j != (width - 1)))
            {
                // calculating new red value
                float sumRed = image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed +
                               image[i][j - 1].rgbtRed + image[i][j].rgbtRed + image[i][j + 1].rgbtRed;
                float avgRED = sumRed / 6;
                temp[i][j].rgbtRed = round(avgRED);
                
                // calculating new blue value
                float sumBlue = image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue +
                                image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue;
                float avgBLUE = sumBlue / 6;
                temp[i][j].rgbtBlue = round(avgBLUE);
                
                // calculating new green value
                float sumGreen = image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen +
                                 image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen;
                float avgGREEN = sumGreen / 6;
                temp[i][j].rgbtGreen = round(avgGREEN);
            }
            
            // middle pixel's algorithm
            else
            {
                // calculating new red value
                float sumRed = image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i][j - 1].rgbtRed +
                               image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed +
                               image[i + 1][j + 1].rgbtRed;
                float avgRED = sumRed / 9;
                temp[i][j].rgbtRed = round(avgRED);
                
                // calculating new blue value
                float sumBlue = image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i][j - 1].rgbtBlue +
                                image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue +
                                image[i + 1][j + 1].rgbtBlue;
                float avgBLUE = sumBlue / 9;
                temp[i][j].rgbtBlue = round(avgBLUE);
                
                // calculating new green value
                float sumGreen = image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen +
                                 image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen +
                                 image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen;
                float avgGREEN = sumGreen / 9;
                temp[i][j].rgbtGreen = round(avgGREEN);
            }
        }
    }
    
    for (int k = 0; k < height; k++)
    {
        for (int r = 0; r < width; r++)
        {
            image[k][r].rgbtRed = temp[k][r].rgbtRed;
            image[k][r].rgbtBlue = temp[k][r].rgbtBlue;
            image[k][r].rgbtGreen = temp[k][r].rgbtGreen;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // top left corner pixel's algorithm
            if (i == 0 && j == 0)
            {
                // calculating new red value
                int redGx = (image[i][j + 1].rgbtRed * 2) + (image[i + 1][j + 1].rgbtRed * 1);
                int redGy = (image[i + 1][j].rgbtRed * 2) + (image[i + 1][j + 1].rgbtRed * 1);
                int sumred = (redGx * redGx) + (redGy * redGy);
                float sqred = sqrt(sumred);
                int redval = round(sqred);
                if (redval > 255)
                {
                    temp[i][j].rgbtRed = 255;
                }
                else
                {
                    temp[i][j].rgbtRed = redval;
                }
                
                // calculating new blue value
                int blueGx = (image[i][j + 1].rgbtBlue * 2) + (image[i + 1][j + 1].rgbtBlue * 1);
                int blueGy = (image[i + 1][j].rgbtBlue * 2) + (image[i + 1][j + 1].rgbtBlue * 1);
                int sumblue = (blueGx * blueGx) + (blueGy * blueGy);
                float sqrblue = sqrt(sumblue);
                int blueval = round(sqrblue);
                if (blueval > 255)
                {
                    temp[i][j].rgbtBlue = 255;
                }
                else
                {
                    temp[i][j].rgbtBlue = blueval;
                }
                
                // calculating new green value
                int greenGx = (image[i][j + 1].rgbtGreen * 2) + (image[i + 1][j + 1].rgbtGreen * 1);
                int greenGy = (image[i + 1][j].rgbtGreen * 2) + (image[i + 1][j + 1].rgbtGreen * 1);
                int sumgreen = (greenGx * greenGx) + (greenGy * greenGy); 
                float sqrgreen = sqrt(sumgreen);
                int greenval = round(sqrgreen);
                if (greenval > 255)
                {
                    temp[i][j].rgbtGreen = 255;
                }
                else
                {
                    temp[i][j].rgbtGreen = greenval;
                }
            }
            
            // top right corner pixel's algorithm
            else if (i == 0 && j == (width - 1))
            {
                // calculating new red value
                int redGx = (image[i][j - 1].rgbtRed * -2) + (image[i][j].rgbtRed * 0) + (image[i + 1][j - 1].rgbtRed * -1) +
                            (image[i + 1][j].rgbtRed * 0);
                int redGy = (image[i][j - 1].rgbtRed * 0) + (image[i][j].rgbtRed * 0) + (image[i + 1][j - 1].rgbtRed * 1) +
                            (image[i + 1][j].rgbtRed * 2);
                int sumred = (redGx * redGx) + (redGy * redGy);
                float sqred = sqrt(sumred);
                int redval = round(sqred);
                if (redval > 255)
                {
                    temp[i][j].rgbtRed = 255;
                }
                else
                {
                    temp[i][j].rgbtRed = redval;
                }
                
                // calculating new blue value
                int blueGx = (image[i][j - 1].rgbtBlue * -2) + (image[i + 1][j - 1].rgbtBlue * -1);
                int blueGy = (image[i + 1][j - 1].rgbtBlue * 1) + (image[i + 1][j].rgbtBlue * 2);
                int sumblue = (blueGx * blueGx) + (blueGy * blueGy);
                float sqrblue = sqrt(sumblue);
                int blueval = round(sqrblue);
                if (blueval > 255)
                {
                    temp[i][j].rgbtBlue = 255;
                }
                else
                {
                    temp[i][j].rgbtBlue = blueval;
                }
                
                // calculating new green value
                int greenGx = (image[i][j - 1].rgbtGreen * -2) + (image[i + 1][j - 1].rgbtGreen * -1);
                int greenGy = (image[i + 1][j - 1].rgbtGreen * 1) + (image[i + 1][j].rgbtGreen * 2);
                int sumgreen = (greenGx * greenGx) + (greenGy * greenGy); 
                float sqrgreen = sqrt(sumgreen);
                int greenval = round(sqrgreen);
                if (greenval > 255)
                {
                    temp[i][j].rgbtGreen = 255;
                }
                else
                {
                    temp[i][j].rgbtGreen = greenval;
                }
            }
            
            // bottom left corner pixel's algorithm
            else if (j == 0 && i == (height - 1))
            {
                // calculating new red value
                int redGx = (image[i - 1][j + 1].rgbtRed * 1) + (image[i][j + 1].rgbtRed * 2);
                int redGy = (image[i - 1][j].rgbtRed * -2) + (image[i - 1][j + 1].rgbtRed * -1);
                int sumred = (redGx * redGx) + (redGy * redGy);
                float sqred = sqrt(sumred);
                int redval = round(sqred);
                if (redval > 255)
                {
                    temp[i][j].rgbtRed = 255;
                }
                else
                {
                    temp[i][j].rgbtRed = redval;
                }
                
                // calculating new blue value
                int blueGx = (image[i - 1][j + 1].rgbtBlue * 1) + (image[i][j + 1].rgbtBlue * 2);
                int blueGy = (image[i - 1][j].rgbtBlue * -2) + (image[i - 1][j + 1].rgbtBlue * -1);
                int sumblue = (blueGx * blueGx) + (blueGy * blueGy);
                float sqrblue = sqrt(sumblue);
                int blueval = round(sqrblue);
                if (blueval > 255)
                {
                    temp[i][j].rgbtBlue = 255;
                }
                else
                {
                    temp[i][j].rgbtBlue = blueval;
                }
                
                // calculating new green value
                int greenGx = (image[i - 1][j + 1].rgbtGreen * 1) + (image[i][j + 1].rgbtGreen * 2);
                int greenGy = (image[i - 1][j].rgbtGreen * -2) + (image[i - 1][j + 1].rgbtGreen * -1);
                int sumgreen = (greenGx * greenGx) + (greenGy * greenGy); 
                float sqrgreen = sqrt(sumgreen);
                int greenval = round(sqrgreen);
                if (greenval > 255)
                {
                    temp[i][j].rgbtGreen = 255;
                }
                else
                {
                    temp[i][j].rgbtGreen = greenval;
                }
            }
            
            // bottom right corner pixel's algorithm
            else if (j == (width - 1) && i == (height - 1))
            {
                // calculating new red value
                int redGx = (image[i - 1][j - 1].rgbtRed * -1) + (image[i][j - 1].rgbtRed * -2);
                int redGy = (image[i - 1][j - 1].rgbtRed * -1) + (image[i - 1][j].rgbtRed * -2);
                int sumred = (redGx * redGx) + (redGy * redGy);
                float sqred = sqrt(sumred);
                int redval = round(sqred);
                if (redval > 255)
                {
                    temp[i][j].rgbtRed = 255;
                }
                else
                {
                    temp[i][j].rgbtRed = redval;
                }
                
                // calculating new blue value
                int blueGx = (image[i - 1][j - 1].rgbtBlue * -1) + (image[i][j - 1].rgbtBlue * -2);
                int blueGy = (image[i - 1][j - 1].rgbtBlue * -1) + (image[i - 1][j].rgbtBlue * -2);
                int sumblue = (blueGx * blueGx) + (blueGy * blueGy);
                float sqrblue = sqrt(sumblue);
                int blueval = round(sqrblue);
                if (blueval > 255)
                {
                    temp[i][j].rgbtBlue = 255;
                }
                else
                {
                    temp[i][j].rgbtBlue = blueval;
                }
                
                // calculating new green value
                int greenGx = (image[i - 1][j - 1].rgbtGreen * -1) + (image[i][j - 1].rgbtGreen * -2);
                int greenGy = (image[i - 1][j - 1].rgbtGreen * -1) + (image[i - 1][j].rgbtGreen * -2);
                int sumgreen = (greenGx * greenGx) + (greenGy * greenGy); 
                float sqrgreen = sqrt(sumgreen);
                int greenval = round(sqrgreen);
                if (greenval > 255)
                {
                    temp[i][j].rgbtGreen = 255;
                }
                else
                {
                    temp[i][j].rgbtGreen = greenval;
                }
            }
            
            // 1st column pixel's algorithm
            else if (j == 0 && (i != 0 || i != (height - 1)))
            {
                // calculating new red value
                int redGx = (image[i - 1][j + 1].rgbtRed * 1) + (image[i][j + 1].rgbtRed * 2) + (image[i + 1][j + 1].rgbtRed * 1);
                int redGy = (image[i - 1][j].rgbtRed * -2) + (image[i - 1][j + 1].rgbtRed * -1) + (image[i + 1][j].rgbtRed * 2) +
                            (image[i + 1][j + 1].rgbtRed * 1);
                int sumred = (redGx * redGx) + (redGy * redGy);
                float sqred = sqrt(sumred);
                int redval = round(sqred);
                if (redval > 255)
                {
                    temp[i][j].rgbtRed = 255;
                }
                else
                {
                    temp[i][j].rgbtRed = redval;
                }
                
                // calculating new blue value
                int blueGx = (image[i - 1][j + 1].rgbtBlue * 1) + (image[i][j + 1].rgbtBlue * 2) + (image[i + 1][j + 1].rgbtBlue * 1);
                int blueGy = (image[i - 1][j].rgbtBlue * -2) + (image[i - 1][j + 1].rgbtBlue * -1) + (image[i + 1][j].rgbtBlue * 2) +
                             (image[i + 1][j + 1].rgbtBlue * 1);
                int sumblue = (blueGx * blueGx) + (blueGy * blueGy);
                float sqrblue = sqrt(sumblue);
                int blueval = round(sqrblue);
                if (blueval > 255)
                {
                    temp[i][j].rgbtBlue = 255;
                }
                else
                {
                    temp[i][j].rgbtBlue = blueval;
                }
                
                // calculating new green value
                int greenGx = (image[i - 1][j + 1].rgbtGreen * 1) + (image[i][j + 1].rgbtGreen * 2) + (image[i + 1][j + 1].rgbtGreen * 1);
                int greenGy = (image[i - 1][j].rgbtGreen * -2) + (image[i - 1][j + 1].rgbtGreen * -1) + (image[i + 1][j].rgbtGreen * 2) +
                              (image[i + 1][j + 1].rgbtGreen * 1);
                int sumgreen = (greenGx * greenGx) + (greenGy * greenGy); 
                float sqrgreen = sqrt(sumgreen);
                int greenval = round(sqrgreen);
                if (greenval > 255)
                {
                    temp[i][j].rgbtGreen = 255;
                }
                else
                {
                    temp[i][j].rgbtGreen = greenval;
                }
            }
            
            // 1st row pixel's algorithm
            else if (i == 0 && (j != 0 || j != (width - 1)))
            {
                // calculating new red value
                int redGx = (image[i][j - 1].rgbtRed * -2) + (image[i][j + 1].rgbtRed * 2) + (image[i + 1][j - 1].rgbtRed * -1) +
                            (image[i + 1][j + 1].rgbtRed * 1);
                int redGy = (image[i + 1][j - 1].rgbtRed * 1) + (image[i + 1][j].rgbtRed * 2) + (image[i + 1][j + 1].rgbtRed * 1);
                int sumred = (redGx * redGx) + (redGy * redGy);
                float sqred = sqrt(sumred);
                int redval = round(sqred);
                if (redval > 255)
                {
                    temp[i][j].rgbtRed = 255;
                }
                else
                {
                    temp[i][j].rgbtRed = redval;
                }
                
                // calculating new blue value
                int blueGx = (image[i][j - 1].rgbtBlue * -2) + (image[i][j + 1].rgbtBlue * 2) + (image[i + 1][j - 1].rgbtBlue * -1) +
                             (image[i + 1][j + 1].rgbtBlue * 1);
                int blueGy = (image[i + 1][j - 1].rgbtBlue * 1) + (image[i + 1][j].rgbtBlue * 2) + (image[i + 1][j + 1].rgbtBlue * 1);
                int sumblue = (blueGx * blueGx) + (blueGy * blueGy);
                float sqrblue = sqrt(sumblue);
                int blueval = round(sqrblue);
                if (blueval > 255)
                {
                    temp[i][j].rgbtBlue = 255;
                }
                else
                {
                    temp[i][j].rgbtBlue = blueval;
                }

                // calculating new green value
                int greenGx = (image[i][j - 1].rgbtGreen * -2) + (image[i][j + 1].rgbtGreen * 2) + (image[i + 1][j - 1].rgbtGreen * -1) +
                              (image[i + 1][j + 1].rgbtGreen * 1);
                int greenGy = (image[i + 1][j - 1].rgbtGreen * 1) + (image[i + 1][j].rgbtGreen * 2) + (image[i + 1][j + 1].rgbtGreen * 1);
                int sumgreen = (greenGx * greenGx) + (greenGy * greenGy); 
                float sqrgreen = sqrt(sumgreen);
                int greenval = round(sqrgreen);
                if (greenval > 255)
                {
                    temp[i][j].rgbtGreen = 255;
                }
                else
                {
                    temp[i][j].rgbtGreen = greenval;
                }

            }
            
            // last column pixel's algorithm
            else if (j == (width - 1) && (i != 0 || i != (height - 1)))
            {
                // calculating new red value
                int redGx = (image[i - 1][j - 1].rgbtRed * -1) + (image[i][j - 1].rgbtRed * -2) + (image[i + 1][j - 1].rgbtRed * -1);
                int redGy = (image[i - 1][j - 1].rgbtRed * -1) + (image[i - 1][j].rgbtRed * -2) + (image[i + 1][j - 1].rgbtRed * 1) +
                            (image[i + 1][j].rgbtRed * 2);
                int sumred = (redGx * redGx) + (redGy * redGy);
                float sqred = sqrt(sumred);
                int redval = round(sqred);
                if (redval > 255)
                {
                    temp[i][j].rgbtRed = 255;
                }
                else
                {
                    temp[i][j].rgbtRed = redval;
                }
                
                // calculating new blue value
                int blueGx = (image[i - 1][j - 1].rgbtBlue * -1) + (image[i][j - 1].rgbtBlue * -2) + (image[i + 1][j - 1].rgbtBlue * -1);
                int blueGy = (image[i - 1][j - 1].rgbtBlue * -1) + (image[i - 1][j].rgbtBlue * -2) + (image[i + 1][j - 1].rgbtBlue * 1) +
                             (image[i + 1][j].rgbtBlue * 2);
                int sumblue = (blueGx * blueGx) + (blueGy * blueGy);
                float sqrblue = sqrt(sumblue);
                int blueval = round(sqrblue);
                if (blueval > 255)
                {
                    temp[i][j].rgbtBlue = 255;
                }
                else
                {
                    temp[i][j].rgbtBlue = blueval;
                }

                // calculating new green value
                int greenGx = (image[i - 1][j - 1].rgbtGreen * -1) + (image[i][j - 1].rgbtGreen * -2) + (image[i + 1][j - 1].rgbtGreen * -1);
                int greenGy = (image[i - 1][j - 1].rgbtGreen * -1) + (image[i - 1][j].rgbtGreen * -2) + (image[i + 1][j - 1].rgbtGreen * 1) +
                              (image[i + 1][j].rgbtGreen * 2);
                int sumgreen = (greenGx * greenGx) + (greenGy * greenGy); 
                float sqrgreen = sqrt(sumgreen);
                int greenval = round(sqrgreen);
                if (greenval > 255)
                {
                    temp[i][j].rgbtGreen = 255;
                }
                else
                {
                    temp[i][j].rgbtGreen = greenval;
                }

            }
            
            // last row pixel's algorithm
            else if (i == (height - 1) && (j != 0 || j != (width - 1)))
            {
                // calculating new red value
                int redGx = (image[i - 1][j - 1].rgbtRed * -1) + (image[i - 1][j + 1].rgbtRed * 1) + (image[i][j - 1].rgbtRed * -2) +
                            (image[i][j + 1].rgbtRed * 2);
                int redGy = (image[i - 1][j - 1].rgbtRed * -1) + (image[i - 1][j].rgbtRed * -2) + (image[i - 1][j + 1].rgbtRed * -1);
                int sumred = (redGx * redGx) + (redGy * redGy);
                float sqred = sqrt(sumred);
                int redval = round(sqred);
                if (redval > 255)
                {
                    temp[i][j].rgbtRed = 255;
                }
                else
                {
                    temp[i][j].rgbtRed = redval;
                }
                
                // calculating new blue value
                int blueGx = (image[i - 1][j - 1].rgbtBlue * -1) + (image[i - 1][j + 1].rgbtBlue * 1) + (image[i][j - 1].rgbtBlue * -2) +
                             (image[i][j + 1].rgbtBlue * 2);
                int blueGy = (image[i - 1][j - 1].rgbtBlue * -1) + (image[i - 1][j].rgbtBlue * -2) + (image[i - 1][j + 1].rgbtBlue * -1);
                int sumblue = (blueGx * blueGx) + (blueGy * blueGy);
                float sqrblue = sqrt(sumblue);
                int blueval = round(sqrblue);
                if (blueval > 255)
                {
                    temp[i][j].rgbtBlue = 255;
                }
                else
                {
                    temp[i][j].rgbtBlue = blueval;
                }
                
                // calculating new green value
                int greenGx = (image[i - 1][j - 1].rgbtGreen * -1) + (image[i - 1][j + 1].rgbtGreen * 1) + (image[i][j - 1].rgbtGreen * -2) +
                              (image[i][j + 1].rgbtGreen * 2);
                int greenGy = (image[i - 1][j - 1].rgbtGreen * -1) + (image[i - 1][j].rgbtGreen * -2) + (image[i - 1][j + 1].rgbtGreen * -1);
                int sumgreen = (greenGx * greenGx) + (greenGy * greenGy); 
                float sqrgreen = sqrt(sumgreen);
                int greenval = round(sqrgreen);
                if (greenval > 255)
                {
                    temp[i][j].rgbtGreen = 255;
                }
                else
                {
                    temp[i][j].rgbtGreen = greenval;
                }
            }
            
            // middle pixel's algorithm
            else
            {
                int Gx[3][3] = 
                {
                    {-1, 0, 1},
                    {-2, 0, 2},
                    {-1, 0, 1}
                };
                
                int Gy[3][3] = 
                {
                    {-1, -2, -1},
                    {0, 0, 0},
                    {1, 2, 1}
                };
                
                
                // calculating new red value
                int redGx = (image[i - 1][j - 1].rgbtRed * Gx[0][0]) + (image[i - 1][j].rgbtRed * Gx[0][1]) +
                
                            (image[i - 1][j + 1].rgbtRed * Gx[0][2]) +
                
                            (image[i][j - 1].rgbtRed * Gx[1][0]) + (image[i][j].rgbtRed * Gx[1][1]) + (image[i][j + 1].rgbtRed * Gx[1][2]) +
                
                            (image[i + 1][j - 1].rgbtRed * Gx[2][0]) + (image[i + 1][j].rgbtRed * Gx[2][1]) + (image[i + 1][j + 1].rgbtRed * Gx[2][2]);
                
                int redGy = (image[i - 1][j - 1].rgbtRed * Gy[0][0]) + (image[i - 1][j].rgbtRed * Gy[0][1]) +
                
                            (image[i - 1][j + 1].rgbtRed * Gy[0][2]) +
                
                            (image[i][j - 1].rgbtRed * Gy[1][0]) + (image[i][j].rgbtRed * Gy[1][1]) + (image[i][j + 1].rgbtRed * Gy[1][2]) +
                
                            (image[i + 1][j - 1].rgbtRed * Gy[2][0]) + (image[i + 1][j].rgbtRed * Gy[2][1]) + (image[i + 1][j + 1].rgbtRed * Gy[2][2]);
                
                int sumred = (redGx * redGx) + (redGy * redGy);
                float sqred = sqrt(sumred);
                int redval = round(sqred);
                if (redval > 255)
                {
                    temp[i][j].rgbtRed = 255;
                }
                
                else
                {
                    temp[i][j].rgbtRed = redval;
                }
                
                // calculating new blue value
                int blueGx = (image[i - 1][j - 1].rgbtBlue * Gx[0][0]) + (image[i - 1][j].rgbtBlue * Gx[0][1]) +
                
                             (image[i - 1][j + 1].rgbtBlue * Gx[0][2]) +
                
                             (image[i][j - 1].rgbtBlue * Gx[1][0]) + (image[i][j].rgbtBlue * Gx[1][1]) + (image[i][j + 1].rgbtBlue * Gx[1][2]) +
                
                             (image[i + 1][j - 1].rgbtBlue * Gx[2][0]) + (image[i + 1][j].rgbtBlue * Gx[2][1]) + (image[i + 1][j + 1].rgbtBlue * Gx[2][2]);
                
                int blueGy = (image[i - 1][j - 1].rgbtBlue * Gy[0][0]) + (image[i - 1][j].rgbtBlue * Gy[0][1]) +
                
                             (image[i - 1][j + 1].rgbtBlue * Gy[0][2]) +
                
                             (image[i][j - 1].rgbtBlue * Gy[1][0]) + (image[i][j].rgbtBlue * Gy[1][1]) + (image[i][j + 1].rgbtBlue * Gy[1][2]) +
                
                             (image[i + 1][j - 1].rgbtBlue * Gy[2][0]) + (image[i + 1][j].rgbtBlue * Gy[2][1]) + (image[i + 1][j + 1].rgbtBlue * Gy[2][2]);
                
                int sumblue = (blueGx * blueGx) + (blueGy * blueGy);
                float sqrblue = sqrt(sumblue);
                int blueval = round(sqrblue);
                if (blueval > 255)
                {
                    temp[i][j].rgbtBlue = 255;
                }
                else
                {
                    temp[i][j].rgbtBlue = blueval;
                }
                
                // calculating new green value
                int greenGx = (image[i - 1][j - 1].rgbtGreen * Gx[0][0]) + (image[i - 1][j].rgbtGreen * Gx[0][1]) +
                
                              (image[i - 1][j + 1].rgbtGreen * Gx[0][2]) +
                
                              (image[i][j - 1].rgbtGreen * Gx[1][0]) + (image[i][j].rgbtGreen * Gx[1][1]) + (image[i][j + 1].rgbtGreen * Gx[1][2]) +
                
                              (image[i + 1][j - 1].rgbtGreen * Gx[2][0]) + (image[i + 1][j].rgbtGreen * Gx[2][1]) + (image[i + 1][j + 1].rgbtGreen * Gx[2][2]);
                
                int greenGy = (image[i - 1][j - 1].rgbtGreen * Gy[0][0]) + (image[i - 1][j].rgbtGreen * Gy[0][1]) +
                
                              (image[i - 1][j + 1].rgbtGreen * Gy[0][2]) +
                
                              (image[i][j - 1].rgbtGreen * Gy[1][0]) + (image[i][j].rgbtGreen * Gy[1][1]) + (image[i][j + 1].rgbtGreen * Gy[1][2]) +
                
                              (image[i + 1][j - 1].rgbtGreen * Gy[2][0]) + (image[i + 1][j].rgbtGreen * Gy[2][1]) + (image[i + 1][j + 1].rgbtGreen * Gy[2][2]);
                
                int sumgreen = (greenGx * greenGx) + (greenGy * greenGy); 
                float sqrgreen = sqrt(sumgreen);
                int greenval = round(sqrgreen);
                if (greenval > 255)
                {
                    temp[i][j].rgbtGreen = 255;
                }
                else
                {
                    temp[i][j].rgbtGreen = greenval;
                }
            }
        }
    }
    
    for (int k = 0; k < height; k++)
    {
        for (int r = 0; r < width; r++)
        {
            image[k][r].rgbtRed = temp[k][r].rgbtRed;
            image[k][r].rgbtBlue = temp[k][r].rgbtBlue;
            image[k][r].rgbtGreen = temp[k][r].rgbtGreen;
        }
    }
    return;
}
