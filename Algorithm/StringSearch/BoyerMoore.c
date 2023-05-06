#include "BoyerMoore.h"

/** 보이어-무어 알고리즘으로 본문에서 패턴 찾는 함수
 *  @param text 찾는 문자열이 있는지 확인할 본문
 *  @param text_len 본문의 길이
 *  @param pattern  찾고자 하는 패턴
 *  @param pattern_len  패턴의 길이
 *  @return 본문에서 최초로 찾은 패턴의 시작위치 */
int BoyerMoore(char* text, int text_len, char* pattern, int pattern_len) {
    int bct[128];
    _BadCharacterTable(pattern, pattern_len, bct);
    int* gst = _GoodSuffixTable(pattern, pattern_len);

    int pos = -1;

    // 본문의 비교할 영역의 시작 위치
    int i = 0;
    // 패턴에서 불일치 문자의 인덱스( 모두 일치하면 -1 )
    int j = pattern_len - 1;

    while (i + pattern_len <= text_len) {
        j = pattern_len - 1;
        while (j >= 0 && text[i+j] == pattern[j]) j--;

        if (j < 0) {    // 문자열 일치
            pos = i;
            break;
        }
        else {  // 문자열 불일치
            // 나쁜 문자 이동과 좋은 접미부 이동 중 가장 많이 움직이는 것을 선택
            i += _get_max(j - bct[text[i + j]], gst[j+1]);
        }
    }

    free(gst);
    return pos;
}


/** 나쁜 문자 테이블 만들기
 *  @param pattern  테이블을 만들 패턴 문자열
 *  @param len  패턴의 길이
 *  @param bct  만들어진 나쁜 문자 테이블을 저장할 배열 */
void _BadCharacterTable(char* pattern, int len, int* bct) {
    for (int i = 0; i < 128; i++) bct[i] = -1;
    for (int i = 0; i < len; i++) bct[pattern[i]] = i;
}


/** 착한 접미부 테이블 만들기
 *  @param pattern  테이블을 만들 패턴 문자열
 *  @param len  패턴의 길이
 *  @return 만들어진 착한 접미부 테이블의 주소 */
int* _GoodSuffixTable(char* pattern, int len) {
    int* suffix = (int*) calloc(len + 1, sizeof(int));
    int* gst = (int*) calloc(len + 1, sizeof(int));

    // 패턴의 접미부의 최대 길이 경계 저장
    // suffix[i]  =  pattern[i:]의 가장 긴 경계의 시작위치
    int j = len + 1;
    suffix[len] = j;
    for (int i = len - 1; i >= 0; i--) {
        //          j <= len            => 접미부가 경계가 될 수 있는지
        // pattern[i] != pattern[j-1]   => 확장 가능 여부 체크
        while (j <= len && pattern[i] != pattern[j-1]) {
            if (gst[j] == 0) gst[j] = j - i - 1;
            j = suffix[j];
        }
        suffix[i] = --j;
    }

    // 패턴의 경계 시작 위치
    int boundary = suffix[0];
    for (int i = 0; i <= len; i++) {
        // 접미부의 길이가 경계의 길이보다 짧아지면
        // 기존의 경계인 접미부의 경계의 시작위치를 덮어 씌움
        while (boundary < i) boundary = suffix[boundary];
        if (gst[i] == 0) gst[i] = boundary;
    }

    free(suffix);
    return gst;
}

int _get_max(int a, int b) {
    return (a > b ? a : b);
}