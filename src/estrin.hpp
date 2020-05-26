#pragma once

/**
 * Evaluate polynomial P(x) using Estrin's scheme.
 *
 * @param x variable
 * @param c coefficients (c[0], c[1], ..., c[len-1])
 *
 * @return value of P(x)
 *
 * @note Author: Alexander Voigt
 */
template <unsigned len>
double estrin(double x, const double c[len])
{
   if constexpr (len == 0)
      return 0.0;
   if constexpr (len == 1)
      return c[0];
   if constexpr (len == 2)
      return c[0] + x*c[1];
   if constexpr (len == 3)
      return c[0] + x*c[1] + x*x*c[2];
   if constexpr (len == 4)
      return c[0] + x*c[1] + x*x*(c[2] + x*c[3]);

   constexpr unsigned nd = 1 + len/2;
   double d[nd];

   for (unsigned i = 0; i < nd - 1; ++i)
      d[i] = c[2*i] + c[2*i + 1]*x;

   if constexpr (len % 2) {
      d[nd - 1] = c[len - 1];
      return estrin<nd>(x*x, d);
   } else {
      return estrin<nd-1>(x*x, d);
   }
}
