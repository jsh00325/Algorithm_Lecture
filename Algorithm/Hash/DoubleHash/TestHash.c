#include "DoubleHash.h"

int main() {
    HashTable* HT = DH_CreateHashTable(20);

    DH_Set( &HT, "MSFT",   "Microsoft Corporation");
    DH_Set( &HT, "JAVA",   "Sun Microsystems");
    DH_Set( &HT, "REDH",   "Red Hat Linux");
    DH_Set( &HT, "APAC",   "Apache Org");
    DH_Set( &HT, "ZYMZZ",  "Unisys Ops Check");
    DH_Set( &HT, "IBM",    "IBM Ltd.");
    DH_Set( &HT, "ORCL",   "Oracle Corporation");
    DH_Set( &HT, "CSCO",   "Cisco Systems, Inc.");
    DH_Set( &HT, "GOOG",   "Google Inc.");
    DH_Set( &HT, "YHOO",   "Yahoo! Inc.");
    DH_Set( &HT, "NOVL",   "Novell, Inc.");
    printf("input test is done!\n\n");

    printf("key(%5s) - Value(%s)\n", "MSFT",   DH_Get( HT, "MSFT" ) );
    printf("key(%5s) - Value(%s)\n", "REDH",   DH_Get( HT, "REDH" ) );
    printf("key(%5s) - Value(%s)\n", "APAC",   DH_Get( HT, "APAC" ) );
    printf("key(%5s) - Value(%s)\n", "ZYMZZ",  DH_Get( HT, "ZYMZZ" ) );
    printf("key(%5s) - Value(%s)\n", "JAVA",   DH_Get( HT, "JAVA" ) );
    printf("key(%5s) - Value(%s)\n", "IBM",    DH_Get( HT, "IBM" ) );
    printf("key(%5s) - Value(%s)\n", "ORCL",   DH_Get( HT, "ORCL" ) );
    printf("key(%5s) - Value(%s)\n", "CSCO",   DH_Get( HT, "CSCO" ) );
    printf("key(%5s) - Value(%s)\n", "GOOG",   DH_Get( HT, "GOOG" ) );
    printf("key(%5s) - Value(%s)\n", "YHOO",   DH_Get( HT, "YHOO" ) );
    printf("key(%5s) - Value(%s)\n", "NOVL",   DH_Get( HT, "NOVL" ) );
    printf("find test is done!\n\n");

    DH_DestroyHashTable(HT);
    printf("program is end.\n");
    return 0;
}