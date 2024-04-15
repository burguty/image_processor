#pragma once
#include "Applier.h"
#include "Parser.h"
#include "../InOut/Reader.h"
#include "../InOut/Writer.h"

class Application {
public:
    Application() = default;
    Application(const Application& app);
    Application(int size, char* query[]);
    ~Application() = default;

    Application& operator=(const Application& app);

    void Launch();

private:
    int size_;
    char** query_;
    Reader reader_;
    Writer writer_;
    Parser parser_;
    Applier applier_;
};
