double horner(double x, const double* c, int len)
{
   double p = 0.0;
   while (len--)
      p = p*x + c[len];
   return p;
}
