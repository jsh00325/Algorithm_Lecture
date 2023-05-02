#include "DoubleHash.h"

/** 새로운 해시 테이블을 생성하고 반환
 *  @param tableSize 해시 테이블의 크기
 *  @return 새롭게 만들어진 해시 테이블 */
HashTable* DH_CreateHashTable(int tableSize) {
    HashTable* HT = (HashTable*) malloc(sizeof(HashTable));
    HT->occupiedCount = 0;
    HT->tableSize = tableSize;
    HT->table = (DHNode*) malloc(sizeof(DHNode) * tableSize);
    memset(HT->table, 0, sizeof(HT->table));
    return HT;
}

/** 해시 테이블 삭제
 *  @param HT 삭제할 해시 테이블 */
void DH_DestroyHashTable(HashTable* HT) {
    for (int i = 0; i < HT->tableSize; i++)
        DH_ClearNode(&(HT->table[i]));
    free(HT->table);
    free(HT);
}

/** 해시 노드를 빈 값으로 변경하기
 *  @param node 변경하고자 하는 노드 */
void DH_ClearNode(DHNode* node) {
    if (node->status == OCCUPIED) {
        free(node->key);    node->key = NULL;
        free(node->value);  node->value = NULL;
    }
}

/** 해시 테이블에 값 추가
 *  @param HT 추가할 해시 테이블
 *  @param key 추가할 값의 키
 *  @param value 추가할 값의 값 */
void DH_Set(HashTable** HT, KeyType key, ValueType value) {
    if ((*HT)->occupiedCount * 2 > (*HT)->tableSize) DH_Rehash(HT);
    
    int address = DH_Hash(key, (*HT)->tableSize);
    int step = DH_Hash2(key, (*HT)->tableSize);

    // 이중 해시를 이용하여 들어갈 자리 찾기
    /** @todo 만약 이중해시로 계속 건너갈 때 그 자리가 꽉 찼을 경우 예외처리 어떻게??  */
    while ((*HT)->table[address].status == OCCUPIED &&
                strcmp((*HT)->table[address].key, key) != 0) {
        printf("  [충돌 발생] Key(%s), Address(%d), StepSize(%d)\n", 
                key, address, step);            
        address = (address + step) % (*HT)->tableSize;
    }

    // 해당 자리의 노드 값 채우기
    (*HT)->table[address].key = (char*) malloc(sizeof(char) * (strlen(key) + 1));
    strcpy((*HT)->table[address].key, key);
    (*HT)->table[address].value = (char*) malloc(sizeof(char) * (strlen(value) + 1));
    strcpy((*HT)->table[address].value, value);
    (*HT)->table[address].status = OCCUPIED;

    ((*HT)->occupiedCount)++;

    printf("[삽입] Key(%s) at Address(%d)\n", key, address);
}

/** 해시 테이블에서 key를 키로 하는 값이 있는지 탐색
 *  @param HT 찾을 해시 테이블
 *  @param key 찾고자 하는 값의 키
 *  @return 찾은 값 (존재하지 않으면 NULL) */
ValueType DH_Get(HashTable* HT, KeyType key) {
    int address = DH_Hash(key, HT->tableSize);
    int origin_add = address;
    int step = DH_Hash2(key, HT->tableSize);

    while (HT->table[address].status != EMPTY && 
                strcmp(HT->table[address].key, key) != 0) {
        address = (address + step) % HT->tableSize;
        if (origin_add == address) return NULL;
    }
    return HT->table[address].value;
}

/** 해시 함수1 (djb2 함수)
 *  @param key 해시함수를 사용할 키값
 *  @param tableSize 추가할 해시 테이블의 크기(인덱스를 맞춰주기 위함) */
int DH_Hash(KeyType key, int tableSize) {
    unsigned long hash = 5381;
    int c;
    while (c = *(key++))
        hash = (((hash << 5) + hash) + c) % tableSize;
    return hash;
}

/** 해시 함수2 (sdbm 함수)
 *  @param key 해시함수를 사용할 키값
 *  @param tableSize 추가할 해시 테이블의 크기(인덱스를 맞춰주기 위함) */
int DH_Hash2(KeyType key, int tableSize) {
    unsigned long hash = 0;
    int c;
    while (c = *(key++))
        hash = (hash << 6) + (hash << 16) + c - hash;
    return hash % (tableSize - 3) + 1;
}

/** 해시테이블의 50%가 채워졌을 때, 해시 테이블 크기 늘림
 *  @param HT 늘리고자 하는 해시 테이블 */
void DH_Rehash(HashTable** HT) {
    HashTable* newHT = DH_CreateHashTable((*HT)->tableSize * 2);
    for (int i = 0; i < (*HT)->tableSize; i++) {
        if ((*HT)->table[i].status == EMPTY) continue;
        DH_Set(&newHT, (*HT)->table[i].key, (*HT)->table[i].value);
    }
    DH_DestroyHashTable(*HT);
    (*HT) = newHT;
}