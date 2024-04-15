#include <catch.hpp>
#include "./Tools/Application.h"

TEST_CASE("Without arguments") {
    char* query[] = {const_cast<char*>("./image_processor")};  // NOLINT
    Application app(1, query);
    REQUIRE_NOTHROW(app.Launch());
}

void ThrowExceptionWithMessage(int size, char* query[]) {
    Application app(size, query);
    app.Launch();
}

TEST_CASE("Exceptions") {
    char* query_1[6] = {const_cast<char*>("./image_processor"),                                  // NOLINT
                        const_cast<char*>("/tasks/image_processor/test_script/data/lenna.bmp"),  // NOLINT
                        const_cast<char*>("./"),                                                 // NOLINT
                        const_cast<char*>("-crop"),                                              // NOLINT
                        const_cast<char*>("-7"),                                                 // NOLINT
                        const_cast<char*>("7")};                                                 // NOLINT

    REQUIRE_THROWS_WITH(ThrowExceptionWithMessage(2, query_1), "ERROR: Not enough arguments");
    REQUIRE_THROWS_WITH(ThrowExceptionWithMessage(3, query_1), "ERROR: Wrong path to the file");
    REQUIRE_THROWS_WITH(ThrowExceptionWithMessage(5, query_1), "ERROR: Not enough arguments for -crop");
    REQUIRE_THROWS_WITH(ThrowExceptionWithMessage(6, query_1), "ERROR: Wrong argument for -crop, expected >= 0");

    char* query_2[] = {const_cast<char*>("./image_processor"),                                           // NOLINT
                       const_cast<char*>("./test_script/data/lenna.bmp"),                                // NOLINT
                       const_cast<char*>("./"), const_cast<char*>("-edge"), const_cast<char*>("-0.5")};  // NOLINT
    REQUIRE_THROWS_WITH(ThrowExceptionWithMessage(4, query_2), "ERROR: Not enough arguments for -edge");
    REQUIRE_THROWS(ThrowExceptionWithMessage(5, query_2));

    char* query_3[] = {const_cast<char*>("./image_processor"),                                    // NOLINT
                       const_cast<char*>("../tasks/image_processor/test_script/data/lenna.bmp"),  // NOLINT
                       const_cast<char*>("/Users/nikitasevryukov/CppProjects/output.bmp"),        // NOLINT
                       const_cast<char*>("-blur"),                                                // NOLINT
                       const_cast<char*>("-0.5")};                                                // NOLINT
    REQUIRE_THROWS_WITH(ThrowExceptionWithMessage(4, query_3), "ERROR: Not enough arguments for -blur");
    REQUIRE_THROWS_WITH(ThrowExceptionWithMessage(5, query_3),
                        "ERROR: Wrong argument for -blur, expected double sigma > 0");
    query_3[4] = const_cast<char*>("0.5");  // NOLINT
    REQUIRE_NOTHROW(ThrowExceptionWithMessage(5, query_3));
    query_3[4] = const_cast<char*>("0");  // NOLINT
    REQUIRE_THROWS_WITH(ThrowExceptionWithMessage(5, query_3),
                        "ERROR: Wrong argument for -blur, expected double sigma > 0");

    char* query_4[] = {const_cast<char*>("./image_processor"),                                    // NOLINT
                       const_cast<char*>("../tasks/image_processor/test_script/data/lenna.bmp"),  // NOLINT
                       const_cast<char*>("/Users/nikitasevryukov/CppProjects/output.bmp"),        // NOLINT
                       const_cast<char*>("-fish_eye"), const_cast<char*>("-0.5")};                // NOLINT
    REQUIRE_THROWS_WITH(ThrowExceptionWithMessage(4, query_4), "ERROR: Not enough arguments for -fish_eye");
    REQUIRE_THROWS_WITH(ThrowExceptionWithMessage(5, query_4),
                        "ERROR: Invalid argument for -fish_eye, expected double sigma >= 0");
    query_4[4] = const_cast<char*>("0.5");  // NOLINT
    REQUIRE_NOTHROW(ThrowExceptionWithMessage(5, query_4));

    char* query_5[] = {const_cast<char*>("./image_processor"),                                    // NOLINT
                       const_cast<char*>("../tasks/image_processor/test_script/data/lenna.bmp"),  // NOLINT
                       const_cast<char*>("/Users/nikitasevryukov/CppProjects/output.bmp"),        // NOLINT
                       const_cast<char*>("-pixel"),                                               // NOLINT
                       const_cast<char*>("-0.5")};                                                // NOLINT
    REQUIRE_THROWS_WITH(ThrowExceptionWithMessage(4, query_5), "ERROR: Not enough arguments for -pixel");
    REQUIRE_THROWS_WITH(ThrowExceptionWithMessage(5, query_5),
                        "ERROR: Invalid argument for -pixel, expected integer block > 0");
    query_5[4] = const_cast<char*>("0.5");  // NOLINT
    REQUIRE_THROWS_WITH(ThrowExceptionWithMessage(5, query_5),
                        "ERROR: Invalid argument for -pixel, expected integer block > 0");
    query_5[4] = const_cast<char*>("0");  // NOLINT
    REQUIRE_THROWS_WITH(ThrowExceptionWithMessage(5, query_5),
                        "ERROR: Invalid argument for -pixel, expected integer block > 0");
    query_5[4] = const_cast<char*>("2");  // NOLINT
    REQUIRE_NOTHROW(ThrowExceptionWithMessage(5, query_5));

    char* query_6[] = {const_cast<char*>("./image_processor"),                                    // NOLINT
                       const_cast<char*>("../tasks/image_processor/test_script/data/lenna.bmp"),  // NOLINT
                       const_cast<char*>("/Users/nikitasevryukov/CppProjects/output.bmp"),        // NOLINT
                       const_cast<char*>("-glass"),                                               // NOLINT
                       const_cast<char*>("-0.5")};                                                // NOLINT
    REQUIRE_THROWS_WITH(ThrowExceptionWithMessage(4, query_6), "ERROR: Not enough arguments for -glass");
    REQUIRE_THROWS_WITH(ThrowExceptionWithMessage(5, query_6),
                        "ERROR: Invalid argument for -glass, expected integer offset >= 0");
    query_6[4] = const_cast<char*>("0.5");  // NOLINT
    REQUIRE_THROWS_WITH(ThrowExceptionWithMessage(5, query_6),
                        "ERROR: Invalid argument for -glass, expected integer offset >= 0");
    query_6[4] = const_cast<char*>("0");  // NOLINT
    REQUIRE_NOTHROW(ThrowExceptionWithMessage(5, query_6));
    query_6[4] = const_cast<char*>("2");  // NOLINT
    REQUIRE_NOTHROW(ThrowExceptionWithMessage(5, query_6));
}
