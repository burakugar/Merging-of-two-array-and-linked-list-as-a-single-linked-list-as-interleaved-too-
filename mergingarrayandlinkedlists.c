#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

struct node_list
{
    int data;
    float number;
    char* name;
    struct node_list *next;
};

/*Do not modify the following function.*/

void insert_end(struct node_list **head, int val, float num, char* name_)
{ 
    struct node_list *newnode = malloc(sizeof(struct node_list));
    newnode->data = val;
    newnode->number = num;
    newnode->name = name_;
    newnode->next = NULL;

    if(*head == NULL)
 		*head = newnode;
    else
    {
        struct node_list *lastnode = *head;

        while(lastnode->next != NULL)
			lastnode = lastnode->next;

        lastnode->next = newnode;
    }
}


/*Do not modify the following function.*/

void print_list(struct node_list *head)
{
	struct node_list *temp = head;

    while(temp != NULL)
    {
		printf("%d->", temp->data);
		printf("%lf->", temp->number);
		printf("%s", temp->name);
		printf("\t");
		temp = temp->next;
    }
    
    printf("NULL\n\n");
}

/*Do not modify the following function.*/

void print_array(struct node_list *array, int sizeof_array)
{
	int i;
	
	for(i=0;i<sizeof_array;i++)
	{
		printf("%d->", (array+i)->data);
    	printf("%lf->", (array+i)->number);
		printf("%s", (array+i)->name);
		printf("\t");
	}
		
    	printf("NULL\n\n");
}

/*You can modify following functions.*/

struct node_list* merge_list(struct node_list* head_1, struct node_list* head_2)
{ 
	if (!head_1)
        return head_2;
    if (!head_2)
        return head_1;
 
    // start with the linked list
    // whose head data is the least
    if (head_1->data < head_2->data) {
        head_1->next = merge_list(head_1->next, head_2);
        return head_1;
    }
    else {
        head_2->next = merge_list(head_1, head_2->next);
        return head_2;
    }
}

struct node_list* merge_interleaved(struct node_list* head_1, struct node_list* head_2)
{ /* i use two link list and append each element at the end of that linked lists instead of two arrays since the inputs of the
function is link lists */
 	struct node_list r;  /* a new node is created*/
    struct node_list* tail = &r;
    r.next = NULL;
 
    while (1)
    {
        // empty list cases
        if (head_1 == NULL)
        {
            tail->next = head_2;
            break;
        }
 
        else if (head_2 == NULL)
        {
            tail->next = head_1;
            break;
        }
 
        // common case: move two nodes to the tail
        else {
            tail->next = head_1;
            tail = head_1;
            head_1 = head_1->next;
 
            tail->next = head_2;
            tail = head_2;
            head_2 = head_2->next;
        }
    }
	return r.next;
}
void append(struct node_list** head_ref, int new_data)
{
    /* 1. allocate node */
    struct node_list* new_node = (struct node_list*) malloc(sizeof(struct node_list));
 
    struct node_list *last = *head_ref;  /* used in step 5*/
  
    /* 2. put in the data  */
    new_node->data  = new_data;
 
    /* 3. This new node is going to be the last node, so make next
          of it as NULL*/
    new_node->next = NULL;
 
    /* 4. If the Linked List is empty, then make the new node as head */
    if (*head_ref == NULL)
    {
       *head_ref = new_node;
       return;
    } 
      
    /* 5. Else traverse till the last node */
    while (last->next != NULL)
        last = last->next;
  
    /* 6. Change the next of last node */
    last->next = new_node;
    return;   
}

struct node_list* merge_array(struct node_list* a, int na, struct node_list* b, int nb)
{	  
	  int i = 0, j = 0;
	  struct node_list* node = (struct node_list*) calloc(1,sizeof(struct node_list));
 	  struct node_list* head3=node;
 	 
    /* Traverse both array */
    while (i<na && j <nb) /* appending each element at the end of the link list */
    {	append(&head3,a->next->data);
    	append(&head3,b->next->data);
    	i++;
    	j++;
    }
 
    /* Store remaining elements of first link list */
    while (i < na){
        append(&head3,a->next->data);
        i++;
    	}
 
    // Store remaining elements of second link list */
    while (j < nb){
       append(&head3,b->next->data);
       j++;
   	}
	/*You can modify the entire body of the function including the return statement one line below.*/
	return head3;
}


int main()
{	int n,a,c,i;
	/*Do not modify anything between 95 and 130 lines.*/
	
	struct node_list *head_1 = NULL;
	struct node_list *head_2 = NULL;
	struct node_list *merged = NULL;
	struct node_list *interleaved = NULL;
	
	insert_end(&head_1,10,1.5,"hello1");
	insert_end(&head_1,30,3.5,"hello3");
	insert_end(&head_1,50,5.5,"hello5");
	 
	insert_end(&head_2,20,2.5,"hello2");
	insert_end(&head_2,40,4.5,"hello4");
	insert_end(&head_2,60,6.5,"hello6");
	
	printf("Print List 1: \n");
	 
	print_list(head_1);
	 
	printf("Print List 2: \n");
	 
	print_list(head_2);
	 
	merged=merge_list(head_1, head_2);
	
	printf("Print List Merged: \n");

    print_list(merged);
	head_1=NULL;  /* head pointers are NULL initially */
	head_2=NULL;
	printf("Please enter the first array size: "); /* entering the array size */
	scanf("%d",&n);
	for(i=0;i<n;i++){
		printf("Enter the %d'th element of the array: ", i);
		scanf("%d",&a);
		append(&head_1,a);
	}
	
	printf("Please enter the second array size: "); /* entering the second array size */
	scanf("%d",&n);	
	/* scanning the array's element as integer */
	for(i=0;i<n;i++){
		printf("Enter the %d'th element of the array: ", i);
		scanf("%d",&a);
		append(&head_2,a);
	}
	
	interleaved=merge_interleaved(head_1, head_2);
	
	printf("Print List Interleaved: \n");
	
	print_list(interleaved);
 	
 	/*Do not modify anything between 95 and 130 lines.*/    
 	
	/*YOU CAN MODIFY BELOW THIS LINE FOR ONLY PART 3.*/
	
	
	
	
	
	
	
	
	
	
	
	return 0;
}
