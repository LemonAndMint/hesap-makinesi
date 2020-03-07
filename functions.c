#include <stdlib.h>
#include <stdio.h>

typedef struct islem{
  int deger; //#TODO degerini float yap
  int konum; //agaca bu degere gore yerlestirilir
  struct islem * sol_dugum;
  struct islem * sag_dugum;
} Islem;

Islem * islem_olustur( int deger , int konum ){
  Islem * yeni_dugum = ( Islem * )malloc( sizeof( Islem ) );
  yeni_dugum->deger = deger;
  yeni_dugum->konum = konum;
  yeni_dugum->sag_dugum = NULL;
  yeni_dugum->sol_dugum = NULL;
  return yeni_dugum;
}

void agaca_ekle( Islem ** islem , int deger , int konum ){
    if ( *islem == NULL ){
      *islem = islem_olustur( deger , konum );
    }
    else if ( (*islem)->konum > konum ){
      agaca_ekle( &((*islem)->sol_dugum) , deger , konum ); 
    }
    else{
      agaca_ekle( &((*islem)->sag_dugum) , deger , konum ); 
    }
}

void inorder_tra( Islem * islem ){
  if( islem != NULL ){
    inorder_tra( islem->sol_dugum );
    printf("%d ", islem->deger );
    inorder_tra( islem->sag_dugum );
  }
}

// AYIRICI +

int * oncelik_belirleme( char fonksiyon[] ){
  int parantez_counter = 0;
  int i = 0; 
  int * oncelik_array = ( int * )malloc( sizeof( fonksiyon ) * sizeof( int ) * 5 );
  for( ; fonksiyon[i] != '#' ; i++ ){
    switch ( fonksiyon[i] ){
      case '+':
      case '-': // #TODO negatif sayılar için lan durumu da ekle
        //*(oncelik_array + i) = parantez_counter ? 1 : 4;
        *(oncelik_array + i) = 1 ;
        break;
      case '(':
        parantez_counter++;
        *(oncelik_array + i) = 5;
        break;
      case ')':
        parantez_counter--;
        *(oncelik_array + i) = 5;
        break;
      case '*':
      case '/':
        *(oncelik_array + i) = 3;
        break;
      case '^':
        *(oncelik_array + i) = 2;
      break;
      default:
        *(oncelik_array + i) = 0;
        break;
    }
  }
  *(oncelik_array + i) = 6;
  return oncelik_array;
}

char * ree_array( char array[] ){
  free(array);
  return array = (char *)malloc( sizeof( char ) * 10 );
}

void rakam_ekle( Islem ** islem , char fonksiyon[] , int * oncelik_array ){
  char * sayilar = (char *)malloc( sizeof( char ) * sizeof( fonksiyon ) );
  int k = 0;
  for( int i = 0 ; *(oncelik_array + i) != 6 ; i++ ){
    if( *(oncelik_array + i) == 0 ){
      sayilar[k++] = fonksiyon[i];
      if( *(oncelik_array + i + 1 ) != 0 ){
        agaca_ekle( islem , atoi(sayilar) , i );
        sayilar = ree_array( sayilar );
        k = 0;
      }
    }
  }
}

void islem_ekle( Islem ** islem , char fonksiyon[] , int * oncelik_array ){
  for( int k = 1 ; k < 5 ; k++ ){
    for( int i = 0 ; *(oncelik_array + i) != 6 ; i++ ){
      if( *(oncelik_array + i) == k ){
        agaca_ekle( islem , fonksiyon[i] , i );
      }
    }
  }
  rakam_ekle( islem , fonksiyon , oncelik_array );
}

// AYIRICI -

int fonksiyon_sonucu ( Islem * islem ){
  if( islem != NULL ){
    int deger1 = fonksiyon_sonucu( islem->sol_dugum );
    int deger2 = fonksiyon_sonucu( islem->sag_dugum );
    if( deger1 != 0 || deger2 != 0 ){
    int sonuc = 0;
      switch ( islem->deger ){
        case '+':
          sonuc = deger1 + deger2;
          break;
        case '-': 
          sonuc = deger1 - deger2;
          break;
        case '*':
          sonuc = deger1 * deger2;
          break;
        case '/':
          sonuc = deger1 / deger2;
          break;
      }
      return sonuc;
    }
    else{
      return islem->deger;
    }
  }
  else{
    return 0;
  }
}