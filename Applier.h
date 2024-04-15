#pragma once
#include "../Filters/Filters.h"

class Applier {
public:
    Applier() = default;
    explicit Applier(const std::vector<Option>& options);
    ~Applier();

    void MakeFilters(const std::vector<Option>& options);
    void ApplyFilters(Image& image);

private:
    std::vector<IFilter*> filters_;
};
