#include "list.h"
#include "QueueSystem.h"
#include "boolean.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>




/*********** PROTOTYPE ****************/
/**** Predikat untuk test keadaan LIST  ****/
boolean ListEmpty (List L){
/* Mengirim true jika List Kosong */
	if(First(L)==Nil){
		return true;
	}
}

/**** Konstruktor/Kreator List Kosong ****/
void CreateList (List * L){
	/* IS : L sembarang */
    /* FS : Terbentuk List Kosong */
	First(*L)=Nil;
}

/**** Manajemen Memory ****/
addressList AlokasiList (String Penyakit){
/*Mengirimkan addressList hasil alokasi sebuah elemen 
  Jika alokasi berhasil, maka addressList != Nil, 	   
  dan misalnya menghasilkan P, maka Info(P) = X, Next(P) = Nil 
  Jika alokasi gagal, mengirimkan Nil */
   addressList P;
   P=(addressList)malloc(sizeof(ElmtList));  //Memesan memori
   if(P!=Nil) { 
     strcpy(P->info,Penyakit);
	 Next(P)=Nil;
	 //jika pemesanan memori sukses maka P->info = X dan P->Next = NULL
   }
   return P;	   
}

void DeAlokasiList (addressList P){
	/* IS : P terdefinisi */
	/* FS : P dikembalikan ke sistem */
	/* Melakukan dealokasi / pengembalian addressList P ke system */
	Next(P)=Nil; //Jika dealloc, maka P->Next tidak boleh menunjuk kemanapun (NULL)	
    free(P);     //Dealloc P
}

void InsVFirst (List * L, String X){
/* IS : L mungkin Kosong */
/* FS : melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil 
   Jika alokasi gagal maka element pertama tidak ditambahkan*/
   addressList P = AlokasiList(X);
   if(P!=Nil) { 
      InsertFirst(&(*L),P);
    }
}

void InsVLast (List * L, String Penyakit){
/* IS : L mungkin Kosong */
/* FS : melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir (elemen terakhir adalah yang baru) */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal IS = FS */
	addressList P = AlokasiList(Penyakit);
	if(P!=Nil){
		InsertLast(&(*L),P);
	}
}



///**** Penghapusan Elemen ****/
void DelAll (List * L){
	/* Delete semua elemen list dan alamat elemen di dealokasi */
	
	while(First(*L)!=Nil){
		DelVFirst (&(*L));
	}
}

void DelVFirst (List * L){
/* IS : L TIDAK Kosong */
/* FS : Elemen pertama List dihapus, nilai info disimpan ke X */
/* 	dan alamat elemen pertama di dealokasi 
    Nilai dari info akan ditampung ke X , lalu dealokasi dari memori*/

  addressList Pertama;
  
  DelFirst(&(*L),&Pertama); 		
  DeAlokasiList(Pertama);
	
}

void DelFirst (List * L, addressList * P){
/* IS : L TIDAK kosong */
/* FS : P adalah alamat elemen pertama list sebelum penghapusan */
/*	elemen list berkurang satu (mungkin menjadi kosong) */
/* First elemen yang baru adalah suksessor elemen pertama yang lama 
   jika element pertama sudah berganti maka yang menunjuk ke next nya diisi NULL*/

	*P = First(*L);
	First(*L) = First(*L)->next;
	Next(*P)=Nil;		
}

/**** PRIMITIF BERDASARKAN ALAMAT ****/
/**** Penambahan elemen berdasarkan alamat ****/
void InsertFirst (List * L, addressList P){
/* IS : L sembarang, P sudah dialokasi */
/* FS : menambahkan elemen ber-addressList P sebagai elemen pertama */
	Next(P)=Nil;
    First(*L)=P;
}

void InsertAfter (List * L, addressList P, addressList Prec){
/* IS : Prec pastilah elemen List dan bukan elemen terakhir */
/*	P sudah dialokasi */
/* FS : Insert P sebagai elemen sesudah elemen beralamat Prec */
	Next(P)=Next(Prec);
	Next(Prec)=P;	
}

void InsertLast (List * L, addressList P){
/* IS : L sembarang, P sudah dialokasi */
/* FS : P ditambahkan sebagai elemen terakhir yang baru */
/* Pertama, cek dulu apakah list kosong atau tidak, jika kosong
   maka yang dinnputkan akan menjadi element list pertama. Dan 
   jika sudah ada list sebelumnya maka cari sampai element list terakhir
   atau X->next = NULL. lalu tunjukan atau sambungkan X->next tersebut ke P (alokasi baru)*/
   	addressList X = First(*L);
	if(First(*L)==Nil){
		InsertFirst(&(*L),P);
	}else{	
		while(Next(X)!=Nil){
			X = Next(X);
		}
	  Next(X) = P;
	}
}


///**** PROSES SEMUA ELEMEN LIST  ****/
void PrintDaftarPenyakit (addressList L){
/* IS : L mungkin kosong */
/* FS : Jika List tidak kosong, semua info yang disimpan pada elemen list */
/*	diprint. Jika list kosong, hanya menuliskan "List Kosong" */
	
	if(L == Nil){
		printf("\nList Kosong");
	}else{
		while(L->next != Nil){
			printf("%s,",L->info);
			L=L->next;
		}printf("%s\n",L->info);
	}
}

int NbElmt (List L){
/* Mengirimkan banyaknya elemen list, mengirimkan 0 jika list kosong */
	addressList P=First(L);
	int totalElmt=0;
	
	if(P==Nil){
		return totalElmt;
	}else{
		while(Next(P)!=Nil){
			totalElmt++;
			P=Next(P);
		}totalElmt++;
	}
	
	return totalElmt;
}


