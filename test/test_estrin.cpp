#include "estrin.h"
#include "horner.h"
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


int main()
{
   test_empty();
   test_non_empty();

   return errors;
}
