#include "Parser.h"

static constexpr std::string_view HELP =
    "Usage:\n\n"
    "   ./image_processor {path to input file} {path to output file}\n"
    "   [-{filter name 1} [filter parameter 1] [filter parameter 2] ...]\n"
    "   [-{filter name 2} [filter parameter 1] [filter parameter 2] ...]\n"
    "   ...\n\n"
    "filter names: crop, gs, neg, sharp, edge, blur, fish_eye, pixel, glass\n";

Parser::Parser(int size, char* query[]) {
    ParseQuery(size, query);
}

Parser::Parser(const Parser& parser)
    : input_path_(parser.input_path_), output_path_(parser.output_path_), options_(parser.options_) {
}

Parser::~Parser() {
    for (size_t i = 0; i < options_.size(); ++i) {
        delete options_[i].parameters;
    }
}

Parser& Parser::operator=(const Parser& parser) {
    input_path_ = parser.input_path_;
    output_path_ = parser.output_path_;
    options_ = parser.options_;
    return *this;
}

void Parser::ParseQuery(int size, char* query[]) {
    if (size == 1) {
        std::cout << HELP << std::endl;
        return;
    }
    if (size < 3) {
        throw std::runtime_error("ERROR: Not enough arguments");
    }
    input_path_ = query[1];
    output_path_ = query[2];
    for (size_t i = 3; i < size;) {
        if (strcmp(query[i], "-crop") == 0) {
            if (i + 2 >= size) {
                throw std::runtime_error("ERROR: Not enough arguments for -crop");
            }
            if (!(std::stoi(query[i + 1]) >= 0 && std::stoi(query[i + 2]) >= 0)) {
                throw std::runtime_error("ERROR: Wrong argument for -crop, expected >= 0");
            }
            size_t arg1 = std::stoi(query[i + 1]);
            size_t arg2 = std::stoi(query[i + 2]);
            if (arg1 == 0 || arg2 == 0) {
                arg1 = arg2 = 0;
            }
            options_.push_back(Option(CROP, new CropParameters(arg1, arg2)));
            i += 3;
        } else if (strcmp(query[i], "-gs") == 0) {
            options_.push_back(Option(GRAYSCALE, new GrayscaleParameters()));
            ++i;
        } else if (strcmp(query[i], "-neg") == 0) {
            options_.push_back(Option(NEGATIVE, new NegativeParameters()));
            ++i;
        } else if (strcmp(query[i], "-sharp") == 0) {
            options_.push_back(Option(SHARPENING, new SharpeningParameters()));
            ++i;
        } else if (strcmp(query[i], "-edge") == 0) {
            if (i + 1 >= size) {
                throw std::runtime_error("ERROR: Not enough arguments for -edge");
            }
            if (!(std::stod(query[i + 1]) >= 0)) {
                throw std::runtime_error("ERROR: Wrong argument for -edge, expected double >= 0");
            }
            double arg = std::stod(query[i + 1]);
            options_.push_back(Option(EDGE_DETECTION, new EdgeDetectionParameters(arg)));
            i += 2;
        } else if (strcmp(query[i], "-blur") == 0) {
            if (i + 1 >= size) {
                throw std::runtime_error("ERROR: Not enough arguments for -blur");
            }
            if ((std::stod(query[i + 1]) <= EPS)) {
                throw std::runtime_error("ERROR: Wrong argument for -blur, expected double sigma > 0");
            }
            double arg = std::stod(query[i + 1]);
            options_.push_back(Option(BLUR, new BlurParameters(arg)));
            i += 2;
        } else if (strcmp(query[i], "-fish_eye") == 0) {
            if (i + 1 >= size) {
                throw std::runtime_error("ERROR: Not enough arguments for -fish_eye");
            }
            if (std::stod(query[i + 1]) < -EPS) {
                throw std::runtime_error("ERROR: Invalid argument for -fish_eye, expected double sigma >= 0");
            }
            double arg = std::stod(query[i + 1]);
            options_.push_back(Option(FISH_EYE, new FishEyeParameters(arg)));
            i += 2;
        } else if (strcmp(query[i], "-pixel") == 0) {
            if (i + 1 >= size) {
                throw std::runtime_error("ERROR: Not enough arguments for -pixel");
            }
            if (std::stod(query[i + 1]) < EPS || (std::stoi(query[i + 1]) - std::stod(query[i + 1]) != 0)) {
                throw std::runtime_error("ERROR: Invalid argument for -pixel, expected integer block > 0");
            }
            size_t arg = static_cast<size_t>(std::stoi(query[i + 1]));
            options_.push_back(Option(PIXELATION, new PixelationParameters(arg)));
            i += 2;
        } else if (strcmp(query[i], "-glass") == 0) {
            if (i + 1 >= size) {
                throw std::runtime_error("ERROR: Not enough arguments for -glass");
            }
            if (std::stod(query[i + 1]) < 0 || (std::stoi(query[i + 1]) - std::stod(query[i + 1]) != 0)) {
                throw std::runtime_error("ERROR: Invalid argument for -glass, expected integer offset >= 0");
            }
            int32_t arg = static_cast<int32_t>(std::stoi(query[i + 1]));
            options_.push_back(Option(GLASS_DISTORTION, new GlassDistortionParameters(arg)));
            i += 2;
        } else {
            throw std::runtime_error("ERROR: Wrong filter name");
        }
    }
}

char* Parser::GetInputPath() {
    return input_path_;
}

char* Parser::GetOutputPath() {
    return output_path_;
}

std::vector<Option> Parser::GetOptions() {
    return options_;
}
