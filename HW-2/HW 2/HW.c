#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define size 6


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


int main() {
	Worker worker1, worker2, worker3;
	worker1.name = "Nathan";
	worker1.pay = 2000;
	WorkerList* worker1_ptr = (WorkerList*)malloc(sizeof (WorkerList));
	worker1_ptr->data = &worker1;
	worker1_ptr->next = NULL;

	WorkerList* worker2_ptr = (WorkerList*)malloc(sizeof (WorkerList));
	worker2.name = "Bob";
	worker2.pay = 3000;
	worker2_ptr->data = &worker2;
	worker1_ptr->next = worker2_ptr;
	worker2_ptr->next = NULL;

	worker3.name = "Igal";
	worker3.pay = 3000;
	WorkerList* worker3_ptr = (WorkerList*)malloc(sizeof(WorkerList));
	worker3_ptr->data = &worker3;
	worker2_ptr->next = worker3_ptr;
	worker3_ptr->next = NULL;

	update_worker(worker1_ptr, 22.00);
	reverse(worker1_ptr);

	free(worker1_ptr);
	free(worker2_ptr);
	free(worker3_ptr);
}


