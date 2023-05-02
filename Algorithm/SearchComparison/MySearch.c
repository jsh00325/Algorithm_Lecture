#include "MySearch.h"

bool LinearSearch(int arr[], int len, int target) {
    for (int i = 0; i < len; i++)
        if (arr[i] == target) return true;
    return false;
}
bool BinarySearch(int arr[], int len, int target) {
    int st = 0, en = len - 1;
    while (st <= en) {
        int mid = (st + en) / 2;
        if (mid == target) return true;
        if (mid < target) st = mid + 1;
        else en = mid - 1;
    } return false;
}