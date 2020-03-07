#include <stdio.h>
#include "functions.c"

int main( int argc, char * argv[] ){
 Islem * islem = NULL;
 int * oncelik = oncelik_belirleme( argv[1] );
 int * fonksiyon = (int*)malloc(sizeof(int)*3);
 islem_ekle( &islem , argv[1] , oncelik );
 //inorder_tra( islem );
 printf( "%d" , fonksiyon_sonucu( islem ) );
}