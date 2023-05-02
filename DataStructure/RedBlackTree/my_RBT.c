#include "my_RBT.h"

extern RBTNode* NIL;

/* ���ο� ��� ���� */
RBTNode* RBT_CreateNode(ElementType new_data) {
    RBTNode* new_node = (RBTNode*) malloc(sizeof(RBTNode));
    new_node->parent = NULL;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->color = BLACK;
    new_node->data = new_data;
    return new_node;
}

/* ��� �Ҹ� */
void RBT_DestroyNode(RBTNode* node) {
    free(node);
}

/* Red Black Tree ���� ��ü �Ҹ� */
void RBT_DestroyTree(RBTNode* tree) {
    if (tree->left != NIL)  RBT_DestroyTree(tree->left);
    if (tree->right != NIL) RBT_DestroyTree(tree->right);
    RBT_DestroyNode(tree);
}


/** target���� ������ ��� ã�� ��ȯ
 *  @details ��͸� �̿��Ͽ� O(lgN)�� �ð����⵵�� ��带 ã��
 *  @param tree ã���� �ϴ� RBT�� root ���
 *  @param target ã���� �ϴ� ������ �� 
 *  @return ���� ������ NULL��, ������ �� ���� ������ ��带 ��ȯ�� */
RBTNode* RBT_SearchNode(RBTNode* tree, ElementType target) {
    if (tree == NULL) return NULL;
    if (tree == NIL) return NULL;

    if (tree->data > target)
        return RBT_SearchNode(tree->left, target);
    else if (tree->data < target)
        return RBT_SearchNode(tree->right, target);
    else return tree;
}

/** target���� ������ ��� ã�� ��ȯ
 *  @param tree ã���� �ϴ� RBT�� root �ּ�
 *  @return tree�� ���� �ϴ� ����Ʈ������ �ִ��� ������ ��� ��ȯ */
RBTNode* RBT_SearchMaxNode(RBTNode* tree) {
    if (tree == NIL) return NIL;

    if (tree->right == NIL) return tree;
    else return RBT_SearchMaxNode(tree->right);
}

/** pNode�� �������� �ð���� ȸ��
 *  @param root �����ϰ��� �ϴ� RBT�� root �ּ�
 *  @param pNode ȸ���� �������� �Ǵ� ���  */
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

/** pNode�� �������� �ݽð���� ȸ��
 *  @param root �����ϰ��� �ϴ� RBT�� root �ּ�
 *  @param pNode ȸ���� �������� �Ǵ� ���  */
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


/** RBT�� ���ο� ��带 ����
 *  @param tree �����Ϸ��� �ϴ� RBT�� �ּ�
 *  @param new_node �����ϰ��� �ϴ� ���
 *  @return ������ ���� ����(������ �����Ͱ� ������ ����) */
bool RBT_InsertNode(RBTNode** tree, RBTNode* new_node) {
    new_node->color = RED;
    new_node->left = NIL;
    new_node->right = NIL;
    if (!_RBT_FindAndInsert(tree, new_node)) return false;
    _RBT_RebuildAfterInsert(tree, new_node);
    return true;
}

/** ���ο� ����� ���� ��ġ�� ã�� �� ��ġ�� ����
 *  @details ������� �ȿ��� ����
 *  @param tree �����Ϸ��� �ϴ� RBT�� �ּ�
 *  @param new_node �����ϰ��� �ϴ� ���
 *  @return ������ ���� ����(������ �����Ͱ� ������ ����) */
bool _RBT_FindAndInsert(RBTNode** tree, RBTNode* new_node) {
    if ((*tree) == NULL) {  // RBT�� ������� ��
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

/** ����� ���� ���� RBT ������ �����ϴ��� Ȯ���ϰ�, �����ִ� �Լ�
 *  @details ������� �ȿ��� ����(������ �ʱ� ����)
 *  @param root �����Ϸ��� �ϴ� RBT�� root ��� �ּ�
 *  @param cur ������ �����ϴ��� Ȯ���ϰ��� �ϴ� ��� ��� */
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

/** RBT���� target ���� ������ ��带 Ʈ������ ����
 *  @details ����Ž��Ʈ���� ���� ������ Ȱ���Ͽ� ��带 ������
 *  @param root ã���� �ϴ� RBT�� root ���
 *  @param target ã���� �ϴ� �������� ��
 *  @return ã�� ���� ������ NULL, ������ �� ��� �ּ� ��ȯ */
RBTNode* RBT_RemoveNode(RBTNode** root, ElementType target_data) {
    RBTNode* remove_node = NULL;    // �����ؾ� �� ���
    RBTNode* nxt_node = NULL;       // ��������� ���� ���
    RBTNode* target = RBT_SearchNode((*root), target_data);
    if (target == NULL) return NULL;

    // �����ؾ��� ��� ����
    if (target->left == NIL || target->right == NIL)
        remove_node = target;
    else {
        remove_node = RBT_SearchMaxNode(target->left);
        target->data = remove_node->data;
    }

    // ���� ��� ����
    if (remove_node->left != NIL)
        nxt_node = remove_node->left;
    else
        nxt_node = remove_node->right;
    
    // ��� ���� ���� ������ ������
    if (remove_node->parent == NULL)
        (*root) = nxt_node;
    else {
        if (remove_node->parent->left == remove_node)
            remove_node->parent->left = nxt_node;
        else
            remove_node->parent->right = nxt_node;
    }
    nxt_node->parent = remove_node->parent;

    // ��������� ��� �̸� �ذ�
    if (remove_node->color == BLACK)
        _RBT_RebuildAfterRemove(root, nxt_node);
    return remove_node;
}

/** ��������� ������ ��带 �ذ��ϴ� �Լ�
 *  @param root �������� �ϴ� RBT�� root ���
 *  @param cur ��������� ������ ����� �ּ� */
void _RBT_RebuildAfterRemove(RBTNode** root, RBTNode* cur) {
    // root���� �׳� ��������� ���� �� �ְ�
    // cur�� ���� �������̸� �׳� ���������� �ٲٸ� ��.
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