#include "Filters.h"

const std::vector<std::vector<double>> SHARPENING_MATRIX{{0, -1, 0},   // NO LINT
                                                         {-1, 5, -1},  // NO LINT
                                                         {0, -1, 0}};  // NO LINT

void Sharpening::Apply(Image& image) {
    Image original(image);
    for (size_t i = 0; i < image.GetHeight(); ++i) {
        for (size_t j = 0; j < image.GetWidth(); ++j) {
            Pixel new_pixel = original.ApplyMatrixToPixel(i, j, SHARPENING_MATRIX);
            image.SetPixel(i, j, new_pixel);
        }
    }
}
