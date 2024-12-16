#include "core/Engine.hpp"
#include <iostream>

int main() {
    try {
        Engine::Engine engine;
        if (!engine.Initialize()) {
            std::cerr << "Failed to initialize engine" << std::endl;
            return 1;
        }
        engine.Run();
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}
