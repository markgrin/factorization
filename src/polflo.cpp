#include "polflo.hpp"

#include <iostream>
#include "common.hpp"

namespace {

mpz_class func_1 (mpz_class number) {
    return number * number + 1;
}

mpz_class func_2 (mpz_class number) {
    return number * number * number + number * number + 2;
}

mpz_class func_3 (mpz_class number) {
    return number * number * number * number + 1;
}

mpz_class find_one_polflo (mpz_class number) {
    if (mpz_probab_prime_p(number.get_mpz_t(), 50) > 0) {
        return number;
    }
    std::function<mpz_class(mpz_class)> fncs[3] = {func_1, func_2, func_3};

    for (auto fnc : fncs) {
        mpz_class x = 1;
        mpz_class z = x;
        mpz_class y = x;
        mpz_class p = 1;
        while(p <= 1) {
            x = fnc(x) % number;
            y = fnc(z) % number;
            z = fnc(y) % number;
            mpz_class diff = z - x;
            diff = (diff >= 0 ? diff : diff*-1);
            p = gcd(number, diff % number);
        }
        if (p != number) {
            return p;
        }
    }
    return number;
}

mpz_class find_one_brent (mpz_class number) {
    if (mpz_probab_prime_p(number.get_mpz_t(), 50) > 0) {
        return number;
    }
    std::function<mpz_class(mpz_class)> fncs[3] = {func_1, func_2, func_3};

    for (auto fnc : fncs) {
        mpz_class x = 1;
        mpz_class z = 1;
        mpz_class p = 1;
        mpz_class k = 0;
        mpz_class two_power = 1;
        mpz_class tries = 1000 * 1000 * 10;
        while(p <= 1 && tries) {
            tries = tries - 1;
            k = k + 1;
            if (two_power == k) {
                z = x;
                two_power = two_power * 2;
            }
            x = fnc(x) % number;
            mpz_class diff = z - x;
            diff = (diff >= 0 ? diff : diff*-1);
            p = gcd(number, diff % number);
        }
        if (p != number) {
            return p;
        }
    }
    return number;
}

} // namespace

std::vector<mpz_class> polflo (mpz_class number) {
    return apply_method(find_one_polflo, number);
}

std::vector<mpz_class> brent (mpz_class number) {
    return apply_method(find_one_brent, number);
}
