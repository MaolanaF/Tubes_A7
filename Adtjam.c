/* Body ADT Jam 
   Referensi https://github.com/miftahulmahfuzh/ADT.git modified by */

#include "Adtjam.h"

/* -----------konstruktor Jam--------- */

Jam MakeJam(int H, int M, int S)
/* Membentuk Jam dari H, M, S yg valid */
{ 
  /* Kamus Lokal */
   Jam J1;
  /* Algoritma */
   Hour(J1) = H;
   Minute(J1) = M;
   Second(J1) = S;
   return J1;
}

/*------------validator Jam------------*/
/* Mengirim true jika H,M,S dapat membentuk Jam yang valid */
boolean IsJValid(Jam J){
   return ((Hour(J) >= 0 && Hour(J) <= 23) && (Minute(J) >= 0 && Minute(J) <= 59) && (Second(J) >= 0 && Second(J) <= 59));
}

/*------------Baca & Tulis jam-----------*/

void BacaJam(Jam *J)
/* I.S.   : J tak terdefinisi */
/* F.S.   : J terdefinisi dan merupakan jam valid */
/* Proses : mengulang baca komponen H, M, S sehingga membentuk J
             yang valid */
{
  /* Kamus Lokal */ 
   int H, M;
   int S = 0;
  /* Algoritma */
	printf("\t\t\t\t\tJam Kedatangan   : ");
    scanf("%d",&H);
    printf("\t\t\t\t\tMenit Kedatangan : ");
    scanf("%d",&M);

   *J = MakeJam(H,M,S);
}

void TulisJam(Jam J)
/* I.S. : J sembarang*/
/* F.S. : J ditulis ke layar dengan format HH:MM:SS */
/* Proses : Menulis ke layar */

{ 
  /* Kamus lokal */
  /* Algoritma */
  if(Hour(J)<10 && Minute(J)<10){
  	printf("0%d:0%d",Hour(J),Minute(J));
  }else if(Hour(J) < 10){
  	printf("0%d:%d",Hour(J),Minute(J));
  }else if(Minute(J)<10){
     printf("%d:0%d",Hour(J),Minute(J));
  }else{
  	printf("%d:%d",Hour(J),Minute(J));
  }

   
}

int JamToDetik(Jam J)
/* Konversi Jam menjadi detik */

{ 
  /* Kamus Lokal */
  /* Algoritma */
   return(3600 *Hour(J) + 60 *Minute(J) + Second(J));
}

Jam DetikToJam(int N)
/* Konversi detik ke Jam */

{ 
  /* Kamus Lokal */
   int sisa;
   Jam JOut;
  /* Algoritma */
   Hour(JOut) = N / 3600;
   sisa = N % 3600;
   Minute(JOut) = sisa / 60;
   Second(JOut) = sisa % 60;
   return JOut;
}
