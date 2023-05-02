#include "Score.h"
#include <stdio.h>
#include <stdlib.h>

int cmp(const void* va, const void* vb) {
    Score* a = (Score*)va;
    Score* b = (Score*)vb;
    if (a->score == b->score) {
        if (a->number == b->number) return 0;
        else if (a->number < b->number) return -1;
        else return 1;
    }
    else if (a->score < b->score) return -1;
    else return 1;
}

int main() {
    printf("[before sorting...]\n");
    for (int i = 0; i < 7; i++)
        printf("%d\t%.2lf\n", DataSet[i].number, DataSet[i].score);

    qsort(DataSet, sizeof(DataSet)/sizeof(Score), sizeof(Score), cmp);

    printf("\n[after sorting...]\n");
    for (int i = 0; i < 7; i++)
        printf("%d\t%.2lf\n", DataSet[i].number, DataSet[i].score);
    
    printf("\n17,213번째 정보\n%d\t%.2lf\n", DataSet[17212].number, DataSet[17212].score);
}