#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <functions.h>

void ReadImage(char *filename, Image &output){
 FILE *f_in;
 f_in = fopen(filename, "r");

 char magicNum[128];
 int width, height, maxval;
 fscanf(f_in, "%s\n%d %d\n%d\n", magicNum, &width, &height, &maxval);  


 output.height = height;        
 output.width = width;
 output.p = (Pixel *) malloc(output.width * output.height * sizeof(Pixel)); 

 fread(output.p, sizeof(Pixel), output.width * output.height, f_in);
 fclose(f_in);
 

}
void WriteImage(char *filename, Image &img){
	FILE *f_out;
	f_out = fopen(filename, "w");

	fprintf(f_out, "%s\n%d %d\n%d\n","P6", img.width, img.height, img.maxval); 
	fwrite(img.p, sizeof(Pixel), img.width * img.height, f_out); 
	fclose(f_out);
}

void HalfSize(Image &input, Image &output)
{
	int halfW = (input.width)/2;
	int halfH = (input.height)/2;

	output.ResetSize(halfW, halfH);
	output.maxval = 255;
	output.p = (Pixel *) malloc(sizeof(Pixel) * output.width * output.height);

	for(int i = 0; i < halfH; i++) {
		for(int j = 0; j < halfW; j++) {
			int in = (i*2*input.width+j*2);
			int out = (i*halfW+j);
			output.p[out].red = input.p[in].red;
			output.p[out].green = input.p[in].green;
			output.p[out].blue = input.p[in].blue; 	
		}	
	}
}

void LeftRightCombine(Image &leftInput, Image &rightinput, Image &output)
{
	int combinedWidth = leftInput.width + rightinput.width;
	int _height = (leftInput.height + rightinput.height)/2;
	output.ResetSize(combinedWidth, _height);

	output.maxval = 255;
	output.p = (Pixel *) malloc(sizeof(Pixel) * output.width * output.height);

	for(int i = 0; i < leftInput.width; i++) {	
		for(int j = 0; j < output.height; j++) {
			int out = (j*output.width+i); 	
			int in = (j*leftInput.width+i);
			output.p[out].red = leftInput.p[in].red;				
			output.p[out].green = leftInput.p[in].green;				
			output.p[out].blue = leftInput.p[in].blue;				
		}
	}
	
	for(int i = 0; i < rightinput.width; i++) {
		for(int j = 0; j < output.height; j++) {
			int out = (j*output.width+leftInput.width+i);
			int in = (j*rightinput.width+i);
			output.p[out].red = rightinput.p[in].red;				
			output.p[out].green = rightinput.p[in].green;				
			output.p[out].blue = rightinput.p[in].blue;		
		}
	}

}

void TopBottomCombine(Image &topInput, Image &bottomInput, Image &output)
{
	int combinedHeight = topInput.height + bottomInput.height;
	int _width = (topInput.width + bottomInput.width)/2;
	output.ResetSize(_width, combinedHeight);
	
	output.maxval = 255;
	output.p = (Pixel *) malloc(sizeof(Pixel) * output.width * output.height);

	for(int i = 0; i < output.width; i++) {	
		for(int j = 0; j < topInput.height; j++) {
			int out = (j*output.width+i); 	
			int in = (j*topInput.width+i);
			output.p[out].red = topInput.p[in].red;				
			output.p[out].green = topInput.p[in].green;				
			output.p[out].blue = topInput.p[in].blue;				
		}
	}
	
	for(int i = 0; i < output.width; i++) {
		for(int j = 0; j < bottomInput.height; j++) {
			int out = ((j+topInput.height)*output.width+i);
			int in = (j*bottomInput.width+i);
			output.p[out].red = bottomInput.p[in].red;				
			output.p[out].green = bottomInput.p[in].green;				
			output.p[out].blue = bottomInput.p[in].blue;		
		}
	}

}

void Blend(Image &input1, Image &input2, double factor, Image &output)
{
	int _height = (input1.height + input2.height)/2;
	int _width = (input1.width + input2.width)/2;
	output.ResetSize(_width,_height);

	output.maxval = 255;
	output.p = (Pixel *) malloc(sizeof(Pixel) * output.width * output.height);

	for(int i=0; i < output.width; i++) {	
		for(int j=0; j < output.height; j++) {
			int val = (j*output.width+i); 
			output.p[val].red = input1.p[val].red * factor + input2.p[val].red * (1-factor);				
			output.p[val].green = input1.p[val].green * factor + input2.p[val].green * (1-factor);	
			output.p[val].blue = input1.p[val].blue * factor + input2.p[val].blue * (1-factor);					}
	}

}
