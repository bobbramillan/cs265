#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Pet {
    char name[16];  
    int age;
    char species[16];
};

typedef struct Node Node;
struct Node {
    struct Pet pet;  
    Node *next;       
};

Node* createNode(struct Pet pet) {
    Node *newNode = malloc(sizeof(Node));
    if (newNode == NULL) {
        exit(0);
    }
    newNode->pet = pet;
    newNode->next = NULL;
    return newNode;
}

void insertNode(Node **head, struct Pet pet) {
    Node *newNode = createNode(pet);
    if (*head == NULL) {
        *head = newNode;
    } else {
        Node *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

void printPets(Node *head) {
    Node *current = head;
    while (current != NULL) {
        printf("%s, %d, %s\n", current->pet.name, current->pet.age, current->pet.species);
        current = current->next;
    }
}

void freeList(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
}

int main() {
    Node *head = NULL;
    char name[16];
    char species[16];
    int age;


    
    while (scanf("%15s %d %15s", name, &age, species) == 3) {
        struct Pet pet;
        strcpy(pet.name, name);
        pet.age = age;
        strcpy(pet.species, species);
        insertNode(&head, pet);
    }
    

    if (!feof(stdin)) {
        freeList(head);
        return 1;
    }
    printPets(head);
    freeList(head);

    return 0;
}
