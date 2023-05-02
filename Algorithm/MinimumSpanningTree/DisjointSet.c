#include "DisjointSet.h"

/** Set1과 Set2를 같은 집합으로 합침
 *  [수정사항] 두 집합이 이미 한 집합 안에 있는 경우 예외처리 */
void DS_UnionSet(DisjointSet* Set1, DisjointSet* Set2) {
    // 각각의 Set을 최상위 부모로 바꿈
    Set1 = DS_FindSet(Set1);
    Set2 = DS_FindSet(Set2);

    // 이미 두 Set이 한 집합에 속하는 경우
    if (Set1 == Set2) return;

    // Set1을 Set2의 부모로 설정
    Set2->Parent = Set1;
}

/** Set의 부모를 찾아서 반환
 *  [수정사항]  재귀를 이용하여 부모를 찾고, 이 과정에서 경로 압축을 진행 */
DisjointSet* DS_FindSet(DisjointSet* Set) {
    if (Set->Parent == NULL) return Set;
    else return Set->Parent = DS_FindSet(Set->Parent);
}

/* 새로운 DisjointSet을 만들어서 반환 */
DisjointSet* DS_MakeSet(void* NewData) {
    DisjointSet* NewNode = (DisjointSet*)malloc(sizeof(DisjointSet));
    NewNode->Data   = NewData;
    NewNode->Parent = NULL;

    return NewNode;
}
/* Set을 자원 해제 */
void DS_DestroySet(DisjointSet* Set) {
    free(Set);
}
/* 두 Set이 다른 집합에 속해있다면 1, 아니면 0 반환 */
bool DS_isDiffrentSet( DisjointSet* Set1, DisjointSet* Set2 ) {
    return DS_FindSet(Set1) != DS_FindSet(Set2);
}