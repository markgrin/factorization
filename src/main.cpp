#include <iostream>
#include <set>
#include <vector>
#include <functional>
#include <gmpxx.h>

#include "full.hpp"
#include "fermat.hpp"
#include "polflo.hpp"
#include "pollard.hpp"
#include "polflomt.hpp"
#include "timer.hpp"

int help () {
    std::cout << "factorization programm.\n"
                 "USAGE: factorization [method number]\n"
                 "method - method of factorization to use\n"
                 "  Availible methods full, fermat\n"
                 "number - number to factorize\n"
                 "\n"
                 "If called with no arguments they will be promted at runtime\n";
    return 1;
}

int main (int argv, char ** argc) {
    try {
        std::string number;
        std::string method;
        if (argv == 1) {
            std::cout << "Input method(full):";
            std::cin >> method;
            std::cout << "Input number:";
            std::cin >> number;
        } else if (argv == 3) {
            method = argc[1];
            number = argc[2];
        } else {
            return help();
        }

        std::function<std::vector<mpz_class>(mpz_class)> method_ptr = nullptr;

        if (method == "full") {
            method_ptr = full;
        } else if (method == "fermat") {
            method_ptr = fermat;
        } else if (method == "polflo") {
            method_ptr = polflo;
        } else if (method == "brent") {
            method_ptr = brent;
        } else if (method == "pollard") {
            method_ptr = pollard;
        } else if (method == "brentmt") {
            method_ptr = brentmt;
        } else {
            std::cout << "Unknown method:" + method << "\n";
            return 1;
        }
        auto input_number = mpz_class(number.data());
        if (input_number == 1) {
            std::cout << "Found 1 divisor\n1\n";
            return 0;
        } else if (input_number < 1) {
            std::cout << "Bad input\n";
            return 1;
        }
        timer t;
        t.begin();
        auto result = method_ptr(input_number);
        t.end();
        std::cout << "DURATION:" << t.duration() << "\n";

        std::cout << "Found " << result.size() << " divisors\n";
        std::sort(result.begin(), result.end());
        for (std::size_t i = 0; i < 100 && i < result.size(); i++) {
            std::cout << result[i] << "\n";
        }
        if (result.size() > 100) {
            std::cout << "... (" << result.size() - 100 << " more divisors) ...\n";
        }
        mpz_class check = 1;
        for (auto i : result) {
            if (!mpz_probab_prime_p(i.get_mpz_t(), 50)) {
                std::cout << "INCORRECT NON PRIME ANSWER:" << i << "\n";
                return 1;
            }
            check *= i;
        }
        if (check != input_number) {
            std::cout << "INCORRECT ANSWER!\n";
        }

    } catch (...) {
        std::cout << "Error!\n";
        return 1;
    }
    return 0;
    
}
