/****************************************************************************
 * resize.c More confotable
 * Programmeren 01 - pset 04 - exercise 02
 * By Maxim Stomphorst
 * 
 * enlarges a .bmp file factor times. 
***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>

// including .bmp file struct 
#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: factor ./copy infile outfile\n");
        return 1;
    }

    // remember filenames
    int factor = atoi(argv[1]);
    char *infile = argv[2];
    char *outfile = argv[3];
    
    // check user input
    if (factor < 0 || factor > 100)
    {
        fprintf(stderr, "Usage: factor between 0 & 100 input: %i.\n", factor);
        return 1;
    }

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    // creating old(original file's bf) and new file's bf
    // keeping track of old en new dimensions 
    BITMAPFILEHEADER old_bf, new_bf;
    fread(&old_bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    new_bf = old_bf;
    
    // read infile's BITMAPINFOHEADER (see note above)
    BITMAPINFOHEADER old_bi, new_bi;
    fread(&old_bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    new_bi = old_bi;

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (old_bf.bfType != 0x4d42 || old_bf.bfOffBits != 54 || 
        old_bi.biSize != 40 || old_bi.biBitCount != 24 || 
        old_bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    // getting size for repeated use
    int size_RGBTRIPLE = sizeof(RGBTRIPLE);
    
    // getting new width and height dimensions
    new_bi.biWidth = new_bi.biWidth * factor;
    new_bi.biHeight = new_bi.biHeight * factor;
    
    // creating padding for scanlines (old and new)
    int old_padding = (4 - (old_bi.biWidth * size_RGBTRIPLE) % 4) % 4;
    int new_padding = (4 - (new_bi.biWidth * size_RGBTRIPLE) % 4) % 4;
    
    // creating new file dimensions
    new_bi.biSizeImage = ((size_RGBTRIPLE * new_bi.biWidth) + 
                         new_padding) * abs(new_bi.biHeight);
    new_bf.bfSize = new_bi.biSizeImage + sizeof(BITMAPFILEHEADER) + 
                    sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&new_bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&new_bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, old_biHeight = abs(old_bi.biHeight); i < old_biHeight; i++)
    {
        // printing line factor times
        for (int j = 0; j < factor; j++)
        {
            // iterate over pixels in scanline
            for (int k = 0; k < old_bi.biWidth; k++)
            {
                // temporary storage
                RGBTRIPLE triple;
    
                // read RGB triple from infile
                fread(&triple, size_RGBTRIPLE, 1, inptr);
                
                // writing rgbtriple factor times andwrite outfile
                for (int l = 0; l < factor; l++)
                {
                    fwrite(&triple, size_RGBTRIPLE, 1, outptr);
                }
            }
            
            // after pixels write new padding if needed
            for (int m = 0; m < new_padding; m++)
            {
                fputc(0x00, outptr);
            }
            
            // moving file cursor back to the start of the line
            if (j < factor - 1)
            {
                fseek(inptr, -(old_bi.biWidth * size_RGBTRIPLE), SEEK_CUR);
            }
        } 
        // skip over padding, if any to start reading next line
        fseek(inptr, old_padding, SEEK_CUR);
    }
    
    // close opend file's return 0 for succes
    fclose(inptr);
    fclose(outptr);
    return 0;
}
