#include "./Tools/Application.h"

const int RETURN_RUNTIME_ERROR = 120;  // NOLINT
const int RETURN_LOGIC_ERROR = 121;    // NOLINT
const int RETURN_OTHER_ERROR = 666;    // NOLINT

int main(int argc, char* argv[]) {
    try {
        Application app(argc, argv);
        app.Launch();
    } catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
        return RETURN_RUNTIME_ERROR;
    } catch (std::logic_error& e) {
        std::cout << e.what() << std::endl;
        return RETURN_LOGIC_ERROR;
    } catch (...) {
        std::cout << "Undefined error" << std::endl;
        return RETURN_OTHER_ERROR;
    }
    return 0;
}
