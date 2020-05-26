#include "estrin.h"
#include "horner.h"
#include "stopwatch.hpp"
#include <cstdio>


#define CHECK(cond)                                     \
   do {                                                 \
      if (!(cond)) {                                    \
         printf("FAILED test in line %d\n", __LINE__);  \
         errors++;                                      \
      }                                                 \
   } while (0)


#define CHECK_EQ(lhs,rhs)                               \
   do {                                                 \
      if (!((lhs) == (rhs))) {                          \
         printf("FAILED test in line %d", __LINE__);    \
         printf(": lhs (%f) != rhs (%f)\n", lhs, rhs);  \
         errors++;                                      \
      }                                                 \
   } while (0)


#define NELEMS(a) (sizeof(a)/sizeof(a[0]))


int errors = 0;


void test_empty()
{
   CHECK(estrin(1.0, 0, 0) == 0.0);
}


void test_non_empty()
{
   double x = 2.0;
   {
      double c[] = { 2.0 };
      CHECK_EQ(estrin(x, c, NELEMS(c)), horner(x, c, NELEMS(c)));
   }
   {
      double c[] = { 2.0, 3.0 };
      CHECK_EQ(estrin(x, c, NELEMS(c)), horner(x, c, NELEMS(c)));
   }
   {
      double c[] = { 2.0, 3.0, 4.0 };
      CHECK_EQ(estrin(x, c, NELEMS(c)), horner(x, c, NELEMS(c)));
   }
   {
      double c[] = { 2.0, 3.0, 4.0, 5.0 };
      CHECK_EQ(estrin(x, c, NELEMS(c)), horner(x, c, NELEMS(c)));
   }
   {
      double c[] = { 2.0, 3.0, 4.0, 5.0, 6.0 };
      CHECK_EQ(estrin(x, c, NELEMS(c)), horner(x, c, NELEMS(c)));
   }
}


template <class F>
double bench_fn(F f,
                double x,
                const double* c,
                unsigned long len,
                unsigned long n_evals)
{
   bench::Stopwatch sw;
   sw.start();

   for (unsigned long n = 0; n < n_evals; ++n)
      f(x, c, len);

   sw.stop();

   return sw.get_time_in_milliseconds() / n_evals;
}


void test_bench()
{
   const unsigned long n_evals = 10000;
   const unsigned long N = 100000;
   double x = 2.0;
   double coeffs[N];

   for (unsigned i = 0; i < N; ++i)
      coeffs[i] = i;

   const double estrin_t = bench_fn(::estrin, x, coeffs, NELEMS(coeffs), n_evals);
   const double horner_t = bench_fn(::horner, x, coeffs, NELEMS(coeffs), n_evals);

   printf("benchmark results\n");
   printf("  Horner: %f ms\n", horner_t);
   printf("  Estrin: %f ms\n", estrin_t);
}


int main()
{
   test_empty();
   test_non_empty();
   test_bench();

   return errors;
}
