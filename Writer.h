#pragma once
#include "BMP.h"
#include "../Image/Image.h"
#include <fstream>

class Writer {
public:
    Writer() = default;
    ~Writer() = default;

    void Write(const char* path, Image& image);
};
