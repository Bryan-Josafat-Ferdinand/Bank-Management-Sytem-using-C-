#include<stdio.h>
#include<stdlib.h>

int i,j;
int main_exit;

void menu();

struct dat{
    int mon,d,yr;
};
struct {
    char name[80];
    int accno;
    char addr[80];
    double phon;
    float am;
    struct dat depo;
}ad,chck,rem,transacti;

void delay(int h){   /*berfungsi untuk memberi jeda waktu sebelum melanjutkan proses selanjutnya*/
	int l,k;
    for(l=0;l<h;l++){
        k=l;
    }
}

void new_acc(){
	
	/*fungsi ini untuk membuat akun, di dalam fungsi ini kita akan meminta 
	inputan data diri dari user lalu mencetaknya ke dalam file record.in dan 
	dapat mengecek apakah nomor akun sudah dipakai atau tidak bila sudah maka 
	akan mencetak tulisan Account no. already in use! jika belum maka akan 
	dilanjutkan pada pengisian data setelah selesai fungsi ini memberikan 
	pilihan kembali ke menu utama atau keluar*/
	
    int choice;
    FILE *ptr;
    ptr=fopen("record.in","a+");
    account_no:
    system("cls");
    printf("\t\t\t================== ADD RECORD ====================");
    printf("\n\n\nMasukan tanggal hari ini(mm/dd/yyyy):");
    scanf("%d/%d/%d",&ad.depo.mon,&ad.depo.d,&ad.depo.yr);
    printf("\nMasukan Account Number (must 6 digits):");
    scanf("%d",&chck.accno);
    while(fscanf(ptr,"%d %s %s %lf %f %d/%d/%d\n",&ad.accno,ad.name,ad.addr,&ad.phon,&ad.am,&ad.depo.mon,&ad.depo.d,&ad.depo.yr)!=EOF)
    {
        if (chck.accno==ad.accno){
			printf("Account no. already in use!");
            delay(1000000000);
            goto account_no;
        }
    }
    ad.accno=chck.accno;
    printf("\nMasukan Nama:");
    scanf("%s",ad.name);
    printf("\nMasukan Alamat:");
    scanf("%s",ad.addr);
    printf("\nMasukan Nomor Handphone: ");
    scanf("%lf",&ad.phon);
    printf("\nMasukan Nilai Deposit Awal (Min Rp.50000):Rp.");
    scanf("%f",&ad.am);
    
	fprintf(ptr,"%d %s %s %lf %f %d/%d/%d\n",ad.accno,ad.name,ad.addr,ad.phon,ad.am,ad.depo.mon,ad.depo.d,ad.depo.yr);
    fclose(ptr);
    printf("\nAccount created successfully!");
    add_invalid:
    printf("\n\n\n\t\tPress 1 for return to main menu | Press 0 for exit:");
    scanf("%d",&main_exit);
    system("cls");
    if (main_exit==1){
        menu();
    }
    else if(main_exit==0){
        close();
    }
    else{
        printf("\nInvalid!\a");
        goto add_invalid;
    }
}
// Fungsi new_acc ditulis oleh Bryan Josafat Ferdinand - 2502003743

void transact(void){
   
	/*fungsi ini berfungsi untuk melakukan deposit atau penarikan pada no akun yang tercatat 
	dan membatasi minimal penarikan dan minimal deposit lalu melakukan pengurangan atau pertambahan 
	pada saldo akun yang dieksekusi setelah selesai melakukan penarikan atau deposit maka fungsi ini 
	akan memberi pilihan untuk kembali pada menu utama, keluar, atau melakukan transaksi lagi*/
	
	int choice,test=0;
    FILE *old,*newrec;
    old=fopen("record.in","r");
    newrec=fopen("new.in","w");
	printf("Enter the account number:");
    scanf("%d",&transacti.accno);
    while (fscanf(old,"%d %s %s %lf %f %d/%d/%d",&ad.accno,ad.name,ad.addr,&ad.phon,&ad.am,&ad.depo.mon,&ad.depo.d,&ad.depo.yr)!=EOF)
	{
        if(ad.accno==transacti.accno){   
			test=1;
            printf("\n\nDo you want to\n1.Deposit\n2.Penarikan\n\nEnter your choice:");
            scanf("%d",&choice);
            if (choice==1){
                printf("Enter the amount you want to deposit:Rp. ");
                scanf("%f",&transacti.am);
                if(transacti.am<100000){
                    fprintf(newrec,"%d %s %s %lf %f %d/%d/%d\n",ad.accno,ad.name,ad.addr,ad.phon,ad.am,ad.depo.mon,ad.depo.d,ad.depo.yr);
                    printf("\n\nDeposit unsuccess");
                }
                else{
					ad.am+=transacti.am;
                    fprintf(newrec,"%d %s %s %lf %f %d/%d/%d\n",ad.accno,ad.name,ad.addr,ad.phon,ad.am,ad.depo.mon,ad.depo.d,ad.depo.yr);
                    printf("\n\nDeposit success");
                }
            }
            else{
            	printf("Masukan Nominal yang ingin ditarik:Rp. ");
                scanf("%f",&transacti.am);
                if(transacti.am>=100000 && transacti.am<=5000000 && ad.am > transacti.am){
                    ad.am-=transacti.am;
                    fprintf(newrec,"%d %s %s %lf %f %d/%d/%d\n",ad.accno,ad.name,ad.addr,ad.phon,ad.am,ad.depo.mon,ad.depo.d,ad.depo.yr);
                    printf("\n\nPenarikan success");
                }
				else{
					fprintf(newrec,"%d %s %s %lf %f %d/%d/%d\n",ad.accno,ad.name,ad.addr,ad.phon,ad.am,ad.depo.mon,ad.depo.d,ad.depo.yr);
                    printf("\n\nPenarikan unsuccess");
				}
            }
        }
        else{
            fprintf(newrec,"%d %s %s %lf %f %d/%d/%d\n",ad.accno,ad.name,ad.addr,ad.phon,ad.am,ad.depo.mon,ad.depo.d,ad.depo.yr);
        }
    }
   fclose(old);
   fclose(newrec);
   remove("record.in");
   rename("new.in","record.in");
   if(test!=1){
    	printf("\n\nRecord not found!!");
    	transact_invalid:
    	printf("\n\nPress 0 for try again | 1 for return to main menu | Press 2 for exit:");
    	scanf("%d",&main_exit);
    	system("cls");
    	if (main_exit==0){
        	transact();
        }
    	else if (main_exit==1){
        	menu();
        }
    	else if (main_exit==2){
        	close();
        }
    	else{
        	printf("\nInvalid!");
        	goto transact_invalid;
    	}
	}
   else{
    	printf("\nPress 1 for return to main menu | Press 0 for exit:");
    	scanf("%d",&main_exit);
        system("cls");
        if (main_exit==1){
            menu();
        }
        else{
            close();
        }
   }
}
// Fungsi transact ditulis oleh Bryan Josafat Ferdinand - 2502003743

void erase(void){
	
	/*Fungsi ini berfungsi untuk menghapus akun yang ada dalam daftar, dengan cara 
	meminta input dari user lalu mengecek inputan user ada dalam daftar atau tidak 
	apabila tidak maka akan mengeluarkan tulisan record not found bila ada maka data akan dihapus 
	lalu mengeluarkan tulisan Record deleted successfully dan memberi pilihan 
	untuk kembali pada main menu atau keluar*/
	
    FILE *old,*newrec;
    int test=0;
    old=fopen("record.in","r");
    newrec=fopen("new.in","w");
    printf("Enter the account number:");
    scanf("%d",&rem.accno);
    while (fscanf(old,"%d %s %s %lf %f %d/%d/%d",&ad.accno,ad.name,ad.addr,&ad.phon,&ad.am,&ad.depo.mon,&ad.depo.d,&ad.depo.yr)!=EOF)
	{
        if(ad.accno!=rem.accno){
            fprintf(newrec,"%d %s %s %lf %f %d/%d/%d\n",ad.accno,ad.name,ad.addr,ad.phon,ad.am,ad.depo.mon,ad.depo.d,ad.depo.yr);
		}
        else{
			test++;
            printf("\nRecord deleted successfully!\n");
        }
	}
   fclose(old);
   fclose(newrec);
   remove("record.in");
   rename("new.in","record.in");
   if(test==0){
    	printf("\nRecord not found!!\a\a\a");
        erase_invalid:
        printf("\nPress 0 for try again | Press 1 for return to main menu | Press 2 for exit:");
        scanf("%d",&main_exit);
        if (main_exit==1){
            menu();
		}
        else if (main_exit==2){
            close();
        }
        else if(main_exit==0){
            erase();
        }
        else{
			printf("\nInvalid!\a");
            goto erase_invalid;
		}
    }
    else{
		printf("\nPress 1 for return to  main menu | Press 0 to exit:");
        scanf("%d",&main_exit);
        system("cls");
        if (main_exit==1){
            menu();
        }
        else{
            close();
        }
    }
}
// Fungsi erase ditulis oleh Bryan Josafat Ferdinand - 2502003743

void clo(void){
	
	/*fungsi ini dibuat untuk menuliskan "Thank you!" saat program akan ditutup*/
	
	printf("\nThank you!\n");
}
// Fungsi clo ditulis oleh Bryan Josafat Ferdinand - 2502003743

void menu(void){   
	
	/*fungsi ini untuk menampilkan menu utama*/
	
	int choice;
    system("cls");
    system("color 0");
    printf(" Kelompok 11 : \n");
    printf(" 2502003743 - Bryan Josafat Ferdinand\n 2501993434 - Rickie Chandra Pangestu\n");
    printf("\n\n\t\t\t\t\t    BANKING MANAGEMENT SYSTEM");
    printf("\n\n\n\t\t=========================== WELCOME TO THE MAIN MENU =============================");
    printf("\n\n\t\t1.Create new account\n\t\t2.transactions\n\t\t3.Delete account\n\t\t4.Exit\n\n\n\t\t Masukan Pilihan:");
    scanf("%d",&choice);

    system("cls");
    switch(choice){
    case 1:
		new_acc();
    	break;
    case 2:
		transact();
        break;
    case 3:
		erase();
        break;
    case 4:
		clo();
        break;
    }
}
// Fungsi menu ditulis oleh Bryan Josafat Ferdinand - 2502003743

int main(){
	// memanggil fungsi menu
    menu();
	return 0;
}
