#include <stdio.h>
#include "fonk_derleyici.c"
#include "saycoz.c"

int main( int argc, char * argv[] ){
  Islem * islem = islem_olusturucu(argv[1]);
  aib_cagirici(islem);
  return 0;
}