#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct List{
    int priority;
    char name[100];
    char time[100];
};

typedef struct List* node;

struct Queue{
    node* data;
    int size;
};

typedef struct Queue* queue;

queue create(int n){
    queue priorityQ=(queue)malloc(sizeof(struct Queue));
    priorityQ->data = (node*)malloc(sizeof(node) * n);
    priorityQ->size=0;
    return priorityQ;
}

void swap(node* a, node* b){
    node t = *a;
    *a = *b;
    *b = t;
}


void maxheapify(queue priorityQ, int i) {
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int largest = i;

    // Compare priorities
    if (left < priorityQ->size &&
        (priorityQ->data[left]->priority > priorityQ->data[largest]->priority ||
         (priorityQ->data[left]->priority == priorityQ->data[largest]->priority &&
          strcmp(priorityQ->data[left]->time, priorityQ->data[largest]->time) < 0)))
        largest = left;

    if (right < priorityQ->size &&
        (priorityQ->data[right]->priority > priorityQ->data[largest]->priority ||
         (priorityQ->data[right]->priority == priorityQ->data[largest]->priority &&
          strcmp(priorityQ->data[right]->time, priorityQ->data[largest]->time) < 0)))
        largest = right;

    if (largest != i) {
        swap(&(priorityQ->data[i]), &(priorityQ->data[largest]));
        maxheapify(priorityQ, largest);
    }
}

void buildMaxHeap(queue priorityQ){
    for(int i=priorityQ->size/2 -1; i>=0; i--){
        maxheapify(priorityQ,i);
    }
    return;
}

node extractMax(queue priorityQ) {
    if (priorityQ->size == 0) return NULL;

    node maxPatient = (node)malloc(sizeof(struct List));
    if (maxPatient != NULL) {
        strcpy(maxPatient->name, priorityQ->data[0]->name);
        maxPatient->priority = priorityQ->data[0]->priority;
        strcpy(maxPatient->time, priorityQ->data[0]->time);

        swap(&(priorityQ->data[0]), &(priorityQ->data[priorityQ->size - 1]));
        priorityQ->size--;
        maxheapify(priorityQ, 0);
    }

    return maxPatient;
}

queue copyQueue(queue original) {
    queue copyQ = create(100);
    for (int i = 0; i < original->size; i++) {
        copyQ->data[i] = (node)malloc(sizeof(struct List));
        if (copyQ->data[i] != NULL) {
            strcpy(copyQ->data[i]->name, original->data[i]->name);
            copyQ->data[i]->priority = original->data[i]->priority;
            strcpy(copyQ->data[i]->time, original->data[i]->time);
            copyQ->size++;
        }
    }
    return copyQ;
}

void patientInfo(queue priorityQ) {
    queue copyQ = copyQueue(priorityQ);

    while (copyQ->size > 0) {
        node maxPatient = extractMax(copyQ);
        if (maxPatient != NULL) {
            printf("%s %d %s\n", maxPatient->name, maxPatient->priority, maxPatient->time);
            free(maxPatient);
        }
    }
    for (int i = 0; i < copyQ->size; i++) {
        free(copyQ->data[i]);
    }
    free(copyQ->data);
    free(copyQ);
}


void admitPatient(queue priorityQ, char *name, int priority, char *time){
    node patient = (node)malloc(sizeof(struct List));
    if(patient==NULL || name == NULL || time == NULL )
        return ;
    else{
        strcpy(patient->name,name);
        patient -> priority = priority;
        strcpy(patient->time,time);

        priorityQ->data[priorityQ->size] = patient;
        priorityQ->size++;

        buildMaxHeap(priorityQ);
    }
    return;
}


void checkNextPatient(queue priorityQ){
    if (priorityQ->size==0){
        return;
    }
    else{
        printf("%s %d %s\n",priorityQ->data[0]->name,priorityQ->data[0]->priority,priorityQ->data[0]->time);
    }
}

int search(queue priorityQ,char* name, char* time){
    int i;
    for (i=0;i<priorityQ->size;i++){
        if (strcmp(priorityQ->data[i]->name,name)==0 && strcmp(priorityQ->data[i]->time,time)==0)
            return i;
    }
    return -1;
}

void dischargePatient(queue priorityQ,char* name,char* time){
    int i;
    i=search(priorityQ,name,time);
    if (i != -1) {
        priorityQ->data[i] = priorityQ->data[priorityQ->size - 1];
        priorityQ->size--;
        buildMaxHeap(priorityQ);
    }
    return;
}

void treatNextPatient(queue priorityQ){
    if (priorityQ->size==0){
        return;
    }
    else{
        node next_patient = priorityQ->data[0];
        printf("%s %d %s\n",next_patient->name,next_patient->priority,next_patient->time);
        dischargePatient(priorityQ,next_patient->name,next_patient->time);
        return;
    }
}

void updateConditionSeverity(queue priorityQ,char* name,char* time,int newPriority){
    int i;
    i=search(priorityQ,name,time);
    if (i==priorityQ->size) return;
    else{
        priorityQ->data[i]->priority=newPriority;
        buildMaxHeap(priorityQ);
    }
    return;
}


int main(){
    queue priorityQ=create(100);
    char choice;
    char name[100];
    char time[100];
    int priority;
    while (1){
        scanf("%c",&choice);
		if (choice=='a'){
			scanf("%s %d %s", name, &priority, time);
            admitPatient(priorityQ, name, priority, time);
		}
		else if (choice=='t'){
			treatNextPatient(priorityQ);
		}
		else if (choice=='c'){
			checkNextPatient(priorityQ);
		}
		else if (choice=='d'){
			scanf("%s %s", name, time);
            dischargePatient(priorityQ, name, time);
		}
		else if (choice=='u'){
			scanf("%s %s %d", name, time,&priority);
            updateConditionSeverity(priorityQ, name, time, priority);
		}
        else if (choice=='p'){
            patientInfo(priorityQ);
        }
		else if (choice=='e'){
			return 0;
		}
	}
}