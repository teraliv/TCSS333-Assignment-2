#include <stdio.h>
#include <stdbool.h>

void checkboard(void);

int main(void) {
    
    unsigned char in1Arr[499446];
    unsigned char in2Arr[499446];
    
//    unsigned char header1[14];
//    unsigned char header2[40];
    
    unsigned char arr2[499446];
    
    int i;
    
    checkboard();
    
    // read the file in binary mode - rb
    FILE *in1 = fopen("in1.bmp", "rb");
    FILE *in2 = fopen("in2.bmp", "rb");
    FILE *outFile = fopen("doubleExposure.bmp", "wb");
    
    // check if the file is open
    if (!in1 || !in2)
    {
        perror("Failed to open file");
    }
    
    
    fread(in1Arr, 1, 499446, in1);
    fread(in2Arr, 1, 499446, in2);
    
    
    // copy header 1
//    for (i = 0; i < 14; i++) {
//        header1[i] = arr[i];
//    }

    // copy header 2
//    for (i = 14; i < 54; i++) {
//        header2[i] = arr[i];
//    }
    
    
//    for (i = 0; i < 14; i++) {
//        arr2[i] = header1[i];
//    }
//    
//    for (i = 14; i < 54; i++) {
//        arr2[i] = header2[i];
//    }
    
    for (i = 0; i < 54; i++) {
        arr2[i] = in1Arr[i];
    }
    
    for (i = 54; i < 499446; i++) {
        arr2[i] = (in1Arr[i] + in2Arr[i]) / 2;
    }
    
//    printf("%d\n", arr2[55]);
//    arr2[55] = arr2[55] - 50;
//    printf("%d\n", arr2[55]);
    
    fwrite(arr2, sizeof(char), 499446, outFile);
    
    fclose(in1);
    fclose(in2);
    fclose(outFile);
    
    return 0;
}

void checkboard(void) {
    int row;   // Row number, from 0 to 7
    int col;   // Column number, from 0 to 7
    int i;
    
    bool status = false;
//    int x,y;   // Top-left corner of square
    
    for ( row = 0;  row < 8;  row++ ) {
        
        for ( col = 0;  col < 8;  col++) {
//            x = col * 20;
//            y = row * 20;
            if ( (row % 2) == (col % 2) )
                // printf("*");
                status = true;
            else
                // printf("-");
                status = false;
            
            if (status) {
                i = 0;
                while (i < 5) {
                    printf("*");
                    i++;
                }
            } else {
                i = 0;
                while (i < 5) {
                    printf("-");
                    i++;
                }
            }
        }
        printf("\n");
        
    } // end for row
}
