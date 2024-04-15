#include "Image.h"

Image::Image() {
    width_ = 0;
    height_ = 0;
    file_header_.header_field = BM;
    file_header_.size = FILE_HEADER_SIZE + INFO_HEADER_SIZE;
    file_header_.specific_first = 0;
    file_header_.specific_second = 0;
    file_header_.offset = FILE_HEADER_SIZE + INFO_HEADER_SIZE;

    info_header_.size = INFO_HEADER_SIZE;
    info_header_.width = static_cast<int32_t>(0);
    info_header_.height = static_cast<int32_t>(0);
    info_header_.planes = 1;
    info_header_.bits_per_pixel = BIT_PER_PIXEL;
    info_header_.compression = 0;
    info_header_.size_bitmap = 0;
    info_header_.x_resolution = 0;
    info_header_.y_resolution = 0;
    info_header_.number_colors = 0;
    info_header_.important = 0;
}

Image::Image(const Image& other) {
    image_ = other.image_;
    file_header_ = other.file_header_;
    info_header_ = other.info_header_;
    SetSize(other.width_, other.height_);
}

Image::Image(const FileHeader file_header, const InfoHeader info_header) {
    file_header_ = file_header;
    info_header_ = info_header;
    SetSize(info_header.width, info_header.height);
}

size_t Image::GetWidth() const {
    return width_;
}

size_t Image::GetHeight() const {
    return height_;
}

std::vector<std::vector<Pixel>> Image::GetImage() const {
    return image_;
}

FileHeader Image::GetFileHeader() const {
    return file_header_;
}

InfoHeader Image::GetInfoHeader() const {
    return info_header_;
}

void Image::SetPixel(const size_t i, const size_t j, const Pixel pixel) {
    if (!(i >= 0 && j >= 0 && i < height_ && j < width_)) {
        throw std::runtime_error("ERROR: Out of the image");
        return;
    }
    image_[i][j] = pixel;
}

void Image::SetSize(const size_t width, const size_t height) {
    size_t real_width = std::min(static_cast<size_t>(width), width_);
    size_t real_height = std::min(static_cast<size_t>(height), height_);
    image_.resize(real_height, std::vector<Pixel>(real_width));
    width_ = real_width;
    height_ = real_height;
    const int64_t padding =
        static_cast<int64_t>((BYTE_ALLIGNMENT - PIXEL_SEGMENTS * (width_ % BYTE_ALLIGNMENT)) % BYTE_ALLIGNMENT);
    file_header_.size = FILE_HEADER_SIZE + INFO_HEADER_SIZE + width_ * height_ * 3 + height_ * padding;
    info_header_.width = static_cast<int32_t>(real_width);
    info_header_.height = static_cast<int32_t>(real_height);
}

bool Image::IsEmpty() const {
    return height_ == 0;
}

Pixel Image::At(const size_t x, const size_t y) const {
    return image_[x][y];
}

Pixel Image::ApplyMatrixToPixel(const size_t i, const size_t j, const std::vector<std::vector<double>>& matrix) {
    double red = 0;
    double green = 0;
    double blue = 0;
    const int32_t center_i = static_cast<int32_t>((matrix.size() - 1) / 2);
    const int32_t center_j = static_cast<int32_t>((matrix.size() - 1) / 2);
    for (size_t n = 0; n < matrix.size(); ++n) {
        for (size_t m = 0; m < matrix[n].size(); ++m) {
            if (matrix[n][m] == 0) {
                continue;
            }
            int32_t i_to_temp = static_cast<int32_t>(i) + static_cast<int32_t>(n) - center_i;
            int32_t j_to_temp = static_cast<int32_t>(j) + static_cast<int32_t>(m) - center_j;
            size_t i_to = std::min(static_cast<int32_t>(height_ - 1), std::max(static_cast<int32_t>(0), i_to_temp));
            size_t j_to = std::min(static_cast<int32_t>(width_ - 1), std::max(static_cast<int32_t>(0), j_to_temp));
            red += matrix[n][m] * static_cast<double>(image_[i_to][j_to].R());
            green += matrix[n][m] * static_cast<double>(image_[i_to][j_to].G());
            blue += matrix[n][m] * static_cast<double>(image_[i_to][j_to].B());
        }
    }
    red = std::min(static_cast<double>(MAX_COLOR), std::max(static_cast<double>(0), red));
    green = std::min(static_cast<double>(MAX_COLOR), std::max(static_cast<double>(0), green));
    blue = std::min(static_cast<double>(MAX_COLOR), std::max(static_cast<double>(0), blue));
    return Pixel(static_cast<uint8_t>(red), static_cast<uint8_t>(green), static_cast<uint8_t>(blue));
}
