#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
	int day, month, year;
} Date;

typedef struct {
	char catID[20];
	char catName[55];
} Category;

typedef struct {
	char proId[20];
	char catId[20];
	char proName[55];
	int quantity;
	int price;
} Product;

typedef struct {
	char orderId[20];
	char customerId[20];
	Date date;
	Product product;
} Order;
