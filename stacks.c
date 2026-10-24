#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct Stack {
    Node* top;
} Stack;

void initStack(Stack* s) {
    s->top = NULL;
}

int isEmpty(Stack s) {
    return s.top == NULL;
}

void push(Stack* s, int value) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->data = value;
    n->next = s->top;
    s->top = n;
}

int pop(Stack* s) {
    if (isEmpty(*s)) {
        printf("Pile vide (underflow) !\n");
        return 0;
    }
    Node* tmp = s->top;
    int value = tmp->data;
    s->top = tmp->next;
    free(tmp);
    return value;
}

int peek(Stack s) {
    if (isEmpty(s)) {
        printf("Pile vide !\n");
        return 0;
    }
    return s.top->data;
}

void display(Stack s) {
    if (isEmpty(s)) {
        printf("Pile vide.\n");
        return;
    }
    printf("Pile (sommet -> base) : ");
    Node* cur = s.top;
    while (cur != NULL) {
        printf("%d ", cur->data);
        cur = cur->next;
    }
    printf("\n");
}

void clearStack(Stack* s) {
    while (!isEmpty(*s)) {
        pop(s);
    }
}

void demoLIFO(void) {
    char expr[] = "(A+B)*C";
    Stack s;
    initStack(&s);

    printf("\nExpression : %s\n", expr);
    printf("--- Empilement caractere par caractere ---\n");
    for (int i = 0; expr[i] != '\0'; i++) {
        push(&s, expr[i]);
        printf("Empile : %c\n", expr[i]);
    }

    printf("--- Depilement (ordre inverse = LIFO) ---\n");
    while (!isEmpty(s)) {
        printf("Depile : %c\n", pop(&s));
    }
}

int evaluatePostfix(char* e, int* result) {
    Stack s;
    initStack(&s);
    int i = 0;

    while (e[i] != '\0') {
        if (e[i] == ' ') {
            i++;
        }
        else if (e[i] >= '0' && e[i] <= '9') {
            int num = 0;
            while (e[i] >= '0' && e[i] <= '9') {
                num = num * 10 + (e[i] - '0');
                i++;
            }
            push(&s, num);
        }
        else if (e[i] == '+' || e[i] == '-' || e[i] == '*' || e[i] == '/') {
            if (isEmpty(s)) { clearStack(&s); return 0; }
            int b = pop(&s);
            if (isEmpty(s)) { clearStack(&s); return 0; }
            int a = pop(&s);
            int r = 0;

            switch (e[i]) {
                case '+': r = a + b; break;
                case '-': r = a - b; break;
                case '*': r = a * b; break;
                case '/':
                    if (b == 0) {
                        printf("Erreur : division par zero !\n");
                        clearStack(&s);
                        return 0;
                    }
                    r = a / b;
                    break;
            }
            printf("  %d %c %d = %d\n", a, e[i], b, r);
            push(&s, r);
            i++;
        }
        else {
            printf("Caractere invalide : '%c'\n", e[i]);
            clearStack(&s);
            return 0;
        }
    }

    if (isEmpty(s)) return 0;
    *result = pop(&s);
    if (!isEmpty(s)) {
        clearStack(&s);
        return 0;
    }
    return 1;
}

int main(void) {
    Stack s;
    initStack(&s);
    int choice;
    char c;
    char expr[100];

    do {
        printf("\n===== MENU PILE =====\n");
        printf("1. Empiler (push)\n");
        printf("2. Depiler (pop)\n");
        printf("3. Afficher la pile\n");
        printf("4. Evaluer une expression postfixee\n");
        printf("5. Demo LIFO : (A+B)*C\n");
        printf("0. Quitter\n");
        printf("Choix : ");
        if (scanf("%d", &choice) != 1) break;

        switch (choice) {
            case 1:
                printf("Caractere a empiler : ");
                scanf(" %c", &c);
                push(&s, c);
                break;
            case 2:
                if (isEmpty(s)) printf("Pile vide !\n");
                else printf("Depile : %c\n", pop(&s));
                break;
            case 3:
                if (isEmpty(s)) {
                    printf("Pile vide.\n");
                } else {
                    printf("Pile (sommet -> base) : ");
                    Node* cur = s.top;
                    while (cur != NULL) {
                        printf("%c ", cur->data);
                        cur = cur->next;
                    }
                    printf("\n");
                }
                break;
            case 4: {
                int res;
                printf("Expression postfixee (ex: 6 3 + 2 * 4 /) : ");
                scanf(" %99[^\n]", expr);
                if (evaluatePostfix(expr, &res))
                    printf("Resultat = %d\n", res);
                else
                    printf("Expression invalide !\n");
                break;
            }
            case 5:
                demoLIFO();
                break;
            case 0:
                printf("Au revoir.\n");
                break;
            default:
                printf("Choix invalide.\n");
        }
    } while (choice != 0);

    clearStack(&s);
    return 0;
}
