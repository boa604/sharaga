#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//9 База данных товаров Интернет-магазина. Поля: название товара, категория, цена товара, описание товара.

#define MAXPRODUCTS 100

struct TSHOP {
    char   PRODUCT_NAME[160];
    char   CATEGORY[160];
    double PRICE;
    char   NOTE[250];
};

struct TLIST {
    struct TSHOP  PRODUCT;
    struct TLIST* prev;
    struct TLIST* next;
};

struct TLIST* PRODUCTS;

void WRITELEFT(){
    printf("\nВведите команду > ");
}

void WRITEHEADER(){
    system("clear");
    printf("Программа для работы с таблицей 'Интернет магазин'.\nРаботу выполнил студент группы П-403 Задйнайский Илья\n");
}

int TREATCOMMAND(char* sCOMMAND, char* sRES) {
    
    int  nEXIT = 0;
    char s1[2] = "";
    strcpy(sRES, "");
    
    for (int i = 0; i < strlen(sCOMMAND) && nEXIT == 0; i++) {
        
        s1[0] = sCOMMAND[i];    
        s1[1] = '\0';
        
        if (strcmp(s1, " ") == 0) {
            nEXIT = 1;
        };
        
        if (nEXIT == 0) {
          strcat(sRES, s1);
        }
    }
    
}

void SHOWHELP() {
    printf("add - добавить запись\n   Параметры: Наименование продукта(строка, уникальный ключ) Категория(строка, уникальный ключ) Цена(число) Примечание(строка)\n");
    printf("help - показать все существующие команды\n");
    printf("remove - удалить запись\n   Параметры: Наименование продукта(строка, уникальный ключ) Категория(строка, уникальный ключ)\n");
    printf("quit - выход\n");
    printf("show - показать записи в БД\n");
    printf("update - исправить запись\n   Параметры: Наименование продукта(строка, уникальный ключ) Категория(строка, уникальный ключ) Цена(число) Примечание(строка)\n");
}

int CHECKUNIQ(char*   PRODUCT_NAME,char*   CATEGORY)
{
    struct TLIST* TPRODUCTS = PRODUCTS;
    
    while (TPRODUCTS != NULL)
    {
        if (strcmp(PRODUCTS->PRODUCT.PRODUCT_NAME, PRODUCT_NAME) == 0 && strcmp(PRODUCTS->PRODUCT.CATEGORY, CATEGORY) == 0)
        {
            return 1;
        }
        TPRODUCTS = TPRODUCTS->next;
    }
    
    return 0;
}

int BASE_ADD(struct TSHOP tsPRODUCT)
{
    printf("%s", tsPRODUCT.PRODUCT_NAME);
    return 1;
}

void main() {

    char s[100]   = "";
    char sEXIT[5] = "quit";
    char sHELP[5] = "help";
    
    WRITEHEADER();
    
    int  nEXIT         = 0;
    char sCOMMAND[250] = "";
    printf("AAAAAAAAAAAAAAAAAAAAA");
    do {
      WRITELEFT();
      fgets(sCOMMAND, sizeof(sCOMMAND) , stdin);
      sCOMMAND[strlen(sCOMMAND) - 1] = '\0';
      if (strcmp(sCOMMAND, sEXIT) == 0) {
          nEXIT = 1;
      }
      else if (strcmp(sCOMMAND, sHELP) == 0)
      {
          SHOWHELP();
      }
      else
      {
        TREATCOMMAND(sCOMMAND, s);
      }
      printf("%s -- %s\n", s, sCOMMAND);
    } while (nEXIT == 0);
    
    //WRITEHEADER();
    //WRITELEFT();
    return;
}