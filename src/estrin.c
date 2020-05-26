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
   switch (len) {
   case 0: return 0.0;
   case 1: return c[0];
   case 2: return c[0] + x*c[1];
   case 3: return c[0] + x*c[1] + x*x*c[2];
   case 4: return c[0] + x*c[1] + x*x*(c[2] + x*c[3]);
   }

   unsigned nd = 1 + len/2;
   double d[nd];

   for (unsigned i = 0; i < nd - 1; ++i)
      d[i] = c[2*i] + c[2*i + 1]*x;

   if (len % 2)
      d[nd - 1] = c[len - 1];
   else
      --nd;

   return estrin(x*x, d, nd);
}
