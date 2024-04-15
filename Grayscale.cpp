#include "Filters.h"

const double RED_KOEF = 0.299;    // NO LINT
const double GREEN_KOEF = 0.587;  // NO LINT
const double BLUE_KOEF = 0.114;   // NO LINT

void Grayscale::Apply(Image& image) {
    for (size_t i = 0; i < image.GetHeight(); ++i) {
        for (size_t j = 0; j < image.GetWidth(); ++j) {
            double edited_red = RED_KOEF * static_cast<double>(image.At(i, j).R());
            double edited_green = GREEN_KOEF * static_cast<double>(image.At(i, j).G());
            double edited_blue = BLUE_KOEF * static_cast<double>(image.At(i, j).B());
            uint8_t edited = static_cast<uint8_t>(edited_red + edited_green + edited_blue);
            image.SetPixel(i, j, Pixel(edited, edited, edited));
        }
    }
}
