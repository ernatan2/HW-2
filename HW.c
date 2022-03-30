#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define size 6
#include <stdlib.h>
#define HEBREW_YEAR '1'
#define FOREIGN_YEAR '0'
#include <string.h>

typedef struct  Worker {
	long unsigned id;
	char* name;
	long unsigned pay;
	union Workyear {
		long unsigned Foreign;
		char hebyear[size];
	} workyear;
} Worker;
typedef struct WorkerList {
	Worker* data;
	struct WorkerList* next;
} WorkerList;

Worker* CreateWorker(Worker* w, char type)
{
	printf("enter id: ");
	scanf_s("%ld", (&w->id));
	printf("\n");
	printf("enter name: ");
	fseek(stdin, 0, SEEK_END);
	scanf("%s", (&w->name));
	/*printf("\n");*/
	printf("enter pay: ");
	scanf_s("%d", *(&w->pay));
	printf("\n");
	printf("enter Year of commencement of work: ");
	switch (type) {
	case (HEBREW_YEAR):
		fseek(stdin, 0, SEEK_END);
		scanf("%c", &(w->workyear.hebyear));
		break;
	case (FOREIGN_YEAR):
		scanf("%ld", &(w->workyear.Foreign));
		break;
	}
	return w;
}

void PrintWorker(Worker* w, char type)
{
	printf("worker id: %ld\n", w->id);
	printf("worker name: ");
	puts(w->name);
	printf("\n");
	printf("worker sallary: %ld\n", w->pay);
	printf("Year of commencement of work: ");
	switch (type) {
	case HEBREW_YEAR:
		printf("%c\n", w->workyear.hebyear);
		break;
	case FOREIGN_YEAR:
		printf("%c\n", w->workyear.Foreign);
		break;
	}
	return 0;


}

void update_worker(WorkerList* head, float percent) {
	WorkerList* curr = head; //Creating a copy of the head integer
	while (curr) {
		curr->data->pay += curr->data->pay * (percent*0.01); // Calculates the the new payment
		curr = curr->next; //Passing the pointer to the next integer
	}
}

WorkerList* reverse(WorkerList* head) {
	WorkerList* prev=NULL, * next, * curr = head;
	if (!head || !head->next) {
		return head;
	}
	while (curr) {
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}

	return prev;
	
}

void freeWorkers(WorkerList* head) {
	WorkerList* curr = head;
	while (curr) {
		free(curr);
		curr=curr->next;
	}
}

int index(WorkerList* head, long unsigned id) {
	int temp = 1;  
	int temp2 = 0;
	WorkerList* curr = head;

	while (curr) {
		temp++;
		if (id == curr->data->id) {
			temp2++;
		}
		curr=curr->next;
	}
	if (!temp2) {
		return -1;
	}
	return temp;
}

int index_rec(WorkerList* head, long unsigned id) {
	static WorkerList* curr = NULL;
	if (!curr) {
		curr = head;
	}
	static int temp = 0, temp2 = 0;
	if (!curr) {
		if (!temp2) {
			return -1;
		}
		return temp;
	}
	temp++;
	if (id == curr->data->id) {
		index_rec(NULL, id);
	}
	index_rec(curr->next, id);
}

WorkerList* addWorker(WorkerList* head, Worker* w){
	WorkerList* curr = head, *prev;
	long unsigned payment = w->pay;
	if (!curr) {
		curr = w;
		return w;
	}
	while (curr) {
		if (w->pay > curr->data->pay) {
			prev = curr;
			curr->data = w;
			curr->next = prev;
		}
		curr = curr->next;
	}
	return curr;
}

WorkerList* deleteWorstWorker(WorkerList* head)
{
	WorkerList* curr = head;
	while (curr->next != NULL) {
		curr = curr->next;
	}
	WorkerList* lastworker = curr;
	curr = NULL;
	free(lastworker);

}

int main() {
	Worker worker1, worker2, worker3;
	worker1.name = "Nathan";
	worker1.pay = 2000;
	worker1.id = 11111;
	worker1.workyear.Foreign = 2020;
	WorkerList* worker1_ptr = (WorkerList*)malloc(sizeof(WorkerList));
	worker1_ptr->data = &worker1;
	
	WorkerList *worker2_ptr = (WorkerList*)malloc(sizeof(WorkerList));
	worker2.name = "Bob";
	worker2.pay = 3000;
	worker2.id = 2222;
	worker2.workyear.Foreign = 2019;
	worker1_ptr->next = worker2_ptr;
	worker2_ptr->data = &worker2;
		
	WorkerList *worker3_ptr = (WorkerList*)malloc(sizeof(WorkerList));
	worker3_ptr->data = &worker3;
	worker2_ptr->next = worker3_ptr;
	worker3_ptr->next = NULL;

	CreateWorker(worker3_ptr->data, 0);
	PrintWorker(worker3_ptr->data, 0);
	addWorker(worker1_ptr, worker3_ptr);
	index(worker1_ptr, 22222);
	deleteWorstWorker(worker1_ptr);
	update_worker(worker1_ptr, 22.00);
	reverse(worker1_ptr);
	freeWorkers(worker1_ptr);
}


