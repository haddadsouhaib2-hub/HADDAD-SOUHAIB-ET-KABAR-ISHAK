#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int customerNumber;
    struct Node* next;
} Node;

typedef struct Queue {
    Node* front;
    Node* rear;
} Queue;

void initQueue(Queue* q) {
    q->front = NULL;
    q->rear = NULL;
}

int isEmpty(Queue q) {
    return q.front == NULL;
}

void enqueue(Queue* q, int number) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->customerNumber = number;
    n->next = NULL;

    if (isEmpty(*q)) {
        q->front = n;
        q->rear = n;
    } else {
        q->rear->next = n;
        q->rear = n;
    }
}

int dequeue(Queue* q) {
    if (isEmpty(*q)) {
        printf("File vide (underflow) !\n");
        return -1;
    }
    Node* tmp = q->front;
    int number = tmp->customerNumber;
    q->front = tmp->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    free(tmp);
    return number;
}

int peek(Queue q) {
    if (isEmpty(q)) {
        printf("File vide !\n");
        return -1;
    }
    return q.front->customerNumber;
}

void display(Queue q) {
    if (isEmpty(q)) {
        printf("File vide.\n");
        return;
    }
    printf("File (tete -> queue) : ");
    Node* cur = q.front;
    while (cur != NULL) {
        printf("%d ", cur->customerNumber);
        cur = cur->next;
    }
    printf("\n");
}

void clearQueue(Queue* q) {
    while (!isEmpty(*q)) {
        dequeue(q);
    }
}

void bankSimulation(void) {
    Queue q;
    initQueue(&q);
    int token = 101;

    printf("\n--- Simulation ---\n");

    printf("Le client %d est arrive et a pris un ticket.\n", token);
    enqueue(&q, token++);

    printf("Le client %d est arrive et a pris un ticket.\n", token);
    enqueue(&q, token++);

    printf("Le client %d est en cours de service.\n", dequeue(&q));

    printf("Le client %d est arrive et a pris un ticket.\n", token);
    enqueue(&q, token++);

    while (!isEmpty(q)) {
        printf("Le client %d est en cours de service.\n", dequeue(&q));
    }
    printf("La file est vide.\n");
}

int main(void) {
    Queue q;
    initQueue(&q);
    int choice;
    int token = 101;

    do {
        printf("\n===== MENU BANQUE =====\n");
        printf("1. Nouveau client (prendre un ticket)\n");
        printf("2. Servir le client suivant\n");
        printf("3. Voir le prochain client\n");
        printf("4. Afficher la file\n");
        printf("5. Lancer la simulation\n");
        printf("0. Quitter\n");
        printf("Choix : ");
        if (scanf("%d", &choice) != 1) break;

        switch (choice) {
            case 1:
                enqueue(&q, token);
                printf("Le client %d est arrive et a pris un ticket.\n", token);
                token++;
                break;
            case 2:
                if (isEmpty(q)) printf("Aucun client en attente !\n");
                else printf("Le client %d est en cours de service.\n", dequeue(&q));
                break;
            case 3:
                if (isEmpty(q)) printf("File vide !\n");
                else printf("Prochain client : %d\n", peek(q));
                break;
            case 4:
                display(q);
                break;
            case 5:
                bankSimulation();
                break;
            case 0:
                printf("Au revoir.\n");
                break;
            default:
                printf("Choix invalide.\n");
        }
    } while (choice != 0);

    clearQueue(&q);
    return 0;
}
