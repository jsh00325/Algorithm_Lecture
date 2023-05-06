#include "BoyerMoore.h"

/** ���̾�-���� �˰������� �������� ���� ã�� �Լ�
 *  @param text ã�� ���ڿ��� �ִ��� Ȯ���� ����
 *  @param text_len ������ ����
 *  @param pattern  ã���� �ϴ� ����
 *  @param pattern_len  ������ ����
 *  @return �������� ���ʷ� ã�� ������ ������ġ */
int BoyerMoore(char* text, int text_len, char* pattern, int pattern_len) {
    int bct[128];
    _BadCharacterTable(pattern, pattern_len, bct);
    int* gst = _GoodSuffixTable(pattern, pattern_len);

    int pos = -1;

    // ������ ���� ������ ���� ��ġ
    int i = 0;
    // ���Ͽ��� ����ġ ������ �ε���( ��� ��ġ�ϸ� -1 )
    int j = pattern_len - 1;

    while (i + pattern_len <= text_len) {
        j = pattern_len - 1;
        while (j >= 0 && text[i+j] == pattern[j]) j--;

        if (j < 0) {    // ���ڿ� ��ġ
            pos = i;
            break;
        }
        else {  // ���ڿ� ����ġ
            // ���� ���� �̵��� ���� ���̺� �̵� �� ���� ���� �����̴� ���� ����
            i += _get_max(j - bct[text[i + j]], gst[j+1]);
        }
    }

    free(gst);
    return pos;
}


/** ���� ���� ���̺� �����
 *  @param pattern  ���̺��� ���� ���� ���ڿ�
 *  @param len  ������ ����
 *  @param bct  ������� ���� ���� ���̺��� ������ �迭 */
void _BadCharacterTable(char* pattern, int len, int* bct) {
    for (int i = 0; i < 128; i++) bct[i] = -1;
    for (int i = 0; i < len; i++) bct[pattern[i]] = i;
}


/** ���� ���̺� ���̺� �����
 *  @param pattern  ���̺��� ���� ���� ���ڿ�
 *  @param len  ������ ����
 *  @return ������� ���� ���̺� ���̺��� �ּ� */
int* _GoodSuffixTable(char* pattern, int len) {
    int* suffix = (int*) calloc(len + 1, sizeof(int));
    int* gst = (int*) calloc(len + 1, sizeof(int));

    // ������ ���̺��� �ִ� ���� ��� ����
    // suffix[i]  =  pattern[i:]�� ���� �� ����� ������ġ
    int j = len + 1;
    suffix[len] = j;
    for (int i = len - 1; i >= 0; i--) {
        //          j <= len            => ���̺ΰ� ��谡 �� �� �ִ���
        // pattern[i] != pattern[j-1]   => Ȯ�� ���� ���� üũ
        while (j <= len && pattern[i] != pattern[j-1]) {
            if (gst[j] == 0) gst[j] = j - i - 1;
            j = suffix[j];
        }
        suffix[i] = --j;
    }

    // ������ ��� ���� ��ġ
    int boundary = suffix[0];
    for (int i = 0; i <= len; i++) {
        // ���̺��� ���̰� ����� ���̺��� ª������
        // ������ ����� ���̺��� ����� ������ġ�� ���� ����
        while (boundary < i) boundary = suffix[boundary];
        if (gst[i] == 0) gst[i] = boundary;
    }

    free(suffix);
    return gst;
}

int _get_max(int a, int b) {
    return (a > b ? a : b);
}