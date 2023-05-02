#include "DisjointSet.h"

/** Set1�� Set2�� ���� �������� ��ħ
 *  [��������] �� ������ �̹� �� ���� �ȿ� �ִ� ��� ����ó�� */
void DS_UnionSet(DisjointSet* Set1, DisjointSet* Set2) {
    // ������ Set�� �ֻ��� �θ�� �ٲ�
    Set1 = DS_FindSet(Set1);
    Set2 = DS_FindSet(Set2);

    // �̹� �� Set�� �� ���տ� ���ϴ� ���
    if (Set1 == Set2) return;

    // Set1�� Set2�� �θ�� ����
    Set2->Parent = Set1;
}

/** Set�� �θ� ã�Ƽ� ��ȯ
 *  [��������]  ��͸� �̿��Ͽ� �θ� ã��, �� �������� ��� ������ ���� */
DisjointSet* DS_FindSet(DisjointSet* Set) {
    if (Set->Parent == NULL) return Set;
    else return Set->Parent = DS_FindSet(Set->Parent);
}

/* ���ο� DisjointSet�� ���� ��ȯ */
DisjointSet* DS_MakeSet(void* NewData) {
    DisjointSet* NewNode = (DisjointSet*)malloc(sizeof(DisjointSet));
    NewNode->Data   = NewData;
    NewNode->Parent = NULL;

    return NewNode;
}
/* Set�� �ڿ� ���� */
void DS_DestroySet(DisjointSet* Set) {
    free(Set);
}
/* �� Set�� �ٸ� ���տ� �����ִٸ� 1, �ƴϸ� 0 ��ȯ */
bool DS_isDiffrentSet( DisjointSet* Set1, DisjointSet* Set2 ) {
    return DS_FindSet(Set1) != DS_FindSet(Set2);
}