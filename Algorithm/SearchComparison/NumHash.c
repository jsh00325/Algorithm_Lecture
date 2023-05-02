#include "NumHash.h"

/** 새로운 해시 테이블을 생성하고 반환
 *  @param tableSize 해시 테이블의 크기
 *  @return 새롭게 만들어진 해시 테이블 */
HashTable* NH_CreateHashTable(int tableSize) {
    HashTable* HT = (HashTable*) malloc(sizeof(HashTable));
    HT->occupiedCount = 0;
    HT->tableSize = tableSize;
    HT->table = (NHNode*) malloc(sizeof(NHNode) * tableSize);
    memset(HT->table, 0, sizeof(HT->table));
    return HT;
}

/** 해시 테이블 삭제
 *  @param HT 삭제할 해시 테이블 */
void NH_DestroyHashTable(HashTable* HT) {
    free(HT->table);
    free(HT);
}

/** 해시 테이블에 값 추가
 *  @param HT 추가할 해시 테이블
 *  @param key 추가할 값의 키
 *  @param value 추가할 값의 값 */
void NH_Set(HashTable** HT, int key) {
    if ((*HT)->occupiedCount * 2 > (*HT)->tableSize) NH_Rehash(HT);
    
    int address = NH_Hash(key, (*HT)->tableSize);
    int step = NH_Hash2(key, (*HT)->tableSize);

    // 이중 해시를 이용하여 들어갈 자리 찾기
    /** @todo 만약 이중해시로 계속 건너갈 때 그 자리가 꽉 찼을 경우 예외처리 어떻게??  */
    while ((*HT)->table[address].status == OCCUPIED && (*HT)->table[address].key != key)         
        address = (address + step) % (*HT)->tableSize;

    // 해당 자리의 노드 값 채우기
    (*HT)->table[address].key = key;
    (*HT)->table[address].status = OCCUPIED;

    ((*HT)->occupiedCount)++;
}

/** 해시 테이블에서 key를 키로 하는 값이 있는지 탐색
 *  @param HT 찾을 해시 테이블
 *  @param key 찾고자 하는 값의 키
 *  @return 찾은 값 (존재하지 않으면 NULL) */
bool NH_Get(HashTable* HT, int key) {
    int address = NH_Hash(key, HT->tableSize);
    int origin_add = address;
    int step = NH_Hash2(key, HT->tableSize);

    while (HT->table[address].status != EMPTY && 
                HT->table[address].key != key) {
        address = (address + step) % HT->tableSize;
        //if (origin_add == address) return false;
    }
    return HT->table[address].key == key;
}

/** 해시 함수1
 *  @param key 해시함수를 사용할 키값
 *  @param tableSize 추가할 해시 테이블의 크기(인덱스를 맞춰주기 위함) */
int NH_Hash(int key, int tableSize) {
    unsigned long hash = 5381;
    while (key > 0) {
        hash = (((hash << 5) + hash) + 3 * (key % 7)) % tableSize;
        key /= 7;
    }
    return hash;
}

/** 해시 함수2
 *  @param key 해시함수를 사용할 키값
 *  @param tableSize 추가할 해시 테이블의 크기(인덱스를 맞춰주기 위함) */
int NH_Hash2(int key, int tableSize) {
    unsigned long hash = 0;
    while (key > 0) {
        hash = (hash << 6) + (hash << 16) + 5 * (key % 5) - hash;
        key /= 5;
    }
    return hash % (tableSize - 3) + 1;
}

/** 해시테이블의 50%가 채워졌을 때, 해시 테이블 크기 늘림
 *  @param HT 늘리고자 하는 해시 테이블 */
void NH_Rehash(HashTable** HT) {
    HashTable* newHT = NH_CreateHashTable((*HT)->tableSize * 2);
    for (int i = 0; i < (*HT)->tableSize; i++) {
        if ((*HT)->table[i].status == EMPTY) continue;
        NH_Set(&newHT, (*HT)->table[i].key);
    }
    NH_DestroyHashTable(*HT);
    (*HT) = newHT;
}