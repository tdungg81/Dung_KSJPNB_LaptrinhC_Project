#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <windows.h>
#include <stdbool.h>
#include "function.h"

Product productList[55];
Order orderList[105];
char idList[20][105];
int choice, total1 = 0;

void bubbleSort_1(Product product[], int n){
	int i, j;
	for(i = 0; i < n; ++i){
		for(j = 0; j < n-1; ++j){
			if(product[j].price > product[j+1].price){
				int tmp = product[j].price;
				product[j].price = product[j+1].price;
				product[j+1].price = tmp;
			}
		}
	}
}

void showProBoard(Product product[], int st, int en){
	showLine_2(106);
	printf("| %-11s || %-30s | %-28s | %-9s | %-13s |\n",
	"Ma san pham", "Ten san pham", "Ma danh muc san pham", "So luong", "Gia thanh");
	showLine_2(106);
	int i;
	if(st < en){
		for(i = st; i < en; ++i){
			printf("| %-11s || %-30s | %-28s | %-9d | %-10d %s|\n",
			product[i].proId, product[i].proName,
			product[i].catId, product[i].quantity, product[i].price, "VND");
			if(i < en-1) showLine_1(106);
			else showLine_2(106);
		}
	}
	else{
		for(i = st-1; i >= en; --i){
			printf("| %-11s || %-33s | %-15s | %-11d | %-10.2f %s|\n",
			product[i].proId, product[i].proName,
			product[i].catId, product[i].quantity, product[i].price, "VND");
			if(i > en) showLine_1(106);
			else showLine_2(106);
		}
	}
	sleep(3);
	printf("Nhan phim bat ky de quay lai...");
	char c = getch();
	clearConsole();
}

void showProductMenu(){
	int n;
	do{
		printf("|-------------------------------------------|\n");
		printf("| ~*~*~*  HE THONG QUAN LY SAN PHAM  *~*~*~ |\n");
		printf("|  ~*~*~*   Menu quan ly san pham   *~*~*~  |\n");
		printf("|-------------------------------------------|\n");
		printf("|[1] Them san pham vao danh sach            |\n");
		printf("|[2] In danh sach san pham                  |\n");
		printf("|[3] Cap nhat thong tin san pham            |\n");
		printf("|[4] Xoa san pham                           |\n");
		printf("|[5] Tim kiem san pham                      |\n");
		printf("|[6] Sap xep san pham                       |\n");
		printf("|[7] Thoat                                  |\n");
		printf("|-------------------------------------------|\n");
		printf("Vui long nhap mot so: ");
		scanf("%d", &choice);
		switch(choice){
			case 1:
				system("cls");
				addProduct(productList, &n);
				break;
			case 2:
				system("cls");
				loadProductfromFile(productList, total1);
				showProductList(productList, total1);
				break;
			case 3:
				system("cls");
				loadProductfromFile(productList, total1);
				updateProduct(productList, total1);
				break;
			case 4:
				system("cls");
				loadProductfromFile(productList, total1);
				deleteProduct(productList, total1);
				break;
			case 5:
				system("cls");
				loadProductfromFile(productList, total1);
				searchProduct(productList, total1);
				break;
			case 6:
				system("cls");
				loadProductfromFile(productList, total1);
				sortProduct(productList, total1);
				break;
			case 7:
				system("cls");
				FILE *ptr = fopen("product.bin", "w"); fclose(ptr);
				exitMenu();
				return;
			default:
				printf("Gia tri khong hop le. Vui long nhap lai...");
				clearConsole();
				break;
		}
	}while(choice != 7);
}

void addProduct(Product product[], int *n){
	int x;
	do{
		printf("|------------------------------------|\n");
		printf("| [1] Them san pham                  |\n");
		printf("| [2] Quay ve menu chinh             |\n");
		printf("|------------------------------------|\n");
		printf("Vui long nhap mot so: ");
		scanf("%d", &x);
		if(x == 1){
			clearConsole();
			printf("Vui long nhap so san pham ban muon them: ");
			scanf("%d", n);
			fflush(stdin);
			int i;
			for(i = 0; i < *n; ++i){
				bool check = 0;
				while(!check){
					enterProInfo(product, i, &check);	
				}
				system("cls");
			}
			printf("Nhap san pham thanh cong\n");
			printf("Quay ve menu...");
			clearConsole();
		}
		else if(x == 2){
			printf("Quay ve menu chinh...");
			clearConsole();
		}
		else{
			printf("Khong hop le! Vui long thu lai...");
			clearConsole();
		}
	} while(x != 2);
}

void enterProInfo(Product product[], int i, bool *check){
	fflush(stdin);
	printf("----------------------------------------------------------\n");
	info(product[i].proId, "Ma san pham", 20);
	info(product[i].catId, "Ma danh muc san pham", 20);
	info(product[i].proName, "Ten san pham", 50);
	printf("So luong:  ");
	scanf("%d", &product[i].quantity);
	printf("Gia thanh: ");
	scanf("%d", &product[i].price);
	printf("----------------------------------------------------------\n");
	if(strcmp(product[i].proName, product[i].proId) == 0){
		printf("Ma va ten san pham khong duoc giong nhau. Vui long nhap lai...");
		clearConsole();
		return;
	}
	if(strcmp(product[i].proName, "\n") == 0 || strcmp(product[i].proName, " ") == 0){
		printf("Ten san pham khong duoc de trong. Vui long nhap lai...");
		clearConsole();
		return;
	}
	if(!total1){
		strcpy(idList[total1++], product[i].proId);
		*check = 1; return;
	}
	int j;
	for(j = 0; j < total1; ++j){
		if(strcmp(product[i].proId, idList[i]) == 0){
			printf("Trung ma san pham. Vui long nhap lai...");
			clearConsole();
			return;
		}
	}
	strcpy(idList[total1++], product[i].proId);
	*check = 1;
}


void showProductList(Product product[], int n){
	clearConsole();
	int x;
	do{
		printf("|------------------------------------|\n");
		printf("| [1] Hien thi danh sach san pham    |\n");
		printf("| [2] Quay ve menu chinh             |\n");
		printf("|------------------------------------|\n");
		printf("Vui long nhap mot so: ");
		scanf("%d", &x);
		if(x == 1){
			clearConsole();
			if(!total1){
				printf("Khong co du lieu\n");
				clearConsole();
			}
			else{
				printf("Danh sach san pham trong cua hang:\n");
				showProBoard(product, 0, total1);
			}
		}
		else if(x == 2){
			printf("Quay ve menu chinh...");
			clearConsole();
			return;
		}
		else{
			printf("Khong hop le! Vui long thu lai...");
			clearConsole();
		}
	} while(x != 2);
}


void updateProduct(Product product[], int n){
	int x;
	do{
		printf("|------------------------------------|\n");
		printf("| [1] Cap nhat san pham              |\n");
		printf("| [2] Quay ve menu chinh             |\n");
		printf("|------------------------------------|\n");
		printf("Vui long nhap mot so: ");
		scanf("%d", &x);
		if(x == 1){
			clearConsole();
			char checkID[20];
			fflush(stdin);
			printf("Vui long nhap ma san pham: ");
			fgets(checkID, sizeof(checkID), stdin);
			checkID[strcspn(checkID, "\n")] = '\0';
			bool ok = 0;
			int i;
			for(i = 0; i < n; ++i){
				if(stricmp(checkID, product[i].catId) == 0){
					ok = 1;
					printf("Tim thay san pham!\n");
					printf("Thong tin san pham:\n");
					printf("----------------------------------------------------------\n");
					printf("| Ma san pham : %s\n", product[i].proId);
					printf("| Ten san pham: %s\n", product[i].proName);
					printf("| Ma danh muc: %s\n", product[i].catId);
					printf("| So luong: %d\n", product[i].quantity);
					printf("| Gia thanh: %.2f\n", product[i].price);
					printf("----------------------------------------------------------\n");
					printf("Vui long cap nhat thong tin san pham:\n");
					printf("----------------------------------------------------------\n");
					printf("| Ten san pham: ");
					fgets(product[i].proName, 55, stdin);
					product[i].proName[strcspn(product[i].proName, "\n")] = '\0';
					printf("| Ma danh muc san pham: ");
					fgets(product[i].catId, 20, stdin);
					product[i].catId[strcspn(product[i].catId, "\n")] = '\0';
					printf("| So luong : ");
					scanf("%d", &product[i].quantity);
					printf("| Gia thanh: ");
					scanf("%d", &product[i].price);
					printf("----------------------------------------------------------\n");
					printf("Cap nhat thanh cong\n");
					break;
				}
			}
			if(!ok){
				printf("Khong co ket qua phu hop\n");
			}
			printf("Nhan phim bat ky de quay lai");
			char c = getch();
			clearConsole();
		}
		else if(x == 2){
			saveProductoFile(product, total1);
			clearConsole();
		}
		else{
			printf("Khong hop le! Vui long thu lai.");
			clearConsole();
		}
	} while(x != 2);
}


void deleteProduct(Product product[], int n){
	int x;
	do{
		printf("|------------------------------------|\n");
		printf("| [1] Xoa san pham                   |\n");
		printf("| [2] Quay ve menu chinh             |\n");
		printf("|------------------------------------|\n");
		printf("Vui long nhap mot so: ");
		scanf("%d", &x);
		switch(x){
			case 1:
				clearConsole();
				break;
			case 2:
				printf("Quay ve menu chinh...");
				clearConsole();
				return;
			default:
				printf("Gia tri khong hop le. Vui long nhap lai...");
				clearConsole();
				break;
		}
	}while(x != 2);
}


void searchProduct(Product product[], int n){
	int x;
	do{
		printf("|------------------------------------|\n");
		printf("| [1] Tim kiem san pham              |\n");
		printf("| [2] Quay ve menu chinh             |\n");
		printf("|------------------------------------|\n");
		printf("Vui long nhap mot so: ");
		scanf("%d", &x);
		switch(x){
			case 1:
				clearConsole();
				break;
			case 2:
				printf("Quay ve menu chinh...");
				clearConsole();
				return;
			default:
				printf("Gia tri khong hop le. Vui long nhap lai...");
				clearConsole();
				break;
		}
	}while(x != 2);
}


void sortProduct(Product product[], int n){
	int x;
	do{
		printf("|-----------------------------------------------|\n");
		printf("| [1] Sap xep san pham theo gia tien tang dan   |\n");
		printf("| [2] Sap xep san pham theo gia tien giam dan   |\n");
		printf("| [0] Quay ve menu chinh                        |\n");
		printf("|-----------------------------------------------|\n");
		printf(" Vui long nhap mot so: ");
		scanf("%d", &x);
		fflush(stdin);
		switch(x){
			case 1:
				system("cls");
				bubbleSort_1(product, total1);
				printf("Danh sach san pham trong cua hang:\n");
				showProBoard(product, 0, total1);
				break;
			case 2:
				system("cls");
				bubbleSort_1(product, total1);
				printf("Danh sach san pham trong cua hang:\n");
				showProBoard(product, total1, 0);
				break;
			case 0:
				printf("Quay ve menu chinh...");
				clearConsole();
				break;
			default:
				printf("Khong hop le! Vui long thu lai.");
				clearConsole();
				break;
		}
	}while(x);
}


void saveProductoFile(Product product[], int n){
	FILE *ptr;
	if(choice == 3 || choice == 6)
		ptr = fopen("product.bin", "wb");
	else
		ptr = fopen("product.bin", "ab");
	if(ptr == NULL){
		printf("Khong the mo file\n");
	}
	fwrite(product, sizeof(Product), n, ptr);
	int i;
	for(i = 1; i <= 100; ++i){
		printf("--- Dang luu: %d%c ---", i, '%');
		system("cls");
	}
	printf("--- Luu thanh cong ---\n");
	fclose(ptr);
}


void loadProductfromFile(Product product[], int n){

	FILE *ptr = fopen("product.bin", "rb");

	if(ptr == NULL){
		printf("Khong the mo tep\n");
	}
	fread(product, sizeof(Product), n, ptr);
	int i;
	for(i = 1; i <= 100; ++i){
		printf("--- Dang tai len: %d%c ---", i, '%');
		system("cls");
	}
	printf(" --- Tai len thanh cong ---\n");
	fclose(ptr);
}
