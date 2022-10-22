#include "stdio.h"
#include "stdlib.h"
#define flag -1
typedef int ADT;
typedef struct node {
    ADT data;
    struct node *next;
} LNode, *LinkList;

int print(LinkList L){
    LinkList temp = L;
    if (temp == NULL) {
        printf("null\n");
        return 0;
    }
    while (temp) {
        printf("%d\t", temp->data);
        temp = temp -> next;
    }
    printf("\n");
    return 1;
}

LinkList Create_LinkList() {
    LinkList L = NULL;
    LNode *s, *r = NULL;
    ADT x;
    printf("请输入插入内容：");
    scanf("%d", &x);
    while (x != flag) {
        s = (LNode *) malloc(sizeof(LNode));
        s -> data = x;
        if (L == NULL) {
            L = s;
        }
        else {
            r -> next = s;
        }
        r = s;
        printf("请输入插入内容：");
        scanf("%d", &x);
    }
    if (r != NULL) {
        r -> next = NULL;
    }
    return L;
};

int find_list(LinkList L, ADT x) {
    LNode *p = L;
    int i = 0;
    while (p) {
        if (p -> data == x) {
            return i;
        }
        p = p -> next;
        i++;
    }
    return -1;
}

LNode *Get_LinkList(LinkList L, int i) {
    LNode *p = L;
    int j = 0;
    while (p->next != NULL && j < i) {
        p = p -> next;
        j++;
    }
    if (j == i) {
        return p;
    }
    else {
        return NULL;
    }
}

int Del_LinkList(LinkList L, int i) {
    LinkList p, s;
    p = Get_LinkList(L, i - 1);
    if (p == NULL) {
        printf("第i-1个节点不存在");
        return -1;
    }
    else if (p -> next == NULL) {
        printf("第i个节点不存在");
        return 0;
    }
    else {
        s = p -> next;
        p -> next = s -> next;
        free(s);
        return 1;
    }
}

int Count_LinkList(LinkList L) {
    int count = 0;
    while (L != NULL) {
        count++;
        L = L -> next;
    }
    return count;
}

int main() {
    LinkList L;
    ADT x, pos;
    char choice;
    while (1) {
        printf("1.插入 ");
        printf("2.查找 ");
        printf("3.删除 ");
        printf("4.求长 ");
        printf("5.结束 ");
        scanf("%c", &choice);
        switch (choice) {
            case '1':
                L = Create_LinkList();
                print(L);
                break;
            case '2':
                printf("值？");
                scanf("%d", &x);
                pos = find_list(L, x);
                if (pos == -1) {
                    printf("\n查找超出范围");
                    break;
                }
                else {
                    printf("\n找到的元素位置是%d\n", pos);
                    break;
                }
            case '3':
                printf("\n请输入要删除的位置：");
                scanf("%d", &pos);
                if (pos == 0) {
                    LinkList temp = L;
                    L = L -> next;
                    free(temp);
                    goto console;
                }
                Del_LinkList(L, pos);
            console:printf("\n删除后的列表为");
                print(L);
                break;
            case '4':
                printf("长度: %d\n", Count_LinkList(L));
                break;
            case '5':
                exit(0);
            default:
                printf("未知的选项");
                break;
        }
        getchar();
    }
    return 0;
}
