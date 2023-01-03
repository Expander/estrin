/**
 * Evaluate polynomial P(x) using Horner's scheme.
 *
 * @param x variable
 * @param c coefficients (c[0], c[1], ..., c[len-1])
 * @param len number of coefficients (length of c array)
 *
 * @return value of P(x)
 */
double horner(double x, const double* c, int len)
{
   double p = 0.0;
   while (len--)
      p = p*x + c[len];
   return p;
}
