#include "write_ppm.h"
#include <fstream>
#include <cassert>
#include <iostream>

bool write_ppm(
    const std::string& filename,
    const std::vector<unsigned char>& data,
    const int width,
    const int height,
    const int num_channels)
{
    ////////////////////////////////////////////////////////////////////////////
    // Replace with your code from computer-graphics-raster-images
    // ppm file format referenced from: https://en.wikipedia.org/wiki/Netpbm#File_formats
    // how to create/write to a (ppm) file referenced from: https://www.youtube.com/watch?v=12IbpyFiIYE
    std::ofstream fout(filename);
    if (fout.fail())
        return false;

    bool grayscale = num_channels == 1;
    fout << (grayscale ? "P2\n" : "P3\n");
    fout << width << " " << height << "\n";
    fout << "255\n";

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int index = num_channels * (x + width * y);
            if (grayscale) {
                fout << (int)data[index] << " ";
            }
            else {
                fout << (int)data[index++] << " ";
                fout << (int)data[index++] << " ";
                fout << (int)data[index] << " ";
            }
        }
        fout << "\n";
    }
    fout.close();
    return true;
    ////////////////////////////////////////////////////////////////////////////
}
