/*
 * Generic queue implementation
 */

#include "queue.h"
#include <stdbool.h> // TODO: Needed?
#include <stddef.h> // TODO: Needed?
#include <stdint.h> // TODO: Needed?

typedef struct node {
    void *data;
    struct node *next;
} node_t;
