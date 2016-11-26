#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "functions.h"

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
    char c[2] = "";
    
    for (int i = 0; i < strlen(sCOMMAND); i++) {
        int  p;
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
                
                
                if (strcmp(c, "-") == 0 && strlen(sPARAMS[nN]) != 0) {
                    return 0;
                }
                
                if (strcmp(c, ".") == 0) {
                    char c1[2]  = "";
                    int  nCOUNT = 0;
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
    
    for (int a = 0; a < 200; a++) {
        sPARAMS[a] = malloc(sizeof(char)*200);
        strcpy (sPARAMS[a] , "");
    }
    
    if (SEPCOMMAND(sCOMMAND, sPARAMS) == 1) {
        char          sFILEFORMAT[5] = "";
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
            if (fclose(fp) == 0) {
                return 1;
            } else {
              return 0;
            }
            
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
    
    for (int a = 0; a < 200; a++) {
        sPARAMS[a] = malloc(sizeof(char)*200);
        strcpy (sPARAMS[a] , "");
    }
    
    if (SEPCOMMAND(sCOMMAND, sPARAMS) == 1) {
        char sFILEFORMAT[5] = "";
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
          int  nINSERT = 0;
          char sS[255] = "";
          int  nN = 0;
          while (feof(fp) == 0 && ferror(fp) == 0) {
            int sREAD;
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
                
                char c[2] = "";
                c[0] = (char)sREAD;
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
          if (fclose(fp) == 0) {
                return 1;
            } else {
              return 0;
            }
        } else {
          return 0;
        }
    }
    else
    {
        return 0;
    }
}