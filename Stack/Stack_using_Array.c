
//------------------ Assumptions ---------------------------------------
// 1. maximum length of stack is 100000
// 2. size of elements in Stack must be less than integer_size (10^9)
// 3. Implemented using Array of Structure 
 
 
#include<stdio.h>

int Max_Size = 10000; // max length of stack 


typedef struct node{  // struct contains element and minimum of stack still that element 
    int element;   
    int min;
}node;


void pop(node stack[],int *size){
    if((*size)>0){
        printf("\n poped element : %d",stack[*size-1].element);
        *size=*size - 1;
    }
    else{
        printf("\n Under Flow.");
    }
}


void push(node stack[],int *size,int value){
   
    if(*size < Max_Size){
        if(*size==0 ){
            stack[*size].min=value;
            stack[*size].element=value;
    
        }
        else if(stack[*size-1].min < value){
            stack[*size].min=stack[*size-1].min;
            stack[*size].element=value;
          
        }
        else{
            stack[*size].min=value;
            stack[*size].element=value;
          
        }
          *size=*size+1;

    }
    else{
        printf("\n Stack Overflow.");
    }
}


void peek(node stack[],int *size){
    if(*size>0){
        printf("\n Peek element : %d",stack[*size-1].element);
    }
    else{
        printf("\n Stack UnderFlow.");
    }
   
}


void Stack_min(node stack[],int *size){
    if(*size > 0){
        printf("\n MIinMum of stack : %d ", stack[*size-1].min);
    }
    else{
        printf("\n Stack UnderFlow.");
    }
   
}
int main(){

	node stack1[Max_Size];  // stack of size 100000 
    	int size=0;
	int choice;
	int Bool=1;
	int value;  // element
	
	
	while(Bool){
	
	printf(" \n 1. PUSH EELEMENT.");
	printf(" \n 2. POP EELEMENT.");
	printf(" \n 3. PEEK EELEMENT.");
	printf(" \n 4. MINIMUM EELEMENT.");
	printf(" \n 5. Exit.");
	printf(" \n Enter the option : \n");
	scanf("%d",&choice);
	
	
	switch(choice){
	case 1: printf("\n Enter Element To PUSH : ");
		scanf("%d",&value);
		push(stack1,&size,value);
		printf("\n -------------------------------------------------- \n ");
		break;
	
	case 2: pop(stack1,&size);
	 	printf("\n -------------------------------------------------- \n ");
		break;
	
	case 3: peek(stack1,&size);
		printf("\n -------------------------------------------------- \n ");
		break;
		
	case 4: Stack_min(stack1,&size);
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