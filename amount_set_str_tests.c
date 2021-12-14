#include "amount_set_str_tests.h"
#include "amount_set_str.h"
#include "tests/test_utilities.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>


bool testAmountSetCreateDestroy()
{
    AmountSet AS = asCreate();
    ASSERT_TEST(AS != NULL);
    ASSERT_TEST(asGetSize(AS) == 0);
    ASSERT_TEST(asGetFirst(AS) == NULL);
    asDestroy(AS);
    asDestroy(NULL);
    return true;
}

bool testRegisterAndClearAndContains()
{
    AmountSet AS = asCreate();
    ASSERT_TEST(AS != NULL);
    ASSERT_TEST(asRegister(AS, NULL) == AS_NULL_ARGUMENT);

    char *name1= "omar";
    ASSERT_TEST(asRegister(AS,name1)==AS_SUCCESS);
    ASSERT_TEST(asContains(AS, "omar") == true);
    ASSERT_TEST(asRegister(AS,name1)== AS_ITEM_ALREADY_EXISTS);

    ASSERT_TEST(asClear(NULL) ==AS_NULL_ARGUMENT);

    char *name2= "";
    ASSERT_TEST(asRegister(AS, name2) == AS_SUCCESS);
    ASSERT_TEST(asContains(AS, "") == true);
    ASSERT_TEST(asContains(AS, "hAhHa") == false);

    char *name3= "******/-92j6";
    ASSERT_TEST(asRegister(AS, name3) == AS_SUCCESS);
    ASSERT_TEST(asContains(AS, "******/-92j6") == true);

    ASSERT_TEST(asContains(NULL, "omar") == false);
    ASSERT_TEST(asClear(AS) == AS_SUCCESS);

    ASSERT_TEST(asContains(AS, "omar") == false);

    ASSERT_TEST(asRegister(AS, "Wijdan") == AS_SUCCESS);
    ASSERT_TEST(asContains(AS, "Wijdan") == true);

    asDestroy(AS);
    return true;
}


bool testCopyAndRegisterAndGetSize()
{
    ASSERT_TEST(asCopy(NULL) == NULL);
    AmountSet AS = asCreate();
    ASSERT_TEST(AS != NULL);

    ASSERT_TEST(asRegister(NULL, "cat") == AS_NULL_ARGUMENT);
    ASSERT_TEST(asRegister(AS, NULL) == AS_NULL_ARGUMENT);
    ASSERT_TEST(asRegister(AS, NULL) == AS_NULL_ARGUMENT);

    ASSERT_TEST(asGetSize(NULL) == -1);

    char* j1 = "cat";
    ASSERT_TEST(asRegister(AS, j1) == AS_SUCCESS);
    ASSERT_TEST(asGetSize(AS) == 1);
    char* j2 = "cat";
    ASSERT_TEST(asRegister(AS, j2) == AS_ITEM_ALREADY_EXISTS);
    ASSERT_TEST(asGetSize(AS) == 1);
    char* j3 = "dat";
    ASSERT_TEST(asRegister(AS, j3) == AS_SUCCESS);
    ASSERT_TEST(asGetSize(AS) == 2);
    char* j4 = "bat";
    ASSERT_TEST(asRegister(AS, j4) == AS_SUCCESS);
    ASSERT_TEST(asGetSize(AS) == 3);

    AmountSet AS_copied = asCopy(NULL);
    ASSERT_TEST(AS_copied == NULL);

    AS_copied = asCopy(AS);
    ASSERT_TEST(AS_copied != NULL);
    asDestroy(AS);
    asDestroy(AS_copied);
    return true;   
}


bool testDelete()
{   
    ASSERT_TEST(asDelete(NULL, "cat") == AS_NULL_ARGUMENT); 
    ASSERT_TEST(asDelete(NULL, NULL) == AS_NULL_ARGUMENT); 

    AmountSet AS = asCreate();
    ASSERT_TEST(AS != NULL);
    ASSERT_TEST(asDelete(AS, NULL) == AS_NULL_ARGUMENT);
    ASSERT_TEST(asGetSize(AS) == 0);

    char* j1 = "cat";
    ASSERT_TEST(asRegister(AS, j1) == AS_SUCCESS);
    ASSERT_TEST(asGetSize(AS) == 1);
    char* j2 = "catyy";
    ASSERT_TEST(asRegister(AS, j2) == AS_SUCCESS);
    ASSERT_TEST(asGetSize(AS) == 2);
    char* j3 = "dat";
    ASSERT_TEST(asRegister(AS, j3) == AS_SUCCESS);
    ASSERT_TEST(asGetSize(AS) == 3);
    char* j4 = "bat";
    ASSERT_TEST(asRegister(AS, j4) == AS_SUCCESS);
    ASSERT_TEST(asGetSize(AS) == 4);

    ASSERT_TEST(asContains(AS, "catyy") == true);
    ASSERT_TEST(asContains(AS, "dat") == true);
    ASSERT_TEST(asContains(AS, "cat") == true);
    ASSERT_TEST(asContains(AS, "bat") == true);

    ASSERT_TEST(asDelete(AS,"bat") == AS_SUCCESS);
    ASSERT_TEST(asGetSize(AS) == 3);
    ASSERT_TEST(asDelete(AS,"cat") == AS_SUCCESS);
    ASSERT_TEST(asGetSize(AS) == 2);

    ASSERT_TEST(asDelete(AS,"bat") == AS_ITEM_DOES_NOT_EXIST);
    ASSERT_TEST(asDelete(AS,"rat") == AS_ITEM_DOES_NOT_EXIST);
    ASSERT_TEST(asContains(AS, "rat") == false);
    ASSERT_TEST(asGetSize(AS) == 2);

    ASSERT_TEST(asDelete(AS,"catyy") == AS_SUCCESS);
    ASSERT_TEST(asGetSize(AS) == 1);
    ASSERT_TEST(asDelete(AS,"dat") == AS_SUCCESS);
    ASSERT_TEST(asGetSize(AS) == 0);

    ASSERT_TEST(asContains(AS, "catyy") == false);
    ASSERT_TEST(asContains(AS, "dat") == false);
    ASSERT_TEST(asContains(AS, "cat") == false);
    ASSERT_TEST(asContains(AS, "bat") == false);
    
    asDestroy(AS);
    return true;
}


bool testGetFirstGetNext()
{
    ASSERT_TEST(asGetFirst(NULL) == NULL);
    ASSERT_TEST(asGetNext(NULL) == NULL);
    AmountSet AS = asCreate();
    ASSERT_TEST(AS != NULL);
    ASSERT_TEST(asGetFirst(NULL) == NULL);

    char* j1 = "far";
    ASSERT_TEST(asRegister(AS, j1) == AS_SUCCESS);
    ASSERT_TEST(asGetSize(AS) == 1);
    char* j2 = "dori";
    ASSERT_TEST(asRegister(AS, j2) == AS_SUCCESS);
    ASSERT_TEST(asGetSize(AS) == 2);
    char* j3 = "dari";
    ASSERT_TEST(asRegister(AS, j3) == AS_SUCCESS);
    ASSERT_TEST(asGetSize(AS) == 3);
    char* j4 = "ri";
    ASSERT_TEST(asRegister(AS, j4) == AS_SUCCESS);
    ASSERT_TEST(asGetSize(AS) == 4);

    ASSERT_TEST(strcmp(asGetFirst(AS), "dori")!=0);
    ASSERT_TEST(strcmp(asGetFirst(AS), "dari")==0);
    ASSERT_TEST(strcmp(asGetNext(AS), "dori")==0);

    ASSERT_TEST(asDelete(AS,"dari") == AS_SUCCESS);
    ASSERT_TEST(asContains(AS, "dari") == false);

    ASSERT_TEST(asContains(NULL, "dori") == false);
    ASSERT_TEST(asContains(NULL, "dari") == false);

    ASSERT_TEST(strcmp(asGetFirst(AS), "dori")==0);
    ASSERT_TEST(strcmp(asGetFirst(AS), "dari")!=0);
    ASSERT_TEST(strcmp(asGetNext(AS), "far")==0);

    ASSERT_TEST(asDelete(AS,"dori") == AS_SUCCESS);
    ASSERT_TEST(asContains(AS, "dori") == false);

    ASSERT_TEST(strcmp(asGetFirst(AS), "far")==0);
    ASSERT_TEST(strcmp(asGetFirst(AS), "ri")!=0);
    ASSERT_TEST(asGetNext(AS)!=NULL);

    ASSERT_TEST(asDelete(AS,"far") == AS_SUCCESS);
    ASSERT_TEST(asContains(AS, "far") == false);

    ASSERT_TEST(strcmp(asGetFirst(AS), "ri")==0);
    ASSERT_TEST(asGetNext(AS)==NULL);

    asDestroy(AS);
    return true;
}

bool testGetAmountAndChangeAmount()
{
    AmountSet AS = asCreate();
    ASSERT_TEST(AS != NULL);

    char* j1 = "noy";
    double amount;
    ASSERT_TEST(asRegister(AS, j1) == AS_SUCCESS);
    ASSERT_TEST(asGetSize(AS) == 1);
    ASSERT_TEST(asGetAmount(AS,"noy",&amount) == AS_SUCCESS);
    ASSERT_TEST(amount==0);
    ASSERT_TEST(asGetAmount(AS,"nanaa",&amount) ==AS_ITEM_DOES_NOT_EXIST );
    ASSERT_TEST(asGetAmount(NULL,"nanaa",&amount) ==AS_NULL_ARGUMENT );
    ASSERT_TEST(asGetAmount(NULL,NULL,&amount) ==AS_NULL_ARGUMENT );
    ASSERT_TEST(asGetAmount(AS,NULL,&amount) ==AS_NULL_ARGUMENT );
    ASSERT_TEST(asGetAmount(AS,"nanaa",NULL) ==AS_NULL_ARGUMENT );
    ASSERT_TEST(asChangeAmount(AS,"noy",5) == AS_SUCCESS);
    ASSERT_TEST(asGetAmount(AS,"noy",&amount) == AS_SUCCESS);
    ASSERT_TEST(amount==5);

    ASSERT_TEST(asChangeAmount(AS,"noy",-2) == AS_SUCCESS);
    ASSERT_TEST(asGetAmount(AS,"noy",&amount) == AS_SUCCESS);
    ASSERT_TEST(amount==3);

    ASSERT_TEST(asChangeAmount(AS,"noy",-2) == AS_SUCCESS);
    ASSERT_TEST(asGetAmount(AS,"noy",&amount) == AS_SUCCESS);
    ASSERT_TEST(amount==1);

    ASSERT_TEST(asChangeAmount(AS,"noy",-3) == AS_INSUFFICIENT_AMOUNT);
    ASSERT_TEST(asGetAmount(AS,"noy",&amount) == AS_SUCCESS);
    ASSERT_TEST(amount==1);

    ASSERT_TEST(asChangeAmount(NULL,"noy",5) == AS_NULL_ARGUMENT);
    ASSERT_TEST(asChangeAmount(AS,NULL,5) == AS_NULL_ARGUMENT);
    ASSERT_TEST(asChangeAmount(NULL,NULL,5) == AS_NULL_ARGUMENT);

    ASSERT_TEST(asGetAmount(AS,"cat",&amount) == AS_ITEM_DOES_NOT_EXIST);
    ASSERT_TEST(asChangeAmount(AS,"cat",0) == AS_ITEM_DOES_NOT_EXIST);

    asDestroy(AS);
    return true;
}


