#include <stdbool.h>
#include "datatype.h"

void showLine_1(int n);
void showLine_2(int n);


void clearConsole();
void exitMenu();

void info(char ans[], char name[], int size);

/*---------------------------------------------------------------------*/

void showAdminMenu();


void saveCategorytoFile(Category categoryList[], int n);
void loadCategoryfromFile(Category categoryList[], int n);


void addCategory(Category categoryList[], int *n);
void enterInfo(Category category[], int i, bool *check);

void showCategoryList(Category categoryList[], int n);
void showCatBoard(Category categoryList[], int st, int en);

void updateCategory(Category categoryList[], int n);
void deleteCategory(Category categoryList[], int n);
void searchCategory(Category categoryList[], int n);
void sortCategory(Category categoryList[], int n);

//Ham sap xep
void bubbleSort(Category categoryList[], int n);



void showProductMenu();


void saveProductoFile(Product ProductList[], int n);
void loadProductfromFile(Product ProductList[], int n);


void addProduct(Product ProductList[], int *n);
void enterProInfo(Product Product[], int i, bool *check);

void showProductList(Product ProductList[], int n);
void showProBoard(Product product[], int st, int en);

void updateProduct(Product ProductList[], int n);
void deleteProduct(Product ProductList[], int n);
void searchProduct(Product ProductList[], int n);
void sortProduct(Product ProductList[], int n);


void bubbleSort_1(Product productList[], int n);

