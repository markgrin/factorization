#ifndef HPP_7FF866427E2E41FA90C92D5128D30C60

#define HPP_7FF866427E2E41FA90C92D5128D30C60

#include <chrono>

struct timer {
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
    std::chrono::time_point<std::chrono::high_resolution_clock> stop;
    void begin() {
        start = decltype(start)::clock::now();
    }
    void end() {
        stop = decltype(stop)::clock::now();
    }
    std::size_t duration() {
        return std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
    }
};

#endif // HPP_7FF866427E2E41FA90C92D5128D30C60
