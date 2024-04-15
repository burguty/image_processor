#pragma once
#include <cstdint>
#include <iostream>

static constexpr uint16_t BIT_PER_PIXEL = 24;  // NOLINT
static constexpr size_t PIXEL_SEGMENTS = 3;    // NOLINT
static constexpr size_t BYTE_ALLIGNMENT = 4;   // NOLINT
static constexpr uint16_t BM = 0x4D42;         // NOLINT

struct __attribute__((packed)) FileHeader {
    uint16_t header_field;
    uint32_t size;
    uint16_t specific_first;
    uint16_t specific_second;
    uint32_t offset;
};

struct __attribute__((packed)) InfoHeader {
    uint32_t size;
    int32_t width;
    int32_t height;
    int16_t planes;
    int16_t bits_per_pixel;
    uint32_t compression;
    uint32_t size_bitmap;
    int32_t x_resolution;
    int32_t y_resolution;
    uint32_t number_colors;
    uint32_t important;
};

static constexpr size_t FILE_HEADER_SIZE = sizeof(FileHeader);  // NOLINT
static constexpr size_t INFO_HEADER_SIZE = sizeof(InfoHeader);  // NOLINT
