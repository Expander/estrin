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


template <unsigned long N, unsigned long N_EVALS>
void test_bench()
{
   double x = 2.0;

   const auto coeffs = make_coeffs<N>();

   const double estrin_t = bench_fn(::estrin, x, &coeffs[0], coeffs.size(), N_EVALS);
   const double horner_t = bench_fn(::horner, x, &coeffs[0], coeffs.size(), N_EVALS);

   printf("Evaluations of a polynomial with %lu coefficients\n", N);
   printf("  Horner (C): %2.1e ms%s\n", horner_t, (horner_t < estrin_t ? " <--": ""));
   printf("  Estrin (C): %2.1e ms%s\n", estrin_t, (horner_t < estrin_t ? "": " <--"));
}


int main()
{
   printf("Benchmark results\n");
   printf("-----------------\n");

   test_bench<1     , 1000000>();
   test_bench<10    , 1000000>();
   test_bench<100   , 1000000>();
   test_bench<1000  ,  100000>();
   test_bench<10000 ,  100000>();
   test_bench<100000,   10000>();
}
