#include "estrin.h"
#include "estrin.hpp"
#include "horner.h"
#include "stopwatch.hpp"
#include <array>
#include <cstdio>


#define NELEMS(a) (sizeof(a)/sizeof(a[0]))


template <class T>
inline void do_not_optimize(const T& value)
{
   asm volatile("" : : "r,m"(value) : "memory");
}


template <class F>
double bench_fn(F f, unsigned long n_evals)
{
   bench::Stopwatch sw;
   sw.start();

   for (unsigned long n = 0; n < n_evals; ++n)
      do_not_optimize(f());

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

   auto estrin_f = [&] () {
      return ::estrin(x, &coeffs[0], coeffs.size());
   };

   auto estrin_t = [&] () {
      return estrin<N>(x, &coeffs[0]);
   };

   auto horner_f = [&] () {
      return ::horner(x, &coeffs[0], coeffs.size());
   };

   const double time_estrin_f = bench_fn(estrin_f, N_EVALS);
   const double time_estrin_t = bench_fn(estrin_t, N_EVALS);
   const double time_horner_f = bench_fn(horner_f, N_EVALS);

   printf("Evaluations of a polynomial with %lu coefficients\n", N);
   printf("  Horner (C)  : %2.1e ms%s\n", time_horner_f, (time_horner_f < time_estrin_f ? " <--": ""));
   printf("  Estrin (C)  : %2.1e ms%s\n", time_estrin_f, (time_horner_f < time_estrin_f ? "": " <--"));
   printf("  Estrin (C++): %2.1e ms  \n", time_estrin_t);
}


int main()
{
   printf("Benchmark results\n");
   printf("-----------------\n");

   test_bench<1     , 1000000>();
   test_bench<2     , 1000000>();
   test_bench<3     , 1000000>();
   test_bench<4     , 1000000>();
   test_bench<5     , 1000000>();
   test_bench<10    , 1000000>();
   test_bench<100   , 1000000>();
   test_bench<1000  ,  100000>();
   test_bench<10000 ,  100000>();
   test_bench<100000,   10000>();
}
