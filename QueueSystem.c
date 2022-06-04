#include "QueueSystem.h"
#include "boolean.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

/** Referensi Praktikum SDA
	Modul untuk membuat Antrian kosong, dimana nantinya head dan tail dari Queue akan bernilai Nil**/
void CreateQueue(Queue *Q){
	HEAD(*Q)=nil;
	TAIL(*Q)=nil;
}

/**	author: Referensi Praktikum SDA modified by  Maolana
 	Modul untuk Alokasi Queue**/
address AlokasiQueue(InfoKucing informasi){
   address P;
   addressList L;
   
   P=(address)malloc(sizeof(ElmQueue));  
   if(P!=nil) {
   	info(P) = informasi;
	next(P) = nil;
   }
   return P;
}

/** Referensi Praktikum SDA
	Modul untuk DeAlokasi Queue**/
 void DeAlokasi(address P){
    free(P);   
 } 

/** author: Referensi Praktikum SDA modified by Maloana
	Modul untuk insert antrian diakhir (enque) **/
void EnQue(Queue *Q, InfoKucing informasi){
	address P = AlokasiQueue(informasi);
	address Temp = HEAD(*Q);
	
	if(IsQueueEmpty(*Q)){
		next(P)=nil;
    	HEAD(*Q)=P;
    	TAIL(*Q)=P;
	}
	else{ 
      	while(next(Temp)!=nil){
			Temp = next(Temp);
	  	}
	  	next(Temp) = P;
	  	TAIL(*Q) = P;
    }
	
}
/** author: Yayang Setia Budi
	Modul untuk menghapus element pertama Queue (deQue), sebelum dihapus informasi dari Head antrian akan
	ditampung dalam variabel**/
void DelQue(Queue *Antrian, Onprocess *onproses){
  address First = HEAD(*Antrian);
  
  HEAD(*Antrian) = next(HEAD(*Antrian));
  next(First)=nil;
  (*onproses).info = First->info;
  (*onproses).OnGoing = true;
  (*onproses).waktuSelesai = First->info.waktuSelesai; 		
  DeAlokasi(First);
}

/** Referensi Praktikum SDA
	Modul cek apakah antrian kosong atau tidak**/
boolean IsQueueEmpty(Queue Q){
	if(HEAD(Q)==nil){
		return true;
	}else{
		return false;
	}
}

/** Referensi modul internet
	Modul untuk mengubah inputan menjadi format tanpa koma. Ch: 1,2,3 menjadi 123 **/
char* Token(String inputanPenyakit, String Hasil){
	strcpy(Hasil,"");
	
	char* token = strtok(inputanPenyakit, ",");
	
	while (token) {
    	strcat(Hasil,token);
    	token = strtok(NULL, ",");
	}
	
	return Hasil;
}

/** author : Maolana F
	Modul membuat sebuah list yang berisi nama penyakit disetiap nodenya **/
List buildList(String daftarPenyakit){
	int i;
	List list;
	CreateList (&list);
	 
	for(i=0;i<strlen(daftarPenyakit);i++){
		
		InsVLast (&list, namaPenyakit(daftarPenyakit[i]));
	}
	
	return list;
}

/** author: Maolana F
	Modul insert after Queue (memasukan antrian diantara antrian lainnya) **/
void AddsortingQueue(Queue *Q, InfoKucing informasi){
	//membuat pointer ke Head antrian
	address Temp = (*Q).HEAD;
	
	//Memesan alamat untuk antrian yang akan dimasukan  
	address P = AlokasiQueue(informasi);
	
	//flag untuk menandakan jika proses insert sudah dilakukan maka tidak ada insert lain (looping berhenti)
	boolean lanjut = true;
	
	//cek kondisi apakah apakah node selanjutnya memiliki prioritas sama
	//Jika priotas sama maka antrian baru akan berada setelah antrian lama yang memiliki prioritas sama
	//Jika beda maka modul akan melakukan pembadingan dengan antrian baru sampai mendapat posisi sesuai
	if(prioritas(next(Temp)) == prioritas(P)){
		P->next =Temp->next->next;
		Temp->next->next = P;
	}else{
		//membandingkan antrian baru dengan antrian lama dan proses membandingkan dimulai dari HEAD->next atau node ke 2
		while(Temp->next != NULL && lanjut ){
			if(Temp->next->info.prioritas < P->info.prioritas){
				P->next = Temp->next;
				Temp->next = P;
				lanjut=false; //Jika insert berhasil maka looping dihentika secara boolean
			}
			Temp = Temp->next;
		}
	}
}

/**	author: Muhammad Dyfan
	Modul insert antriana yang berfokus pada priotas atau modifikasi insert pada Queue**/
void insertAntrian(Queue *Q, InfoKucing informasi){
 	//Kondisi jika antrian kosong atau prioritas antrian baru <= antrian lama bagian terakhir (Tail)
	if(IsQueueEmpty((*Q)) || (informasi.prioritas <= (*Q).TAIL->info.prioritas)){
		EnQue(&(*Q),informasi);
	}else if(informasi.prioritas > (*Q).HEAD->info.prioritas){ 
		address Temp = (*Q).HEAD;
		address P = AlokasiQueue(informasi);

		if(Temp->info.prioritas == P->info.prioritas){
			P->next = Temp->next;
			(*Q).HEAD->next = P;
		}else{
			 P->next = Temp;
			(*Q).HEAD = P;
		}
	}else{
		AddsortingQueue(&(*Q),informasi);
	}
}

/** author: Muhammad Dyfan
	Modul untuk convert index/char menjadi nama penyakit yang sesuai **/
char* namaPenyakit(char nomorPenyakit){
	
	switch(nomorPenyakit){
		case '1': 
			return "Penyakit kulit";
			break;
		case '2': 
			return "Luka ringan";
			break;
		case '3': 
			return "Bersin";
			break;
		case '4': 
			return "Cacingan";
			break;
		case '5': 
			return "Diare";
			break;
		case '6': 
			return "Luka dalam";
			break;
		case '7': 
			return "Gangguan kerongkongan";
			break;
		case '8': 
			return "Kuning";
			break;
		case '9': 
			return "Terkena virus";
			break;
		default: 
			return "Penyakit tidak ada dalam list";
			break;
	}
}

/** author: Maolana F
	Modul untuk convert index/char menjadi Kategori penyakit yang sesuai **/
char *kategoriPenyakit(char Penyakit){
	switch(Penyakit){
		case '1':
		case '2':
		case '3':
			return "Ringan";
			break;
		case '4':
		case '5':
		case '6':
			return "Sedang";
			break;
		case '7':
		case '8':
		case '9':
			return "Berat";
			break;
	}
	
}

/*  author : Muhammad Dyfan Ramadhan
	Menentukan nilai prioritas dari suatu antrian berdasarkan jumlah penyakit yang diderita */
int HitungNilaiPrioritas(JmlKategoriPenyakit jumlahPerKategori){
	
	int nilai = 0;
	nilai = nilai + (jumlahPerKategori.Berat*5);
	nilai = nilai + (jumlahPerKategori.Sedang*2);
	nilai = nilai + jumlahPerKategori.Ringan;

	return nilai;
}

/*  author: -
	Mengembalikan waktu estimasi pelayanan berdasarkan nilai prioritas antrian */
int PeriksaWaktuEstimasi(int Penyakit){
	if (Penyakit<4){
		return 15;
	} else if (Penyakit<7){
		return 30;
	} else if (Penyakit<10){
		return 45;
	}
}

/*  author: Maolana F
	Menghitung waktu estimasi pelayanan */
int HitungWaktuEstimasi(JmlKategoriPenyakit jumlahPerKategori){
	return (jumlahPerKategori.Ringan*15*60) + (jumlahPerKategori.Sedang*30*60) + (jumlahPerKategori.Berat*45*60);
}

/** author: Yayang Setia Budi
	Modul tahap registrasi antrian **/
void Registrasi(Queue *Antrian,Onprocess *Onproses){
	JmlKategoriPenyakit jmlKategori;
	InfoKucing Info;
	boolean validation = true; 
	String daftarPenyakit,penyakitTemp;
	CreateList(&Info.Penyakit);
	createEmptyJmlKategori(&jmlKategori);
	Jam jam;
	
	do{
		system("cls");
		printf("\n\t\t\t\t\t====================== REGISTRASI ======================\n\n");
		fflush(stdin);
		printf("\t\t\t\t\tNama Kucing      : "); scanf("%[^\n]s",&Info.namaKucing);
		fflush(stdin); 
		printf("\t\t\t\t\tNama Pemilik     : "); scanf("%[^\n]s",&Info.namaPemilik);
		fflush(stdin);
		BacaJam(&jam);
		validation = IsJValid(jam);
		if(!validation){
			system("cls");
			printf("\n\n\t\t\tWaktu Kedatangan tidak valid, tolong masukan waktu yang sesuai !!\n\n");
			system("pause");
		}else{
			Info.waktuDatang =JamToDetik(jam);
			validation = IsValidComeTime(Info.waktuDatang,(*Antrian),(*Onproses));
			if(!validation){
				system("cls");
				printf("\n\n\t\t\tWaktu Kurang dari waktu kedatangan terakhir, tolong masukan waktu yang sesuai !!\n\n");
				system("pause");
			}else{
				ListDaftarPenyakit();
				fflush(stdin);
				printf("\t\t\t\t\tDaftar Penyakit  : "); scanf("%[^\n]s",&daftarPenyakit);
				validation = isValidDiseases(daftarPenyakit);
				if(!validation){
					printf("\n\n\t\t\tDaftar Penyakit tidak benar, tolong masukan input yang valid !!\n\n");
					system("pause");
				}
			}
		}
	} while(!validation);
	
	strcpy(daftarPenyakit,Token(daftarPenyakit,penyakitTemp));
	Info.Penyakit = buildList(daftarPenyakit);
	setJmlPerKategori(&jmlKategori,daftarPenyakit);
	Info.estimasiWaktu = HitungWaktuEstimasi(jmlKategori);
	Info.prioritas = HitungNilaiPrioritas(jmlKategori);
    Info.waktuSelesai = 0;
    

	insertAntrian(&(*Antrian),Info);
	UpdateWaktuSelesai(&(*Antrian),(*Onproses));
}

/** author: Muhammad Dyfan
	Modul untuk print daftar antrian**/
void PrintAntrian(Queue Q, Onprocess onproses){
	address Temp = Q.HEAD;
	Jam jam;
	printf("\n\t\t\t\t================== DALAM PERAWATAN ==========================\n");
	if(onproses.OnGoing != false){
		jam = DetikToJam(onproses.waktuSelesai);
		printf("\n\t\t\t\t\tNama Kucing                   : %s",onproses.info.namaKucing);
		printf("\n\t\t\t\t\tNama Pemilik                  : %s",onproses.info.namaPemilik);
		printf("\n\t\t\t\t\tNilai Priotas                 : %d",onproses.info.prioritas);
		printf("\n\t\t\t\t\tSelesai pada                  : ");
		TulisJam(jam);
	}else{
		printf("\n\t\t\t\t\tTidak ada yang sedang dirawat ");
		
	}
	
	printf("\n\n\t\t\t\t================== DAFTAR ANTRIAN ===========================\n");
	if(!IsQueueEmpty(Q)){
		while(Temp->next != NULL){
			jam = DetikToJam(Temp->info.waktuSelesai);
			printf("\n\t\t\t\t\tNama Kucing                   : %s",Temp->info.namaKucing);
			printf("\n\t\t\t\t\tNama Pemilik                  : %s",Temp->info.namaPemilik);
			printf("\n\t\t\t\t\tNilai Priotas                 : %d",Temp->info.prioritas);
			printf("\n\t\t\t\t\tJam Selesai                   : ");
			TulisJam(jam);
			printf("\n\t\t\t\t\tDaftar penyakit yang diderita : ");
			PrintDaftarPenyakit(Temp->info.Penyakit.First);
			printf("\n\t\t\t\t\t-----------------------------------------------------");
			Temp = Temp->next;
		}
			jam = DetikToJam(Temp->info.waktuSelesai);
			printf("\n\t\t\t\t\tNama Kucing                   : %s",Temp->info.namaKucing);
			printf("\n\t\t\t\t\tNama Pemilik                  : %s",Temp->info.namaPemilik);
			printf("\n\t\t\t\t\tNilai Priotas                 : %d",Temp->info.prioritas);
			printf("\n\t\t\t\t\tJam Selesai                   : ");
			TulisJam(jam);
			printf("\n\t\t\t\t\tDaftar penyakit yang diderita : ");
			PrintDaftarPenyakit(Temp->info.Penyakit.First);
	}else{
		printf("\n\n\t\t\t\t\tAntrian Kosong\n\n");
	}

}

void setWaktuSelesai(Queue Antrian,int Estimasi,int *waktuSelesai);

/** author: Muhammad Dyfan
	Modul untuk set jumlah per kategori penyakit menjadi nol**/
void createEmptyJmlKategori(JmlKategoriPenyakit *jumlahPerKategori){
	(*jumlahPerKategori).Ringan = 0;
	(*jumlahPerKategori).Sedang = 0;
	(*jumlahPerKategori).Berat= 0;
}

/** author: Maolana F
	Modul untuk set jumlah per kategori penyakit sesuai dengan jumlah penyakit per kategori yang dialami kucing**/
void setJmlPerKategori(JmlKategoriPenyakit *jumlahPerKategori, String daftarPenyakit){
	int counter;
	for(counter=0;counter<strlen(daftarPenyakit);counter++){
			if(strcmp(kategoriPenyakit(daftarPenyakit[counter]),"Ringan") == 0){
				(*jumlahPerKategori).Ringan++;
			}else if(strcmp(kategoriPenyakit(daftarPenyakit[counter]),"Sedang") == 0){
				(*jumlahPerKategori).Sedang++;
			}else if(strcmp(kategoriPenyakit(daftarPenyakit[counter]),"Berat") == 0){
				(*jumlahPerKategori).Berat++;
			}
		}
}

/** author: Maolana Firmansyah
	Modul untuk set informasi dari onproses menjadi nol/null (kosongan)**/
void createEmptyOnproses(Onprocess *Onproses){
	CreateList(&(*Onproses).info.Penyakit);
	
	(*Onproses).info.Penyakit.First= NULL;
	(*Onproses).waktuSelesai= 0;
	(*Onproses).OnGoing = false;
	(*Onproses).info.prioritas= 0;
	(*Onproses).info.waktuDatang = 0;
	(*Onproses).info.waktuSelesai = 0;
	strcpy((*Onproses).info.namaKucing,"-");
	strcpy((*Onproses).info.namaPemilik,"-");
}

/** author: Muhammad Dyfan Ramadhan
	Modul untuk mengambil waktu terkini	**/
int getTimeRightNow(Onprocess Onproses){
	return Onproses.waktuSelesai;
}

/** author: Muhammad Dyfan Ramadhan
	update waktu selesai pelayanan dari masing-masing kucing**/
void UpdateWaktuSelesai(Queue *Antrian, Onprocess otw){
	address Temp = (*Antrian).HEAD;
	int LastTime = 0;

	if(!IsQueueEmpty(*Antrian)){
		if(otw.OnGoing == true){
			LastTime = otw.waktuSelesai;
		}else{
			LastTime = (*Antrian).HEAD->info.waktuDatang;
		}
		while(Temp->next != NULL){
			LastTime = LastTime + Temp->info.estimasiWaktu;
			Temp->info.waktuSelesai = LastTime ;
			Temp = Temp->next;
		}
		
		LastTime = LastTime + Temp->info.estimasiWaktu;
		Temp->info.waktuSelesai = LastTime ;
	}
}

/** author: Yayang Setia Budi
	Modul untuk check apakah ada yang diproses, jika tidak maka tawari user apakah ingin
	memproses otomatis atau memasukan ke antrian**/
void cekonproses(Queue *Antrian, Onprocess *onproses){
	char jawaban;
	int max = findMaxWaktuKedatangan(*Antrian);
	int i;
	
	if(max >= (*onproses).waktuSelesai){
		(*onproses).OnGoing = false;
	}
	
	if((*onproses).OnGoing == false){
		do{
			system("cls");
			fflush(stdin);
			printf("\n\n\n\t\t\t\t\t\t\t\t-- ALERT !! --\n");
			printf("\n\t\t\tTidak ada kucing dalam perawatan, apakah anda ingin memanggil %s untuk dirawat ?     [Y/N]   : ",(*Antrian).HEAD->info.namaKucing);
			scanf("%c",&jawaban);
			if(jawaban == 'Y' || jawaban == 'y'){
				DelQue(&(*Antrian),&(*onproses));
				printf("\n\n\t\t\t\t\t\t\tMemanggil %s untuk dirawat \n\n",(*onproses).info.namaKucing);
				loading();
				AddRiwayat((*onproses).info);
				DelAll (&(*onproses).info.Penyakit);
			}else if(jawaban == 'N' || jawaban == 'n'){
				printf("\n\n\t\t\t\t\t\t\t\t %s Masuk Antrian \n\n",(*Antrian).HEAD->info.namaKucing);
				loading();
			}else{
				printf("\n\t\t\tJawab yang bener lah!!");
			}
		}
		while(jawaban != 'Y' && jawaban != 'y' && jawaban != 'N' && jawaban != 'n');
	}
}

/** author: Maolana Firmansyah
	Modul untuk memproses antrian dengan cara memanggil kucing atau menghapus salah satu antrian**/
void ProsesAntrian(Queue *Antrian,Onprocess *Onproses){
	int jawaban;
	do{
		system("cls");
		printf("\n\t\t\t\t\t====================== PROSES ANTRIAN ============================\n\n");
		printf("\t\t\t\t\t[1] Panggil kucing\n");
		printf("\t\t\t\t\t[2] Hapus Antrian \n");
		printf("\n\t\t\t\t\t Jawaban Anda : ");
		scanf("%d",&jawaban);
	}
	while(jawaban<1 || jawaban>2);
	
	if(jawaban == 1){
		printf("\n\t\t\t\t\tMemanggil %s untuk dirawat.....",(*Antrian).HEAD->info.namaKucing);
		DelQue(&(*Antrian),&(*Onproses));
		AddRiwayat((*Onproses).info);
	}else{
		system("cls");
		printf("\t\t\t\t\t====================== HAPUS ANTRIAN ============================\n\n");
		DelAfter(&(*Antrian),(*Onproses));


	}
	
	//Hapus Antrian Belum ada
}

int findMaxWaktuKedatangan(Queue Antrian){
	int max = 0;
	
	address Temp = HEAD(Antrian);

	if(IsQueueEmpty(Antrian)){
		return max;
	}

	while(Temp->next != NULL ){
		if(Temp->info.waktuDatang >= max){
			max = Temp->info.waktuDatang;
		}
		Temp = Temp->next;
	}
	
	if(Temp->info.waktuDatang >= max){
		max = Temp->info.waktuDatang;
	}
		
	return max;
}

boolean IsValidComeTime(int waktuKedatangan, Queue Antrian,Onprocess onproses){
	if(onproses.OnGoing = true && IsQueueEmpty(Antrian)){
		if(waktuKedatangan < onproses.info.waktuDatang){
			return false;
		}else{
			return true;
		}
	}else{
		if(waktuKedatangan < findMaxWaktuKedatangan(Antrian)){
			return false;
		}else{
			return true;
		}
	}

}

boolean isValidDiseases(String daftarPenyakit){
	int counter;
	
	char *hasil = strchr(daftarPenyakit,',');
	boolean valid = false;
	 
	if(hasil == NULL && strlen(daftarPenyakit)>1){
		return valid;
	}else{
		while(counter<strlen(daftarPenyakit)){
			if( counter % 2 == 0){
				if(daftarPenyakit[counter] == '0' || !isdigit(daftarPenyakit[counter])){
					return valid;
				}
			}else{
				if(daftarPenyakit[counter] != ','){
					return valid;
				}
			}
			counter++;
		}
		valid = true;
		return valid;
	}
}

/** Fitur Riwayat **/
void ListDaftarPenyakit(){
	printf("\n\t\t\t\t\t[1] Penyakit Kulit \t [6] Luka Dalam\n");
	printf("\t\t\t\t\t[2] Luka Ringan\t\t [7] Gangguan Tenggorokan\n");
	printf("\t\t\t\t\t[3] Bersin\t\t [8] Kuning\n");
	printf("\t\t\t\t\t[4] Cacingan\t\t [9] Terkena Virus\n");
	printf("\t\t\t\t\t[5] Diare\n\n");
}

void AddRiwayat(InfoKucing info){ 
	Riwayat temp;
	String TempString;
	
	strcpy(temp.NamaKucing,info.namaKucing);
	strcpy(temp.NamaPemilik,info.namaPemilik);
	strcpy(temp.DaftarPenyakit,riwayatPenyakit(info.Penyakit.First,TempString));
	strcpy(temp.Date,DateNow(TempString));
	
    FILE *riwayat;
    if ((riwayat = fopen("Riwayat.txt", "ab+")) == NULL)
	{
		printf ("File tidak dapat dibuka\n");
		exit(1);
	}

    fwrite(&temp, sizeof(temp), 1, riwayat);
    fclose(riwayat);
}

void TampilRiwayat(){ 
	system("cls");
    Riwayat temp;
    FILE *riwayat;
    
	riwayat=fopen("Riwayat.txt", "rb+");
	printf("\t\t\t\t\t================ Riwayat Perawatan ==================\n");
	while(fread(&temp, sizeof(temp), 1, riwayat)){
		printf("\t\t\t\t\tNama Kucing      : %s",temp.NamaKucing);
		printf("\n\t\t\t\t\tNama Pemilik     : %s",temp.NamaPemilik);
		printf("\n\t\t\t\t\tDaftar Penyakit  : %s",temp.DaftarPenyakit);
		printf("\n\t\t\t\t\tHari dan Tanggal : %s\n\n",temp.Date);
	}
	fclose(riwayat);
	
	getch();
}

char *riwayatPenyakit(addressList L,String Temp){
	strcpy(Temp,"");
	
	while(L->next != Nil){
			strcat(Temp,L->info);
			strcat(Temp,",");
			L = L->next;
		}
	strcat(Temp,L->info);
	
	return Temp;
}

char *DateNow(String Temp){
	strcpy(Temp,"");
	int Day,Month;
	String TimeNow,Year;
	char* token;
	
	time_t now = time(NULL);
	char *string_now = ctime(&now);
	struct tm *cur_time = localtime(&now);
	
	char *Hari[7] = {"Minggu, ", "Senin, ","Selasa, ","Rabu, ","Kamis, ","Jumat, ","Sabtu, "};
	char *Bulan[12] = {" Januari "," Febuari "," Maret "," April "," Mei "," Juni "," Juli "," Agustus "," September "," November "," Desember "};
	
	strftime(TimeNow,100,"%w %d %m %Y", cur_time);
	
	token = strtok(TimeNow, " ");
	strcat(Temp,Hari[atoi(token)]);
	
	token = strtok(NULL, " ");
	strcat(Temp,token);
	
	token = strtok(NULL, " ");
	strcat(Temp,Bulan[atoi(token)-1]);
	
	token = strtok(NULL, " ");
	strcat(Temp,token);
	
	return Temp;
}

void cariRiwayat(){
	system("cls");
    Riwayat temp;
    String NamaKucing,NamaPemilik;
    FILE *riwayat;
    boolean Ketemu = false;
    
	riwayat=fopen("Riwayat.txt", "rb+");
	printf("\t\t\t\t\t================ Cari Riwayat ==================\n");
	fflush(stdin);
	printf("\t\t\t\t\tNama Kucing : ");
	scanf("%[^\n]s",&NamaKucing);
	fflush(stdin);
	printf("\t\t\t\t\tNama Pemilik: ");
	scanf("%[^\n]s",&NamaPemilik);
	system("cls");
	printf("\t\t\t\t\t================ Riwayat ==================\n");
	while(fread(&temp, sizeof(temp), 1, riwayat)){
		if(strcmp(NamaKucing,temp.NamaKucing) == 0 && strcmp(NamaPemilik,temp.NamaPemilik) == 0 ){
			printf("\t\t\t\t\tNama Kucing      : %s",temp.NamaKucing);
			printf("\n\t\t\t\t\tNama Pemilik     : %s",temp.NamaPemilik);
			printf("\n\t\t\t\t\tDaftar Penyakit  : %s\n\n",temp.DaftarPenyakit);
			Ketemu = true;
		}
	}
	fclose(riwayat);
	
	if(!Ketemu){
		printf("\n\n\t\t\t\t\tData Yang  dicari tidak ditemukan\n\n");
		
	}
	
	system("pause");
}

void MenuRiwayat(){
	
	int jawaban;
	do{
		system("cls");
		printf("\t\t\t\t\t====================== Riwayat ============================\n\n");
		printf("\t\t\t\t\t[1] Tampilkan Seluruh Riwayat\n");
		printf("\t\t\t\t\t[2] Cari Riwayat \n");
		printf("\n\t\t\t\t\t Jawaban Anda : ");
		scanf("%d",&jawaban);
	}
	while(jawaban<1 || jawaban>2);
	
	if(jawaban == 1){
		TampilRiwayat();
	}else{
		cariRiwayat();	
	}	
}

void DelAfter(Queue *Antrian,Onprocess onproses){
	String namaKucing,namaPemilik;
	address Temp = HEAD(*Antrian);
	address Last = TAIL(*Antrian);
	
	address Remove;
	boolean IsExistCat = false;
	
	fflush(stdin);
	printf("\t\t\t\t\tNama Kucing  : "); scanf("%[^\n]s",&namaKucing);
	fflush(stdin);
	printf("\t\t\t\t\tNama Pemilik : "); scanf("%[^\n]s",&namaPemilik);
	
	if(strcmp(namaKucing,NamaKucing(Temp)) == 0 && strcmp(namaPemilik,NamaPemilik(Temp)) == 0){
		HEAD(*Antrian) = next(Temp);
		next(Temp) == NULL;
		UpdateWaktuSelesai(&(*Antrian),onproses);
		DelAll (&(*Antrian).HEAD->info.Penyakit);
		DeAlokasi(Temp);
		IsExistCat = true;
	}else{
		while(next(Temp) != NULL && IsExistCat == false){
			if(strcmp(namaKucing,NamaKucing(next(Temp))) == 0 && strcmp(namaPemilik,NamaPemilik(Temp)) == 0 && next(Temp) != Last){
				Remove = next(Temp);
				next(Temp) = next(next(Temp));
				Remove->next = NULL;
				DelAll (&Remove->info.Penyakit);
				UpdateWaktuSelesai(&(*Antrian),onproses);
				DeAlokasi(Remove);	
				IsExistCat = true;
			}else if(strcmp(namaKucing,NamaKucing(next(Temp))) == 0 && strcmp(namaPemilik,NamaPemilik(Temp)) == 0 && next(Temp) == Last){
				Remove = next(Temp);
				next(Temp) = NULL;
				DelAll (&Remove->info.Penyakit);
				DeAlokasi(Remove);	
				IsExistCat = true;
			}else{
				Temp = next(Temp);
			}
		}
	}
	system("cls");
	if(IsExistCat){
		printf("\n\n\t\t\t\t\tSukses Delete Antrian\n");
	}else{
		printf("\n\n\t\t\t\t\tDelete Antrian Gagal!!\n");
	}
}

void loading(){
	int i;	
	printf("\t\t\t\t\t");
	for(i=0;i<=60;i++){
        printf("%c",219);
        Sleep(25);
    }
}




