#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//#TODO trigonometrik, logaritmik durumları da ekle

typedef struct islem{
  float deger;
  int konum; //agaca bu degere gore yerlestirilir
  struct islem * sol_dugum;
  struct islem * sag_dugum;
} Islem;

Islem * islem_olustur( float deger , int konum ){
  Islem * yeni_dugum = ( Islem * )malloc( sizeof( Islem ) );
  yeni_dugum->deger = deger;
  yeni_dugum->konum = konum;
  yeni_dugum->sag_dugum = NULL;
  yeni_dugum->sol_dugum = NULL;
  return yeni_dugum;
}

void agaca_ekle( Islem ** islem , float deger , int konum ){
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
    printf("%f ", islem->deger );
    inorder_tra( islem->sag_dugum );
  }
}

// AYIRICI +

int sizeofarray( char fonksiyon[] ){
  int i = 0;
  for( ; fonksiyon[i] != '#' ; i++ ){
  }
  return i;
}

int * oncelik_belirleme( char fonksiyon[] ){
  int parantez_counter = 0;
  int i = 0; 
  int * oncelik_array = ( int * )malloc( sizeofarray( fonksiyon ) * sizeof( int ) *5);
  for( ; fonksiyon[i] != '#' ; i++ ){
    switch ( fonksiyon[i] ){
      case '+':
      case '-': 
        //*(oncelik_array + i) = parantez_counter ? 1 : 4;
        *(oncelik_array + i) = 1 ;
        break;
      case '(':
        parantez_counter++;
        *(oncelik_array + i) = 5;
        break;
      case ')':
        parantez_counter--;
        *(oncelik_array + i) = 6;
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
  *(oncelik_array + i) = 7;
  return oncelik_array;
}

char * ree_array( char array[] ){
  free(array);
  return array = (char *)malloc( sizeof( char ) * 10 );
}

void rakam_ekle( Islem ** islem , char fonksiyon[] , int * oncelik_array , int baslangic , int bitis ){
  char * rakamlar = (char *)malloc( sizeof( char ) * sizeofarray( fonksiyon ) );
  int k = 0;
  int psayici = 0;
  for( int i = baslangic ; *(oncelik_array + i) != 7 && i < bitis ; i++ ){
    switch( *(oncelik_array + i) ){
      case 0:
        if( !psayici ){
          rakamlar[k++] = fonksiyon[i];
          if( *(oncelik_array + i + 1 ) != 0 ){
            agaca_ekle( islem , atof(rakamlar) , i );
            rakamlar = ree_array(rakamlar);
            k = 0;
          }
        }
        break;
      case 5:
        psayici++;
        break;
      case 6:
        psayici--;
        break;
      default:
        break;
    }
  }
}

void islem_ekle( Islem ** islem , char fonksiyon[] , int * oncelik_array , int baslangic , int bitis ){
  int psayici = 0;
  for( int k = 1 ; k < 5 ; k++ ){
    for( int i = baslangic ; *(oncelik_array + i) != 7 && i < bitis ; i++ ){
      if(*(oncelik_array + i) == k){
        if( psayici == 0 ){
          agaca_ekle( islem , fonksiyon[i] , i );
        }
      }
      else{
        switch(*(oncelik_array + i)){
          case 5:
            psayici++;
            break;
          case 6:
            psayici--;
            break;
          default:
            break;
        }
      }
    }
  }
  rakam_ekle( islem , fonksiyon , oncelik_array , baslangic , bitis );
  psayici = 0;
  int pbaslangic = baslangic;
  int pbitis = bitis;
  for( int i = baslangic ; *(oncelik_array + i) != 7 && i < bitis ; i++ ){
    switch(*(oncelik_array + i)){
      case 5:
        psayici++;
        pbaslangic = psayici == 1 ? i + 1 : pbaslangic;
        break;
      case 6:
        psayici--;
        pbitis = psayici == 0 ? i : pbitis;
        if( psayici == 0){
          islem_ekle( islem , fonksiyon , oncelik_array , pbaslangic , pbitis );
        }
        break; 
    }
  }
}

// AYIRICI -

float fonksiyon_sonucu ( Islem * islem , float x ){
  if( islem != NULL ){
    float deger1 = fonksiyon_sonucu( islem->sol_dugum , x );
    float deger2 = fonksiyon_sonucu( islem->sag_dugum , x );
    if( deger1 != 0 || deger2 != 0 ){
    deger1 = deger1 == 0 ? x : deger1;
    deger2 = deger2 == 0 ? x : deger2;
    float sonuc = 0;
      switch ( (int) islem->deger ){
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
        case '^':
          sonuc = pow( deger1, deger2 );
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

Islem * islem_olusturucu( char * fonksiyon  ){
  Islem * islem = NULL;
  int * oncelik = oncelik_belirleme( fonksiyon );   
  islem_ekle( &islem , fonksiyon , oncelik , 0 , sizeofarray( fonksiyon ));
  return islem;
}

float hesaplayici( Islem * islem , float x){
  return fonksiyon_sonucu( islem , x);
}
