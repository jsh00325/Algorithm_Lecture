#ifndef BOYER_MOORE_ALGORITHM_H
#define BOYER_MOORE_ALGORITHM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int  BoyerMoore(char* text, int text_len, char* pattern, int pattern_len);

void _BadCharacterTable(char* pattern, int len, int* bct);
int* _GoodSuffixTable(char* pattern, int len);

int  _get_max(int a, int b);

#endif