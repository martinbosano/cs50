#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <stdint.h>

typedef uint8_t BYTE;
/// defining memory card block
#define BLOCK_SIZE 512

///secondary functions
bool is_new_jpeg(BYTE buffer[]);

//main function
int main(int argc, char *argv[])
{
    ///check if user uses function properly
    if (argc != 2)
    {
        printf("usage: ./recover image\n");
        return 1;
    }
    ///open file 
    FILE *infile = fopen(argv[1], "r");
    if (infile == NULL)
    {
        printf("File not found\n");
        return 2;
    }
    /// global variables
    BYTE buffer[BLOCK_SIZE];
    int image_index = 0;
    bool is_first_jpeg = false;
    FILE *outfile;
    char filename[8];
  
///repeat until end
    while (fread(buffer, BLOCK_SIZE, 1, infile))
    {
        ///checks if is a new jpeg
        if (is_new_jpeg(buffer))
        {
            ///checks if is the first jpeg
            if (!is_first_jpeg)
            {
                is_first_jpeg = true;
            }
            else 
            {
                fclose(outfile);
                image_index++;
            }
            /// writing the new jpegs
            sprintf(filename, "%03i.jpg", image_index);
            outfile = fopen(filename, "w");
            if (outfile == NULL)
            {
                return 2;
            }
            fwrite(buffer, BLOCK_SIZE, 1, outfile);
        }
        else if (is_first_jpeg)
        {
            fwrite(buffer, BLOCK_SIZE, 1, outfile);
        }
    }
    fclose(outfile);
    fclose(infile);
    return 0;
}

///secondary function, is a new jpeg boolean
bool is_new_jpeg(BYTE buffer[])
{
    return buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0;
}