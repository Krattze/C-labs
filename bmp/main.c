#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "bmp.h"

unsigned char *LoadBitmapFile(char* filename, BITMAPFILEHEADER* bitmapFileHeader, BITMAPINFOHEADER* bitmapInfoHeader) {
    FILE* filePtr;  //our file pointer
    unsigned char* bitmapImage;  //store image data

    //open file in read binary mode
    filePtr = fopen(filename, "rb");
    if (filePtr == NULL)
        return NULL;

    //read the bitmap file header
    fread(bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);

    //verify that this is a .BMP file by checking bitmap id
    if (bitmapFileHeader->bfType != 0x4D42)
    {
        fclose(filePtr);
        return NULL;
    }

    //read the bitmap info header
    fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr);

    //move file pointer to the beginning of bitmap data
    //fseek(filePtr, bitmapFileHeader->bfOffBits, SEEK_SET);

    //allocate enough memory for the bitmap image data
    bitmapImage = (unsigned char*)malloc(bitmapInfoHeader->biSizeImage);

    //verify memory allocation
    if (!bitmapImage)
    {
        free(bitmapImage);
        fclose(filePtr);
        return NULL;
    }

    //read in the bitmap image data
    fread(bitmapImage, bitmapInfoHeader->biSizeImage, 1, filePtr);

    //make sure bitmap image data was read
    if (bitmapImage == NULL)
    {
        fclose(filePtr);
        return NULL;
    }

    
    fclose(filePtr);
    return bitmapImage;
}


unsigned char* DecreaseBrightness(unsigned char* bitmapImg, BITMAPINFOHEADER bitmapInfoHeader) {
    unsigned int imageIdx = 0;
    double Y, Cb, Cr, R, G, B;



    for (imageIdx = 0; imageIdx < bitmapInfoHeader.biSizeImage; imageIdx += 3)
    {
        R = bitmapImg[imageIdx];
        G = bitmapImg[imageIdx + 1];
        B = bitmapImg[imageIdx + 2];


        Y = 0.257 * R + 0.504 * G + 0.098 * B + 16 - 100; //decrease Y
        Cb = 0.148 * R - 0.291 * G+ 0.439 * B + 128;
        Cr = 0.439 * R - 0.368 * G - 0.071 * B + 128;

        if (Y > 255) Y = 255;
        else if (Y < 0) Y = 0;
        if (Cb > 255) Cb = 255;
        else if (Cb < 0) Cb = 0;
        if (Cr > 255) Cr = 255;
        else if (Cr < 0) Cr = 0;

        R = (1.164*(Y - 16) + 1.596*(Cr - 128));

        G = 1.164*(Y - 16) - 0.813*(Cr - 128) - 0.392*(Cb - 128);

        B = 1.164*(Y - 16) + 2.017*(Cb - 128);

        if (R > 255) R = 255;
        else if (R < 0) R = 0;
        if (G > 255) G = 255;
        else if (G < 0) G= 0;
        if (B > 255) B = 255;
        else if (B < 0) B = 0;

        bitmapImg[imageIdx] = (unsigned char)round(R);
        bitmapImg[imageIdx + 1] = (unsigned char)round(G);
        bitmapImg[imageIdx + 2] = (unsigned char)round(B);
    }

    return bitmapImg;
}

void SaveBitmapFile(char* filename, BITMAPFILEHEADER* bitmapFileHeader, BITMAPINFOHEADER* bitmapInfoHeader, unsigned char* bitmapIm) {
    FILE* file;
    file = fopen(filename, "wb");
    fwrite(bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, file);
    fwrite(bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, file);
    fwrite(bitmapIm, bitmapInfoHeader->biSizeImage, 1, file);
    fclose(file);
}

int main(int argc, char** argv){

    BITMAPINFOHEADER InfoHeader;
    BITMAPFILEHEADER FileHeader;
    unsigned char* bitmapData;


    if (argc != 3) {
        printf("Usage: .exe <input.bmp> <output.bmp>\n");
        return -1;
    }

    if (!(bitmapData = (unsigned char*) LoadBitmapFile(argv[1], &FileHeader, &InfoHeader))) {
        printf("Cannot read file %s\n", argv[1]);
        return -1;
    }

    bitmapData = DecreaseBrightness(bitmapData, InfoHeader);
    SaveBitmapFile(argv[2], &FileHeader, &InfoHeader, bitmapData);
    free(bitmapData);
    return 0;
}