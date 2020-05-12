#ifndef HPP_860EFB633B3C490FB850560907C5A7DD

#define HPP_860EFB633B3C490FB850560907C5A7DD

#include <gmpxx.h>
#include <functional>
#include <vector>

/**
 * Применяет метод выделения делителя, для получения факторизации числа
 *
 * @param method Функция возвращающая делитель
 * @param number Число для факторизации
 *
 * @return Вектор факторизации числа number
 */
std::vector<mpz_class> apply_method(std::function<mpz_class(mpz_class)> method, mpz_class number);

#endif // HPP_860EFB633B3C490FB850560907C5A7DD
