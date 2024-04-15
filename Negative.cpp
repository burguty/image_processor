#include "Filters.h"

void Negative::Apply(Image& image) {
    for (size_t i = 0; i < image.GetHeight(); ++i) {
        for (size_t j = 0; j < image.GetWidth(); ++j) {
            image.SetPixel(i, j, !image.At(i, j));
        }
    }
}
