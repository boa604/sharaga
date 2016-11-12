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
    char sLAS[1000] = "";
    int  nRES      = 0;
    
    if (nTYPE < 0) {
      strcpy(sLAS, "0123456789qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNMйцукенгшщзхъфывапролджэячсмитьбюЙЦУКЕНГШЩЗХЪФЫВАПРОЛДЖЭЯЧСМИТЬБЮ-.@#$%()/:№""'");
    }
    else
    {
      strcpy(sLAS, "0123456789-.");
    }
    
    for (int i = 0; i < strlen(sLAS) && nRES == 0; i++) {
        //printf("%c == %c, ", c, sLAS[i]);
        if (c == sLAS[i]) {
            nRES = 1;
        }
    }
    //printf("\nnRES == %d\n", nRES);
    return nRES;
}

int SEPCOMMAND(char* sCOMMAND, char *sPARAMS[])
{
    int  a    = -1;
    int  b    = -1;
    int  nN   = -2;
    int  p;
    char c[2] = "";
    
    for (int i = 0; i < strlen(sCOMMAND); i++) {
        
        c[0] = sCOMMAND[i];
        c[1] = '\0';
        
        if (strcmp(c, " ") == 0) {
            a = -1;
            b = -1;
        }
        else
        {
            b++;
            if (b == 0) {
                nN++;
            }
            a = 0;
        }
        
        if (a == 0)
        {
            //printf("\n---%d---\n", CHECKSYMB(c[0], -1));
            if ((p = CHECKSYMB(c[0], -1)) == 0) {
                return 0;
            }
        } 
        
        if (nN == 2 && a == 0) {
            if ( (p = CHECKSYMB(c[0], 0)) == 0) {
                return 0;
            }
        }
        //printf("Symbol = %s -- Num word = %d -- Result = %d\n", c, nN, p);
        if (nN > 3) {
            return 0;
        }
        
        if (nN >= 0 && nN < 4 && a == 0) {
            if (nN != 2) {
               strcat(sPARAMS[nN], c);
            } else {
                int nCOUNT = 0;
                
                if (strcmp(c, "-") == 0 && strlen(sPARAMS[nN]) != 0) {
                    return 0;
                }
                
                if (strcmp(c, ".") == 0) {
                    char c1[2] = "";
                    
                    for (int n = 0; n < strlen (sPARAMS[nN]); n++) {
                        c1[0] = sPARAMS[nN][n];
                        c1[1] = '\0';
                        
                        if (strcmp(c1, c) == 0) {
                            nCOUNT++;
                        }
                        
                        
                    }
                    
                    if (nCOUNT > 0) {
                        return 0;
                    }
                }
                
                strcat(sPARAMS[nN], c);
            }
            //printf("%s -- \n", sPARAMS[nN]);
        }
    }
    return nN+1;
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
        printf("Наименование продукта - %s, Категория продукта - %s, Цена - %f, Описание - %s\n"
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
            if (stPRODUCTS->prev == NULL && stPRODUCTS->next == NULL) {
                PRODUCTS = NULL;
            } else if (stPRODUCTS->prev == NULL && stPRODUCTS->next != NULL) {
                stPRODUCTS->next->prev = NULL;
                free(stPRODUCTS);
            } else if (stPRODUCTS->prev != NULL && stPRODUCTS->next == NULL) {
                stPRODUCTS->prev->next = NULL;
            } else if (stPRODUCTS->prev != NULL && stPRODUCTS->next != NULL){
                stPRODUCTS->next->prev = stPRODUCTS->prev;
                stPRODUCTS->prev->next = stPRODUCTS->next;
            } else {
                return 0;
            }
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
    int          p;
    
    for (int a = 0; a < 200; a++) {
        sPARAMS[a] = malloc(sizeof(char)*200);
        strcpy (sPARAMS[a] , "");
    }
    
    if ((p = SEPCOMMAND(sCOMMAND, sPARAMS)) == 4) {
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
        //printf("INSERT p = %d\n", p);
        return 0;
    }
}

int UPDATE(char* sCOMMAND) {
    
    char*        sPARAMS[200];
    struct TSHOP tsPRODUCT;
    
    for (int a = 0; a < 200; a++) {
        sPARAMS[a] = malloc(sizeof(char)*200);
        strcpy (sPARAMS[a] , "");
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
        sPARAMS[a] = malloc(sizeof(char)*200);
        strcpy (sPARAMS[a] , "");
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

int SAVE(char* sCOMMAND) {
    char*         sPARAMS[200];
    struct TLIST* stPRODUCTS     = PRODUCTS;
    char          sFILEFORMAT[5] = "";
    
    for (int a = 0; a < 200; a++) {
        sPARAMS[a] = malloc(sizeof(char)*200);
        strcpy (sPARAMS[a] , "");
    }
    
    if (SEPCOMMAND(sCOMMAND, sPARAMS) == 1) {
        
        sFILEFORMAT[0] = sPARAMS[0][strlen(sPARAMS[0]) - 4];
        sFILEFORMAT[1] = sPARAMS[0][strlen(sPARAMS[0]) - 3];
        sFILEFORMAT[2] = sPARAMS[0][strlen(sPARAMS[0]) - 2];
        sFILEFORMAT[3] = sPARAMS[0][strlen(sPARAMS[0]) - 1];
        sFILEFORMAT[4] = '\0';
        if (strcmp(sFILEFORMAT, ".txt") != 0) {
            printf("Запись в файл производится только в текстовый (.txt) файл");
            return 0;
        }
        
        FILE *fp;
        
        if ((fp = fopen(sPARAMS[0], "w")) != NULL) {
            
          while (stPRODUCTS != NULL) {
            if (fprintf(fp, "%s", stPRODUCTS->PRODUCT.PRODUCT_NAME) < 0) {
                return 0;
            };
            if (fprintf(fp, " ") < 0) {
                return 0;
            };
            if (fprintf(fp, "%s", stPRODUCTS->PRODUCT.CATEGORY) < 0) {
                return 0;
            };
            if (fprintf(fp, " ") < 0) {
                return 0;
            };
            if (fprintf(fp, "%f", stPRODUCTS->PRODUCT.PRICE) < 0) {
                return 0;
            };
            if (fprintf(fp, " ") < 0) {
                return 0;
            };
            if (fprintf(fp, "%s", stPRODUCTS->PRODUCT.NOTE) < 0) {
                return 0;
            };
            if (fprintf(fp, " ") < 0) {
                return 0;
            };
            stPRODUCTS = stPRODUCTS->next;
          }
        } else {
          return 0;
        }
        
        if (fclose(fp) == 0) {
            return 1;
        } else {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}

int LOAD(char* sCOMMAND) {
    char*         sPARAMS[200];
    struct TSHOP  stSHOP;
    char          sFILEFORMAT[5] = "";
    char          c[2]           = "";
    char          sREAD;
    int           nN             = 0;
    int           nINSERT        = 0;
    char          sS[255]        = "";
    
    for (int a = 0; a < 200; a++) {
        sPARAMS[a] = malloc(sizeof(char)*200);
        strcpy (sPARAMS[a] , "");
    }
    
    if (SEPCOMMAND(sCOMMAND, sPARAMS) == 1) {
        
        sFILEFORMAT[0] = sPARAMS[0][strlen(sPARAMS[0]) - 4];
        sFILEFORMAT[1] = sPARAMS[0][strlen(sPARAMS[0]) - 3];
        sFILEFORMAT[2] = sPARAMS[0][strlen(sPARAMS[0]) - 2];
        sFILEFORMAT[3] = sPARAMS[0][strlen(sPARAMS[0]) - 1];
        sFILEFORMAT[4] = '\0';
        if (strcmp(sFILEFORMAT, ".txt") != 0) {
            printf("Чтенение из файла производится только из текстового (.txt) файла");
            return 0;
        }
        
        FILE *fp;
        
        if ((fp = fopen(sPARAMS[0], "r")) != NULL) {
            
          while (feof(fp) == 0 && ferror(fp) == 0) {
            
            sREAD = fgetc(fp);
            if (ferror(fp) == 1) {
                return 0;
            }
            if (sREAD == EOF){
                if (feof(fp) == 0) {
                    printf("Ошибка чтения из файла\n");
                    return 0;
                }
                return 1;
            } else {
                c[0] = sREAD;
                c[1] = '\0';
                if (strcmp(c, " ") != 0) {
                    if (nN == 3) {
                        if (CHECKSYMB(sREAD, 0) == 0) {
                            printf("В файле некорректные данные");
                            return 0;
                        }
                    } else {
                        if (CHECKSYMB(sREAD, -1) == 0) {
                            printf("В файле некорректные данные");
                            return 0;
                        }
                    }
                    strcat(sS, c);
                } else {
                    if (nN == 0) {
                        strcpy(stSHOP.PRODUCT_NAME, sS);
                        strcpy(sS, "");
                        nN++;
                    } else if (nN == 1) {
                        strcpy(stSHOP.CATEGORY, sS);
                        strcpy(sS, "");
                        nN++;
                    } else if (nN == 2) {
                        stSHOP.PRICE = atof(sS);
                        strcpy(sS, "");
                        nN++;
                    } else if (nN == 3) {
                        strcpy(stSHOP.NOTE, sS);
                        strcpy(sS, "");
                        nINSERT = 1;
                        nN++;
                    }
                }
            }
            if (nINSERT == 1 && nN == 4) {    
                if (BASE_INSERT(stSHOP) == 0) {
                    printf("LOAD -- 552");
                    return 0;
                } else
                {
                    nN      = 0;
                    nINSERT = 0;
                };
            }
          }
          
        } else {
          return 0;
        }
        
        if (fclose(fp) == 0) {
            return 1;
        } else {
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
            if (INSERT(sCOMMAND) == 1) {
                printf("\nДобавление прошло успешно\n");
            } else {
                printf("\nДобавление не получилось");
            }
        } else if (strcmp(s, "update") == 0) {
            if (UPDATE(sCOMMAND) == 1) {
                printf("\nИсправление прошло успешно\n");
            } else {
                printf("\nИсправление не получилось");
            }
        } else if (strcmp(s, "remove") == 0) {
            if (DELETE(sCOMMAND) == 1) {
                printf("\nУдаление прошло успешно\n");
            } else {
                printf("\nУдаление не получилось");
            }
        } else if (strcmp(s, "show") == 0) {
            SHOWDATA();
        } else if (strcmp(s, "save") == 0) {
            if (SAVE(sCOMMAND) == 1) {
                printf("\nЗапись в файл прошла успешна\n");
            } else {
                printf("\nЗапись в файл не получилась");
            }
        } else if (strcmp(s, "load") == 0) {
            if (LOAD(sCOMMAND) == 1) {
                printf("\nЧтение из файла прошло успешно\n");
            } else {
                printf("\nЧтенение из файла не получилось");
            }
        }
      }
      //printf("%s -- %s\n", s, sCOMMAND);
    } while (nEXIT == 0);
    
    return;
}