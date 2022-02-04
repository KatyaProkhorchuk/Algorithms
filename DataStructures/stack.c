#include <stdlib.h>
#include <stdio.h>
#define N 10
typedef int Data;
typedef struct Stack
{
    Data *a;
    unsigned int n;
    size_t size;
} Stack;
Stack *create();

void init(Stack *st);
void clear(Stack *st);
void *destroy(Stack *st);
void push(Stack *st, Data data);
void print(Stack *st);
int size(Stack *a);
Data pop(Stack *st);
Data get(Stack *st);
int is_empty(Stack *st);
void init(Stack *st)
{
    st->n = 0;
    st->size = 0;
    st->a = NULL;
}
Data pop(Stack *st)
{
    if (is_empty(st) == 0)
    {
        return st->a[--st->n];
    }
    return 0;
}
int is_full(Stack *st)
{
    return st->size == st->n;
}
void push(Stack *st, Data data)
{
    if (is_full(st) == 1)
    {
        st->size += N;
        st->a = realloc(st->a, st->size * sizeof(Data));
    }
    st->a[st->n] = data;
    st->n++;
    printf("Element %d succesfully add\n", data);
}
void print(Stack *st)
{
    printf("Stack print...\n");
    for (unsigned int i = 0; i < st->n; i++)
        printf("%d ", st->a[i]);
    printf("\n");
}
int size(Stack *a)
{
    return a->n;
}
void clear(Stack *st)
{
    free(st->a);
    st->a = NULL;
    st->size = 0;
    st->n = 0;
}
Stack *create()
{
    Stack *st = malloc(sizeof(Stack));
    init(st);
    return st;
}
void *destroy(Stack *st)
{
    if (st != NULL)
    {
        free(st->a);
        free(st);
    }
    return NULL;
}
int is_empty(Stack *st)
{
    return st->n == 0;
}
Data get(Stack *st)
{
    return st->a[st->n - 1];
}
int main()
{
    Stack *st;
    int n, num;
    while (1)
    {
        scanf("%d", &n);
        switch (n)
        {
        case 1:
            scanf("%d", &num);
            push(st, num);
            break;
        case 2:
            print(st);
            break;
        case 3:
            pop(st);
            break;
        case 4:
            printf("%d\n", get(st));
            break;
        case 5:
            printf("%d\n", size(st));
            break;
        case 6:
            if (is_empty(st) == 1)
            {
                printf("Stack is empty\n");
            }
            else
                printf("Stack isn't empty\n");
            break;
        case 7:
            clear(st);
            break;
        case 8:
            st = destroy(st);
            break;
        case 9:
            st = create();
            printf("Stack is successfully created\n");
            break;
        }
    }
    return 0;
}