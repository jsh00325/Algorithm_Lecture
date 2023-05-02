#include "RedBlackTree.h"
#include "Chaining.h"

RBTNode* NIL;
int main(void) {
    NIL = RBT_CreateNode("NIL", "This is Nil Node");
    NIL->color = BLACK;

    HashTable* HT = CH_CreateHashTable(50);

    CH_Set( HT, "MSFT",   "Microsoft Corporation");
    CH_Set( HT, "JAVA",   "Sun Microsystems");
    CH_Set( HT, "REDH",   "Red Hat Linux");
    CH_Set( HT, "APAC",   "Apache Org");
    CH_Set( HT, "ZYMZZ",  "Unisys Ops Check");
    CH_Set( HT, "IBM",    "IBM Ltd.");
    CH_Set( HT, "ORCL",   "Oracle Corporation");
    CH_Set( HT, "CSCO",   "Cisco Systems, Inc.");
    CH_Set( HT, "GOOG",   "Google Inc.");
    CH_Set( HT, "YHOO",   "Yahoo! Inc.");
    CH_Set( HT, "NOVL",   "Novell, Inc.");
    printf("input test is done!\n\n");

    printf("Key:%s, Value:%s\n", "MSFT",   CH_Get( HT, "MSFT" ) );
    printf("Key:%s, Value:%s\n", "REDH",   CH_Get( HT, "REDH" ) );
    printf("Key:%s, Value:%s\n", "APAC",   CH_Get( HT, "APAC" ) );
    printf("Key:%s, Value:%s\n", "ZYMZZ",  CH_Get( HT, "ZYMZZ" ) );
    printf("Key:%s, Value:%s\n", "JAVA",   CH_Get( HT, "JAVA" ) );
    printf("Key:%s, Value:%s\n", "IBM",    CH_Get( HT, "IBM" ) );
    printf("Key:%s, Value:%s\n", "ORCL",   CH_Get( HT, "ORCL" ) );
    printf("Key:%s, Value:%s\n", "CSCO",   CH_Get( HT, "CSCO" ) );
    printf("Key:%s, Value:%s\n", "GOOG",   CH_Get( HT, "GOOG" ) );
    printf("Key:%s, Value:%s\n", "YHOO",   CH_Get( HT, "YHOO" ) );
    printf("Key:%s, Value:%s\n", "NOVL",   CH_Get( HT, "NOVL" ) );
    printf("find test is done!\n\n");

    CH_DestroyHashTable(HT);
    printf("program is end.\n");
    return 0;
}