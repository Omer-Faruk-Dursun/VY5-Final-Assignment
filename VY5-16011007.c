#include<stdio.h>
#include <string.h>
#include <stdlib.h>

struct STACK{
	int top;
	int arr [100];
};
// The variable that holds the number of variables ( a , b , c .. ) 
int k = -1;

// Initializing the stacks
void initialize(struct STACK *stack, struct STACK * postfix){

	stack->top=-1;
	postfix->top=-1;
	
}

void push(int symbol, struct STACK *stack){
	
	stack->top++;
	stack->arr[stack->top]=symbol;
	
}

int pop(struct STACK *stack){
	
	int value;
	
	value=stack->arr[stack->top];
	stack->top--;
	return value;
	
}

// The function that controls that the stacks status
int IsEmpty(struct STACK *stack){
	
	if(stack->top == -1){
		return 0;
	}
	else{
		return 1;
	}
	
}

// The function that makes the transition to infix to postfix
	void make_postfix(struct STACK *stack,char buffer[],int symbolList[],struct STACK * postfix,int *flag,int *position){
	
	int i=0;
	int j;
	int tmp;
	
	tmp = buffer[i];
	
	for(j=0;j<k;j++){
		
		if(tmp == symbolList[j]){
			*flag=1;
			*position=j;
		}
		
	}			
	
	if(*flag == 0){
		k++;
		symbolList[k]=tmp;
	}
	
	
	i=i+4;
	
	while(buffer[i]!=';'){
		
		if(buffer[i]>= '0' && buffer[i]<='9'){
			// Adds the number to postfix
			int tmp;
			tmp = buffer[i]- '0';
			push(tmp,postfix);
			
		}
		else if(buffer[i]=='+'){
			
			// Checks the stack if the stack is empty adds the symbol to the stack
			// if the stack is not empty does the following,
			
			if(IsEmpty(stack)){
				
				int tmp;
			
				if( stack->arr[stack->top] == '+' || stack->arr[stack->top] == '-' ){
					// If the last symbol on the stack is + or - pops the symbol and adds it on the postfix 
					// then pushes the + symbol to stack
					tmp = pop(stack);
					push(tmp,postfix);
					push(buffer[i],stack);
				}
				else if( stack->arr[stack->top] == '*' || stack->arr[stack->top] == '/'){
					// If the last symbol on the stack is * or / pops the symbol and adds it on the postfix 
					// then pushes the + symbol to stack
					tmp = pop(stack);
					push(tmp,postfix);
					push(buffer[i],stack);
				}
				else if( stack->arr[stack->top] == '('){
					// If the last symbol on the stack is ( pushes the + symbol
					push(buffer[i],stack);
				}
			
			}
			else{
			
				push(buffer[i],stack);
				
			}
			
		
		
		}
		else if(buffer[i]=='-'){
			
			// Checks the stack if the stack is empty adds the symbol to the stack
			// if the stack is not empty does the following,
			
			
			if(IsEmpty(stack)){
				
				int tmp;
			
				if( stack->arr[stack->top] == '+' || stack->arr[stack->top] == '-' ){
					// If the last symbol on the stack is + or - pops the symbol and adds it on the postfix 
					// then pushes the - symbol to stack
					tmp = pop(stack);
					push(tmp,postfix);
					push(buffer[i],stack);
				}
				else if( stack->arr[stack->top] == '*' || stack->arr[stack->top] == '/'){
					// If the last symbol on the stack is * or / pops the symbol and adds it on the postfix 
					// then pushes the - symbol to stack
					tmp = pop(stack);
					push(tmp,postfix);
					push(buffer[i],stack);
				}
				else if( stack->arr[stack->top] == '('){
					// If the last symbol on the stack is ( pushes the - symbol
					push(buffer[i],stack);
				}
			
			}
			else{
			
				push(buffer[i],stack);
				
			}
			
		}
		else if(buffer[i]=='*'){
			
			// Checks the stack if the stack is empty adds the symbol to the stack
			// if the stack is not empty does the following,
			
			if(IsEmpty(stack)){
				
				int tmp;

				if( stack->arr[stack->top] == '+' || stack->arr[stack->top] == '-' || stack->arr[stack->top] == '('){
					// If the last symbol on the stack is + or - just pushes the * symbol to stack 
					push(buffer[i],stack);
				}
				else if( stack->arr[stack->top] == '*' || stack->arr[stack->top] == '/'){
					// If the last symbol on the stack is * or / pops the symbol and adds it on the postfix
					// then pushes the * symbol to stack
					tmp = pop(stack);
					push(tmp,postfix);
					push(buffer[i],stack);
				}
			
			}
			else{
			
				push(buffer[i],stack);
				
			}
			
		}
		else if(buffer[i]=='/'){
		
			// Checks the stack if the stack is empty adds the symbol to the stack
			// if the stack is not empty does the following,
			
			if(IsEmpty(stack)){
				
				int tmp;
			    
				if( stack->arr[stack->top] == '+' || stack->arr[stack->top] == '-' || stack->arr[stack->top] == '(' ){
					// If the last symbol on the stack is + or - just pushes the / symbol to stack 
					push(buffer[i],stack);
				}
				else if( stack->arr[stack->top] == '*' || stack->arr[stack->top] == '/'){
					// If the last symbol on the stack is * or / pops the symbol and adds it on the postfix
					// then pushes the / symbol to stack
					tmp = pop(stack);
					push(tmp,postfix);
					push(buffer[i],stack);
				}
				
			}
			else{
				
				push(buffer[i],stack);
				
			}
			
			
		}
		else if(buffer[i]=='('){
			
			// Directly pushes the ( symbol to the stack
			push(buffer[i],stack);
		}
		else if(buffer[i]==')'){
			// Pops all the symbols on the stack and adds them to the postfix until ) is found
			int tmp;
			
			while( stack->arr[stack->top] != '('){
			
				tmp= pop(stack);
				push(tmp,postfix);
					
			}
		
			tmp= pop(stack);
			
		}
		else{
			// Adds the symbol to the postfix
			push(buffer[i],postfix);
		}
		
		i=i+2;
	}
	
		// Adds all the remaining element to the postfix until the stack is empty
		while(IsEmpty(stack)){
		int tmp;
		tmp = pop(stack);
		push(tmp,postfix);
	}
}

	// Function that calculates the value of the symbol using postfix form
	void solve_postfix(struct STACK * postfix,int symbolList[],int *flag, int *position){
		int i;
		struct STACK stack;
		stack.top=-1;
		int tmp;
		int pop1;
		int pop2;
		int value;
		
		// For all the elements in the postfix
		for(i=0;i<postfix->top+1;i++){
			
			tmp = postfix->arr[i];
			// Adds the numbers to the stack
			if( tmp >= 0 && tmp <=9){
				
				push(tmp,&stack);
			}
			else if(tmp == '*'){
				// If the symbol is an operant pops the first two numbers from the stack and applies the operand then pushes the result to the stack
				pop1 = pop(&stack);
				pop2 = pop(&stack);
				value = pop1 * pop2 ;
				stack.top++;
				stack.arr[stack.top]=value;
			}
			else if(tmp == '+'){
				// If the symbol is an operant pops the first two numbers from the stack and applies the operand then pushes the result to the stack
				pop1 = pop(&stack);
				pop2 = pop(&stack);
				value = pop1 + pop2 ;
				stack.top++;
				stack.arr[stack.top]=value;
			}
			else if(tmp == '-'){
				// If the symbol is an operant pops the first two numbers from the stack and applies the operand then pushes the result to the stack
				pop1 = pop(&stack);
				pop2 = pop(&stack);
				value = pop2 - pop1 ;
				stack.top++;
				stack.arr[stack.top]=value;
			}
			else if(tmp == '/'){
				// If the symbol is an operant pops the first two numbers from the stack and applies the operand then pushes the result to the stack
				pop1 = pop(&stack);
				pop2 = pop(&stack);
				value = pop2 / pop1 ;
				stack.top++;
				stack.arr[stack.top]=value;
			}
			else if(tmp >= 'a' && tmp <= 'z'){
				// If the symbol is a variable symbol finds the value of the symbol then pushes the value to the stack
				int i=0;
				
				while(tmp != symbolList[i]){
					i=i+2;
				}
			
				push(symbolList[i+1],&stack);
			}
			
		}
		
		value=pop(&stack);
		
		if(*flag==1){
			symbolList[*position+1]=value;
		}
		else{
			k++;
			symbolList[k]=value;
		}
		
		
		
	}
	

void display(int symbolList[], struct STACK * postfix, struct STACK * stack,int *flag,int *position){
	
	int i,j;
	if(*flag==0){
		printf("Symbol: %c  \n Value : %d \n" ,symbolList[k-1] , symbolList[k]);
	}
	else{
		printf("Symbol: %c  \n Value : %d \n" ,symbolList[*position] , symbolList[*position+1]);
	}
	
	printf(" Postfix form :");
	for(i=0;i<postfix->top+1;i++){
		
		if(postfix->arr[i] >=0 && postfix->arr[i] <=9){
			printf(" %c ",postfix->arr[i]+'0');
		}
		else{
			printf(" %c ",postfix->arr[i]);
		}
		
	}
	printf("\n");	
	printf("\n");	
}

int main(){
	
	int symbolList[15];  		// Array that hold the varibale symbols and their values
	char buffer[50];     		// Variable that holds the user input 
	struct STACK postfix;     	// Stack varianle that hold the postfix form
	struct STACK stack;  		
	int flag=0;
	int position=0;
	
	printf("---------\n");
		
		FILE *fp;
		fp= fopen("input.txt","r+");
		if(fp==NULL){
		printf("File error\n");
		exit(1);
		}
		

		while (fgets(buffer, sizeof buffer, fp) != NULL) {
    
    	printf(" %s \n ",buffer);
  		initialize(&stack,&postfix);
		make_postfix(&stack,buffer,symbolList,&postfix,&flag,&position);
		solve_postfix(&postfix,symbolList,&flag,&position);
		display(symbolList,&postfix,&stack,&flag,&position);
		flag=0;
		
		printf("---------\n");
		
		}
		
	return 0;
	
}
