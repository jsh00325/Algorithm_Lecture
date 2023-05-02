#include "my_RBT.h"

extern RBTNode* NIL;

/* 새로운 노드 생성 */
RBTNode* RBT_CreateNode(ElementType new_data) {
    RBTNode* new_node = (RBTNode*) malloc(sizeof(RBTNode));
    new_node->parent = NULL;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->color = BLACK;
    new_node->data = new_data;
    return new_node;
}

/* 노드 소멸 */
void RBT_DestroyNode(RBTNode* node) {
    free(node);
}

/* Red Black Tree 구조 전체 소멸 */
void RBT_DestroyTree(RBTNode* tree) {
    if (tree->left != NIL)  RBT_DestroyTree(tree->left);
    if (tree->right != NIL) RBT_DestroyTree(tree->right);
    RBT_DestroyNode(tree);
}


/** target값을 가지는 노드 찾아 반환
 *  @details 재귀를 이용하여 O(lgN)의 시간복잡도로 노드를 찾음
 *  @param tree 찾고자 하는 RBT의 root 노드
 *  @param target 찾고자 하는 데이터 값 
 *  @return 값이 없으면 NULL을, 있으면 그 값을 가지는 노드를 반환함 */
RBTNode* RBT_SearchNode(RBTNode* tree, ElementType target) {
    if (tree == NULL) return NULL;
    if (tree == NIL) return NULL;

    if (tree->data > target)
        return RBT_SearchNode(tree->left, target);
    else if (tree->data < target)
        return RBT_SearchNode(tree->right, target);
    else return tree;
}

/** target값을 가지는 노드 찾아 반환
 *  @param tree 찾고자 하는 RBT의 root 주소
 *  @return tree를 노드로 하는 서브트리에서 최댓값을 가지는 노드 반환 */
RBTNode* RBT_SearchMaxNode(RBTNode* tree) {
    if (tree == NIL) return NIL;

    if (tree->right == NIL) return tree;
    else return RBT_SearchMaxNode(tree->right);
}

/** pNode를 기준으로 시계방향 회전
 *  @param root 변경하고자 하는 RBT의 root 주소
 *  @param pNode 회전의 기준점이 되는 노드  */
void RBT_RotateCW(RBTNode** root, RBTNode* pNode) {
    RBTNode* LC = pNode->left;

    pNode->left = LC->right;
    if (pNode->left != NIL)
        pNode->left->parent = pNode;

    LC->parent = pNode->parent;
    if (LC->parent == NULL)
        (*root) = LC;
    else {
        if (LC->parent->left == pNode)
            LC->parent->left = LC;
        else 
            LC->parent->right = LC;
    }

    LC->right = pNode;
    pNode->parent = LC;
}

/** pNode를 기준으로 반시계방향 회전
 *  @param root 변경하고자 하는 RBT의 root 주소
 *  @param pNode 회전의 기준점이 되는 노드  */
void RBT_RotateCCW(RBTNode** root, RBTNode* pNode) {
    RBTNode* RC = pNode->right;

    pNode->right = RC->left;
    if (pNode->right != NIL)
        pNode->right->parent = pNode;

    RC->parent = pNode->parent;
    if (RC->parent == NULL)
        (*root) = RC;
    else {
        if (RC->parent->left == pNode)
            RC->parent->left = RC;
        else 
            RC->parent->right = RC;
    }

    RC->left = pNode;
    pNode->parent = RC;
}


/** RBT에 새로운 노드를 삽입
 *  @param tree 삽입하려고 하는 RBT의 주소
 *  @param new_node 삽입하고자 하는 노드
 *  @return 삽입의 성공 여부(동일한 데이터가 있으면 실패) */
bool RBT_InsertNode(RBTNode** tree, RBTNode* new_node) {
    new_node->color = RED;
    new_node->left = NIL;
    new_node->right = NIL;
    if (!_RBT_FindAndInsert(tree, new_node)) return false;
    _RBT_RebuildAfterInsert(tree, new_node);
    return true;
}

/** 새로운 노드의 삽입 위치를 찾고 그 위치에 삽입
 *  @details 헤더파일 안에서 사용됨
 *  @param tree 삽입하려고 하는 RBT의 주소
 *  @param new_node 삽입하고자 하는 노드
 *  @return 삽입의 성공 여부(동일한 데이터가 있으면 실패) */
bool _RBT_FindAndInsert(RBTNode** tree, RBTNode* new_node) {
    if ((*tree) == NULL) {  // RBT가 비어있을 때
        (*tree) = new_node;
        return true;
    }

    if ((*tree)->data > new_node->data) {
        if ((*tree)->left == NIL) {
            (*tree)->left = new_node;
            new_node->parent = (*tree);
            return true;
        }
        else return _RBT_FindAndInsert(&((*tree)->left), new_node);
    }
    else if ((*tree)->data < new_node->data) {
        if ((*tree)->right == NIL) {
            (*tree)->right = new_node;
            new_node->parent = (*tree);
            return true;
        }
        else return _RBT_FindAndInsert(&((*tree)->right), new_node);
    }
    else return false;
}

/** 노드의 삽입 이후 RBT 구조를 만족하는지 확인하고, 맞춰주는 함수
 *  @details 헤더파일 안에서 사용됨(구조는 필기 참고)
 *  @param root 삽입하려고 하는 RBT의 root 노드 주소
 *  @param cur 구조를 만족하는지 확인하고자 하는 대상 노드 */
void _RBT_RebuildAfterInsert(RBTNode** root, RBTNode* cur) {
    if (cur == (*root) || cur->parent->color == BLACK) {
        (*root)->color = BLACK;
        return;
    }

    if (cur->parent->parent->left == cur->parent) {
        RBTNode* uncle = cur->parent->parent->right;
        if (uncle->color == RED) {
            cur->parent->color = BLACK;
            uncle->color = BLACK;
            cur->parent->parent->color = RED;
            _RBT_RebuildAfterInsert(root, cur->parent->parent);
        }
        else {
            if (cur->parent->right == cur) {
                cur = cur->parent;
                RBT_RotateCCW(root, cur);
            }
            cur->parent->color = BLACK;
            cur->parent->parent->color = RED;
            RBT_RotateCW(root, cur->parent->parent);
        }
    }
    else {
        RBTNode* uncle = cur->parent->parent->left;
        if (uncle->color == RED) {
            cur->parent->color = BLACK;
            uncle->color = BLACK;
            cur->parent->parent->color = RED;
            _RBT_RebuildAfterInsert(root, cur->parent->parent);
        }
        else {
            if (cur->parent->left == cur) {
                cur = cur->parent;
                RBT_RotateCW(root, cur);
            }
            cur->parent->color = BLACK;
            cur->parent->parent->color = RED;
            RBT_RotateCCW(root, cur->parent->parent);
        }
    }
}

/** RBT에서 target 값을 가지는 노드를 트리에서 삭제
 *  @details 이진탐색트리의 삭제 로직을 활용하여 노드를 삭제함
 *  @param root 찾고자 하는 RBT의 root 노드
 *  @param target 찾고자 하는 데이터의 값
 *  @return 찾는 값이 없으면 NULL, 있으면 그 노드 주소 반환 */
RBTNode* RBT_RemoveNode(RBTNode** root, ElementType target_data) {
    RBTNode* remove_node = NULL;    // 삭제해야 할 노드
    RBTNode* nxt_node = NULL;       // 삭제노드의 후임 노드
    RBTNode* target = RBT_SearchNode((*root), target_data);
    if (target == NULL) return NULL;

    // 삭제해야할 노드 지정
    if (target->left == NIL || target->right == NIL)
        remove_node = target;
    else {
        remove_node = RBT_SearchMaxNode(target->left);
        target->data = remove_node->data;
    }

    // 후임 노드 지정
    if (remove_node->left != NIL)
        nxt_node = remove_node->left;
    else
        nxt_node = remove_node->right;
    
    // 노드 삭제 후의 포인터 재지정
    if (remove_node->parent == NULL)
        (*root) = nxt_node;
    else {
        if (remove_node->parent->left == remove_node)
            remove_node->parent->left = nxt_node;
        else
            remove_node->parent->right = nxt_node;
    }
    nxt_node->parent = remove_node->parent;

    // 이중흑색일 경우 이를 해결
    if (remove_node->color == BLACK)
        _RBT_RebuildAfterRemove(root, nxt_node);
    return remove_node;
}

/** 이중흑색을 가지는 노드를 해결하는 함수
 *  @param root 리빌딩을 하는 RBT의 root 노드
 *  @param cur 이중흑색을 가지는 노드의 주소 */
void _RBT_RebuildAfterRemove(RBTNode** root, RBTNode* cur) {
    // root노드면 그냥 이중흑색을 없앨 수 있고
    // cur의 색이 빨간색이면 그냥 검은색으로 바꾸면 됨.
    if (cur->parent == NULL || cur->color == RED) {
        cur->color = BLACK;
        return;
    }

    if (cur->parent->left == cur) {
        RBTNode* sibling = cur->parent->right;

        if (sibling->color == RED) {
            sibling->color = BLACK;
            cur->parent->color = RED;
            RBT_RotateCCW(root, cur->parent);
            _RBT_RebuildAfterRemove(root, cur);
        }
        else {
            if (sibling->left->color == BLACK && sibling->right->color == BLACK) {
                sibling->color = RED;
                _RBT_RebuildAfterRemove(root, cur->parent);
            }
            else {
                if (sibling->left->color == RED) {
                    sibling->color = RED;
                    sibling->left->color = BLACK;
                    RBT_RotateCW(root, sibling);
                    sibling = cur->parent->right;
                }
                sibling->color = cur->parent->color;
                cur->parent->color = BLACK;
                sibling->right->color = BLACK;
                RBT_RotateCCW(root, cur->parent);
            }
        }
    }
    else {
        RBTNode* sibling = cur->parent->left;

        if (sibling->color == RED) {
            sibling->color = BLACK;
            cur->parent->color = RED;
            RBT_RotateCW(root, cur->parent);
            _RBT_RebuildAfterRemove(root, cur);
        }
        else {
            if (sibling->left->color == BLACK && sibling->right->color == BLACK) {
                sibling->color = RED;
                _RBT_RebuildAfterRemove(root, cur->parent);
            }
            else {
                if (sibling->right->color == RED) {
                    sibling->color = RED;
                    sibling->right->color = BLACK;
                    RBT_RotateCCW(root, sibling);
                    sibling = cur->parent->left;
                }
                sibling->color = cur->parent->color;
                cur->parent->color = BLACK;
                sibling->left->color = BLACK;
                RBT_RotateCW(root, cur->parent);
            }
        }
    }
}

void RBT_PrintTree( RBTNode* Node, int Depth, int BlackCount ) {
    int   i = 0;
    char c = 'X';
    int  v = -1;
    char cnt[100];

    if ( Node == NULL || Node == NIL) return;

    if ( Node->color == BLACK )
        BlackCount++;

    if ( Node->parent != NULL ) 
    {
        v = Node->parent->data;

        if ( Node->parent->left == Node )
            c = 'L';            
        else
            c = 'R';
    }

    if ( Node->left == NIL && Node->right == NIL )
        sprintf(cnt, "--------- %d", BlackCount );
    else
        sprintf(cnt, "");

    for ( i=0; i<Depth; i++)
        printf("  ");

    printf( "%d %s [%c,%d] %s\n", Node->data, 
            (Node->color == RED)?"RED":"BLACK", c, v, cnt);
    
    RBT_PrintTree( Node->left, Depth+1, BlackCount);
    RBT_PrintTree( Node->right, Depth+1, BlackCount );
}