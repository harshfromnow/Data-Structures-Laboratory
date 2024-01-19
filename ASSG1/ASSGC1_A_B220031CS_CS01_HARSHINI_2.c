#include <stdio.h>
#include <stdlib.h>

struct Node{
	int key;
	struct Node* next;
};

typedef struct Node* node;

node createnode(int k){
	node newnode=(node)malloc(sizeof(struct Node));
	newnode->key=k;
	newnode->next=NULL;
	return newnode;
}

node listinsert(node L,int k){
	node newnode=createnode(k);
	if(newnode!=NULL){
		if (L==NULL){
			L=newnode;
		}
		else{
			node temp=L;
			while(temp->next!=NULL){
				temp=temp->next;
			}
			temp->next=newnode;
		}
	}
	return L;
}

node listdelete(node L,int i){
	if (L==NULL) return L;
	if (i==1){
		node temp=L;
		L=temp->next;
		printf("%d\n",temp->key);
		free(temp);
		return L;
	}
	node temp=L;
	int count=1;
	while (count<i-1 && temp->next!=NULL){
		temp=temp->next;
		count++;}
	if (count==i-1 && temp->next!=NULL){
		node deleted=temp->next;
		temp->next=deleted->next;
		printf("%d\n",deleted->key);
		free(deleted);
		return L;
	}
	printf("-1\n");
	return L;
}

void display(node L){
	if (L==NULL){
		printf("-1\n");
		return;
	}
	node temp=L;
	while (temp!=NULL){
		printf("%d ",temp->key);
		temp=temp->next;
	}
	printf("\n");
	return;
}


node listduplicates(node L){
	if (L==NULL){
		printf("-1\n");
		return L;
	}
	node current=L;
	while (current!=NULL){
		node temp=current;
		while(temp->next!=NULL){
			if (temp->next->key==current->key){
				node duplicate=temp->next;
				temp->next=duplicate->next;
				free(duplicate);
			}
			else temp=temp->next;
		}
		current=current->next;
	}
	display(L);
	return L;
}

node palindrome(node L){
	int arr[100];
	if (L==NULL){
		printf("-1\n");
		return L;
	}
	node temp=L;
	int count=-1;
	while (temp!=NULL){
		count++;
		arr[count]=temp->key;
		temp=temp->next;
	}
	int i=0;
	int j=count;
	while (i<j){
		if (arr[i]==arr[j]){
			i++;
			j--;
		}
		else{
			printf("N\n");
			return L;
		}
	}
	printf("Y\n");
	return L;
}

int main(){
	char choice;
	int n;
	node L=NULL;
	while(1){
		scanf("%c",&choice);
		if (choice=='a'){
			scanf("%d",&n);
			L=listinsert(L,n);
		}
		else if (choice=='r'){
			scanf("%d",&n);
			L=listdelete(L,n);
		}
		else if (choice=='d'){
			L=listduplicates(L);
		}
		else if (choice=='p'){
			L=palindrome(L);
		}
		else if (choice=='s'){
			display(L);
		}
		else if (choice=='e'){
			return 0;
		}
	}
}	
