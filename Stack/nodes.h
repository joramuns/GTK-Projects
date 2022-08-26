//
//  nodes.h
//  s21_grep
//
//  Created by Joramun Sasin on 5/26/22.
//

#ifndef SRC_COMMON_NODES_H_
#define SRC_COMMON_NODES_H_

#include <stdlib.h>

typedef struct node {
    int type;
    char sign;
    double value;
    struct node *next;
} node;

node *init_node(void);
node *push(node *head);
node *pop(node *head);
void *clean(node *head);
node *find_last(node *head);
void print_node(node *head);

#endif  // SRC_COMMON_NODES_H_
