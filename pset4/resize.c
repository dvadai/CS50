/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Resizes a BMP by n, taking that as a comman line argument. 
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

#define HEADER 54


int main(int argc, char* argv[])
{
    // ensure proper usage plus getpositive int
    if (argc != 4)
    {
        printf("Usage: ./resize n infile outfile\n");
        return 1;
    }

    int n = atoi(argv[1]);
    
    if(n <= 0 || n > 100)
    {
        printf("%i n must be less than or equal to a 100\n", n);
        return 1;
        //note to myself: this return1 might not be the best. need to come back to this. 
    }
    
    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    

    // read infile's BITMAPINFOHEADER
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
    
    //change the header information for the output file
    BITMAPFILEHEADER bf_resize;
    BITMAPINFOHEADER bi_resize;
    bi_resize = bi;
    bf_resize = bf;
    bi_resize.biWidth = bi.biWidth * n;
    bi_resize.biHeight = bi.biHeight * n;
    
    
    
    // determine padding for scanlines
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int padding_outputFile = (4 - (bi_resize.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    bi.biSizeImage = (abs(bi_resize.biWidth) * 3 + padding_outputFile) * abs(bi_resize.biHeight);
    bf.bfSize = (bi.biSizeImage + HEADER);
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf_resize, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi_resize, sizeof(BITMAPINFOHEADER), 1, outptr);
    
    
            
    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        
        for(int l = 0; l < n; l++)
        {
            
            for (int j = 0; j < bi.biWidth; j++)
            {
                        // temporary storage
                         RGBTRIPLE triple;
                
                        // read RGB triple from infile
                        fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            
                        // write RGB triple to outfile
                        for (int p = 0; p < n; p++)
                        {
                         fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                        }        
              
            }
            
            fseek(inptr, padding, SEEK_CUR);
            
            
            for (int k = 0; k < padding_outputFile; k++)
            {
                    fputc(0x00, outptr);
                    
            }
            fseek(inptr, (HEADER + ((bi.biWidth * 3 + padding) * i)), SEEK_SET);
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
