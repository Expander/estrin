#include "estrin.h"
#include "horner.h"
#include "stopwatch.hpp"
#include <array>
#include <cstdio>


#define NELEMS(a) (sizeof(a)/sizeof(a[0]))


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


template <unsigned long N>
std::array<double, N> make_coeffs()
{
   std::array<double, N> coeffs;
   unsigned long i = 0;

   for (auto& c: coeffs)
      c = i++;

   return coeffs;
}


void test_bench()
{
   const unsigned long n_evals = 10000;
   constexpr unsigned long N = 100000;
   double x = 2.0;

   const auto coeffs = make_coeffs<N>();

   const double estrin_t = bench_fn(::estrin, x, &coeffs[0], coeffs.size(), n_evals);
   const double horner_t = bench_fn(::horner, x, &coeffs[0], coeffs.size(), n_evals);

   printf("Benchmark results\n");
   printf("-----------------\n");
   printf("Evaluations of a polynomial with %lu coefficients, %lu times\n", N, n_evals);
   printf("  Horner (C): %f ms per evaluation\n", horner_t);
   printf("  Estrin (C): %f ms per evaluation\n", estrin_t);
}


int main()
{
   test_bench();
}
