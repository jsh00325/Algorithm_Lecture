#include "NumHash.h"

/** ���ο� �ؽ� ���̺��� �����ϰ� ��ȯ
 *  @param tableSize �ؽ� ���̺��� ũ��
 *  @return ���Ӱ� ������� �ؽ� ���̺� */
HashTable* NH_CreateHashTable(int tableSize) {
    HashTable* HT = (HashTable*) malloc(sizeof(HashTable));
    HT->occupiedCount = 0;
    HT->tableSize = tableSize;
    HT->table = (NHNode*) malloc(sizeof(NHNode) * tableSize);
    memset(HT->table, 0, sizeof(HT->table));
    return HT;
}

/** �ؽ� ���̺� ����
 *  @param HT ������ �ؽ� ���̺� */
void NH_DestroyHashTable(HashTable* HT) {
    free(HT->table);
    free(HT);
}

/** �ؽ� ���̺� �� �߰�
 *  @param HT �߰��� �ؽ� ���̺�
 *  @param key �߰��� ���� Ű
 *  @param value �߰��� ���� �� */
void NH_Set(HashTable** HT, int key) {
    if ((*HT)->occupiedCount * 2 > (*HT)->tableSize) NH_Rehash(HT);
    
    int address = NH_Hash(key, (*HT)->tableSize);
    int step = NH_Hash2(key, (*HT)->tableSize);

    // ���� �ؽø� �̿��Ͽ� �� �ڸ� ã��
    /** @todo ���� �����ؽ÷� ��� �ǳʰ� �� �� �ڸ��� �� á�� ��� ����ó�� ���??  */
    while ((*HT)->table[address].status == OCCUPIED && (*HT)->table[address].key != key)         
        address = (address + step) % (*HT)->tableSize;

    // �ش� �ڸ��� ��� �� ä���
    (*HT)->table[address].key = key;
    (*HT)->table[address].status = OCCUPIED;

    ((*HT)->occupiedCount)++;
}

/** �ؽ� ���̺��� key�� Ű�� �ϴ� ���� �ִ��� Ž��
 *  @param HT ã�� �ؽ� ���̺�
 *  @param key ã���� �ϴ� ���� Ű
 *  @return ã�� �� (�������� ������ NULL) */
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

/** �ؽ� �Լ�1
 *  @param key �ؽ��Լ��� ����� Ű��
 *  @param tableSize �߰��� �ؽ� ���̺��� ũ��(�ε����� �����ֱ� ����) */
int NH_Hash(int key, int tableSize) {
    unsigned long hash = 5381;
    while (key > 0) {
        hash = (((hash << 5) + hash) + 3 * (key % 7)) % tableSize;
        key /= 7;
    }
    return hash;
}

/** �ؽ� �Լ�2
 *  @param key �ؽ��Լ��� ����� Ű��
 *  @param tableSize �߰��� �ؽ� ���̺��� ũ��(�ε����� �����ֱ� ����) */
int NH_Hash2(int key, int tableSize) {
    unsigned long hash = 0;
    while (key > 0) {
        hash = (hash << 6) + (hash << 16) + 5 * (key % 5) - hash;
        key /= 5;
    }
    return hash % (tableSize - 3) + 1;
}

/** �ؽ����̺��� 50%�� ä������ ��, �ؽ� ���̺� ũ�� �ø�
 *  @param HT �ø����� �ϴ� �ؽ� ���̺� */
void NH_Rehash(HashTable** HT) {
    HashTable* newHT = NH_CreateHashTable((*HT)->tableSize * 2);
    for (int i = 0; i < (*HT)->tableSize; i++) {
        if ((*HT)->table[i].status == EMPTY) continue;
        NH_Set(&newHT, (*HT)->table[i].key);
    }
    NH_DestroyHashTable(*HT);
    (*HT) = newHT;
}