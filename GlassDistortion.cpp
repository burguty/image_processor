#include "Filters.h"
#include <random>

GlassDistortionParameters::GlassDistortionParameters(int32_t arg) : offset(arg) {
}

GlassDistortion::GlassDistortion(int32_t offset) : offset_(offset) {
}

GlassDistortion::GlassDistortion(GlassDistortionParameters*& parameters) : offset_(parameters->offset) {
}

void GlassDistortion::Apply(Image& image) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int32_t> dis(-offset_, offset_);

    Image original(image);
    for (size_t y = 0; y < image.GetHeight(); ++y) {
        for (size_t x = 0; x < image.GetWidth(); ++x) {
            int32_t offset_x = dis(gen);
            int32_t offset_y = dis(gen);

            int32_t x_to = static_cast<int32_t>(x) + offset_x;
            int32_t y_to = static_cast<int32_t>(y) + offset_y;

            if (x_to >= 0 && x_to < image.GetWidth() && y_to >= 0 && y_to < image.GetHeight()) {
                image.SetPixel(y, x, original.At(static_cast<size_t>(y_to), static_cast<size_t>(x_to)));
            }
        }
    }
}
