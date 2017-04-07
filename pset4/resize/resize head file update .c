/**
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>

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
    
    // check factor
    if (factor < 0 || factor > 100)
    {
        fprintf(stderr, "the factor must be for 0 up to and including 100. your factor is: %i.\n", factor);
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

    // read infile's BITMAP FILE HEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAP INFO HEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    // determining inptr parameters 
    int old_biWidth = bi.biWidth;
    int old_biHeight = abs(bi.biHeight);   
    

    // new file dimensions
    bi.biWidth = bi.biWidth * factor;
    bi.biHeight = bi.biHeight * factor;
    
    // padding
    int old_padding = (4 - (old_biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int new_padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // new file header
    bi.biSizeImage = ((sizeof(RGBTRIPLE) * bi.biWidth) + new_padding) * abs(bi.biHeight);
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAP INFO HEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    // old_biHeight = abs(old_biHeight)
    for (int i = 0; i < abs(old_biHeight); i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < old_biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            
            // printing pixel factor times
            for (int k = 0; k < factor; k++)
            {
                // write RGB triple to outfile
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            }
        }
        
        // skip infiles padding 
        fseek(inptr, old_padding, SEEK_CUR);
        
        // add the new padding
        for (int k = 0; k < new_padding; k++)
        {
            fputc(0x00, outptr);
        }
    }
    
    
    printf("Factor: %i\noldwith: %i oldheight: %i \n",factor, old_biWidth, old_biHeight);
    printf("NEWdwith: %i NEWheight: %i \n", bi.biWidth, bi.biHeight);
    printf("oldpadding: %i NEWpadding: %i\n",old_padding, new_padding);
    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);
    
    // success
    return 0;
}