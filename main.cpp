/* 
Title:    main.cpp
Author:   Lawrence Gabriel Castillo
Date:     2018-Apr-19
Desc:     Filters image input for edge detection; outputs new image
Purpose:  To demonstrate image manipulation
Build:    Visual Studio Code 1.31.1; compile: g++ main.cpp
*/

#include <iostream>
#include <cassert>
#include <cstdlib>
#include <fstream>

using namespace std;

const int MAX_H = 512;
const int MAX_W = 512;

void readImage(int image[MAX_H][MAX_W], int &height, int &width);
void writeImage(int image[MAX_H][MAX_W], int height, int width);

int main() {
    
    int img[MAX_H][MAX_W];
    int h, w;
    
    readImage(img, h, w); // read it from the file "inImage.pgm"
    // h and w were passed by reference and
    // now contain the dimensions of the picture
    // and the 2-dimesional array img contains the image data
    
    // Now we can manipulate the image the way we like
    // for example we copy its contents into a new array
    int out[MAX_H][MAX_W];
    
    for(int row = 0; row < h; row++) {
        for(int col = 0; col < w; col++) {
            if (row == 0 || col == 0 || row == h-1 || col == w-1) {
                out[row][col] = 0;
            }
            else {
                int tempNumCheck = (img[row + 1][col - 1] + 2 * img[row + 1][col + 0] + img[row + 1][col + 1])
                          - (img[row - 1][col - 1] + 2 * img[row - 1][col + 0] + img[row - 1][col + 1]);
                if (tempNumCheck < 0) {
                    tempNumCheck = 0;
                }
                else if (tempNumCheck > 255) {
                    tempNumCheck = 255;
                }
                out[row][col] = tempNumCheck;
            }
        }
    }
    
    // and save this new image to file "outImage.pgm"
    writeImage(out, h, w);   
}

// Reads a PGM file.
void readImage(int image[MAX_H][MAX_W], int &height, int &width) {
    char c;
    ifstream instr;
    instr.open("input_image.pgm");
    
    // read the header P2
    instr >> c;
    assert(c == 'P');
    instr >> c;
    assert(c == '2');
    
    // skip the comments (if any)
    while ((instr>>ws).peek() == '#') {
        instr.ignore(4096, '\n');
    }
    
    instr >> width;
    instr >> height;
    
    assert(width <= MAX_W);
    assert(height <= MAX_H);
    int max;
    instr >> max;
    assert(max == 255);
    
    for (int row = 0; row < height; row++)
        for (int col = 0; col < width; col++)
            instr >> image[row][col];
    instr.close();
    return;
}

// Writes a PGM file
// Need to provide the array data and the image dimensions
void writeImage(int image[MAX_H][MAX_W], int height, int width) {
    ofstream ostr;
    ostr.open("output_image.pgm");
    if (ostr.fail()) {
        cout << "Unable to write file\n";
        exit(1);
    };
    
    // print the header
    ostr << "P2" << endl;
    // width, height
    ostr << width << ' ';
    ostr << height << endl;
    ostr << 255 << endl;
    
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            assert(image[row][col] < 256);
            assert(image[row][col] >= 0);
            ostr << image[row][col] << ' ';
            ostr << endl;
        }
    }
    ostr.close();
    return;
}