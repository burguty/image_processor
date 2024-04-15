#pragma once
#include "BMP.h"
#include "../Image/Image.h"
#include <fstream>

class Reader {
public:
    Reader() = default;
    ~Reader() = default;
    Image Read(const char* path);
};
