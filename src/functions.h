#pragma once
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

extern struct TLIST* PRODUCTS;// = NULL;

int BASE_DELETE(struct TSHOP tsPRODUCT);
int BASE_UPDATE(struct TSHOP tsPRODUCT);
int BASE_INSERT(struct TSHOP tsPRODUCT);
int TREATCOMMAND(char* sCOMMAND, char* sRES);
int CHECKSYMB(char c, int nTYPE);
int SEPCOMMAND(char* sCOMMAND, char *sPARAMS[]);
int CHECKUNIQ(char*   PRODUCT_NAME,char*   CATEGORY);
void SHOWDATA();
int INSERT(char* sCOMMAND);
int UPDATE(char* sCOMMAND);
int DELETE(char* sCOMMAND);
int SAVE(char* sCOMMAND);
int LOAD(char* sCOMMAND);