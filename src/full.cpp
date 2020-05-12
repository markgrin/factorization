#include "full.hpp"

std::vector<mpz_class> full (mpz_class number) {

    mpz_class border = sqrt(number) + 1;

    mpz_class check = 0;
    std::vector<mpz_class> divisors;

    while (check <= border) {
        check = check + 1;
        if (!mpz_probab_prime_p(check.get_mpz_t(), 50)) {
            continue ;
        }
        if (number % check == 0) {
            divisors.push_back(check);
            number = number / check;
            check -= 1; // Retry
        }
    }
    if (number != 1) {
        divisors.push_back(number);
    }
    return divisors;
}
