#include "SingleLinkedList.h"

typedef struct {
    int start, end;
} Task;

// ���ο� task ����ü ���� & ��ȯ
Task* create_task(int start, int end);

/** print_list���� task ������ ����ϱ� ���� �Լ�
 *  @param data ����ϰ��� �ϴ� task */
void print_task(void* data);

// task�� �����ϱ� ���� ���Լ�
int cmp_task(const void* a, const void* b);

// ���ο� �۾��� ���� ���ο� ��� ����Ʈ�� ����
void append_new_machine(List* machines, Task* task);

/** �۾� �����층�� �����ϴ� �Լ�
 *  @param tasks �����ؾ� �� �۾� �迭
 *  @param len �����ؾ� �� �۾��� ��
 *  @return ���������� ������ ������ ����Ʈ */
List* job_scheduling(Task* tasks, int len);

int main() {
    FILE *fp = fopen("input.txt", "r");

    int n; fscanf(fp, "%d", &n);
    Task* tasks = (Task*) malloc(sizeof(Task) * n);
    for (int i = 0; i < n; i++)
        fscanf(fp, "%d %d", &tasks[i].start, &tasks[i].end);

    List* machines = job_scheduling(tasks, n);

    // ���� ��� ���
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
    // �۾��� ���� �ð��� �������� �������� ����
    qsort(tasks, len, sizeof(Task), cmp_task);

    int cnt = 0;
    // ������ ��� ����Ʈ
    List* machines = create_list();
    for (int i = 0; i < len; i++) {
        Node* cur_mach_node = machines->head;
        int assign_flag = 0;
        while (cur_mach_node) {
            // ���� ���õ� ����� �۾� ����Ʈ
            List* cur_node_list = (List*)cur_mach_node->data;

            // ���� ���õ� ����� ������ �۾�
            Task* cur_mach_last_task = (Task*)cur_node_list->tail->data;

            cnt++;
            // ���� ���õ� ��迡 ���ο� �۾��� ������ �� ���� ��
            if (cur_mach_last_task->end <= tasks[i].start) {
                append_node(cur_node_list, create_node(&tasks[i]));
                assign_flag = 1;
                break;
            }
            cur_mach_node = cur_mach_node->next;
        }

        // ������ ��� ��迡 ������ �� ���� ��� -> �� ��迡 ����
        if (!assign_flag) append_new_machine(machines, &tasks[i]);
    }
    printf("count : %d\n\n", cnt);
    return machines;
}