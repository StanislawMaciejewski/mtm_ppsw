//
//  main.c
//  Testy
//
//  Created by Stanisław Maciejewski on 21/05/2019.
//  Copyright © 2019 Stanisław Maciejewski. All rights reserved.
//

//#include <stdio.h>
#define MAX_TOKEN_NR 3
#define MAX_KEYWORD_STRING_LTH 10
#define MAX_KEYWORD_NR 3
#define NULL '\0'
#include <stdio.h>
#include <string.h>

void CopyString(char pcSource[], char pcDestination[]){
    
    unsigned char ucLicznikZnakow;
    
    for(ucLicznikZnakow=0; pcSource[ucLicznikZnakow]; ucLicznikZnakow++){
        pcDestination[ucLicznikZnakow]=pcSource[ucLicznikZnakow];
    }
    pcDestination[ucLicznikZnakow]=pcSource[ucLicznikZnakow];
}

enum CompResult{DIFFERENT, EQUAL};

enum CompResult eCompareString(char pcStr1[], char pcStr2[]){
    
    unsigned char ucLicznikZnakow;
    
    for(ucLicznikZnakow=0; pcStr1[ucLicznikZnakow]; ucLicznikZnakow++){
        if (pcStr1[ucLicznikZnakow]!=pcStr2[ucLicznikZnakow]){
            return DIFFERENT;
        }
    }
    return EQUAL;
}

void AppendString(char pcSourceStr[],char pcDestinationStr[]){
    
    unsigned char ucLicznikZnakow;
    
    for(ucLicznikZnakow=0; pcDestinationStr[ucLicznikZnakow]; ucLicznikZnakow++){}
    CopyString(pcSourceStr, pcDestinationStr+ucLicznikZnakow);
}

void ReplaceCharactersInString(char pcString[],char cOldChar,char cNewChar){
    
    unsigned char ucLicznikZnakow;
    
    for(ucLicznikZnakow=0; pcString[ucLicznikZnakow]; ucLicznikZnakow++){
        if(pcString[ucLicznikZnakow]==cOldChar){
            pcString[ucLicznikZnakow]=cNewChar;
        }
    }
}
//---------------------------------------------------------------------------------

void UIntToHexStr (unsigned int uiValue, char pcStr[]){
    
    unsigned char ucTetradCounter;
    unsigned char ucCurrentTetrad;
    
    pcStr[0]='0';
    pcStr[1]='x';
    for(ucTetradCounter=0; ucTetradCounter<4; ucTetradCounter++){
        ucCurrentTetrad = ((uiValue >> (ucTetradCounter*4))&0x000F);
        if(ucCurrentTetrad>9)
            pcStr[5-ucTetradCounter]=ucCurrentTetrad-10+'A';
        else
            pcStr[5-ucTetradCounter]=ucCurrentTetrad+'0';
    }
    pcStr[6]='\0';
}

enum Result {OK, ERROR};

enum Result eHexStringToUInt(char pcStr[],unsigned int *puiValue){
    
    unsigned char ucCharCounter;
    
    if((pcStr[0] != '0') | (pcStr[1] != 'x') | (pcStr[2] == '\0'))
        return ERROR;
    *puiValue = 0;
    for(ucCharCounter=2;pcStr[ucCharCounter]!='\0';ucCharCounter++)
    {
        unsigned char ucNumberCounter = pcStr[ucCharCounter];
        if (ucCharCounter > 5)
            return ERROR;
        if(ucNumberCounter == '\0')
            return OK;
        *puiValue = *puiValue << 4;
        if((ucNumberCounter >= 'A') && (ucNumberCounter <= 'F'))
            *puiValue = *puiValue | (ucNumberCounter - 'A' + 10);
        else if ((ucNumberCounter >= '0') && (ucNumberCounter <= '9'))
            *puiValue = *puiValue | (ucNumberCounter - '0');
    }
    return OK;
}

void AppendUIntToString (unsigned int uiValue, char pcDestinationStr[]){
    
    unsigned char ucEndPointer;
    
    for(ucEndPointer=0;pcDestinationStr[ucEndPointer]!='\0';ucEndPointer++) {}
    UIntToHexStr(uiValue,pcDestinationStr+ucEndPointer);
}

//----------------------------------------------------------------------------

typedef enum TokenType
{KEYWORD, NUMBER, STRING} TokenType;

typedef enum KeywordCode
{ LD, ST, RST} KeywordCode;

//typedef enum CompResult
//{ DIFFERENT, EQUAL} CompResult;

//typedef enum Result
//{ OK, ERROR} Result;

typedef union TokenValue
{
    enum KeywordCode eKeyword;
    unsigned int uiNumber;
    char *pcString;
} TokenValue;

typedef struct Token
{
    enum TokenType eType;
    union TokenValue uValue;
} Token;

struct Token asToken[MAX_TOKEN_NR];

typedef struct Keyword
{
    enum KeywordCode eCode;
    char cString[MAX_KEYWORD_STRING_LTH + 1];
} Keyword;

struct Keyword asKeywordList[MAX_KEYWORD_NR]=
{
    {RST, "reset"},
    {LD, "load"},
    {ST, "store"}
};

unsigned char ucTokenNumber;

unsigned char ucFindTokensInString(char *pcString)
{
    unsigned char ucTokenPointer;
    unsigned char ucTokenCounter;
    char cCurrentChar;
    enum State {TOKEN, DELIMITER};
    enum State eState = DELIMITER;
    ucTokenCounter = 0;
    
    for(ucTokenPointer=0;;ucTokenPointer++)
    {
        cCurrentChar = pcString[ucTokenPointer];
        switch(eState)
        {
            case DELIMITER:
                if (cCurrentChar == '\0')
                {
                    return ucTokenCounter;
                }
                else if (cCurrentChar == ' '){}
                else
                {
                    eState = TOKEN;
                    asToken[ucTokenCounter].uValue.pcString = pcString+ucTokenPointer;
                    ucTokenCounter++;
                }
                break;
            case TOKEN:
                if(cCurrentChar == '\0')
                    return ucTokenCounter;
                else if (ucTokenCounter == MAX_TOKEN_NR)
                    return ucTokenCounter;
                else if (cCurrentChar != ' '){}
                else
                    eState = DELIMITER;
                break;
        }
    }
}







enum Result eStringToKeyword (char pcStr[], enum KeywordCode *peKeywordCode)
{
    unsigned char ucTokenNr;
    for (ucTokenNr=0; ucTokenNr<MAX_TOKEN_NR; ucTokenNr++)
    {
        if (eCompareString(pcStr, asKeywordList[ucTokenNr].cString) == EQUAL)
        {
            *peKeywordCode = asKeywordList[ucTokenNr].eCode;
            return OK;
        }
    }
    return ERROR;
}

void DecodeTokens()
{
    unsigned char ucTokenNr;
    Token* tValue;
    for (ucTokenNr=0; ucTokenNr<ucTokenNumber; ucTokenNr++)
    {
        tValue = &asToken[ucTokenNr];
        if (eStringToKeyword(tValue->uValue.pcString, &tValue->uValue.eKeyword) == OK)
        {
            tValue->eType = KEYWORD;
        }
        else if (eHexStringToUInt(tValue->uValue.pcString, &tValue->uValue.uiNumber) == OK)
        {
            tValue->eType = NUMBER;
        }
        else
        {
            tValue->eType = STRING;
        }
    }
}
void DecodeMsg(char *pcString)
{
    ucTokenNumber = ucFindTokensInString(pcString);
    ReplaceCharactersInString(pcString, ' ', '\0');
    DecodeTokens();
}

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
//pozmieniajcie zmienne i komentarze troche
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

void TestOf_CopyString(void) {
    
    printf("CopyString\n\n ");
    
    printf("Test 1 - ");
    //o takiej samej dlugosci
    char cCopyVersion1[]="tyuiop";
    CopyString("qwerty", cCopyVersion1);
    if (strcmp("qwerty", cCopyVersion1)==0) printf("OK\n\n "); else printf("Error\n\n ");
    
    printf("Test 2 - ");
    //pierwszy jest krotszy
    char cCopyVersion2[]="qwerty";
    CopyString("rty", cCopyVersion2);
    if (strcmp("rty", cCopyVersion2)==0) printf("OK\n\n "); else printf("Error\n\n ");
    
    printf("Test 3 - ");
    //pierwszy jest pusty
    char cAfterCopy3[]="qwerty";
    CopyString("", cAfterCopy3);
    if (strcmp("", cAfterCopy3)==0) printf("OK\n\n "); else printf("Error\n\n ");
}

void TestOf_eCompareString(void) {
    
    printf("eCompareString\n\n ");
    
    printf("Test 1 - ");
    //takie same, o tej samej dlugosci
    if (eCompareString("qwerty", "qwerty")==EQUAL) printf("OK\n\n "); else printf("Error\n\n ");
    
    printf("Test 2 - ");
    //rozne, ale o tej samej dlugosci
    if (eCompareString("qwerty", "tyuiop")==DIFFERENT) printf("OK\n\n "); else printf("Error\n\n ");
    
    printf("Test 3 - ");
    ///pierwszy jest pusty
    if (eCompareString("", "uiop")==DIFFERENT) printf("OK\n\n "); else printf("Error\n\n ");
    
    printf("Test 4 - ");
    //drugi jest pusty
    if (eCompareString("qwerty", "")==DIFFERENT) printf("OK\n\n "); else printf("Error\n\n ");
    
    printf("Test 5 - ");
    ///oba sa puste
    if (eCompareString("", "")==EQUAL) printf("OK\n\n "); else printf("Error\n\n ");
    
    printf("Test 6 - ");
    ///drugi jest dluzszy
    if (eCompareString("qwerty", "qwertyu")==DIFFERENT) printf("OK\n\n\n"); else printf("Error\n\n\n");
}

void TestOf_AppendString(void) {
    
    printf("AppendString\n\n ");
    
    printf("Test 1 - ");
    //dowolna zawartosc
    char cAppendStrTest1[]="tyuiop";
    AppendString("qwerty", cAppendStrTest1);
    if (strcmp(cAppendStrTest1, "ftyuiopqwerty")==0) printf("OK\n\n "); else printf("Error\n\n ");
    
    printf("Test 2 - ");
    //pierwszy jest pusty
    char cAppendStrTest2[]="qwerty";
    AppendString("", cAppendStrTest2);
    if (strcmp(cAppendStrTest2, "qwerty")==0) printf("OK\n\n "); else printf("Error\n\n ");
    
    printf("Test 3 - ");
    //drugi pusty
    char cAppendStrTest3[]="";
    AppendString("qwerty", cAppendStrTest3);
    if (strcmp(cAppendStrTest3, "qwerty")==0) printf("OK\n\n\n"); else printf("Error\n\n\n");
}

void TestOf_ReplaceCharactersInString(void) {
    
    printf("ReplaceCharactersInString\n\n ");
    
    printf("Test 1 - ");
    //zamiana znakow
    char cOrginalStr1[]="ala ma kota";
    ReplaceCharactersInString(cOrginalStr1, 'a', 'A');
    if (strcmp(cOrginalStr1, "AlA mA kotA")==0) printf("OK\n\n "); else printf("Error\n\n ");
    
    printf("Test 2 - ");
    //zmiana ze spacji na NULL
    char cOryginal2[]="ala ma kota";
    ReplaceCharactersInString(cOryginal2, ' ', '\0');
    if (strcmp(cOryginal2, "ala\0ma\0kota")==0) printf("OK\n\n"); else printf("Error\n\n");
}

void TestOf_UIntToHexStr(void) {
    
    printf("UIntToHexStr\n\n ");
    
    printf("Test 1 - ");
    //konwersja na lancuch tekstowy
    char cAfterChange[6];
    UIntToHexStr(0x079A, cAfterChange);
    if (strcmp(cAfterChange, "0x079A")==0) printf("OK\n "); else printf("Error\n\n ");
    
    printf("Test 2 - ");
    //zera po 0x w lancuchu
    UIntToHexStr(0x21, cAfterChange);
    if (strcmp(cAfterChange, "0x0021")==0) printf("OK\n "); else printf("Error\n\n");
}

void TestOf_eHexStringToUInt() {
    
    enum Result eReturnResult;
    unsigned int uiReturnValue;
    
    printf("eHexStringToUInt\n\n ");
    
    printf("Test 1 - ");
    //po tetradach 0,7,9,A
    eReturnResult = eHexStringToUInt("0x079A", &uiReturnValue);
    if (eReturnResult==OK) printf("OK\n\n "); else printf("Error\n\n ");
    
    printf("Test 2 - ");
    //za krotki
    eReturnResult = eHexStringToUInt("0x", &uiReturnValue);
    if (eReturnResult==ERROR) printf("OK\n\n "); else printf("Error\n\n ");
    
    printf("Test 3 - ");
    //za dlugi
    eReturnResult = eHexStringToUInt("0xEEAB2", &uiReturnValue);
    if (eReturnResult==ERROR) printf("OK\n\n "); else printf("Error\n\n ");
    
    printf("Test 4 - ");
    //poczatek rozny od 0x
    eReturnResult = eHexStringToUInt("qwerty", &uiReturnValue);
    if (eReturnResult==ERROR) printf("OK\n\n "); else printf("Error\n\n ");
    
    printf("Test 5 - ");
    //mniej znakow
    eReturnResult = eHexStringToUInt("0x034", &uiReturnValue);
    if (eReturnResult==OK) printf("OK\n\n"); else printf("Error\n\n");
}

void TestOf_AppendUIntToString() {
    
    printf("AppendUIntToString\n\n ");
    
    printf("Test 1 - ");
    //dopisywanie od NULLa stringa
    char cOrginal1[]="qwerty uiop";
    AppendUIntToString(0xAB12,cOrginal1);
    if (strcmp(cOrginal1,"qwerty uiop0xAB12")==0) printf("OK\n\n "); else printf("Error\n\n ");
    
    printf("Test 2 - ");
    //pusty string
    char cOrginal2[]="";
    AppendUIntToString(0xAB12,cOrginal2);
    if (strcmp(cOrginal2,"0xAB12")==0) printf("OK\n\n\n"); else printf("Error\n\n\n");
}

void TestOf_ucFindTokensInString() {
    
    unsigned char ucTokenNumber;
    
    printf("ucFindTokensInString\n\n ");
    
    printf("Test 1 - ");
    //maksymalna liczba tokenow
    ucTokenNumber=ucFindTokensInString("0x31AB QWERTY reset");
    if (ucTokenNumber==3) printf("OK\n\n "); else printf("Error\n\n ");
    
    printf("Test 2 - ");
    //tylko delimitery
    ucTokenNumber=ucFindTokensInString("    ");
    if (ucTokenNumber==0) printf("OK\n\n "); else printf("Error\n\n ");
    
    printf("Test 3 - ");
    //delimiter przed pierwszym tokenem, mniej niz 3 tokeny
    ucTokenNumber=ucFindTokensInString("   0x31AB QWERTY ");
    if (ucTokenNumber==2) printf("OK\n\n "); else printf("Error\n\n ");
    
    printf("Test 4 - ");
    //pomiedzy tokenami wiecej niz jeden delimiter
    ucTokenNumber=ucFindTokensInString("0x31AB   QWERTY      reset");
    if (ucTokenNumber==3) printf("OK\n\n "); else printf("Error\n\n ");
    
}

void TestOf_eStringToKeyword() {
    
    enum KeywordCode eTestCode;
    
    printf("eStringToKeyword\n\n ");
    
    printf("Test 1 - ");
    //reset - slowo kluczowe
    if (eStringToKeyword("reset", &eTestCode)==OK) printf("OK\n\n "); else printf("Error\n\n ");
    
    printf("Test 2 - ");
    //slowo inne niz kluczowe
    if (eStringToKeyword("qwerty", &eTestCode)==ERROR) printf("OK\n\n\n"); else printf("Error\n\n\n");
}

void TestOf_DecodeTokens() {
    
    unsigned char ucTokenNumber;
    
    char pcTokens[]="0x31AB QWERTY reset";
    
    printf("DecodeTokens\n\n ");
    
    printf("Test 1 - ");
    //liczba i zapis jej, string i ustawienie wskaznika, keyword i zapis kodu
    ucTokenNumber=ucFindTokensInString(pcTokens);
    ReplaceCharactersInString(pcTokens,' ','\0');
    DecodeTokens();
    if ((asToken[0].eType==NUMBER) && (asToken[0].uValue.uiNumber==0x31AB) &&
        (asToken[1].eType==STRING) && (&pcTokens[7]==asToken[1].uValue.pcString) &&
        (asToken[2].eType==KEYWORD) && (asToken[2].uValue.eKeyword==RST)) printf("OK\n\n\n"); else printf("Error\n\n\n");
}

void TestOf_DecodeMsg() {
    
    char pcDecodeTokens[]="0x31AB QWERTY reset";
    
    printf("DecodeMsg\n\n ");
    
    printf("Test 1 - ");
    //liczba, string, keyword
    DecodeMsg(pcDecodeTokens);
    if ((asToken[0].eType==NUMBER) && (asToken[0].uValue.uiNumber==0x31AB) &&
        (asToken[1].eType==STRING) && (&pcDecodeTokens[7]==asToken[1].uValue.pcString) &&
        (asToken[2].eType==KEYWORD) && (asToken[2].uValue.eKeyword==RST)) printf("OK\n\n\n"); else printf("Error\n\n\n");
}

int main(void) {
    printf("TESTY FUNKCJI - LANCUCHY ZNAKOWE - OPERACJE PROSTE\n\n\n");
    
    TestOf_CopyString();
    TestOf_eCompareString();
    TestOf_AppendString();
    TestOf_ReplaceCharactersInString();
    
    printf("TESTY FUNKCJI - LANCUCHY ZNAKOWE - KONWERSJE\n\n\n");
    
    TestOf_UIntToHexStr();
    TestOf_eHexStringToUInt();
    TestOf_AppendUIntToString();
    
    printf("TESTY FUNKCJI - DEKODOWANIE KOMUNIKATOW\n\n");
    
    TestOf_ucFindTokensInString();
    TestOf_eStringToKeyword();
    TestOf_DecodeTokens();
    TestOf_DecodeMsg();
}
