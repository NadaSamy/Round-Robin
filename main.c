#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct
{
    char *name;
    int starting_time;
    int remaining_time;
} Process;

typedef struct Node
{
    Process data;
    struct Node* next;
} Node;

typedef struct
{
    Node * head;
    Node * tail;
} Queue;

Queue* init()
{
    Queue* q =malloc(sizeof(Queue));
    q->head=NULL;
    q->tail=NULL;
    return q;
}
Node* newNode(Process p)
{
    Node *n =malloc(sizeof(Node));
    n->data=p;
    n->next=NULL;
    return n;
}

int isEmpty(Queue *q)
{
    if(q->head==NULL)
        return 1;
    else
        return 0;
}

Process dequeue(Queue *q)
{
    Process p;
    if(q->head)
    {

        Node*temp=q->head;
        p=temp->data;
        q->head=temp->next;
        free(temp);
        if(q->head==NULL)
            q->tail=NULL;
        return p;
    }
    return p;
}

void enqueue(Queue *q, Process val)
{
    Node* n =newNode(val);
    if(q->head==NULL)
        q->head=q->tail=n;
    else
    {
        q->tail->next=n;
        q->tail=n;
    }
}

void destroy(Queue *q)
{
    Node *node = q->head;
    while(node!=NULL)
    {
        Node *prevNode= node;
        node = node->next;
        free(prevNode);
    }
    free(q);
}

void RoundRobin(char* filename)
{
    FILE *f1;

    Process arr[100];
    int i=0,j,z;
    Process temp;
    temp.name=malloc(sizeof(int));
    int timeSlot;
    Queue *q=init();
    char arrayGrabage[15],arrayGrabage1[10],arrayGrabage2[5];
    char A;
    f1=fopen(filename,"r");

    fscanf(f1,"%s %s %s %c %d\n",arrayGrabage,arrayGrabage1,arrayGrabage2,&A,&timeSlot);
    while(!feof(f1))
    {
        arr[i].name=malloc(sizeof(int));
        fscanf(f1,"%s %d %d\n",arr[i].name,&arr[i].starting_time,&arr[i].remaining_time);

        i++;
    }
    fclose(f1);

    for(j=0; j<timeSlot; j++)
    {

        for(z=0; z<i; z++)
        {
            if(arr[z].starting_time==j)
            {
                enqueue(q,arr[z]);

            }

        }
        if(isEmpty(q))
        {
            printf("idle (%d-->%d)\n",j,(j+1));

        }
        else
        {
            temp=dequeue(q);
            printf("%s   (%d-->%d)",temp.name,j,(j+1));
            temp.remaining_time--;
            if(temp.remaining_time==0)
            {
                printf(" %s aborts\n",temp.name);

            }
            else
            {
                printf("\n");
                enqueue(q,temp);

            }
        }


    }
    printf("stop\n");
    destroy(q);
    free(temp.name);
}


int main()
{
    char filename[261];
    puts("Enter file name or Ctrl+Z to exit:");
    puts("----------------------------------");
    while(fgets(filename, 260, stdin) != NULL)
    {
        filename[strlen(filename)-1]='\0';
        if(fopen(filename,"r"))
            RoundRobin(filename);
        else
        {
            puts("File Not Found!");
            puts("----------------------------------");
        }
        puts("Enter file name or Ctrl+Z to exit:");
        puts("----------------------------------");
    }

    return 0;
}
