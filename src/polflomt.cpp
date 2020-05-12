#include "polflo.hpp"

#include <iostream>
#include <thread>
#include <atomic>
#include "common.hpp"

namespace {

mpz_class func_1 (mpz_class number) {
    return number * number + 1;
}

mpz_class func_2 (mpz_class number) {
    return number * number * number + number * number + 1;
}

mpz_class func_3 (mpz_class number) {
    return number * number * number + 1;
}

mpz_class func_4 (mpz_class number) {
    return number * number * number * number + 1;
}

mpz_class func_5 (mpz_class number) {
    return number * number * number * number + number * number * number + 1;
}

mpz_class func_6 (mpz_class number) {
    return number * number * number * number + number * number * number + number * number + 1;
}

mpz_class func_7 (mpz_class number) {
    return number * number * number * number * number + 1;
}

mpz_class func_8 (mpz_class number) {
    return number * number * number * number * number + number * number * number * number + 1;
}

mpz_class func_9 (mpz_class number) {
    return number * number * number * number * number + number * number * number * number + number * number * number + 1;
}

mpz_class func_10 (mpz_class number) {
    return number * number * number * number * number + number * number * number * number + number * number * number + number * number + 1;
}

mpz_class func_11 (mpz_class number) {
    return number * number * number * number * number * number + 1;
}

mpz_class func_12 (mpz_class number) {
    return number * number * number * number * number * number + number * number + 1;
}

std::function<mpz_class(mpz_class)> functions[] = {func_1, func_2, func_3, func_4, func_5, func_6, func_7, func_8, func_9, func_10, func_11, func_12};

void find_one_brent (mpz_class number, std::function<mpz_class(mpz_class)> func, std::atomic_char& stopper, mpz_class& result) {
    char stop = 0;
    if (mpz_probab_prime_p(number.get_mpz_t(), 50) > 0) {
        if (stopper.compare_exchange_weak(stop, 1)) {
            result = number;
        }
        return ;
    }

    mpz_class x = 1;
    mpz_class z = 1;
    mpz_class p = 1;
    mpz_class k = 0;
    mpz_class two_power = 1;
    mpz_class tries = 1000 * 1000 * 1;
    while(p <= 1 && tries) {
        if (stopper.load()) { // Нашел другой поток
            return ;
        }
        tries = tries - 1;
        k = k + 1;
        if (two_power == k) {
            z = x;
            two_power = two_power * 2;
        }
        x = func(x) % number;
        mpz_class diff = z - x;
        diff = (diff >= 0 ? diff : diff*-1);
        p = gcd(number, diff % number);
    }
    if (number == p) {
        return ;
    }
    if (stopper.compare_exchange_weak(stop, 1)) {
        result = p;
    }
}

mpz_class find_one_mt(mpz_class number) {
    mpz_class result = 0;
    std::atomic_char stopper;
    stopper.exchange(0);
    std::vector<std::thread> threads;
    for (auto& func : functions) {
        if (threads.size() >= std::thread::hardware_concurrency() || stopper.load()) {
            break ;
        }
        threads.emplace_back([&number, &result, &stopper, &func](){
            find_one_brent(number, func, stopper, result);
        });
    }
    for (auto& thread : threads) {
        thread.join();
    }
    if (!result) {
        result = number;
    }
    return result;
}

} // namespace

std::vector<mpz_class> brentmt (mpz_class number) {
    return apply_method(find_one_mt, number);
}
