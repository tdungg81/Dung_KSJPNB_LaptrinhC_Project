#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <windows.h>
#include <stdbool.h>
#include "function.h"


Category categoryList[55];
char idList[20][105];
int choice, total = 0;


void bubbleSort(Category category[], int n){
	int i, j;
	char tmp[55];
	for(i = 0; i < n; ++i){
		for(j = 0; j < n-1; ++j){
			if(strcmp(category[j].catName, category[j+1].catName) == 1){
				strcpy(tmp, category[j].catID);
				strcpy(category[j].catID, category[j+1].catID);
				strcpy(category[j+1].catID, tmp);
				strcpy(tmp, category[j].catName);
				strcpy(category[j].catName, category[j+1].catName);
				strcpy(category[j+1].catName, tmp);
			}
		}
	}
}


void clearConsole(){
	sleep(1);
	system("cls");
}

void info(char ans[], char name[], int size){
	char tmp[105];
	do{
		printf("%s (khong qua %d ky tu): ", name, size);
		fgets(tmp, sizeof(tmp), stdin);
		tmp[strcspn(tmp, "\n")] = '\0';
		if(strlen(tmp) > size){
			printf("Qua gioi han cho phep!!!\n");
			printf("----------------------------------------------------------\n");
		}
	}while(strlen(tmp) > size);
	strcpy(ans, tmp);
}

void showLine_1(int n){
	int i;
	printf("|");
	for(i = 1; i <= n; ++i){ printf("-"); }
	printf("|\n");
}

void showLine_2(int n){
	int i;
	printf("|");
	for(i = 1; i <= n; ++i){ printf("="); }
	printf("|\n");
}

void showCatBoard(Category category[], int st, int en){
	showLine_2(48);
	printf("| %-11s || %-32s|\n", "Ma danh muc", "Ten danh muc");
	showLine_2(48);
	int i;
	if(st < en){
		for(i = st; i < en; ++i){
			printf("| %-11s || %-32s|\n", category[i].catID, category[i].catName);
			if(i < en-1) showLine_1(48);
			else showLine_2(48);
		}	
	}
	else{
		for(i = st-1; i >= en; --i){
			printf("| %-11s || %-32s|\n", category[i].catID, category[i].catName);
			if(i > en) showLine_1(48);
			else showLine_2(48);
		}
	}
	sleep(3);
	printf("Nhan phim bat ky de quay lai...");
	char c = getch();
	clearConsole();
}

//Ham tach tu
int sepWord(char ans[][55], char s[]){
	int cnt = 0;
	char *spr = strtok(s, " ");
	while(spr != NULL){
		strcpy(ans[cnt++], spr);
		spr = strtok(NULL, " ");
	}
	return cnt;
}


void showAdminMenu(){
	int n;
	do{
		printf("|-------------------------------------------|\n");
		printf("| ~*~*~*  HE THONG QUAN LY SAN PHAM  *~*~*~ |\n");
		printf("|  ~*~*~*   Menu quan ly danh muc   *~*~*~  |\n");
		printf("|-------------------------------------------|\n");
		printf("|[1] Them danh muc vao danh sach            |\n");
		printf("|[2] In danh sach danh muc                  |\n");
		printf("|[3] Cap nhat thong tin danh muc            |\n");
		printf("|[4] Xoa danh muc                           |\n");
		printf("|[5] Tim kiem danh muc                      |\n");
		printf("|[6] Sap xep danh muc                       |\n");
		printf("|[7] Thoat                                  |\n");
		printf("|-------------------------------------------|\n");
		printf("Vui long nhap mot so: ");
		scanf("%d", &choice);
		switch(choice){
			case 1:
				system("cls");
				addCategory(categoryList, &n);
				break;
			case 2:
				system("cls");
				loadCategoryfromFile(categoryList, total);
				showCategoryList(categoryList, total);
				break;
			case 3:
				system("cls");
				loadCategoryfromFile(categoryList, total);
				updateCategory(categoryList, total);
				break;
			case 4:
				system("cls");
				loadCategoryfromFile(categoryList, total);
				deleteCategory(categoryList, total);
				break;
			case 5:
				system("cls");
				loadCategoryfromFile(categoryList, total);
				searchCategory(categoryList, total);
				break;
			case 6:
				system("cls");
				loadCategoryfromFile(categoryList, total);
				sortCategory(categoryList, total);
				break;
			case 7:
				system("cls");
				FILE *ptr = fopen("category.bin", "w"); fclose(ptr);
				exitMenu();
				return;
			default:
				printf("Gia tri khong hop le. Vui long nhap lai...");
				clearConsole();
				break;
		}
	}while(choice != 7);
}


void addCategory(Category category[], int *n){
	int x;
	do{
		printf("|------------------------------------|\n");
		printf("| [1] Them danh muc                  |\n");
		printf("| [2] Quay ve menu chinh             |\n");
		printf("|------------------------------------|\n");
		printf("Vui long nhap mot so: ");
		scanf("%d", &x);
		if(x == 1){
			clearConsole();
			printf("Vui long nhap so danh muc ban muon them: ");
			scanf("%d", n);
			fflush(stdin);
			int i;
			for(i = 0; i < *n; ++i){
				bool check = 0;
				while(!check){
					enterInfo(category, i, &check);	
				}
				system("cls");
			}
			printf("Nhap danh muc thanh cong\n");
			saveCategorytoFile(category, total);
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

void enterInfo(Category category[], int i, bool *check){
	char tmp[105];
	printf("----------------------------------------------------------\n");
	info(category[i].catID, "Ma danh muc", 20);
	info(category[i].catName, "Ten danh muc", 50);
	printf("----------------------------------------------------------\n");
	if(strcmp(category[i].catName, category[i].catID) == 0){
		printf("Ma va ten danh muc khong duoc giong nhau. Vui long nhap lai...");
		clearConsole();
		return;
	}
	if(strcmp(category[i].catName, "\n") == 0 || strcmp(category[i].catName, " ") == 0){
		printf("Ten danh muc khong duoc de trong. Vui long nhap lai...");
		clearConsole();
		return;
	}
	if(!total){
		strcpy(idList[total++], category[i].catID);
		*check = 1; return;
	}
	int j;
	for(j = 0; j < total; ++j){
		if(strcmp(category[i].catID, idList[i]) == 0){
			printf("Trung ma danh muc. Vui long nhap lai...");
			clearConsole();
			return;
		}
	}
	strcpy(idList[total++], category[i].catID);
	*check = 1;
}


void showCategoryList(Category category[], int n){
	clearConsole();
	int x;
	do{
		printf("|------------------------------------|\n");
		printf("| [1] Hien thi danh sach danh muc    |\n");
		printf("| [2] Quay ve menu chinh             |\n");
		printf("|------------------------------------|\n");
		printf("Vui long nhap mot so: ");
		scanf("%d", &x);
		if(x == 1){
			clearConsole();
			if(!total){
				printf("Khong co du lieu\n");
				clearConsole();
			}
			else{
				printf("Danh sach danh muc trong cua hang:\n");
				showCatBoard(category, 0, total);
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


void updateCategory(Category category[], int n){
	int x;
	do{
		printf("|------------------------------------|\n");
		printf("| [1] Cap nhat danh muc              |\n");
		printf("| [2] Quay ve menu chinh             |\n");
		printf("|------------------------------------|\n");
		printf("Vui long nhap mot so: ");
		scanf("%d", &x);
		if(x == 1){
			clearConsole();
			char checkID[20];
			fflush(stdin);
			printf("Vui long nhap ma danh muc: ");
			fgets(checkID, sizeof(checkID), stdin);
			checkID[strcspn(checkID, "\n")] = '\0';
			bool ok = 0;
			int i;
			for(i = 0; i < n; ++i){
				if(stricmp(checkID, category[i].catID) == 0){
					ok = 1;
					printf("Tim thay danh muc!\n");
					printf("Thong tin danh muc:\n");
					printf("----------------------------------------------------------\n");
					printf("| Ma danh muc : %s\n", category[i].catID);
					printf("| Ten danh muc: %s\n", category[i].catName);
					printf("----------------------------------------------------------\n");
					printf("Vui long cap nhat thong tin danh muc:\n");
					printf("----------------------------------------------------------\n");
					printf("| Ten danh muc: ");
					fgets(category[i].catName, 55, stdin);
					category[i].catName[strcspn(category[i].catName, "\n")] = '\0';
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
			saveCategorytoFile(category, total);
			clearConsole();
		}
		else{
			printf("Khong hop le! Vui long thu lai.");
			clearConsole();
		}
	} while(x != 2);
}


void deleteCategory(Category category[], int n){
	int x;
	do{
		printf("|------------------------------------|\n");
		printf("| [1] Xoa danh muc                   |\n");
		printf("| [2] Quay ve menu chinh             |\n");
		printf("|------------------------------------|\n");
		printf("Vui long nhap mot so: ");
		scanf("%d", &x);
		if(x == 1){
			clearConsole();
			char checkID[20];
			fflush(stdin);
			printf("Vui long nhap ma danh muc: ");
			fgets(checkID, sizeof(checkID), stdin);
			checkID[strcspn(checkID, "\n")] = '\0';
			bool ok = 0;
			int i;
			for(i = 0; i < n; ++i){
				if(stricmp(checkID, category[i].catID) == 0){
					ok = 1;
					printf("Tim thay danh muc!\n");
					printf("Thong tin danh muc:\n");
					printf("Ma danh muc : %s\n", category[i].catID);
					printf("Ten danh muc: %s\n", category[i].catName);
					printf("----------------------------------------------------------\n");
					printf("Ban co muon xoa danh muc nay khong? (Y/N) ");
					char c; scanf("%c", &c);
					if(c == 'Y' || c == 'y'){
						getchar();
						int j;
						for(j = i; j < n-1; ++j){
							strcpy(category[j].catID, category[j+1].catID);
							strcpy(category[j].catName, category[j+1].catName);
						}
						memset(category[n-1].catID, '\0', sizeof(category[n-1].catID));
						strcpy(category[n-1].catName, category[n-1].catID);
						printf("Xoa danh muc thanh cong\n");
						total -= 1;
					}
					else{
						printf("Quay lai menu...");
						clearConsole();
					}
					break;
				}
			}
			if(!ok){
				printf("Khong co ket qua phu hop\n");
				printf("Nhan phim bat ky de quay lai...");
				char c = getch();
				clearConsole();
			}
		}
		else if(x == 2){
			printf("Quay ve menu chinh...");
			saveCategorytoFile(categoryList, total);
			clearConsole();
			return;
		}
		else{
			printf("Khong hop le! Vui long thu lai...");
			clearConsole();
		}
	} while(x != 2);
}


void searchCategory(Category category[], int n){
	int x;
	do{
		printf("|------------------------------------|\n");
		printf("| [1] Tim kiem danh muc              |\n");
		printf("| [2] Quay ve menu chinh             |\n");
		printf("|------------------------------------|\n");
		printf("Vui long nhap mot so: ");
		scanf("%d", &x);
		fflush(stdin);
		if(x == 1){
			clearConsole();
			char name[55], nameL[55][55];
			Category res[55];
			printf("Vui long nhap tu khoa: ");
			fgets(name, sizeof(name), stdin);
			name[strcspn(name, "\n")] = '\0';
			int i, k, cnt = 0, ok = 0;
			k = sepWord(nameL, name);
			for(i = 0; i < n; ++i){
				int j;
				for(j = 0; j < k; ++j){
					if(strstr(category[i].catName, nameL[j]) != NULL){
						ok = 1;
						strcpy(res[cnt].catID, category[i].catID);
						strcpy(res[cnt++].catName, category[i].catName);
						break;
					}
				}
			}
			if(!ok){
				printf("Khong co ket qua phu hop\n");
			}
			else{
				printf("Danh sach ket qua tim kiem phu hop:\n");
				showCatBoard(res, 0, cnt);
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


void sortCategory(Category category[], int n){
	int x;
	do{
		printf("|------------------------------------------|\n");
		printf("| [1] Sap xep danh muc theo ten (A-Z)      |\n");
		printf("| [2] Sap xep danh muc theo ten (Z-A)      |\n");
		printf("| [0] Quay ve menu chinh                   |\n");
		printf("|------------------------------------------|\n");
		printf(" Vui long nhap mot so: ");
		scanf("%d", &x);
		fflush(stdin);
		switch(x){
			case 1:
				system("cls");
				bubbleSort(category, total);
				printf("Danh sach danh muc trong cua hang:\n");
				showCatBoard(category, 0, total);
				break;
			case 2:
				system("cls");
				bubbleSort(category, total);
				printf("Danh sach danh muc trong cua hang:\n");
				showCatBoard(category, total, 0);
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


void saveCategorytoFile(Category category[], int n){
	FILE *ptr;
	if(choice == 3 || choice == 6)
		ptr = fopen("category.bin", "wb");
	else
		ptr = fopen("category.bin", "ab");
	if(ptr == NULL){
		printf("Khong the mo file\n");
	}
	fwrite(category, sizeof(Category), n, ptr);
	int i;
	for(i = 1; i <= 100; ++i){
		printf("--- Dang luu: %d%c ---", i, '%');
		system("cls");
	}
	printf("--- Luu thanh cong ---\n");
	fclose(ptr);
}


void loadCategoryfromFile(Category category[], int n){
	FILE *ptr = fopen("category.bin", "rb");
	if(ptr == NULL){
		printf("Khong the mo tep\n");
	}
	fread(category, sizeof(Category), n, ptr);
	int i;
	for(i = 1; i <= 100; ++i){
		printf("--- Dang tai len: %d%c ---", i, '%');
		system("cls");
	}
	printf(" --- Tai len thanh cong ---\n");
	fclose(ptr);
}


void exitMenu(){
	printf("-----------------------------------------------\n");
	printf("|		--- Tam biet ---	      %c\n", '|');
	printf("-----------------------------------------------");
	total = choice = 0;
	clearConsole();
}

