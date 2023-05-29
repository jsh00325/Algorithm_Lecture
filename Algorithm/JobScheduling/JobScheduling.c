#include "SingleLinkedList.h"

typedef struct {
    int start, end;
} Task;

// 새로운 task 구조체 생성 & 반환
Task* create_task(int start, int end);

/** print_list에서 task 정보를 출력하기 위한 함수
 *  @param data 출력하고자 하는 task */
void print_task(void* data);

// task를 정렬하기 위한 비교함수
int cmp_task(const void* a, const void* b);

// 새로운 작업을 담은 새로운 기계 리스트에 삽입
void append_new_machine(List* machines, Task* task);

/** 작업 스케쥴링을 실행하는 함수
 *  @param tasks 실행해야 할 작업 배열
 *  @param len 실행해야 할 작업의 수
 *  @return 최종적으로 배정된 기계들의 리스트 */
List* job_scheduling(Task* tasks, int len);

int main() {
    FILE *fp = fopen("input.txt", "r");

    int n; fscanf(fp, "%d", &n);
    Task* tasks = (Task*) malloc(sizeof(Task) * n);
    for (int i = 0; i < n; i++)
        fscanf(fp, "%d %d", &tasks[i].start, &tasks[i].end);

    List* machines = job_scheduling(tasks, n);

    // 수행 결과 출력
    Node* cur_mach = machines->head;
    for (int idx = 1; cur_mach; idx++) {
        List* cur_mach_list = (List*)cur_mach->data;
        printf("Mach%d :\t", idx);
        print_list(cur_mach_list, print_task);
        printf("\n");
        cur_mach = cur_mach->next;
    }
    destroy_list(machines);
    free(tasks);
}

Task* create_task(int start, int end) {
    Task* new_task = (Task*) malloc(sizeof(Task));
    new_task->start = start;
    new_task->end = end;
    return new_task;
}

void print_task(void* data) {
    Task* cur = (Task*)data;
    printf("(%d ~ %d) ", cur->start, cur->end);
}

int cmp(int a, int b) { return (a == b ? 0 : (a < b ? -1 : 1)); }
int cmp_task(const void* a, const void* b) {
    Task* t1 = (Task*)a;
    Task* t2 = (Task*)b;
    if (t1->start == t2->start) return cmp(t1->end, t2->end);
    else return cmp(t1->start, t2->start);
}

void append_new_machine(List* machines, Task* task) {
    List* new_mach = create_list();
    append_node(new_mach, create_node(task));
    append_node(machines, create_node(new_mach));
}

List* job_scheduling(Task* tasks, int len) {
    // 작업을 시작 시간을 기준으로 오름차순 정렬
    qsort(tasks, len, sizeof(Task), cmp_task);

    int cnt = 0;
    // 배정된 기계 리스트
    List* machines = create_list();
    for (int i = 0; i < len; i++) {
        Node* cur_mach_node = machines->head;
        int assign_flag = 0;
        while (cur_mach_node) {
            // 현재 선택된 기계의 작업 리스트
            List* cur_node_list = (List*)cur_mach_node->data;

            // 현재 선택된 기계의 마지막 작업
            Task* cur_mach_last_task = (Task*)cur_node_list->tail->data;

            cnt++;
            // 현재 선택된 기계에 새로운 작업을 배정할 수 있을 때
            if (cur_mach_last_task->end <= tasks[i].start) {
                append_node(cur_node_list, create_node(&tasks[i]));
                assign_flag = 1;
                break;
            }
            cur_mach_node = cur_mach_node->next;
        }

        // 기존의 모든 기계에 배정할 수 없는 경우 -> 새 기계에 배정
        if (!assign_flag) append_new_machine(machines, &tasks[i]);
    }
    printf("count : %d\n\n", cnt);
    return machines;
}