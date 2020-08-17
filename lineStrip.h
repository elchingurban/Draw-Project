/*==============================================
For representing line strips Singly Linked Lists
data structure were used/
================================================*/

#include "Vector.h"
#include "stdlib.h"

struct lineStrip {
    struct vector v;
    struct lineStrip *next;
};

struct lineStrip *newList();

struct lineStrip *append(struct vector v, struct lineStrip *head);

struct lineStrip *pop(struct lineStrip *head);

struct lineStrip *deleteElement(struct lineStrip *element, struct lineStrip *head);

struct lineStrip *insert(struct vector v, struct lineStrip *prev, struct lineStrip *head);
