#include <stdio.h>
#include <stdlib.h>
 

float bagil_yuzdelik_hata( float onceki_sonuc , float simdiki_sonuc ){
  return (fabs(simdiki_sonuc - onceki_sonuc )) / simdiki_sonuc * 100;
}

void araligi_ikiye_bolme( Islem * islem , float alt , float ust , int iter , float hata ){  
  float oncekir;
  float mhata;
  float r;
  float altsonuc;
  float ustsonuc;
  float rsonuc;
  printf("\ti\talt\tust\tr\tf(alt)\tf(ust)\tf(r)\tbagilhata\t");
  for( int i = 0 ; i < iter || mhata > hata ; i++ ){ //#FIXME iter ve hata degerlerinden biri girildiğinde de calisabilecek bicimde kodu duzenle
    altsonuc = hesaplayici( islem , alt );
    ustsonuc = hesaplayici( islem , ust );
    if( altsonuc * ustsonuc > 0 ){
      printf(" alt ve ustun isaretlerinin farkli olmasi gerek ");
      break;
    }
    else{
      r = (alt + ust) / 2;
      rsonuc = hesaplayici( islem , r );
      mhata = i != 0 ? bagil_yuzdelik_hata( oncekir , r ) : mhata; 
      printf("\n\t%d\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t\n", i , alt , ust , r , altsonuc , ustsonuc , rsonuc ,mhata );   
      if( altsonuc * rsonuc > 0 ){
        oncekir = r;
        alt = r;
      }
      else if ( ustsonuc * rsonuc > 0 ){
        oncekir = r;
        ust = r;
      }
    }
  }
}

void aib_cagirici( Islem * islem ){
  float alt; 
  float ust;
  int iter;
  float hata ;
  scanf("%f", &alt);
  scanf("%f", &ust);
  scanf("%d", &iter);
  scanf("%f", &hata);
  araligi_ikiye_bolme( islem , alt , ust , iter , hata );
}