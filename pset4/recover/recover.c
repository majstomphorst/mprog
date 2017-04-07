/****************************************************************************
 * recover.c 
 * Programmeren 01 - pset 04 - exercise 03
 * By Maxim Stomphorst
 * 
 * Recovers deleted .jpg files from a .raw file. 
***************************************************************************/
       
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// for reading 512 bytes 
#define BLOCK 512
#define NAME_SIZE 8


int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./path/card.raw \n");
        return 1;
    }

    // deffing in and outfile
    char *infile = argv[1];
    FILE *outfile;
    // making temporarily storage container 
    uint8_t buffer[BLOCK];
    // jpg's found counter
    int count = 0;
    // temporarly store filename
    char filename[NAME_SIZE];
    
    // opening file in read mode and checking for NULL
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }
    
    // reading file until fread retuns fail 
    while (fread(buffer, BLOCK, 1, inptr))
    {
        // checking for start jpg file 
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && 
        buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // if (new) .jpg found close file current file
            if (count > 0)
            {
                fclose(outfile);
            }
                
            // creating filename 
            sprintf(filename,"%03i.jpg",count);
            
            // open input file and checking for NULL
            outfile = fopen(filename, "w");
            if (inptr == NULL)
            {
                fprintf(stderr, "Could not open %s.\n", infile);
                return 2;
            }
                
            // counting .jpg found for naming scream
            count++; 
            }
            
            // if not .jpg found downt write.
        if (count > 0)
        {
            // writing file. 
            fwrite(buffer,BLOCK, 1, outfile);
        }
    }
    
    // closing files return 0 for succes
    fclose(inptr);
    fclose(outfile);
    return 0;
}
   