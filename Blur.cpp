#include "Filters.h"
#include <cmath>

BlurParameters::BlurParameters(double arg) : sigma(arg) {
}

Blur::Blur(double sigma) : sigma_(sigma) {
}

Blur::Blur(BlurParameters*& parameters) : sigma_(parameters->sigma) {
}

double Blur::Gauss(int32_t c0, int32_t c) const {
    double delta_c = static_cast<double>(c0) - static_cast<double>(c);
    double gauss = exp(-delta_c * delta_c / (2 * sigma_ * sigma_));
    gauss = gauss / sqrt(2 * M_PI * sigma_ * sigma_);
    return gauss;
}

void Blur::Apply(Image& image) {
    std::vector<std::vector<Pixel>> gauss_horizont(image.GetHeight(), std::vector<Pixel>(image.GetWidth()));
    int32_t delta_sigma = static_cast<int32_t>(ceil(3 * sigma_));
    for (size_t x = 0; x < image.GetHeight(); ++x) {
        for (size_t y = 0; y < image.GetWidth(); ++y) {
            double red = 0;
            double green = 0;
            double blue = 0;
            int32_t y0_min = static_cast<int32_t>(y) - delta_sigma;
            int32_t y0_max = static_cast<int32_t>(y) + delta_sigma;
            for (int32_t y0 = y0_min; y0 <= y0_max; ++y0) {
                double gauss = Gauss(y0, static_cast<int32_t>(y));
                size_t y0_real =
                    std::min(static_cast<int32_t>(image.GetWidth() - 1), std::max(static_cast<int32_t>(0), y0));
                red += gauss * static_cast<double>(image.At(x, y0_real).R());
                green += gauss * static_cast<double>(image.At(x, y0_real).G());
                blue += gauss * static_cast<double>(image.At(x, y0_real).B());
            }
            red = std::min(static_cast<double>(MAX_COLOR), std::max(static_cast<double>(0), red));
            green = std::min(static_cast<double>(MAX_COLOR), std::max(static_cast<double>(0), green));
            blue = std::min(static_cast<double>(MAX_COLOR), std::max(static_cast<double>(0), blue));
            gauss_horizont[x][y] =
                Pixel(static_cast<uint8_t>(red), static_cast<uint8_t>(green), static_cast<uint8_t>(blue));
        }
    }
    for (size_t y = 0; y < image.GetWidth(); ++y) {
        for (size_t x = 0; x < image.GetHeight(); ++x) {
            double red = 0;
            double green = 0;
            double blue = 0;
            int32_t x0_min = static_cast<int32_t>(x) - delta_sigma;
            int32_t x0_max = static_cast<int32_t>(x) + delta_sigma;
            for (int32_t x0 = x0_min; x0 <= x0_max; ++x0) {
                double gauss = Gauss(x0, static_cast<int32_t>(x));
                size_t x0_real =
                    std::min(static_cast<int32_t>(image.GetHeight() - 1), std::max(static_cast<int32_t>(0), x0));
                red += gauss * static_cast<double>(gauss_horizont[x0_real][y].R());
                green += gauss * static_cast<double>(gauss_horizont[x0_real][y].G());
                blue += gauss * static_cast<double>(gauss_horizont[x0_real][y].B());
            }
            red = std::min(static_cast<double>(MAX_COLOR), std::max(static_cast<double>(0), red));
            green = std::min(static_cast<double>(MAX_COLOR), std::max(static_cast<double>(0), green));
            blue = std::min(static_cast<double>(MAX_COLOR), std::max(static_cast<double>(0), blue));
            image.SetPixel(x, y,
                           Pixel(static_cast<uint8_t>(red), static_cast<uint8_t>(green), static_cast<uint8_t>(blue)));
        }
    }
}
