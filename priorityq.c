#include "priorityq.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

list* newlist(int d, int p)
{
        list* temp = (list*)malloc(sizeof(list));
        temp->data = d;
        temp->priority = p;
        temp->next = NULL;

        return temp;
}

int peek(list** head)
{
        return (*head)->data;
}

int pop(list** head)
{
        int retValue = (*head)->data;
        list* temp = *head;
        (*head) = (*head)->next;
        free(temp);

        return retValue;
}

void push(list** head, int d, int p)
{
        list* start = (*head);

        list* temp = newlist(d, p);

        if ((*head)->priority > p)
        {
                temp->next = *head;
                (*head) = temp;
        }

        else
        {
                while (start->next != NULL && start->next->priority <= p)
                {
                        start = start->next;
                }

                temp->next = start->next;
                start->next = temp;
        }
}

void destroy(list **head)
{
        list *temp;
        while(*head!=NULL);
        {
                temp=*head;
                *head=(*head)->next;
                free(temp);
        }
}

void deleteList(list **head)
{
        list *current = *head;
        list *next;

        while (current != NULL)
        {
                next = current->next;
                free(current);
                current = next;
        }
        *head = NULL;
}



int isEmptys(list** head)
{
        return (*head) == NULL;
}

//int main()
//{
//        int inData, inPriority, length, input,checker=-1;

/*
        printf("Prioritetine eile, tai algoritmas leidziantis pagal prioriteta surikiuoti narius");

        while(input!=8)
        {
                printf("\nIveskite skaiciu nuo 1 iki 6:\n1) Sukuria sarasa\n2) Push pagal prioritetine eile\n3) Pop pirmaji nari eileje\n4) Peek pagal prioritetine eile(parodo i pirmaji nari)\n5) Patikrina ar sarasas yra tuscias\n6) Patikrina ar sarasas pilnas\n7) Panaikina sarasa\n8) Isjungti programa\n\n");

                scanf("%d",&input);

                switch (input)
                {
                case 1:
                        if(checker==-1)
                        {
                                list* priorityQ = NULL;
                                printf("Iveskite maximalu saraso ilgi:");
                                scanf("%d",&length);
                                checker=0;
                                break;
                        }
                        else
                        {
                                printf("Neimanoma sukurti saraso, nes sarasas jau yra sukurtas\n");
                                break;
                        }
                case 2:
                        if(checker==0)
                        {
                                printf("Iveskite reiksme:\n");
                                scanf("%d",&inData);
                                printf("Iveskite prioriteta:\n");
                                scanf("%d",&inPriority);
                                priorityQ = newlist(inData,inPriority,&checker);
                                break;
                        }

                        if((checker>0)&&(checker<length))
                        {
                                printf("Iveskite reiksme:\n");
                                scanf("%d",&inData);
                                printf("Iveskite prioriteta:\n");
                                scanf("%d",&inPriority);
                                push(&priorityQ,inData,inPriority,&checker);
                                break;
                        }
                        if (checker<0)
                        {
                                printf("Neimanoma ipushinti reiksmes, nes sarasas nera sukurtas\n");
                                break;
                        }
                        if (checker==0)
                        {
                                printf("Neimanoma ipushinti reiksmes, nes sarasas tuscias\n");
                                break;
                        }
                        if (checker>=length)
                        {
                                printf("Neimanoma ipushinti reiksmes, nes sarasas jau pilnas\n");
                                break;
                        }

                case 3:
                        if(checker>0)
                        {
                                pop(&priorityQ);
                                checker--;
                                break;
                        }
                        if(checker==-1)
                        {
                                printf("Neimanoma ispopinti reiksmes, nes sarasas nera sukurtas\n");
                                break;
                        }
                        if(checker==0)
                        {
                                printf("Neimanoma ispopinti reiksmes, nes sarasas tuscias\n");
                                break;
                        }
                case 4:
                        if(checker>0)
                        {
                                printf("Pirmojo elemento reiksme: %d\n",peek(&priorityQ));
                                break;
                        }
                        if(checker==-1)
                        {
                                printf("Neimanoma parodyti pirmojo elemento reiksmes, nes sarasas nera sukurtas\n");
                                break;
                        }
                        if(checker==0)
                        {
                                printf("Neimanoma parodyti pirmojo elemento reiksmes, nes sarasas tuscias\n");
                                break;
                        }
                case 5:
                        if(checker>0)
                        {
                                printf("Sarasas netuscias");
                                break;
                        }
                        if(checker==-1)
                        {
                                printf("Sarasas nera sukurtas\n");
                                break;
                        }
                        if(checker==0)
                        {
                                printf("Sarasas tuscias\n");
                                break;
                        }
                case 6:
                        if(length==checker)
                        {
                                printf("Sarasas pilnas");
                                break;
                        }
                        if(checker==-1)
                        {
                                printf("Sarasas nera sukurtas\n");
                                break;
                        }
                        else
                        {
                                printf("Sarasas netuscias\n");
                                break;
                        }
                case 7:
                        if(checker>-1)
                        {
                                deleteList(&priorityQ);
                                checker = -1;
                                break;
                        }
                        if(checker==-1)
                        {
                                printf("Sarasas nera sukurtas\n");
                                break;
                        }
                }

        }

        return 0;
   }
 */
