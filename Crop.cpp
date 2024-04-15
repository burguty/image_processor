#include "Filters.h"

CropParameters::CropParameters(size_t arg1, size_t arg2) : new_width(arg1), new_height(arg2) {
}

Crop::Crop(size_t new_width, size_t new_height) : new_width_(new_width), new_height_(new_height) {
}

Crop::Crop(CropParameters*& parameters) : new_width_(parameters->new_width), new_height_(parameters->new_height) {
}

void Crop::Apply(Image& image) {
    image.SetSize(new_width_, new_height_);
}
