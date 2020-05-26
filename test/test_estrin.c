#include "estrin.h"
#include <stdio.h>


#define CHECK(cond)                                     \
   do {                                                 \
      if (!(cond)) {                                    \
         printf("FAILED test in line %d\n", __LINE__);  \
         errors++;                                      \
      }                                                 \
   } while (0)


unsigned errors = 0;


void test_empty()
{
   CHECK(estrin(1.0, 0, 0) == 0.0);
}


int main()
{
   test_empty();

   return errors;
}
