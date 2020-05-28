#pragma once

/**
 * Evaluate polynomial P(z) for complex z and real coefficients using
 * Horner's scheme.  Algorithm based on [Knuth, The Art of Computer
 * Programming II, Section 4.6.4, Eq. (3)].
 *
 * @param z variable
 * @param c coefficients (c[0], c[1], ..., c[N-1])
 * @tparam T real type
 * @tparam N number of coefficients
 *
 * @return value of P(z)
 *
 * @note Author: Alexander Voigt
 */
template <typename T, int N>
std::complex<T> horner(const std::complex<T>& z, const T (&c)[N]) noexcept
{
   static_assert(N >= 2, "more than two coefficients required");

   const T x = std::real(z);
   const T y = std::imag(z);
   const T r = x + x;
   const T s = x * x + y * y;
   T a = c[N - 1], b = c[N - 2];

   for (int i = N - 3; i >= 0; --i) {
      const T t = a;
      a = b + r * a;
      b = c[i] - s * t;
   }

   return std::complex<T>(x * a + b, y * a);
}
