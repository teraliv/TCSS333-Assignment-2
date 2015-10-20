/*
 * TCSS 333 - Autumn 2015
 *
 * Assignment 2 - Bitmap image manipulation.
 * Alex Terikov
 */

#include <stdio.h>

void imageDoubleExposure(unsigned char *image1, unsigned char *image2);
void imageCheckerBoard(unsigned char *image1, unsigned char *image2);

int main(void) {
    
    // arrays to hold image data
    unsigned char image1[499446];
    unsigned char image2[499446];
    
    // read the bitmap image files in binary mode
    FILE *bmpFile1 = fopen("in1.bmp", "rb");
    FILE *bmpFile2 = fopen("in2.bmp", "rb");
    
    // check if the files are open
    if (!bmpFile1 || !bmpFile2) {
        perror("Failed to open file");
    }
    
    // load image data into arrays
    fread(image1, 1, 499446, bmpFile1);
    fread(image2, 1, 499446, bmpFile2);
    
    // make a double exposure image
    imageDoubleExposure(image1, image2);
    // make a checker board image
    imageCheckerBoard(image1, image2);
    
    // close files
    fclose(bmpFile1);
    fclose(bmpFile2);
    
    return 0;
}

/*
 * Creates a bitmap image file with double exposure
 * effect base on two images.
 *
 * @param *image1 - pointer to the 1st image array
 * @param *image2 - pointer to the 2nd image array
 */
void imageDoubleExposure(unsigned char *image1, unsigned char *image2) {
    
    // image file to write
    FILE *bmpFile = fopen("blend.bmp", "wb");
    
    int i;
    unsigned char doubleExposure[499446]; // array to hold image data

    // load header data into array
    for (i = 0; i < 54; i++) {
        doubleExposure[i] = image1[i];
    }
    
    // load double exposure data into array
    for (i = 54; i < 499446; i++) {
        doubleExposure[i] = (image1[i] + image2[i]) / 2;
    }
    
    // wride bmp image data into file
    fwrite(doubleExposure, sizeof(unsigned char), 499446, bmpFile);
    fclose(bmpFile); // close file
}


/*
 * Creates a bitmap image file with checker board
 * effect base on two images.
 *
 * @param *image1 - pointer to the 1st image array
 * @param *image2 - pointer to the 2nd image array
 */
void imageCheckerBoard(unsigned char *image1, unsigned char *image2) {
    
    // image file to write
    FILE *bmpFile = fopen("checker.bmp", "wb");
    
    int i;
    unsigned char checkerBoard[499446]; // array to hold image data
    
    int row;   // Row number
    int col;   // Column number
    int count = 54; // Current pixel color location
    
    // load header data into array
    for (i = 0; i < 54; i++) {
        checkerBoard[i] = image1[i];
    }
    
    // load data from two image arrays as a check board
    for ( row = 0;  row < 8;  row++ ) {
        
        for ( col = 0;  col < 408;  col++) {
            
            if ( (row % 2) == (col % 2) ) {
                i = 0;
                while (i < (153)) {
                    checkerBoard[count] = image1[count];
                    count++;
                    i++;
                }
            }
            else {
                i = 0;
                while (i < (153)) {
                    checkerBoard[count] = image2[count];
                    count++;
                    i++;
                }
            }

        } // end for cols
    } // end for rows
    
    // wride bmp image data into file
    fwrite(checkerBoard, sizeof(unsigned char), 499446, bmpFile);
    fclose(bmpFile); //close file
}
