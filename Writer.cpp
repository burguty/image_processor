#include "Writer.h"

void Writer::Write(const char* path, Image& image) {
    std::ofstream file;
    file.open(path, std::ios::binary | std::ios::out);
    if (!file) {
        throw std::runtime_error("ERROR: Wrong output path");
    }

    size_t width = image.GetWidth();
    size_t height = image.GetHeight();

    const int64_t padding =
        static_cast<int64_t>((BYTE_ALLIGNMENT - PIXEL_SEGMENTS * (width % BYTE_ALLIGNMENT)) % BYTE_ALLIGNMENT);

    FileHeader file_header = image.GetFileHeader();
    InfoHeader info_header = image.GetInfoHeader();
    file.write(reinterpret_cast<char*>(&file_header), FILE_HEADER_SIZE);
    file.write(reinterpret_cast<char*>(&info_header), INFO_HEADER_SIZE);
    uint8_t pad[3] = {0, 0, 0};
    for (ssize_t i = static_cast<ssize_t>(height) - 1; i >= 0; --i) {
        for (size_t j = 0; j < width; ++j) {
            uint8_t pixel[3] = {image.At(i, j).B(), image.At(i, j).G(), image.At(i, j).R()};
            file.write(reinterpret_cast<char*>(pixel), 3);
        }
        if (padding != 0) {
            file.write(reinterpret_cast<char*>(pad), padding);
        }
    }
    file.close();
}
