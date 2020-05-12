#include "pollard.hpp"

#include "common.hpp"

#include <iostream>

namespace {

mpz_class find_one (mpz_class number) {
    if (mpz_probab_prime_p(number.get_mpz_t(), 50) > 0) {
        return number;
    }
    std::vector<mpz_class> primes;
    mpz_class B = 1000;
    for (mpz_class i = 2; i < B; i++) {
        if (mpz_probab_prime_p(i.get_mpz_t(), 50) > 0) {
            primes.push_back(i);
        }
    }
    mpz_class k = 1;
    for (auto const & prime : primes) {
        k = k * prime;
    }

    std::size_t counter = 0;
    std::size_t tries = 1000 * 1000;
    while (counter < tries && counter < primes.size()) {
        mpz_class a = primes[counter];
        mpz_class p = gcd(a, number);
        if (p > 1) {
            return p;
        }
        mpz_class powered = 1;
        mpz_powm(powered.get_mpz_t(), a.get_mpz_t(), k.get_mpz_t(), number.get_mpz_t());
        powered = (powered + number - 1) % number;
        p = gcd(number, powered);
        if (p > 1 && p < number) {
            return p;
        }
        counter = counter + 1;
    }
    return number;
}

} // namespace


std::vector<mpz_class> pollard (mpz_class number) {
    return apply_method(find_one, number);
}

