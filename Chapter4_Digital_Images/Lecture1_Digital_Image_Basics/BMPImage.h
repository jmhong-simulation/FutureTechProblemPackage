#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

struct BMPHeader
{
	// http://en.wikipedia.org/wiki/BMP_file_format

	char file_type[2];        // "BM"
	int file_size;            // Size of file in bytes
	int reserved;             // set to 0
	int offBits;              // Byte offset to actual bitmap data (= 54)
	int header_size;          // Size of BITMAPINFOHEADER, in bytes (= 40)
	int width;                // Width of image, in pixels
	int height;               // Height of images, in pixels
	short planes;             // Number of planes in target device (set to 1)
	short bit_count;          // Bits per pixel (24 in this case)
	int compression;          // Type of compression (0 if no compression)
	int size_image;           // Image size, in bytes (0 if no compression)
	int pixel_per_meter_x;    // Horizontal resolution of the image (pixel per meter)
	int pixel_per_meter_y;    // Vertical resolution of the image (pixel per meter)
	int num_color_palette;    // Number of colors in the color table (if 0, use maximum allowed by biBitCount)
	int num_color_important;  // Number of important colors.  If 0, all colors are important
};

const bool writeBMP24(const char *filename, const int x_res, const int y_res, const unsigned char* rgb_array)
{
	int i, j, ipos;
	int bytesPerLine;
	unsigned char *buffer;

	FILE *file;
	struct BMPHeader header;

	int width = x_res;
	int height = y_res;

	// The length of each line must be a multiple of 4 bytes
	bytesPerLine = (3 * (width + 1) / 4) * 4;

	header.file_type[0] = 'B';
	header.file_type[1] = 'M';

	header.offBits = 54;
	header.file_size = header.offBits + bytesPerLine * height;
	header.reserved = 0;
	header.header_size = 40;
	header.width = width;
	header.height = height;
	header.planes = 1;
	header.bit_count = 24;
	header.compression = 0;
	header.size_image = bytesPerLine * height;
	header.pixel_per_meter_x = 0;
	header.pixel_per_meter_y = 0;
	header.num_color_palette = 0;
	header.num_color_important = 0;

	//file = fopen(filename, "wb");
	if (fopen_s(&file, filename, "wb")) {
		printf("File open failed. Terminating.\n");
		return(0);
	}

	fwrite(&header.file_type, 2, 1, file);
	fwrite(&header.file_size, 4, 1, file);
	fwrite(&header.reserved, 4, 1, file);
	fwrite(&header.offBits, 4, 1, file);
	fwrite(&header.header_size, 4, 1, file);
	fwrite(&header.width, 4, 1, file);
	fwrite(&header.height, 4, 1, file);
	fwrite(&header.planes, 2, 1, file);
	fwrite(&header.bit_count, 2, 1, file);
	fwrite(&header.compression, 4, 1, file);
	fwrite(&header.size_image, 4, 1, file);
	fwrite(&header.pixel_per_meter_x, 4, 1, file);
	fwrite(&header.pixel_per_meter_y, 4, 1, file);
	fwrite(&header.num_color_palette, 4, 1, file);
	fwrite(&header.num_color_important, 4, 1, file);

	buffer = (unsigned char*)malloc(bytesPerLine);
	if (buffer == NULL)
	{
		fprintf(stderr, "Can't allocate memory for BMP file.\n");
		return false;
	}

	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			ipos = 3 * (width * i + j);
			buffer[3 * j]	  = rgb_array[(j + i * x_res) * 3 + 2]; // blue
			buffer[3 * j + 1] = rgb_array[(j + i * x_res) * 3 + 1]; // green
			buffer[3 * j + 2] = rgb_array[(j + i * x_res) * 3 + 0];	// red
		}

		fwrite(buffer, bytesPerLine, 1, file);
	}

	free(buffer);
	fclose(file);

	return true;
}

const bool readBMP24(const char* imagepath, int* res_x_, int* res_y_, unsigned char** rgb_array)
{
    printf("Reading image %s\n", imagepath);

    // Data read from the header of the BMP file
    unsigned char header[54];
    unsigned int dataPos;
    unsigned int imageSize;
    unsigned int width, height;

    // Open the file
    FILE * file = NULL;
    if (fopen_s(&file, imagepath, "rb")) {
		printf("File open failed. Terminating."); 
		return 0;
	}

    // Read the header, i.e. the 54 first bytes

    // If less than 54 bytes are read, problem
    if (fread(header, 1, 54, file) != 54) {
        printf("Not a correct BMP file\n");
        return false;
    }
    // A BMP files always begins with "BM"
    if (header[0] != 'B' || header[1] != 'M') {
        printf("Not a correct BMP file\n");
        return false;
    }

    // Make sure this is a 24bpp file
    if (*(int*)&(header[0x1E]) != 0) { printf("Not a correct BMP file\n");    return false; }
    if (*(int*)&(header[0x1C]) != 24) { printf("Not a correct BMP file\n");    return false; }

    // Read the information about the image
    dataPos = *(int*)&(header[0x0A]);
    imageSize = *(int*)&(header[0x22]);
    width = *(int*)&(header[0x12]);
    height = *(int*)&(header[0x16]);

    // Some BMP files are mis-formatted, guess missing information
    //	if (imageSize == 0)    imageSize = width*height*3; // 3 : one byte for each Red, Green and Blue component
    if (dataPos == 0)      dataPos = 54; // The BMP header is done that way

    *res_x_ = width;
    *res_y_ = height;

    int scanline_byte = *res_x_ * 3;
    int padding = 0;

    while ((scanline_byte + padding) % 4 != 0) padding++;

    int psb = scanline_byte + padding; // padded scanline byte
    imageSize = psb*height;

    // Read the actual data from the file into the buffer
    unsigned char* image_buf = (unsigned char*)malloc(sizeof(unsigned char)*imageSize);
    fread(image_buf, 1, imageSize, file);

    // Create a buffer
    *rgb_array = (unsigned char*)malloc(sizeof(unsigned char)*(width * height * 3));

    long buf_pos = 0;
    long new_pos = 0;

    for (unsigned int y = 0; y < height; y++)
        for (unsigned int x = 0; x < 3 * width; x += 3)
        {
            new_pos = y*width + x / 3;
            buf_pos = y*psb + x;

            (*rgb_array)[new_pos * 3 + 0] = image_buf[buf_pos + 2];
            (*rgb_array)[new_pos * 3 + 1] = image_buf[buf_pos + 1];
            (*rgb_array)[new_pos * 3 + 2] = image_buf[buf_pos + 0];
        }

    // Everything is in memory now, the file wan be closed
    fclose(file);

    free(image_buf);

    return true;
}
