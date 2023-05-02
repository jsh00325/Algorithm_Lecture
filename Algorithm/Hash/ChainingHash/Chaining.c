#include "Chaining.h"

/** 새로운 해시 테이블을 생성하고 반환
 *  @param TabSize 해시 테이블의 크기
 *  @return 새롭게 만들어진 해시 테이블 */
HashTable* CH_CreateHashTable(int TableSize) {
    HashTable* HT = (HashTable*) malloc(sizeof(HashTable));
    HT->table = (Tree*) malloc(sizeof(RBTNode) * TableSize);
    HT->tableSize = TableSize;
    for (int i = 0; i < HT->tableSize; i++)
        HT->table[i] = NULL;
    return HT;
}

/** 해시 테이블 삭제
 *  @brief 바로 삭제하는것이 아닌 연결된 RBT구조도 모두 날려줌
 *  @param HT 삭제할 해시 테이블 */
void CH_DestroyHashTable(HashTable* HT) {
    for (int i = 0; i < HT->tableSize; i++) {
        RBTNode* deleteNode = HT->table[i];
        RBT_DestroyTree(deleteNode);
    }
    free(HT->table);
    free(HT);
}

/** 해시 테이블에 추가
 *  @param HT 추가할 해시 테이블
 *  @param Key 추가할 값의 키
 *  @param Value 추가할 값의 값 */
void CH_Set(HashTable* HT, KeyType Key, ValueType Value) {
    int address = CH_Hash(Key, HT->tableSize);
    RBTNode* newNode = RBT_CreateNode(Key, Value);
    printf("[cur] %s\t%d\n", Key, address);

    if (HT->table[address] == NULL) {
        HT->table[address] = newNode;
    }
    else {
        printf("  [충돌 발생] key(%s), address(%d)\n", Key, address);
        RBT_InsertNode(&(HT->table[address]), newNode);
    }
}

/** 해시 테이블에서 key를 키로 하는 값이 있는지 탐색
 *  @param HT 찾을 해시 테이블
 *  @param Key 찾고자 하는 값의 키
 *  @return 찾은 값 (존재하지 않으면 NULL) */
ValueType CH_Get(HashTable* HT, KeyType Key) {
    int address = CH_Hash(Key, HT->tableSize);
    Tree tree = HT->table[address];
    Tree target = RBT_SearchNode(tree, Key);
    
    if (target == NULL) return NULL;
    else return target->value;
}

/** 해시 함수 (djb2 함수)
 *  @param Key 해시함수를 사용할 키값
 *  @param TableSize 추가할 해시 테이블의 크기(인덱스를 맞춰주기 위함) */
int CH_Hash(KeyType Key, int TableSize) {
    unsigned long hash = 5381;
    int c;
    while (c = *(Key++))
        hash = (((hash << 5) + hash) + c) % TableSize;
    return hash;
}