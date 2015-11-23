/*
DO THANH NAM - namdothanh87@gmail.com
GIAI BAI TOAN CAI TUI
	THUAT TOAN GAN DUNG - NIFF
	THUAT TOAN CHINH XAC - VET CAN
n=20, 30, 40
So lan chay cho moi thu nghiem la 40 lan
Kich thuoc moi tui: T=1.0
0 < Kich thuoc cac do vat <= T
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <string.h>

/////////////////////////////////////BIEN TOAN CUC////////////////////////////////////////
#define SoDoVatMAX	40						//So tui	
#define T			1.0				//Kich thuoc cua cac tui
#define SoLan		40				//Moi gia tri n thuc hien 40 lan
#define TRUE	1
#define FALSE	0

float s[SoDoVatMAX];					//Tap kich thuoc cua cac do vat
float used[SoDoVatMAX];					//Kich thuoc hien tai cua cac tui, toi da so tui = so do vat
int b[SoDoVatMAX];						//Cho biet do vat i thuoc cai tui nao

///////////////////HAM TAO TAP SO NGAU NHIEN LAM DAU VAO DE THU NGHIEM////////////////////
void Tao_du_lieu(int n_)
{
	int i=0;
	float tg;

	for(i=0; i<n_; ++i)
	{
		tg = (float)rand()/(RAND_MAX);			//Tao so ngau nhien <=1.0
		tg*=10;								//Lam tron den 1 so thap phan
		tg = (float)ceil((double)tg);
		tg/=10;
		if (tg<0.1)	tg=0.1;				//Chong truong hop bang 0.0
		s[i] = tg;		
		//printf("\n %0.1f", s[i]);
	
	}//for i
	

	

	//getch();
}

///////////////////////////////HAM THUC HIEN THUAT TOAN NIFF/////////////////////////////
//Thuc hien 1 lan
//Tra ve so tui can su dung
int Thuat_toan_NIFF(int n)
{
	int sotui=0;
	int i=0, j=0, k=0;
	float tg;
	
	//---1. Sap xep tap do vat theo thu tu khong tang
	for(i=0; i<n-1; ++i)
	{
		k=i;
		for(j=i+1; j<n; ++j)	if(s[k] < s[j]) k=j;
	
		if(k!=i)	//doi cho
		{
			tg=s[i];
			s[i]=s[k];
			s[k]=tg;
		}
	}//for i
	
	
	//---2. Quy khong kich thuoc hien hanh cua cac tui
	for (i=0; i< n; ++i) used[i]=0.0;
	
	//---3. Thuc hien thuat toan chinh	
	for (i=0; i< n; ++i)
	{
		j=0;
		tg=used[j]+s[i];
		while( tg> T) 
		{
			j++;	
			tg=used[j]+s[i];
		}
		used[j] += s[i];
		b[i]=j;
		if(sotui<j+1) sotui=j+1;
	}
	
	//debug
	/*printf("\n");
	for (i=0; i<n; ++i) printf("  %0.1f", s[i]);
	
	printf("\n");
	for (i=0; i<n; ++i) printf("  %d", b[i]);
	
	printf("\n So tui= %d", sotui);
	getch();
	*/
	

	return sotui;
}

/////////////////////////////HAM TRA VE GIA TRI LON NHAT CUA MANG////////////////////////
int Max(int m[], int sopt)
{
	int _max, i;
	_max=m[0];
	for(i=1; i<sopt; ++i)
	{
		if(m[i]>_max) _max=m[i];
	}
	return _max;
}
///////////////////////////HAM KIEM TRA TINH HOP LE CUA PHUONG AN X/////////////////////////
//Phuong an x la phuong an trong mang b
int Fit(int n)
{
	float ts;
	int i, j;
	
	for(i=0; i<=Max(b,n); ++i)		//so tui
	{
		ts=0.0;
		for(j=0; j<n; ++j)
			if(b[j]==i) ts += s[j];
		if(ts>T) return FALSE;
	}//for i
	
	//
	return TRUE;
}

//////////////////////////////HAM THUC HIEN THUAT TOAN VET CAN///////////////////////////
//Thuc hien 1 lan
//Khong de quy
//Tra ve so tui can su dung
int Thuat_toan_vet_can(int n)
{
	int sotui=0;
	int i=0, k=0;
	int stop=FALSE;
	int t;
	
	//
	for(i=0; i<n; ++i)		b[i]=i;			//Truong hop moi tap con trong phan hoach co 1 phan tu
	sotui=n;
	while(stop==FALSE)
	{
		k=n-1;
		//printf("\nSo tui= %d", sotui);
		while((k>=0)&&(b[k]==0)) k--;			//Tim chi so k lon nhat ma b[k]>0
		//printf("\n %d--", k);
		if(k>=0)
		{
			b[k] -= 1; 
			t=Max(b, k+1);
			for(i=k+1; i<n; ++i) b[i]=t+i-k;
			//printf("\n");
			//for(i=0; i<n; ++i)		printf("  %d", b[i]);
			//getch();
			if(Fit(n)==TRUE)
			{
				t=Max(b, n)+1;
				if(t<sotui) 
				{
					sotui=t;
					//debug
					/*printf("\nSo tui= %d:::", sotui);
					for(i=0; i<n; ++i)		printf("  %d", b[i]);
					getch();	*/
				}
			}//if
		}
		else stop=TRUE;
	}//while stop

	
	printf("\nVet can xong 1 lan. So tui= %d", sotui); //getch();
	//
	return sotui;
}

//////////////////////HAM THUC HIEN THUAT TOAN DE GIAI BAI TOAN CAI TUI VOI n=20, 30, 40//////////////////////////
//Thuc hien 40 lan
//Ghi ket qua ra file "Output_n.txt"
void Giai_bai_toan_cai_tui(int n_)
{
	int i=0;
	int _niff=0, _vetcan=0;
	int thucte=0, lythuyet=0, phantram=0;
	FILE *fileout;
	char filename[]="_Output_";
	char buff[3];
	time_t rawtime;
	
	
	//Tao file de ghi ket qua
	itoa(n_, buff, 10);
	strcat(filename, buff);
	fileout = fopen(filename, "wt");
	
	//Thoi gian bat dau
	time(&rawtime);
	printf("\n\tThoi gian bat dau: %s", ctime(&rawtime));
	fprintf(fileout, "n= %d:", n_);
	fprintf(fileout,"\nThoi gian bat dau: %s", ctime(&rawtime));
	
	//thuc hien lap 40 lan thuat toan 	
	fprintf(fileout, "\n[Lan]   [Gan dung]   [Chinh xac]   [Sai so]   [%sSai so]   [(Chinh xac-1)/3]","%");
	for(i=0; i<SoLan; ++i)
	{
		//---Tao du lieu ngau nhien
		Tao_du_lieu(n_);
		
		//---Thuc hien thuat toan chinh xac - Vet can
		_vetcan=Thuat_toan_vet_can(n_);
		
		//---Thuc hien thuat toan gan dung - NIFF
		_niff=Thuat_toan_NIFF(n_);
		
		//---In ra file
		thucte=_niff - _vetcan;
		lythuyet=(int)round((float)(_vetcan-1)/3);	
		phantram=thucte*100/_vetcan;
	
		fprintf(fileout,"\n  %d         %d            %d            %d          %d%s             %d", i+1, _niff, _vetcan, thucte, phantram, "%", lythuyet);
	
	}//for i
	
	
	//Thoi gian ket thuc
	time(&rawtime);
	printf("\n\tThoi gian ket thuc: %s", ctime(&rawtime));
	fprintf(fileout,"\nThoi gian ket thuc: %s", ctime(&rawtime));
	
	//dong file
	fclose(fileout);
	
}


//////////////////////////////////////HAM MAIN////////////////////////////////////////////
int main(int argc, char *argv[]) 
{
	
	
	printf("---------------------GIAI BAI TOAN CAI TUI--------------------------\nSO SANH GIUA THUAT TOAN GAN DUNG (NIFF) VA THUAT TOAN CHINH XAC (VET CAN)");
	
	//Truong hop 1: n=10
	printf("\n\nTruong hop 1: n=10.");
	Giai_bai_toan_cai_tui(10);
	
	//Truong hop 2: n=12
	printf("\n\nTruong hop 2: n=12");
	Giai_bai_toan_cai_tui(12);
		
	//Truong hop 3: n=14
	printf("\n\nTruong hop 3: n=14");
	Giai_bai_toan_cai_tui(14);
	
	//
	printf("\n\n==>Thuc hien xong. Xem cac file ket qua.");
	getch();
	return 0;
}


