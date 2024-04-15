#pragma once
#include "../Filters/Filters.h"
#include "string.h"

class Parser {
public:
    Parser() = default;
    Parser(const Parser& parser);
    Parser(int size, char** query);
    ~Parser();

    Parser& operator=(const Parser& parser);

    char* GetInputPath();
    char* GetOutputPath();
    std::vector<Option> GetOptions();

    void ParseQuery(int size, char** query);

private:
    char* input_path_;
    char* output_path_;
    std::vector<Option> options_;
};
