#include <stdio.h>
#include "lineStrip.h"

struct lineStrip *newList() {
    return NULL;
}

struct lineStrip *append(struct vector v, struct lineStrip *head) {
    struct lineStrip *newNode = (struct lineStrip *)malloc(sizeof(struct lineStrip));

    newNode->v = v;
    newNode->next = NULL;

    if(head == NULL) {
        return newNode;
    }

    struct lineStrip *temp = head;

    while(temp->next) {
        temp = temp->next;
    }
    temp->next = newNode;

    return head;
}

struct lineStrip *pop(struct lineStrip *head) {
    if(head == NULL) {
        printf("No vertices to remove.\n");
        return NULL;
    } else if(head->next == NULL) {
        return NULL;
    } else {
        struct lineStrip *temp = head;

        while(temp->next->next) {
            temp = temp->next;
        } 

        temp->next = NULL;

        return head;
    }
}

struct lineStrip *deleteElement(struct lineStrip *element, struct lineStrip *head) {
    if(element == head) {
        return head->next;
    }

    struct lineStrip *temp = head;

    while(temp->next != element) {
        temp = temp->next;
    }

    temp->next = temp->next->next;

    return head;
}

struct lineStrip *insert(struct vector v, struct lineStrip *prev, struct lineStrip *head) {
    struct lineStrip *newNode = (struct lineStrip *)malloc(sizeof(struct lineStrip));
    newNode->v = v;
    newNode->next = prev->next;
    prev->next = newNode;

    return head;
}