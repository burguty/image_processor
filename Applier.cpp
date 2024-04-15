#include "Applier.h"

Applier::Applier(const std::vector<Option>& options) {
    MakeFilters(options);
}

Applier::~Applier() {
    for (size_t i = 0; i < filters_.size(); ++i) {
        delete filters_[i];
    }
}

void Applier::MakeFilters(const std::vector<Option>& options) {
    for (const Option& option : options) {
        switch (option.filter_name) {
            case CROP: {
                CropParameters* parameters = reinterpret_cast<CropParameters*>(option.parameters);
                filters_.push_back(new Crop(parameters));
            } break;
            case GRAYSCALE: {
                filters_.push_back(new Grayscale());
            } break;
            case NEGATIVE: {
                filters_.push_back(new Negative());
            } break;
            case SHARPENING: {
                filters_.push_back(new Sharpening());
            } break;
            case EDGE_DETECTION: {
                EdgeDetectionParameters* parameters = reinterpret_cast<EdgeDetectionParameters*>(option.parameters);
                filters_.push_back(new EdgeDetection(parameters));
            } break;
            case BLUR: {
                BlurParameters* parameters = reinterpret_cast<BlurParameters*>(option.parameters);
                filters_.push_back(new Blur(parameters));
            } break;
            case FISH_EYE: {
                FishEyeParameters* parameters = reinterpret_cast<FishEyeParameters*>(option.parameters);
                filters_.push_back(new FishEye(parameters));
            } break;
            case PIXELATION: {
                PixelationParameters* parameters = reinterpret_cast<PixelationParameters*>(option.parameters);
                filters_.push_back(new Pixelation(parameters));
            } break;
            case GLASS_DISTORTION: {
                GlassDistortionParameters* parameters = reinterpret_cast<GlassDistortionParameters*>(option.parameters);
                filters_.push_back(new GlassDistortion(parameters));
            } break;
            default: {
                std::cout << "Unknown filter name";
            } break;
        }
    }
}

void Applier::ApplyFilters(Image& image) {
    for (IFilter* const filter : filters_) {
        filter->Apply(image);
    }
}
