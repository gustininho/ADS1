#ifndef priorityq_h
#define priorityq_h

typedef struct list
{
        int data;
        // Kuo mazesne reiksme tuo didesnis prioritetas
        int priority;
        struct list* next;
} list;

list* priorityQ;

list* newlist(int d, int p);
int peek(list** head);
int pop(list** head);
void push(list** head, int d, int p);
void destroy(list **head);
void deleteList(list **head);
int isEmptys(list** head);

#endif
