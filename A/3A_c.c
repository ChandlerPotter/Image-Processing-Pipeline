//Chandler Potter CIS 330 Spring 2018
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
	unsigned char red;
	unsigned char green;
	unsigned char blue;
} Pixel;

typedef struct
{
	int width;
	int height; 
	int maxval;
	Pixel *p;
} Image;

Image * ReadImage(char *filename)
{
 FILE *f_in;
 f_in = fopen(filename, "r");

 Image *image;
 image = malloc(sizeof(Image)); //initialize Image struct and malloc size of the Image struct

 char magicNum[128];
 int width, height, maxval;
 fscanf(f_in, "%s\n%d %d\n%d\n", magicNum, &width, &height, &maxval);  


 image->height = height;        //assign the scanned height, width, and maxvals to the corresponding image attributes
 image->width = width;
 image->maxval = maxval;
 image->p = malloc(image->width * image->height * sizeof(Pixel)); //malloc the size of a pixel(3 unsigned chars)

 fread(image->p, sizeof(Pixel), image->width * image->height, f_in);
 fclose(f_in);

 return image; 
}


void WriteImage(Image *image, char *filename)
{
	FILE *f_out;
	f_out = fopen(filename, "w");

	fprintf(f_out, "%s\n%d %d\n%d\n","P6", image->width, image->height, image->maxval); 
	fwrite(image->p, sizeof(Pixel), image->width * image->height, f_out); //write all the bytes to the output file (the pixels to the output image)
	fclose(f_out);

}

Image * YellowDiagonal(Image *input)
{
	Image *output;
	output = malloc(sizeof(Image));

	output->width = input->width;
	output->height = input->height;
	output->maxval = input->maxval;
	output->p = malloc(output->width*output->height*sizeof(Pixel));

	memcpy(output->p, input->p, sizeof(Pixel)*input->width*input->height);
	int i;

	for(i = 0; i<output->width * output->height;) { 
		output->p[i].red = 255; 							
		output->p[i].green = 255;
		output->p[i].blue = 0;
		i += output->width + 1;							
	}

	return output;
}

int main(int argc, char *argv[])
{

	if (argc !=3)
    {
      printf("Usage: %s <file1> <file2>\n", argv[0]);
      exit(EXIT_FAILURE);
    }

    Image *image;
	image = ReadImage(argv[1]);
	image = YellowDiagonal(image);
	WriteImage(image, argv[2]);
	free(image);	
}
