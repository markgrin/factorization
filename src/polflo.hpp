#ifndef HPP_7B3F3B4DB45A4E29AEEBD3371B283C64

#define HPP_7B3F3B4DB45A4E29AEEBD3371B283C64

#include <gmpxx.h>
#include <vector>

/**
 * Факторизация методом Полларда-Флойда
 */
std::vector<mpz_class> polflo (mpz_class number);

/**
 * Факторизация методом Брента
 */
std::vector<mpz_class> brent (mpz_class number);

#endif // HPP_7B3F3B4DB45A4E29AEEBD3371B283C64

