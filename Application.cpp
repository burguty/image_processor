#include "Application.h"

Application::Application(int size, char* query[]) : size_(size), query_(query) {
}

Application::Application(const Application& app) {
    size_ = app.size_;
    query_ = app.query_;
}

Application& Application::operator=(const Application& app) {
    size_ = app.size_;
    query_ = app.query_;
    return *this;
}

void Application::Launch() {
    parser_.ParseQuery(size_, query_);
    if (size_ == 1) {
        return;
    }
    Image image = reader_.Read(parser_.GetInputPath());
    applier_.MakeFilters(parser_.GetOptions());
    applier_.ApplyFilters(image);
    writer_.Write(parser_.GetOutputPath(), image);
}
