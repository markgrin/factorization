#include "common.hpp"

std::vector<mpz_class> apply_method(std::function<mpz_class(mpz_class)> method, mpz_class number) {
    std::vector<mpz_class> result;
    std::vector<mpz_class> remaining;
    remaining.push_back(number);
    while (!remaining.empty()) {
        auto number = remaining.back();
        remaining.pop_back();
        auto divisor = method(number);
        if (number == divisor) {
            result.push_back(number);
            continue ;
        }
        number /= divisor;
        remaining.push_back(number);
        remaining.push_back(divisor);
    }
    return result;
}


