#include <stdio.h>
#include <stdlib.h>
#include "priorityq.h"
#include "hqueue.h"

int T=1;
int listLength = 0;


void generateClientProc2(int oddsVIP, int oddsSimple, int *currentClient, int *randoms, int *y, Queue* vip, Queue * simple )
{
        int temporary;
        temporary = randoms[*y];
        (*y)++;

        printf(" T=%d",T);

        if (temporary < oddsSimple)
        {
                printf(" Atejo klientas %d (paprastas).", (*currentClient) );

                enqueue(simple,(*currentClient));

                listLength++;
                (*currentClient)++;
                //    print_list(simple);
        }

        if (temporary >= (100-oddsVIP))
        {
                printf(" Atejo klientas %d (VIP).", (*currentClient) );

                enqueue(vip,(*currentClient));


                listLength++;
                (*currentClient)++;
                //  print_list(vip);
        }

}

void generateClient(int oddsVIP, int oddsSimple, int *currentClient, int* randoms, int *y)
{
        int temporary = (rand() % 100);

        printf(" T=%d",T);

        randoms[(*y)] = temporary;
        (*y)++;

        if (temporary < oddsSimple)
        {
                printf(" Atejo klientas %d (paprastas).",(*currentClient) );

                if ((listLength) == 0)
                {
                        priorityQ = newlist((*currentClient), 2);
                }
                else
                {
                        push(&priorityQ,(*currentClient), 2);
                }
                listLength++;
                (*currentClient)++;
        }

        if (temporary >= (100-oddsVIP))
        {
                printf(" Atejo klientas %d (VIP).",(*currentClient) );

                if ((listLength) == 0)
                {
                        priorityQ = newlist((*currentClient), 1);
                }
                else
                {
                        push(&priorityQ,(*currentClient), 1);
                }

                listLength++;
                (*currentClient)++;
        }
}

void checkWorkersProc2(int vipWorkers, int* vipWorkersArray, int vipTime, int* vipWaitingArray, Queue* vip, int type, int counter, int vipQueue[], int* freeWorkerProc2)
{
        //    printf("kiekis: %d    ",kiekis(vip));

        for (int i=0; i<vipWorkers; i++)
        {

                if ((vipWorkersArray[i] == 0))
                {
                        if( vip->rear != NULL)
                        {
                                if (type == 1)
                                {
                                        printf(" Klientas (VIP) %d nueina pas darbuotoja %d.", vip->front->data, i+1 );
                                }
                                else
                                {
                                        printf(" Klientas (paprastas) %d nueina pas darbuotoja %d.", vip->front->data, i+1+counter );
                                }
                                dequeue(vip);
                                listLength--;
                                vipWorkersArray[i] = vipWorkersArray[i] + vipTime;

                                if ( vip->count == 0)
                                {
                                        vip->front = NULL;
                                        vip->rear = NULL;
                                }
                        }

                }
        }

        Node* temporary = vip->front;
        int temp;

        while (temporary!=NULL)
        {
                temp = temporary->data;

                if(vipQueue[temp] == -1)
                {
                        vipQueue[temp]++;
                }
                vipQueue[temp]++;

                if (temporary->next!=NULL)
                {
                        temporary = temporary->next;
                }

                else
                {
                        break;
                }
        }



        for (int j=0; j<vipWorkers; j++)
        {
                if (vipWorkersArray[j] == 0)
                {
                        (*freeWorkerProc2)++;
                }

                if( vipWorkersArray[j]>0 )
                {
                        vipWorkersArray[j]=vipWorkersArray[j]-1;
                        if (vipWorkersArray[j] == 0)
                        {
                                if(type == 1)
                                {
                                        printf(" Darbuotojas (VIP klientams) %d atsilaisvino.",j+1);
                                }
                                if(type == 0)
                                {
                                        printf(" Darbuotojas (paprastiems klientams) %d atsilaisvino.",j+1+counter);
                                }
                        }
                }
        }
}

void checkWorkers (int* workers, int vipTime, int simpleTime, int totalWorkers, int *waitingTime, int *vipWaiting, int *freeWorker)
{
        // jeigu yra laisvu darbuotoju ir yra laukianciu klientu
        // eina prie darbuotojo
        for (int i=0; i<totalWorkers; i++)
        {
                if ((workers[i] == 0)&&( priorityQ!=NULL))
                {
                        printf(" Klientas %d nueina pas darbuotoja %d.", (priorityQ->data), i+1 );

                        if( (priorityQ->priority) == 1)
                        {
                                workers[i] = workers[i] + vipTime;
                        }

                        if( (priorityQ->priority) == 2)
                        {
                                workers[i] = workers[i] + simpleTime;
                        }

                        pop(&priorityQ);
                        listLength--;
                }
        }

        list* temporary = priorityQ;
        int temp;

        // jeigu yra laukianciu eileje
        // pridedame prie ju laukimo laiko 1
        while (temporary!=NULL)
        {
                temp = temporary->data;

                if (temporary->priority == 1)
                {
                        if(vipWaiting[temp] == -1)
                        {
                                vipWaiting[temp]++;
                        }
                        vipWaiting[temp]++;
                }

                if (temporary->priority == 2)
                {
                        if(waitingTime[temp] == -1)
                        {
                                waitingTime[temp]++;
                        }
                        waitingTime[temp]++;
                }

                if (temporary->next!=NULL)
                {
                        temporary = temporary->next;
                }

                else
                {
                        break;
                }
        }

        // momento pabaigoje
        // visi darbuotojai, kurie uzimti dirba
        for (int j=0; j<totalWorkers; j++)
        {
                if (workers[j] == 0)
                {
                        (*freeWorker)++;
                }
                if (workers[j] > 0)
                {
                        workers[j]--;
                        if (workers[j] == 0)
                        {
                                printf(" Darbuotojas %d atsilaisvino.",j+1);
                        }
                }
        }
        printf("\n");
}

void checkWorkersAfterShift (int* workers, int vipTime, int simpleTime, int totalWorkers, int *waitingTime, int *vipWaiting, int* afterHours)
{
        printf(" T=%d",T);
        // jeigu yra laisvu darbuotoju ir yra laukianciu klientu
        // eina prie darbuotojo
        for (int i=0; i<totalWorkers; i++)
        {
                if ((workers[i] == 0)&&( priorityQ!=NULL))
                {
                        printf(" Klientas %d nueina pas darbuotoja %d.",(priorityQ->data), i+1 );

                        if( (priorityQ->priority) == 1)
                        {
                                workers[i] = workers[i] + vipTime;
                        }

                        if( (priorityQ->priority) == 2)
                        {
                                workers[i] = workers[i] + simpleTime;
                        }

                        pop(&priorityQ);
                        listLength--;
                }
        }

        list* temporary = priorityQ;
        int temp;

        // jeigu yra laukianciu eileje
        // pridedame prie ju laukimo laiko 1
        while (temporary!=NULL)
        {
                temp = temporary->data;

                if (temporary->priority == 1)
                {
                        if(vipWaiting[temp] == -1)
                        {
                                vipWaiting[temp]++;
                        }
                        vipWaiting[temp]++;
                }

                if (temporary->priority == 2)
                {
                        if(waitingTime[temp] == -1)
                        {
                                waitingTime[temp]++;
                        }
                        waitingTime[temp]++;
                }

                if (temporary->next!=NULL)
                {
                        temporary = temporary->next;
                }

                else
                {
                        break;
                }
        }

        for (int p=0; p<totalWorkers; p++)
        {
                if (workers[p] != 0)
                {
                        afterHours[p]++;
                }
        }

        // momento pabaigoje
        // visi darbuotojai, kurie uzimti dirba
        for (int j=0; j<totalWorkers; j++)
        {
                if (workers[j] > 0)
                {
                        workers[j]--;
                        if (workers[j] == 0)
                        {
                                printf(" Darbuotojas %d atsilaisvino.",j+1);
                        }
                }
        }
        printf("\n");
}

int afterHoursSum (int* afterHours, int totalWorkers)
{
        int sum=0;
        for(int i=0; i<totalWorkers; i++)
        {
                sum = sum + afterHours[i];
        }
        return 2*sum;
}

double countAverage (int* waitingTime, int currentClient )
{
        double total=0;

        for (int i=0; i<currentClient; i++)
        {
                if (waitingTime[i] != -1)
                {
                        total = total + waitingTime[i];
                }

        }
        return 3*(total/currentClient);
}

int longestWaitVIP (int* vipWaiting, int currentClient)
{
        int maxValue = -2;

        for (int i=0; i<currentClient; i++)
        {
                if (maxValue < vipWaiting[i] && vipWaiting[i] != -1)
                {
                        maxValue = vipWaiting[i];
                }
        }

        return maxValue*10;
}

void answerer (int ans1, float ans2, int ans3, int ans4, int ans21, float ans22, int ans23, int ans24)
{
        printf("\n\n          III DALIS\n\n");
        printf("Prastovu kiekis:                                    Procesas 1=%d  Procesas 2=%d\n",ans1,ans21);
        printf("Trigubas paprasto kliento laukimo vidurkis:         Procesas 1=%f  Procesas 2=%f\n",ans2,ans22);
        printf("Desimtgubas ilgiausiai laukusio vip kliento laikas: Procesas 1=%d  Procesas 2=%d\n",ans3,ans23);
        printf("Dvigubas banko darbuotoju virsvalandziu laikas:     Procesas 1=%d  Procesas 2=%d\n\n",ans4,ans24);
        if (ans1+ans2+ans3+ans4<ans21+ans22+ans23+ans24)
        {
                printf("Ivertinus pagal duotus rodiklius procesas 1 yra efektyvesnis\n");
        }
        if (ans1+ans2+ans3+ans4>ans21+ans22+ans23+ans24)
        {
                printf("Ivertinus pagal duotus rodiklius procesas 2 yra efektyvesnis\n");
        }
        if (ans1+ans2+ans3+ans4==ans21+ans22+ans23+ans24)
        {
                printf("Ivertinus pagal duotus rodiklius procesas 1 ir procesas 2 vienodo efekyvumo\n");
        }
}

int main()
{
        int oddsVIP, oddsSimple,currentClient=1,vipWorkers,simpleWorkers,totalWorkers,vipTime, simpleTime,process,currentTime=0,workEnd,y=0;
        int *workers, *afterHours, waitingTime[1000]={-1}, vipWaiting[1000]={-1}, randoms[10000];
        int freeWorker = 0, freeWorkerProc2=0;
        int *vipWorkersArray, *simpleWorkersArray, vipWaitingArray[1000]={-1}, simpleWaitingArray[1000]={-1}, vipQueue[1000]={-1},simpleQueue[1000]={-1};

        vipWorkersArray = (int*)malloc(sizeof(int)*vipWorkers);
        simpleWorkersArray = (int*)malloc(sizeof(int)*simpleWorkers);


        Queue *simple = (Queue*) malloc (sizeof(Queue)*50);
        Queue *vip = (Queue*) malloc (sizeof(Queue)*50);

        init(simple);
        init(vip);

        printf("\n\n          I DALIS\n\n");

        priorityQ = NULL;

        printf("Iveskite paprasto kliento tikimybe procentais\n");
        scanf("%d", &oddsSimple);
        printf("Iveskite VIP kliento tikimybe procentais\n");
        scanf("%d", &oddsVIP);

        if (oddsSimple + oddsVIP > 100)
        {
                printf("Tikimybe negali virsyti 100 procentu\n");
                return 0;
        }

        printf("Iveskite banko darbuotoju paprastiems klientams kieki:\n");
        scanf("%d", &simpleWorkers);
        printf("Iveskite banko darbuotoju VIP klientams kieki:\n");
        scanf("%d", &vipWorkers);
        printf("Iveskite VIP kliento aptarnavimo trukme:\n");
        scanf("%d", &vipTime);
        printf("Iveskite paprasto kliento aptarnavimo trukme:\n");
        scanf("%d", &simpleTime);
        printf("Iveskite darbo dienos trukme\n");
        scanf("%d", &workEnd);

        printf("\n\n          II DALIS\n\n");

        printf("-----PRASIDEDA-PIRMAS-PROCESAS-------\n");

        totalWorkers = simpleWorkers + vipWorkers;
        workers = (int*)malloc(sizeof(int)*totalWorkers);
        afterHours = (int*)malloc(sizeof(int)*totalWorkers);
        int *afterHoursVipQueue = (int*)malloc(sizeof(int)*(totalWorkers));
        int *afterHoursSimpleQueue = (int*)malloc(sizeof(int)*(simpleWorkers));

        while (currentTime!=workEnd)
        {
                generateClient(oddsVIP, oddsSimple, &currentClient,randoms,&y);
                checkWorkers(workers,vipTime,simpleTime,totalWorkers,waitingTime,vipWaiting,&freeWorker);
                currentTime++;
                T++;
        }

        int allDone=0;

        printf("-----DARBO-DIENOS-PABAIGA----------\n");

        while (priorityQ != NULL || allDone==0)
        {
                allDone=1;

                if (priorityQ==NULL)
                {
                        for (int i=0; i<totalWorkers; i++)
                        {
                                if (workers[i]!=0)
                                {
                                        allDone=0;
                                }
                        }
                }
                checkWorkersAfterShift(workers,vipTime,simpleTime,totalWorkers,waitingTime,vipWaiting,afterHours);
                T++;
        }

        printf("Suminis kasininku prastovu laikas: %d\n", freeWorker );
        printf("Trigubas paprasto kliento laukimo vidurkis: %f\n", countAverage(waitingTime, currentClient) );
        printf("Vip desimtgubas ilgiausias laukimo laikas: %d\n", longestWaitVIP(vipWaiting, currentClient) );
        printf("Dvigubas kasininku virsvalandziu laikas: %d\n",afterHoursSum(afterHours,totalWorkers));

        currentClient=1;
        currentTime=0;
        T=1;
        y=0;
        printf("-----PRASIDEDA-ANTRAS-PROCESAS-------\n");

        while (currentTime!=workEnd)
        {
                generateClientProc2(oddsVIP, oddsSimple, &currentClient,randoms,&y,vip,simple);
                checkWorkersProc2(vipWorkers,vipWorkersArray, vipTime,vipWaitingArray,vip,1,vipWorkers,vipQueue,&freeWorkerProc2);
                checkWorkersProc2(simpleWorkers,simpleWorkersArray, simpleTime,simpleWaitingArray,simple,0,vipWorkers,simpleQueue,&freeWorkerProc2);
                printf("\n");
                currentTime++;
                T++;
                //    checkWorkersProc2()
        }
        printf("-----DARBO-DIENOS-PABAIGA----------\n");

        allDone = 0;
        int nobody=0;

        while (vip->front != NULL || simple->front !=NULL || allDone == 0)
        {
                allDone=1;

                printf(" T=%d",T);

                if (vip->front == NULL || simple->front ==NULL)
                {
                        for (int i=0; i<vipWorkers; i++)
                        {
                                if (vipWorkersArray[i]!=0)
                                {
                                        allDone=0;
                                }
                        }
                        for (int j=0; j<simpleWorkers; j++)
                        {
                                if (simpleWorkersArray[j]!=0)
                                {
                                        allDone=0;
                                }
                        }
                }

                checkWorkersProc2(vipWorkers,vipWorkersArray, vipTime,vipWaitingArray,vip,1,vipWorkers,vipQueue,&nobody);
                checkWorkersProc2(simpleWorkers,simpleWorkersArray, simpleTime,simpleWaitingArray,simple,0,simpleWorkers,simpleQueue,&nobody);

                for (int p=0; p<vipWorkers; p++)
                {
                        if (vipWorkersArray[p] != 0)
                        {
                                afterHoursVipQueue[p]++;
                        }
                }

                for (int q=0; q<simpleWorkers; q++)
                {
                        if (simpleWorkersArray[q] != 0)
                        {
                                afterHoursVipQueue[q+vipWorkers]++;
                        }
                }

                printf("\n");
                T++;
        }

        printf("Suminis kasininku prastovu laikas: %d\n", freeWorkerProc2 );
        printf("Trigubas paprasto kliento laukimo vidurkis: %f\n", countAverage(simpleQueue, currentClient) );
        printf("Vip desimtgubas ilgiausias laukimo laikas: %d\n", longestWaitVIP(vipQueue, currentClient) );
        printf("Dvigubas kasininku virsvalandziu laikas: %d\n",afterHoursSum(afterHoursVipQueue,totalWorkers));

        answerer(freeWorker,countAverage(waitingTime, currentClient),longestWaitVIP(vipWaiting, currentClient),afterHoursSum(afterHours,totalWorkers),freeWorkerProc2,countAverage(simpleQueue, currentClient),longestWaitVIP(vipQueue, currentClient),afterHoursSum(afterHoursVipQueue,totalWorkers));

        return 0;
}
