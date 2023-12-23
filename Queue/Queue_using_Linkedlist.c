
//  Simulate a print queue for a printer, where print jobs are processed in the order they are received.

#include<stdio.h>
#include<stdlib.h>

struct node{
	int jobid;
	struct node  *next;

}node;

struct queue{
	struct node *head;
	struct node *tail;
	int size;
}queue;

// create the Queue for jobs
struct queue *create_queue(){
	struct queue  *Q;
	Q = (struct queue *)malloc (sizeof(queue));
	Q->head=NULL;
	Q->tail=NULL;
	Q->size=0;
	return Q;
}

// enqueue : Insert the Job into a Queue
void  enqueue(struct queue *Q,int job_id){
	struct node *elt;
	elt = (struct node *)malloc(sizeof(node));
	elt->jobid=job_id;
	elt->next = NULL;
//	Q->size=Q->size+1;

	if(Q->size == 0){
		Q->head = elt;
		Q->tail = elt;

	}
	else if(Q->head != NULL){
		Q->tail->next = elt;
		Q->tail= Q->tail->next;
		
	}	
	Q->size=Q->size+1;

}

// Remove the jobs from Queue
void dequeue(struct queue *Q){
	if(Q->head == NULL){
		printf("\n Queue is empty." );

	}
	else{
		struct node *curr= Q->head;
		int j = Q->head->jobid;
	
		Q->head = Q->head->next;
		free(curr);
		Q->size = Q->size-1;
		printf("\n Removed job is : %d ",j);
	}
}


// isEmpty:  return the 1 if queue is empty else return 0
int isEmpty(struct queue *Q){
	if(Q->size == 0 ){
		return 1;
	}
	else{
		return 0;
	}
}


// queue_size :  return the size of queue
int queue_size(struct queue *Q){
	return Q->size;
}


//print_Queue :  print the all jobs in the Queue
void print_Queue(struct queue *Q){
	struct node *temp;
	temp= Q->head;
	for(int i=0;i<Q->size;i++){
	 printf("  %d  ",temp->jobid);
	 temp=temp->next;
	}

}

int main(){
	struct queue *q;
	q = create_queue();
	
	int Bool = 1;
	int value,choice;
	while(Bool){
	
	printf(" \n 1. Enqueue Job.");
	printf(" \n 2. Dequeuef Job.");
	printf(" \n 3. Size Of Queue. ");
	printf(" \n 4. Show Jobs.");
	printf(" \n 5. Exit.");
	printf(" \n Enter the option : \n");
	scanf("%d",&choice);
	
	
	switch(choice){
	case 1: printf("\nEnter Element for Enqueue : ");
		scanf("%d",&value);
		enqueue(q,value);
		printf("\n -------------------------------------------------- \n ");
		break;
	
	case 2: dequeue(q);
	 	printf("\n -------------------------------------------------- \n ");
		break;
	
	case 3: int s = queue_size(q);
		printf("\n size : %d ",s);
		printf("\n -------------------------------------------------- \n ");
		break;
		
	case 4: print_Queue(q);
		printf("\n -------------------------------------------------- \n ");
		break;
		
	case 5: Bool=0;
		printf("\n -------------------------------------------------- \n ");
		break;
	default : printf("\n Enter correct choice. \n");
		  printf("\n -------------------------------------------------- \n ");
		  break;
		
	}
}

	return 0;

}
