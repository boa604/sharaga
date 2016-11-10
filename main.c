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

struct TLIST* PRODUCTS = NULL;

void WRITELEFT(){
    printf("\nВведите команду > ");
}

void WRITEHEADER(){
    system("clear");
    printf("Программа для работы с таблицей 'Интернет магазин'.\nРаботу выполнил студент группы П-403 Задйнайский Илья\n");
}

void CLEANSCREEN(){
    system("clear");
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

int CHECKSYMB(char c, int nTYPE) // nTYPE < 0 - проверка на буквы + цифры; >= 0 - проверка на цифры
{
    char sLAS[200] = "";
    int  nRES      = 0;
    
    if (nTYPE < 0) {
      strcpy(sLAS, "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNMйцукенгшщзхъфывапролджэячсмитьбюЙЦУКЕНГШЩЗХЪФЫВАПРОЛДЖЭЯЧСМИТЬБЮ-.@#$%()/:№""'0123456789");
    }
    else
    {
      strcpy(sLAS, "0123456789-.");
    }
    
    for (int i = 0; i < strlen(sLAS) && nRES == 0; i++) {
        if (c == sLAS[i]) {
            nRES = 1;
        }
    }
    printf("\nnRES == %d\n", nRES);
    return nRES;
}

int SEPCOMMAND(char* sCOMMAND, char *sPARAMS[])
{
    int  a    = -1;
    int  b    = 0;
    char c[2] = "";
    
    for (int i = 0; i < strlen(sCOMMAND); i++) {
        
        c[0] = sCOMMAND[i];
        c[1] = '\0';
        
        if (a < 0)
        {
            printf("\n---%d---\n", CHECKSYMB(c[0], -1));
            if (CHECKSYMB(c[0], -1) == 1) {
                b++;printf("CHECKSYMB -- 95");
                a = b;
            }
        } 
        if (strcmp(c, " ") == 0) {
            a = -1;
        }
        
        if (a == 3) {
            if (CHECKSYMB(c[0], 0) == 0) {
                return 0;
            }
        }
        
        if (a > 4) {
            return 0;
        }
        
        if (a > 0 && a < 5) {
            //printf("%s -- \n", c);
            if (a != 3) {
               strcat(sPARAMS[a-1], c);
            } else {
                int nCOUNT = 0;
                
                if (strcmp(c, "-") == 0 && strlen(sPARAMS[a-1]) != 0) {
                    return 0;
                }
                
                strcat(sPARAMS[a-1], c);
                
                if (strcmp(c, ".") == 0) {
                    char c1[2] = "";
                    
                    for (int n = 0; n < strlen (sPARAMS[a-1]); n++) {
                        c1[0] = sPARAMS[a-1][n];
                        c1[1] = '\0';
                        
                        if (strcmp(c1, c) == 0) {
                            nCOUNT++;
                        }
                        
                        
                    }
                    
                    if (nCOUNT > 1) {
                        return 0;
                    }
                }
            }
        }
    }
    return a;
}

void SHOWHELP() {
    printf("add - добавить запись\n   Параметры: Наименование продукта(строка, уникальный ключ) Категория(строка, уникальный ключ) Цена(число) Примечание(строка)\n");
    printf("clear - очистить экран\n");
    printf("help - показать все существующие команды\n");
    printf("load - загрузить из файла\n   Параметры: Наименование файла\n");
    printf("remove - удалить запись\n   Параметры: Наименование продукта(строка, уникальный ключ) Категория(строка, уникальный ключ)\n");
    printf("save - сохранить в файл\n   Параметры: Наименование файла\n");
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

void SHOWDATA()
{
    struct TLIST* stPRODUCTS = PRODUCTS;
    
    while (stPRODUCTS != NULL) {
        printf("Наименование продукта - %s, Категория продукта - %s, Цена - %f, Описание - %s"
              ,stPRODUCTS->PRODUCT.PRODUCT_NAME
              ,stPRODUCTS->PRODUCT.CATEGORY
              ,stPRODUCTS->PRODUCT.PRICE
              ,stPRODUCTS->PRODUCT.NOTE);
        stPRODUCTS = stPRODUCTS->next;
    }
    
    return;
}

int BASE_DELETE(struct TSHOP tsPRODUCT)
{
    struct TLIST* stPRODUCTS  = PRODUCTS;
    
    while (stPRODUCTS != NULL) {
        if (strcmp(PRODUCTS->PRODUCT.PRODUCT_NAME, tsPRODUCT.PRODUCT_NAME) == 0 
         && strcmp(PRODUCTS->PRODUCT.CATEGORY, tsPRODUCT.CATEGORY)         == 0)
        {
            free(stPRODUCTS);
            return 1;
        }
        stPRODUCTS = stPRODUCTS->next;
    }
    
    return 0;
}

int BASE_UPDATE(struct TSHOP tsPRODUCT)
{
    struct TLIST* stPRODUCTS  = PRODUCTS;
    
    while (stPRODUCTS != NULL) {
        if (strcmp(PRODUCTS->PRODUCT.PRODUCT_NAME, tsPRODUCT.PRODUCT_NAME) == 0 
         && strcmp(PRODUCTS->PRODUCT.CATEGORY, tsPRODUCT.CATEGORY)         == 0)
        {
            stPRODUCTS->PRODUCT.PRICE = tsPRODUCT.PRICE;
            strcpy(stPRODUCTS->PRODUCT.NOTE, tsPRODUCT.NOTE);
            return 1;
        } 
        stPRODUCTS = stPRODUCTS->next;
    }
    
    return 0;
}

int BASE_INSERT(struct TSHOP tsPRODUCT)
{
    struct TLIST* stPRODUCTS  = PRODUCTS;
    struct TLIST* stPRODUCTS2 = PRODUCTS;
    
    if (stPRODUCTS != NULL) {
        
        while (stPRODUCTS->next != NULL) {
            stPRODUCTS->next;
        }
        
        stPRODUCTS2          = (struct TLIST*) calloc(100, sizeof(struct TLIST));
        if (!stPRODUCTS2) {
            return 0;
        }
        stPRODUCTS2->PRODUCT = tsPRODUCT;
        stPRODUCTS2->next    = NULL;
        stPRODUCTS2->prev    = stPRODUCTS;
        
        stPRODUCTS->next     = stPRODUCTS2;
    }
    else {
        PRODUCTS          = (struct TLIST*) calloc(100, sizeof(struct TLIST));
        if (!PRODUCTS) {
            return 0;
        }
        PRODUCTS->PRODUCT = tsPRODUCT;
        PRODUCTS->next    = NULL;
        PRODUCTS->prev    = NULL;
    }
    
    return 1;
}

int INSERT(char* sCOMMAND) {
    
    char*        sPARAMS[200];
    struct TSHOP tsPRODUCT;
    
    for (int a = 0; a < 200; a++) {
        sPARAMS[a] = "";
    }
    
    if (SEPCOMMAND(sCOMMAND, sPARAMS) == 4) {
       if (CHECKUNIQ(sPARAMS[0], sPARAMS[1]) == 0) {
           
           strcpy(tsPRODUCT.PRODUCT_NAME, sPARAMS[0]);
           strcpy(tsPRODUCT.CATEGORY    , sPARAMS[1]);
           strcpy(tsPRODUCT.NOTE        , sPARAMS[3]);
           tsPRODUCT.PRICE = atof(sPARAMS[2]);
           
           if (BASE_INSERT(tsPRODUCT) == 1) {
               return 1;
           }
           else
           {
               return 0;
           }
           
       }
       else
       {
           return 0;
       }
    }
    else
    {
        return 0;
    }
}

int UPDATE(char* sCOMMAND) {
    
    char*        sPARAMS[200];
    struct TSHOP tsPRODUCT;
    
    for (int a = 0; a < 200; a++) {
        sPARAMS[a] = "";
    }
    
    if (SEPCOMMAND(sCOMMAND, sPARAMS) == 4) {
       if (CHECKUNIQ(sPARAMS[0], sPARAMS[1]) == 1) {
           
           strcpy(tsPRODUCT.PRODUCT_NAME, sPARAMS[0]);
           strcpy(tsPRODUCT.CATEGORY    , sPARAMS[1]);
           strcpy(tsPRODUCT.NOTE        , sPARAMS[3]);
           tsPRODUCT.PRICE = atof(sPARAMS[2]);
           
           if (BASE_UPDATE(tsPRODUCT) == 1) {
               return 1;
           }
           else
           {
               return 0;
           }
           
       }
       else
       {
           return 0;
       }
    }
    else
    {
        return 0;
    }
}

int DELETE(char* sCOMMAND) {
    
    char*        sPARAMS[200];
    struct TSHOP tsPRODUCT;
    
    for (int a = 0; a < 200; a++) {
        strcpy(sPARAMS[a], "");
    }
    
    if (SEPCOMMAND(sCOMMAND, sPARAMS) == 2) {
       if (CHECKUNIQ(sPARAMS[0], sPARAMS[1]) == 1) {
           
           strcpy(tsPRODUCT.PRODUCT_NAME, sPARAMS[0]);
           strcpy(tsPRODUCT.CATEGORY    , sPARAMS[1]);
           strcpy(tsPRODUCT.NOTE        , "");
           tsPRODUCT.PRICE        = 0.00;
           
           if (BASE_DELETE(tsPRODUCT) == 1) {
               return 1;
           }
           else
           {
               return 0;
           }
           
       }
       else
       {
           return 0;
       }
    }
    else
    {
        return 0;
    }
}

void main() {

    char s[100]    = "";
    char sEXIT[5]  = "quit";
    char sHELP[5]  = "help";
    char sCLEAR[6] = "clear";
    
    WRITEHEADER();
    
    int  nEXIT         = 0;
    char sCOMMAND[250] = "";
    
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
      else if (strcmp(sCOMMAND, sCLEAR) == 0)
      {
          CLEANSCREEN();
      }
      else
      {
        TREATCOMMAND(sCOMMAND, s);
        if (strcmp(s, "add") == 0) {
            INSERT(sCOMMAND);
        } else if (strcmp(s, "update") == 0) {
            UPDATE(sCOMMAND);
        } else if (strcmp(s, "remove") == 0) {
            DELETE(sCOMMAND);
        } else if (strcmp(s, "show") == 0) {
            SHOWDATA();
        }
      }
      printf("%s -- %s\n", s, sCOMMAND);
    } while (nEXIT == 0);
    
    return;
}