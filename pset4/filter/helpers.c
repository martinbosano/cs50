#include "helpers.h"
#include <math.h>
#include <cs50.h>

///functions declaration
bool isValid(int x, int y, int height, int width);
void blurPixel(int x, int y, int height, int width, RGBTRIPLE image[height][width], RGBTRIPLE bluredImage[height][width]);


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int average = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            /// sepia formula for each colour
            int sepiaRed = round(0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue);
            int sepiaBlue = round(0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue);
            int sepiaGreen = round(0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue);
            
            ///setting the maximun value for each color
            if (sepiaRed > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else 
            {
                image[i][j].rgbtRed = sepiaRed;
            }
            if (sepiaBlue > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else 
            {
                image[i][j].rgbtBlue = sepiaBlue;
            }
            if (sepiaGreen > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else 
            {
                image[i][j].rgbtGreen = sepiaGreen;
            }
            
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    /// swap depositary
    RGBTRIPLE swap;
    int y = width - 1;
    for (int i = 0; i < height; i++)
    {
        swap = image[i][0];
        image[i][0] = image[i][y];
        image[i][y] = swap;
        ///copy
        for (int j = 0; j < ((width - 1) / 2); j++)
        {
            swap = image[i][j + 1];
            image[i][j + 1] = image[i][y - 1];
            image[i][y - 1] = swap;
        }
    }
    
    return;
}




// Blur image function
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    ///array to allocate the new 
    RGBTRIPLE bluredImage[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            blurPixel(j, i, height, width, image, bluredImage);
        }
    }
    ///copy the alternative array to the image array
    for (int k = 0; k < height; k++)
    {
        for (int l = 0; l < width; l++)
        {
            image[k][l].rgbtRed = bluredImage[k][l].rgbtRed;
            image[k][l].rgbtGreen = bluredImage[k][l].rgbtGreen;
            image[k][l].rgbtBlue = bluredImage[k][l].rgbtBlue;
        }
    }
    return;
}


/// bool for checking if you are on a existing spot
bool isValid(int x, int y, int height, int width)
{
    /// if you are in a spot outside of the array, it would return false
    if (y < 0 || y > height - 1 || x < 0 || x > width - 1)
    {
        return false;
    }
    else
    {
        return true;
    }
}


/// blurring each pixel function
void blurPixel(int x, int y, int height, int width, RGBTRIPLE image[height][width], RGBTRIPLE bluredImage[height][width])
{
    /// variables for the new parametres
    float red = 0.0;
    float green = 0.0;
    float blue = 0.0;
    int counter = 0;
    for (int k = y - 1; k < y + 2; k++)
    {
        for (int l = x - 1; l < x + 2; l++)
        {
            if (isValid(l, k, height, width))
            {
                red += image[k][l].rgbtRed;
                green += image[k][l].rgbtGreen;
                blue += image[k][l].rgbtBlue;
                counter ++;
            }
        }
    }
    ////copying everything to the alternative array
    bluredImage[y][x].rgbtRed = round(red / counter);
    bluredImage[y][x].rgbtGreen = round(green / counter);
    bluredImage[y][x].rgbtBlue = round(blue / counter);
}
