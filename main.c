#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "functions.h"

//9 База данных товаров Интернет-магазина. Поля: название товара, категория, цена товара, описание товара.

void WRITELEFT()
{
    printf("\nВведите команду > ");
}

void WRITEHEADER()
{
    system("clear");
    printf("Программа для работы с таблицей 'Интернет магазин'.\nРаботу выполнил студент группы П-403 Задйнайский Илья\n");
}

void CLEANSCREEN()
{
    system("clear");
}

void SHOWHELP()
{
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

void main()
{

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
                printf("\nДобавление не получилось\n");
            }
        } else if (strcmp(s, "update") == 0) {
            if (UPDATE(sCOMMAND) == 1) {
                printf("\nИсправление прошло успешно\n");
            } else {
                printf("\nИсправление не получилось\n");
            }
        } else if (strcmp(s, "remove") == 0) {
            if (DELETE(sCOMMAND) == 1) {
                printf("\nУдаление прошло успешно\n");
            } else {
                printf("\nУдаление не получилось\n");
            }
        } else if (strcmp(s, "show") == 0) {
            SHOWDATA();
        } else if (strcmp(s, "save") == 0) {
            if (SAVE(sCOMMAND) == 1) {
                printf("\nЗапись в файл прошла успешна\n");
            } else {
                printf("\nЗапись в файл не получилась\n");
            }
        } else if (strcmp(s, "load") == 0) {
            if (LOAD(sCOMMAND) == 1) {
                printf("\nЧтение из файла прошло успешно\n");
            } else {
                printf("\nЧтенение из файла не получилось\n");
            }
        }
      }
      //printf("%s -- %s\n", s, sCOMMAND);
    } while (nEXIT == 0);
    
    return;
}