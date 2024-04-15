#include "Filters.h"

const std::vector<std::vector<double>> EDGE_DETECTION_MATRIX{{0, -1, 0},   // NO LINT
                                                             {-1, 4, -1},  // NO LINT
                                                             {0, -1, 0}};  // NO LINT

EdgeDetectionParameters::EdgeDetectionParameters(double arg) : threshold(arg) {
}

EdgeDetection::EdgeDetection(double threshold) : threshold_(threshold) {
}

EdgeDetection::EdgeDetection(EdgeDetectionParameters*& parameters) : threshold_(parameters->threshold) {
}

void EdgeDetection::Apply(Image& image) {
    grayscale_.Apply(image);
    Image original(image);
    for (size_t i = 0; i < image.GetHeight(); ++i) {
        for (size_t j = 0; j < image.GetWidth(); ++j) {
            Pixel new_pixel = original.ApplyMatrixToPixel(i, j, EDGE_DETECTION_MATRIX);
            if (new_pixel.R() > static_cast<uint8_t>(MAX_COLOR * threshold_)) {
                new_pixel = Pixel(MAX_COLOR, MAX_COLOR, MAX_COLOR);
            } else {
                new_pixel = Pixel(MIN_COLOR, MIN_COLOR, MIN_COLOR);
            }
            image.SetPixel(i, j, new_pixel);
        }
    }
}
