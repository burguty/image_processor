#include "Filters.h"

PixelationParameters::PixelationParameters(size_t arg) : block(arg) {
}

Pixelation::Pixelation(size_t block) : block_(block) {
}

Pixelation::Pixelation(PixelationParameters*& parameters) : block_(parameters->block) {
}

void Pixelation::Apply(Image& image) {
    Image original(image);
    for (size_t y = 0; y < image.GetHeight(); y += block_) {
        for (size_t x = 0; x < image.GetWidth(); x += block_) {
            double red = 0;
            double green = 0;
            double blue = 0;
            size_t count = 0;
            for (size_t dy = 0; dy < block_ && y + dy < image.GetHeight(); ++dy) {
                for (size_t dx = 0; dx < block_ && x + dx < image.GetWidth(); ++dx) {
                    red += static_cast<double>(original.At(y + dy, x + dx).R());
                    green += static_cast<double>(original.At(y + dy, x + dx).G());
                    blue += static_cast<double>(original.At(y + dy, x + dx).B());
                    ++count;
                }
            }
            red = red / static_cast<double>(count);
            green = green / static_cast<double>(count);
            blue = blue / static_cast<double>(count);
            Pixel average(static_cast<uint8_t>(red), static_cast<uint8_t>(green), static_cast<uint8_t>(blue));
            for (size_t dy = 0; dy < block_ && y + dy < image.GetHeight(); ++dy) {
                for (size_t dx = 0; dx < block_ && x + dx < image.GetWidth(); ++dx) {
                    image.SetPixel(y + dy, x + dx, average);
                }
            }
        }
    }
}
