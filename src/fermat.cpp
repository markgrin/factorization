#include "fermat.hpp"
#include "common.hpp"

namespace {

    mpz_class find_one (mpz_class number) {
        if (mpz_probab_prime_p(number.get_mpz_t(), 50) > 0) {
            return number;
        }
        if (number % 2 == 0) {
            return 2;
        }
        mpz_class left = sqrt(number);
        mpz_class full = left * left;
        if (full == number) {
            return left;
        } else if (full < number) {
            left += 1;
        }
        mpz_class x = left;
        mpz_class v = x * x - number;
        mpz_class k = 0;
        mpz_class additor = 1;
        while(true) {
            mpz_class check = sqrt(v);
            if (check * check == v) {
                return x + check;
            }
            x = x + 1;
            k += 1;
            // (x + 1)^2 = x^2 + 2x + 1
            // (x + 2)^2 = x^2 + 4x + 4
            // (x + 3)^2 = x^2 + 6x + 9
            v = v + left * 2 + k * 2 - 1;
            //v = x * x - number;
        }
        return number;
    }

} // namespace

std::vector<mpz_class> fermat (mpz_class number) {
    return apply_method(find_one, number);
}

