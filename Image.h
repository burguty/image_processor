#pragma once
#include "../InOut/BMP.h"
#include "Pixel.h"
#include <vector>

static constexpr double EPS = 0.0000001;  // NOLINT

class Image {
public:
    Image();
    Image(const Image& other);
    Image(const FileHeader file_header, const InfoHeader info_header);
    ~Image() = default;

    size_t GetWidth() const;
    size_t GetHeight() const;
    std::vector<std::vector<Pixel>> GetImage() const;
    FileHeader GetFileHeader() const;
    InfoHeader GetInfoHeader() const;

    void SetPixel(const size_t i, const size_t j, const Pixel pixel);
    void SetSize(const size_t width, const size_t height);

    bool IsEmpty() const;

    Pixel At(const size_t x, const size_t y) const;

    Pixel ApplyMatrixToPixel(const size_t i, const size_t j, const std::vector<std::vector<double>>& matrix);

private:
    std::vector<std::vector<Pixel>> image_;
    size_t width_;
    size_t height_;
    FileHeader file_header_;
    InfoHeader info_header_;
};
