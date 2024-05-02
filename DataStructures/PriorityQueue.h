#include "Queue.h"


struct PQnode;
typedef struct PQnode* PQnodePtr;

typedef struct PQnode {
    process* nodeProcess;
    PQnodePtr next;
} PQnode;


typedef struct PriorityQueue {
    PQnode* front;
} PriorityQueue;


PriorityQueue* createPriorityQueue() {
    PriorityQueue* pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    if (pq == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    pq->front = NULL;
    return pq;
}

int PQisEmpty (PriorityQueue* pq) {
    if (pq->front == NULL)
        return 1;
    return 0;
}


void PQenqueue(PriorityQueue* pq, process* newprocess, int priority) {
    // Create a new PQnode
    PQnode* newNode = (PQnode*)malloc(sizeof(PQnode));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newNode->nodeProcess = newprocess;

    if (pq->front == NULL || priority < pq->front->nodeProcess->priority) {
        newNode->next = pq->front;
        pq->front = newNode;
    } else {
        PQnode* current = pq->front;
        while (current->next != NULL && current->next->nodeProcess->priority <= priority) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}


void STRNenqueue(PriorityQueue* pq, process* newprocess, int remtime) {
    // Create a new PQnode
    PQnode* newNode = (PQnode*)malloc(sizeof(PQnode));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newNode->nodeProcess = newprocess;

    if (pq->front == NULL || remtime < pq->front->nodeProcess->remainingtime) {
        newNode->next = pq->front;
        pq->front = newNode;
    } else {
        PQnode* current = pq->front;
        while (current->next != NULL && current->next->nodeProcess->remainingtime <= remtime) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}



process* PQdequeue(PriorityQueue* pq) {
    if (pq->front == NULL) {
        printf("Queue is empty\n");
        return NULL;
    }
    PQnode* temp = pq->front;
    pq->front = pq->front->next;
    process* dequeuedProcess = temp->nodeProcess;
    temp = NULL;
    free(temp);
    return dequeuedProcess;
}


process* PQpeek(PriorityQueue* pq) {
    if (pq->front == NULL) {
        printf("Queue is empty\n");
        return NULL;
    }
    return pq->front->nodeProcess;
}


void PQdisplay(PriorityQueue* pq) {
    PQnode* current = pq->front;
    if (current == NULL) {
        printf("Queue is empty\n");
        return;
    }
    printf("Priority Queue:\n");
    while (current != NULL) {
        printf("Process ID: %d, Priority: %d\n", current->nodeProcess->id, current->nodeProcess->priority);
        current = current->next;
    }
}

// Function to free the memory allocated for the priority queue
void freePriorityQueue(PriorityQueue* pq) {
    PQnode* current = pq->front;
    PQnode* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    free(pq);
}