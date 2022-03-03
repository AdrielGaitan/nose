// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("./Usage: copy infile outfile\n");
        return 1;
    }

    // remember filenames
    int factor = atoi(argv[1]);
    char *infile = argv[2];
    char *outfile = argv[3];

    if (factor < 1 || factor > 100)
    {
        printf("Factor must be in the range 1-100\n");
        return 1;
    }

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
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
    BITMAPFILEHEADER bf;
    BITMAPFILEHEADER bf_nuev;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    bf_nuev = bf;

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    BITMAPINFOHEADER bi_nuev;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    bi_nuev = bi;

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    bi_nuev.biWidth = bi.biWidth * factor;
    bi_nuev.biHeight = bi.biHeight * factor;

    //determinar los padding por lineas
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int nuev_padding = (4 - (bi_nuev.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;


    bi_nuev.biSizeImage = ((sizeof(RGBTRIPLE) * bi_nuev.biWidth) + nuev_padding) * abs(bi_nuev.biHeight);
    bf_nuev.bfSize = bi_nuev.biSizeImage + 54;


    // write outfile's BITMAPFILEHEADER
    fwrite(&bf_nuev, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi_nuev, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {

        int rowcounter = 0;

        while (rowcounter < factor)
        {

            // iterate over pixels in scanline
            for (int j = 0; j < bi.biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                int pixelcounter = 0;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                while (pixelcounter < factor)
                {
                    // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                    pixelcounter++;
                }
            }
            // then add it back (to demonstrate how)
            for (int k = 0; k < nuev_padding; k++)
            {
                fputc(0x00, outptr);
            }

            if (rowcounter < (factor - 1))
            {
                fseek(inptr, - (bi.biWidth * sizeof(RGBTRIPLE)), SEEK_CUR);
            }
            rowcounter++;
        }

        fseek(inptr, padding, SEEK_CUR);



    }



    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
