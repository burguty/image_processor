#include "Pixel.h"

Pixel::Pixel() : r_(0), g_(0), b_(0) {
}

Pixel::Pixel(const Pixel& other) {
    r_ = other.r_;
    g_ = other.g_;
    b_ = other.b_;
}

Pixel::Pixel(const uint8_t r, const uint8_t g, const uint8_t b) : r_(r), g_(g), b_(b) {
}

Pixel operator*(double k, Pixel pixel) {
    return Pixel(static_cast<uint8_t>(k * pixel.R()), static_cast<uint8_t>(k * pixel.G()),
                 static_cast<uint8_t>(k * pixel.B()));
}

Pixel& Pixel::operator+=(Pixel other) {
    r_ += other.R();
    g_ += other.G();
    b_ += other.B();
    return *this;
}

Pixel operator+(Pixel lhs, Pixel rhs) {
    return Pixel(lhs.R() + rhs.R(), lhs.G() + rhs.G(), lhs.B() + rhs.B());
}

Pixel operator!(const Pixel& pixel) {
    return Pixel(MAX_COLOR - pixel.r_, MAX_COLOR - pixel.g_, MAX_COLOR - pixel.b_);
}

uint8_t Pixel::R() const {
    return r_;
}

uint8_t Pixel::G() const {
    return g_;
}

uint8_t Pixel::B() const {
    return b_;
}

void Pixel::SetR(const uint8_t r) {
    r_ = r;
}
void Pixel::SetG(const uint8_t g) {
    g_ = g;
}
void Pixel::SetB(const uint8_t b) {
    b_ = b;
}
