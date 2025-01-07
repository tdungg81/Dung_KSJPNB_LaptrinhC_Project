#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "function.h"
#include "account.h"


int main(int argc, char *argv[]) {
	int x;
	do{
		showLoginMenu(&x);
		if(!x) break;
		showChoosingMode();
	} while(x != 0);
	return 0;
}

