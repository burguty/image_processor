#include "Filters.h"

FishEyeParameters::FishEyeParameters(double arg) {
    sigma = arg;
}

FishEye::FishEye(double sigma) {
    sigma_ = sigma;
}

FishEye::FishEye(FishEyeParameters*& parameters) {
    sigma_ = parameters->sigma;
}

void FishEye::Apply(Image& image) {
    if (image.IsEmpty()) {
        return;
    }
    const double center_x = static_cast<double>(static_cast<double>(image.GetWidth()) / 2);
    const double center_y = static_cast<double>(static_cast<double>(image.GetHeight()) / 2);
    const double max_distance = std::min(center_x, center_y);
    Image original(image);
    for (size_t y = 0; y < image.GetHeight(); ++y) {
        for (size_t x = 0; x < image.GetWidth(); ++x) {
            const double offset_x = static_cast<double>(x) - center_x;
            const double offset_y = static_cast<double>(y) - center_y;
            const double distance = std::hypot(offset_x, offset_y);
            if (max_distance - distance > EPS) {
                const double normalized_distance = distance / max_distance;
                double delta = 1. - std::pow(1. - normalized_distance, sigma_);
                int32_t x_to = static_cast<int32_t>(center_x + offset_x * delta);
                int32_t y_to = static_cast<int32_t>(center_y + offset_y * delta);
                if (x_to >= 0 && y_to >= 0 && x_to < image.GetWidth() && y_to < image.GetHeight()) {
                    image.SetPixel(y, x, original.At(static_cast<size_t>(y_to), static_cast<size_t>(x_to)));
                }
            }
        }
    }
}
