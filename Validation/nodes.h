//
//  nodes.h
//  s21_grep
//
//  Created by Joramun Sasin on 5/26/22.
//

#ifndef SRC_COMMON_NODES_H_
#define SRC_COMMON_NODES_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int number;
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
void push_n_pop(node *dest, node *src);

#endif  // SRC_COMMON_NODES_H_
