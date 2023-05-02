#include "DoubleHash.h"

/** ���ο� �ؽ� ���̺��� �����ϰ� ��ȯ
 *  @param tableSize �ؽ� ���̺��� ũ��
 *  @return ���Ӱ� ������� �ؽ� ���̺� */
HashTable* DH_CreateHashTable(int tableSize) {
    HashTable* HT = (HashTable*) malloc(sizeof(HashTable));
    HT->occupiedCount = 0;
    HT->tableSize = tableSize;
    HT->table = (DHNode*) malloc(sizeof(DHNode) * tableSize);
    memset(HT->table, 0, sizeof(HT->table));
    return HT;
}

/** �ؽ� ���̺� ����
 *  @param HT ������ �ؽ� ���̺� */
void DH_DestroyHashTable(HashTable* HT) {
    for (int i = 0; i < HT->tableSize; i++)
        DH_ClearNode(&(HT->table[i]));
    free(HT->table);
    free(HT);
}

/** �ؽ� ��带 �� ������ �����ϱ�
 *  @param node �����ϰ��� �ϴ� ��� */
void DH_ClearNode(DHNode* node) {
    if (node->status == OCCUPIED) {
        free(node->key);    node->key = NULL;
        free(node->value);  node->value = NULL;
    }
}

/** �ؽ� ���̺� �� �߰�
 *  @param HT �߰��� �ؽ� ���̺�
 *  @param key �߰��� ���� Ű
 *  @param value �߰��� ���� �� */
void DH_Set(HashTable** HT, KeyType key, ValueType value) {
    if ((*HT)->occupiedCount * 2 > (*HT)->tableSize) DH_Rehash(HT);
    
    int address = DH_Hash(key, (*HT)->tableSize);
    int step = DH_Hash2(key, (*HT)->tableSize);

    // ���� �ؽø� �̿��Ͽ� �� �ڸ� ã��
    /** @todo ���� �����ؽ÷� ��� �ǳʰ� �� �� �ڸ��� �� á�� ��� ����ó�� ���??  */
    while ((*HT)->table[address].status == OCCUPIED &&
                strcmp((*HT)->table[address].key, key) != 0) {
        printf("  [�浹 �߻�] Key(%s), Address(%d), StepSize(%d)\n", 
                key, address, step);            
        address = (address + step) % (*HT)->tableSize;
    }

    // �ش� �ڸ��� ��� �� ä���
    (*HT)->table[address].key = (char*) malloc(sizeof(char) * (strlen(key) + 1));
    strcpy((*HT)->table[address].key, key);
    (*HT)->table[address].value = (char*) malloc(sizeof(char) * (strlen(value) + 1));
    strcpy((*HT)->table[address].value, value);
    (*HT)->table[address].status = OCCUPIED;

    ((*HT)->occupiedCount)++;

    printf("[����] Key(%s) at Address(%d)\n", key, address);
}

/** �ؽ� ���̺��� key�� Ű�� �ϴ� ���� �ִ��� Ž��
 *  @param HT ã�� �ؽ� ���̺�
 *  @param key ã���� �ϴ� ���� Ű
 *  @return ã�� �� (�������� ������ NULL) */
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

/** �ؽ� �Լ�1 (djb2 �Լ�)
 *  @param key �ؽ��Լ��� ����� Ű��
 *  @param tableSize �߰��� �ؽ� ���̺��� ũ��(�ε����� �����ֱ� ����) */
int DH_Hash(KeyType key, int tableSize) {
    unsigned long hash = 5381;
    int c;
    while (c = *(key++))
        hash = (((hash << 5) + hash) + c) % tableSize;
    return hash;
}

/** �ؽ� �Լ�2 (sdbm �Լ�)
 *  @param key �ؽ��Լ��� ����� Ű��
 *  @param tableSize �߰��� �ؽ� ���̺��� ũ��(�ε����� �����ֱ� ����) */
int DH_Hash2(KeyType key, int tableSize) {
    unsigned long hash = 0;
    int c;
    while (c = *(key++))
        hash = (hash << 6) + (hash << 16) + c - hash;
    return hash % (tableSize - 3) + 1;
}

/** �ؽ����̺��� 50%�� ä������ ��, �ؽ� ���̺� ũ�� �ø�
 *  @param HT �ø����� �ϴ� �ؽ� ���̺� */
void DH_Rehash(HashTable** HT) {
    HashTable* newHT = DH_CreateHashTable((*HT)->tableSize * 2);
    for (int i = 0; i < (*HT)->tableSize; i++) {
        if ((*HT)->table[i].status == EMPTY) continue;
        DH_Set(&newHT, (*HT)->table[i].key, (*HT)->table[i].value);
    }
    DH_DestroyHashTable(*HT);
    (*HT) = newHT;
}