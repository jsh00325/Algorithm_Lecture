#include "Chaining.h"

/** ���ο� �ؽ� ���̺��� �����ϰ� ��ȯ
 *  @param TabSize �ؽ� ���̺��� ũ��
 *  @return ���Ӱ� ������� �ؽ� ���̺� */
HashTable* CH_CreateHashTable(int TableSize) {
    HashTable* HT = (HashTable*) malloc(sizeof(HashTable));
    HT->table = (Tree*) malloc(sizeof(RBTNode) * TableSize);
    HT->tableSize = TableSize;
    for (int i = 0; i < HT->tableSize; i++)
        HT->table[i] = NULL;
    return HT;
}

/** �ؽ� ���̺� ����
 *  @brief �ٷ� �����ϴ°��� �ƴ� ����� RBT������ ��� ������
 *  @param HT ������ �ؽ� ���̺� */
void CH_DestroyHashTable(HashTable* HT) {
    for (int i = 0; i < HT->tableSize; i++) {
        RBTNode* deleteNode = HT->table[i];
        RBT_DestroyTree(deleteNode);
    }
    free(HT->table);
    free(HT);
}

/** �ؽ� ���̺� �߰�
 *  @param HT �߰��� �ؽ� ���̺�
 *  @param Key �߰��� ���� Ű
 *  @param Value �߰��� ���� �� */
void CH_Set(HashTable* HT, KeyType Key, ValueType Value) {
    int address = CH_Hash(Key, HT->tableSize);
    RBTNode* newNode = RBT_CreateNode(Key, Value);
    printf("[cur] %s\t%d\n", Key, address);

    if (HT->table[address] == NULL) {
        HT->table[address] = newNode;
    }
    else {
        printf("  [�浹 �߻�] key(%s), address(%d)\n", Key, address);
        RBT_InsertNode(&(HT->table[address]), newNode);
    }
}

/** �ؽ� ���̺��� key�� Ű�� �ϴ� ���� �ִ��� Ž��
 *  @param HT ã�� �ؽ� ���̺�
 *  @param Key ã���� �ϴ� ���� Ű
 *  @return ã�� �� (�������� ������ NULL) */
ValueType CH_Get(HashTable* HT, KeyType Key) {
    int address = CH_Hash(Key, HT->tableSize);
    Tree tree = HT->table[address];
    Tree target = RBT_SearchNode(tree, Key);
    
    if (target == NULL) return NULL;
    else return target->value;
}

/** �ؽ� �Լ� (djb2 �Լ�)
 *  @param Key �ؽ��Լ��� ����� Ű��
 *  @param TableSize �߰��� �ؽ� ���̺��� ũ��(�ε����� �����ֱ� ����) */
int CH_Hash(KeyType Key, int TableSize) {
    unsigned long hash = 5381;
    int c;
    while (c = *(Key++))
        hash = (((hash << 5) + hash) + c) % TableSize;
    return hash;
}