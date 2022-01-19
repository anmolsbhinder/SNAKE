#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
struct row_list
{
    int row;
    struct row_list *next_row;
    struct val_list *next_element;
};

struct val_list
{
    int col;
    int val;
    struct val_list *next;
};

void insert_node(int data, int c, struct row_list **r)
{
    struct val_list *temp, *d;
    temp = (struct val_list *)malloc(sizeof(struct val_list));
    temp->col = c;
    temp->val = data;
    temp->next = NULL;

    if ((*r)->next_element == NULL)
 (*r)->next_element = temp;
    else
    {
        d = (*r)->next_element;
        while (d->next != NULL)
            d = d->next;
        d->next = temp;
    }
}

void insert_row(struct row_list **s, int r, int c, int val)
{
    for (int i = 0; i < r; i++)
    {
        struct row_list *q, *p;
        q = (struct row_list *)malloc(sizeof(struct row_list));
        q->row = i;
        q->next_row = NULL;
        q->next_element = NULL;

        if (i == 0)
            *s = q;
        else
        {
            p = *s;
            while (p->next_row != NULL)
            {
                p = p->next_row;
            }
            p->next_row = q;
        }

        int j = 0, data;
        printf("For row no %d: \n", i);
        printf("To stop adding values, enter %d in column no.\n", c);
        printf("Enter Column no.: ");
        scanf("%d", &j);
        while (j < c && val)
        {
            printf("Enter value: ");
            scanf("%d", &data);
            insert_node(data, j, &q);
            val--;
            printf("Enter Column no.: ");
            scanf("%d", &j);
        }
    }
}

void printMat(struct row_list *s, int r, int c)
{
    struct row_list *t;
    struct val_list *q;
    t = s;
    int f = 1;
    while (t)
    {
        f = 0;
        if (t->next_element != NULL)
        {
            q = t->next_element;
            for (int j = 0; j < c; j++)
            {

                if (q != NULL && q->col == j)
                {
                    printf("%d ", q->val);
                    q = q->next;
                }
                else
                    printf("0 ");
            }
        }
        else
        {
            for (int j = 0; j < c; j++)
            {
                printf("0 ");
            }
        }
        t = t->next_row;
        printf("\n");
    }
    if (f == 1)
    {
        for (int i = 0; i < r; i++)
        {
            for (int j = 0; j < c; j++)
                printf("0 ");
            printf("\n");
}
    }
}

void insertInSum(struct row_list **T, struct val_list **x)
{
    if ((*T)->next_element == NULL)
        (*T)->next_element = *x;
    else
    {
        struct val_list *v;
        v = (*T)->next_element;
        while (v->next != NULL)
        {
            v = v->next;
        }
        v->next = *x;
    }
}

void addMat(struct row_list *s, struct row_list *s1, struct row_list **S)
{
    struct row_list *t, *t1;
    t = s;
    t1 = s1;
    while (t != NULL && t1 != NULL)
    {
        struct row_list *T;
        T = (struct row_list *)malloc(sizeof(struct row_list *));
        T->next_row = NULL;
        T->next_element = NULL;
        T->row = t->row;
        struct val_list *p, *q;
        p = t->next_element;
        q = t1->next_element;
        while (p != NULL && q != NULL)
        {
            struct val_list *x;
            x = (struct val_list *)malloc(sizeof(struct val_list));
            x->next = NULL;
            if (p->col < q->col)
            {
                x->col = p->col;
                x->val = p->val;
  p = p->next;
            }
            else if (q->col < p->col)
            {
                x->col = q->col;
                x->val = q->val;
                q = q->next;
            }
            else
            {
                x->col = q->col;
                x->val = q->val + p->val;
                p = p->next;
                q = q->next;
            }
            insertInSum(&T, &x);
        }

        while (p != NULL)
        {
            struct val_list *x;
            x = (struct val_list *)malloc(sizeof(struct val_list));
            x->next = NULL;
            x->col = p->col;
            x->val = p->val;
            p = p->next;
            insertInSum(&T, &x);
        }

        while (q != NULL)
        {
            struct val_list *x;
            x = (struct val_list *)malloc(sizeof(struct val_list));
            x->next = NULL;
            x->col = q->col;
            x->val = q->val;
            q = q->next;
            insertInSum(&T, &x);
        }

        if (*S == NULL)
            *S = T;
        else
        {
            struct row_list *R;
  R = *S;
            while (R->next_row != NULL)
                R = R->next_row;
            R->next_row = T;
        }
        t = t->next_row;
        t1 = t1->next_row;
    }
}

int main()
{
    struct row_list *s = NULL;
    int r, c, val;
    printf("For matrix 1: \n");
    printf("Enter row and column: ");
    scanf("%d %d", &r, &c);
    printf("Enter no of non zero values: ");
    scanf("%d", &val);
    insert_row(&s, r, c, val);
    system("cls");

    struct row_list *s1 = NULL;
    printf("For matrix 2: \n");
    printf("Enter no of non zero values: ");
    scanf("%d", &val);
    insert_row(&s1, r, c, val);
    system("cls");

    struct row_list *S = NULL;
    addMat(s, s1, &S);
    printf("Matrix 1:\n");
    printMat(s, r, c);
    printf("\n");
    printf("Matrix 2:\n");
    printMat(s1, r, c);
    printf("\n");
    printf("Matrix after adding:\n");
    printMat(S, r, c);

    return 0;
}