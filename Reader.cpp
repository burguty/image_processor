#include "Reader.h"

Image Reader::Read(const char* path) {
    std::ifstream file;
    file.open(path, std::ios::binary | std::ios::in);

    // Checking for the opening a file
    if (!file) {
        throw std::runtime_error("ERROR: Wrong path to the file");
    }

    char file_header_buffer[FILE_HEADER_SIZE];
    file.read(file_header_buffer, FILE_HEADER_SIZE);
    FileHeader* file_header = reinterpret_cast<FileHeader*>(file_header_buffer);
    // Checking for the right image type
    if (file_header->header_field != BM) {
        file.close();
        throw std::runtime_error("ERROR: Wrong image type");
    }

    char info_header_buffer[INFO_HEADER_SIZE];
    file.read(info_header_buffer, INFO_HEADER_SIZE);
    InfoHeader* info_header = reinterpret_cast<InfoHeader*>(info_header_buffer);

    // Checking for the right bits per pixel
    if (info_header->bits_per_pixel != BIT_PER_PIXEL) {
        file.close();
        throw std::runtime_error("ERROR: Wrong BMP-image type");
    }

    size_t width = info_header->width;
    size_t height = info_header->height;

    if (width == 0 || height == 0) {
        width = height = 0;
    }

    Image image(*file_header, *info_header);

    const int padding =
        static_cast<int>((BYTE_ALLIGNMENT - PIXEL_SEGMENTS * (width % BYTE_ALLIGNMENT)) % BYTE_ALLIGNMENT);
    for (ssize_t i = static_cast<ssize_t>(height - 1); i >= 0; --i) {
        for (ssize_t j = 0; j < static_cast<ssize_t>(width); ++j) {
            uint8_t pixel[3];
            file.read(reinterpret_cast<char*>(pixel), 3);
            image.SetPixel(i, j, Pixel(pixel[2], pixel[1], pixel[0]));
        }
        file.ignore(padding);
    }
    file.close();
    return image;
}
