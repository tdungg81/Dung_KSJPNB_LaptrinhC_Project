#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "account.h"
#include "product.h"

#define acCount "tien"
#define passWord "dung"

int checkStr(char acc[], char pass[]){
	return(strcmp(acCount, acc) == 0 && strcmp(passWord, pass) == 0);
}

void showLoginMenu(int *choice_1){
	do{
		printf("|===============================|\n");
		printf("|   He thong quan ly cua hang   |\n");
		printf("|===============================|\n");
		printf("|                               |\n");
		printf("| [1] Dang nhap                 |\n");
		printf("| [0] Thoat                     |\n");
		printf("|                               |\n");
		printf("|===============================|\n");
		printf(" Vui long nhap mot so: ");
		scanf("%d", choice_1);
		fflush(stdin);
		switch(*choice_1){
			case 1:
				system("cls");
				loggingIn();
				break;
			case 0:
				exitt();
				return;
				break;
			default:
				printf("Gia tri khong hop le! Nhap lai...");
				sleep(1);
				system("cls");
		}
	}while(*choice_1 != 1);
}

void loggingIn(){
	char acc[20], pass[30];
	do{
		fflush(stdin);
		printf("|===============================|\n");
		printf("|           Dang nhap           |\n");
		printf("|===============================|\n");
		printf("| Email (admin): ");
		fgets(acc, sizeof(acc), stdin);
		acc[strcspn(acc, "\n")] = '\0';
		printf("| Mat khau (admin): ");
		hidePassword(pass);
		if(!checkStr(acc, pass)){
			printf("Sai email hoac mat khau! Nhap lai...");
			sleep(1);
			system("cls");
		}
	}while(!checkStr(acc, pass));
	saveAccInfo(acc, pass);
	int i = 0;
	for(i; i <= 100; i += 5){
		printf("Dang nhap ... %d%c", i,'%');
		if(i == 100){
			printf("\nDang nhap thanh cong!");
			sleep(1);
		}
		system("cls");
	}
}

void showChoosingMode(){
	int choice;
	do{
		printf("|===============================|\n");
		printf("|            Xin chao           |\n");
		printf("|===============================|\n");
		printf("|                               |\n");
		printf("| [1] Quan ly danh muc          |\n");
		printf("| [2] Quan ly san pham          |\n");
		printf("| [0] Thoat                     |\n");
		printf("|                               |\n");
		printf("|===============================|\n");
		printf(" Vui long nhap mot so: ");
		scanf("%d", &choice);
		switch(choice){
			case 1:
				system("cls");
				showAdminMenu();
				break;
			case 2:
				system("cls");
				showProductMenu();
				break;
			case 0:
				printf("Quay ve man hinh dang nhap...");
				sleep(1);
				system("cls");
				break;
			default:
				printf("Gia tri khong hop le! Nhap lai...");
				sleep(1);
				system("cls");
		}
	}while(choice != 0);
}

void hidePassword(char pass[]){
	int i = 0;
	while(1){
		char c = getch();
		if(c == '\r'){
			pass[i] = '\0';
			break;
		}
		else if(c == '\b'){
			if(i){
				--i;
				printf("\b \b");
			}
		}
		else{
			pass[i++] = c;
			printf("*");
		}
	}
	printf("\n");
}

void saveAccInfo(char acc[], char pass[]){
	FILE *ptr = fopen("adminInfo.dat", "wb");
	if(ptr == NULL){
		printf("Khong the mo file\n");
	}
	fwrite(acc, sizeof(acc), 1, ptr);
	fwrite(pass, sizeof(pass), 1, ptr);
	fclose(ptr);
}

void exitt(){
	FILE *ptr = fopen("adminInfo.dat", "wb");
	fclose(ptr);
}

