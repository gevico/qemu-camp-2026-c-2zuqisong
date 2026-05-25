#include "circular_linked_list.h"

#include <stdio.h>
#include <stdlib.h>

Node* create_circular_list(int n) {
    if (n <= 0) return NULL;

    Node* head = malloc(sizeof(Node));
    head->id = 1;
    Node* tail = head;

    for (int i = 2; i <= n; i++) {
        Node* new_node = malloc(sizeof(Node));
        new_node->id = i;
        tail->next = new_node;
        tail = new_node;
    }

    tail->next = head;
    return head;
}

void free_list(Node* head) {
    if (head == NULL) return;

    if (head->next == head) {
        free(head);
        return;
    }

    Node* tail = head;
    while (tail->next != head) {
        tail = tail->next;
    }
    tail->next = NULL;

    Node* current = head;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }
}
