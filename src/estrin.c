/**
 * Evaluate polynomial P(x) using Estrin's scheme.
 *
 * @param x variable
 * @param c coefficients (c[0], c[1], ..., c[len-1])
 * @param len number of coefficients
 *
 * @return value of P(x)
 *
 * @note Author: Alexander Voigt
 */
double estrin(double x, const double* c, unsigned len)
{
   if (len == 0)
      return 0.0;

   unsigned nd = 1 + len/2;
   double d[nd];

   for (unsigned i = 0; i < nd - 1; ++i)
      d[i] = c[2*i] + c[2*i + 1]*x;

   if (len % 2)
      d[nd - 1] = c[len - 1];
   else
      --nd;

   return len <= 2 ? d[0] : estrin(x*x, d, nd);
}
