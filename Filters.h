#pragma once
#include "../Image/Image.h"
#include <cmath>

enum FilterName { CROP, GRAYSCALE, NEGATIVE, SHARPENING, EDGE_DETECTION, BLUR, FISH_EYE, PIXELATION, GLASS_DISTORTION };

struct BaseParameters {};

struct Option {
    Option(FilterName arg1, BaseParameters* arg2) : filter_name(arg1), parameters(arg2) {
    }
    ~Option() = default;
    FilterName filter_name;
    BaseParameters* parameters;
};

class IFilter {
public:
    virtual void Apply(Image& image) = 0;
    virtual ~IFilter() = default;
};

// CROP // NO LINT

struct CropParameters : BaseParameters {
    CropParameters(size_t arg1, size_t arg2);
    size_t new_width;
    size_t new_height;
};

class Crop final : public IFilter {
public:
    Crop() = default;
    Crop(size_t new_width, size_t new_height);
    explicit Crop(CropParameters*& parameters);
    ~Crop() final = default;

    void Apply(Image& image) override;

private:
    size_t new_width_;
    size_t new_height_;
};

// GRAYSCALE // NO LINT

struct GrayscaleParameters : BaseParameters {};

class Grayscale final : public IFilter {
public:
    Grayscale() = default;
    void Apply(Image& image) final;
    ~Grayscale() final = default;
};

// NEGATIVE // NOLINT

struct NegativeParameters : BaseParameters {};

class Negative final : public IFilter {
public:
    Negative() = default;
    void Apply(Image& image) final;
    ~Negative() final = default;
};

// SHARPENING //NO LINT

struct SharpeningParameters : BaseParameters {};

class Sharpening final : public IFilter {
public:
    Sharpening() = default;
    void Apply(Image& image) final;
    ~Sharpening() final = default;
};

// EDGE_DETECTION // NOLINT

struct EdgeDetectionParameters : BaseParameters {
    explicit EdgeDetectionParameters(double arg);
    double threshold;
};

class EdgeDetection final : public IFilter {
public:
    EdgeDetection() = default;
    explicit EdgeDetection(double threshold);
    explicit EdgeDetection(EdgeDetectionParameters*& parameters);
    ~EdgeDetection() final = default;

    void Apply(Image& image) final;

private:
    double threshold_;
    Grayscale grayscale_;
};

// BLUR // NOLINT

struct BlurParameters : BaseParameters {
    explicit BlurParameters(double arg);
    double sigma;
};

class Blur final : public IFilter {
public:
    Blur() = default;
    explicit Blur(double sigma);
    explicit Blur(BlurParameters*& parameters);
    ~Blur() final = default;

    void Apply(Image& image) final;

private:
    double Gauss(int32_t c0, int32_t c) const;

private:
    double sigma_;
};

// FISH_EYE // NOLINT

struct FishEyeParameters : BaseParameters {
    explicit FishEyeParameters(double arg);
    double sigma;
};

class FishEye final : public IFilter {
public:
    FishEye() = default;
    explicit FishEye(double sigma);
    explicit FishEye(FishEyeParameters*& parameters);
    ~FishEye() final = default;

    void Apply(Image& image) final;

private:
    double sigma_;
};

// PIXELATION // NOLINT

struct PixelationParameters : BaseParameters {
    explicit PixelationParameters(size_t arg);
    size_t block;
};

class Pixelation final : public IFilter {
public:
    Pixelation() = default;
    explicit Pixelation(size_t block);
    explicit Pixelation(PixelationParameters*& parameters);
    ~Pixelation() final = default;

    void Apply(Image& image) final;

private:
    size_t block_;
};

// GLASS_DISTORTION // NOLINT

struct GlassDistortionParameters : BaseParameters {
    explicit GlassDistortionParameters(int32_t arg);
    int32_t offset;
};

class GlassDistortion final : public IFilter {
public:
    GlassDistortion() = default;
    explicit GlassDistortion(int32_t offset);
    explicit GlassDistortion(GlassDistortionParameters*& parameters);
    ~GlassDistortion() final = default;

    void Apply(Image& image) final;

private:
    int32_t offset_;
};
