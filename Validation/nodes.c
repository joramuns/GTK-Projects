//
//  nodes.c
//  s21_grep
//
//  Created by Joramun Sasin on 5/26/22.
//

#include "nodes.h"

node *init_node(void) {
    node *head = (node *)malloc(sizeof(node));
    if (head) {
        head->number = 0;
        head->type = 0;
        head->sign = 0;
        head->value = 0.0;
        head->next = NULL;
    }

    return head;
}

node *push(node *head) {
    node *next = NULL;
    if (head) {
        next = malloc(sizeof(node));
        if (next) {
            next->number = 0;
            next->type = 0;
            next->sign = 0;
            next->value = 0.0;
            next->next = NULL;
            node *last = find_last(head);
            if (last) {
                next->number = last->number + 1;
                last->next = next;
            }
        } else {
            next = head;
        }
    }

    return next;
}

node *pop(node *head) {
    node *last = NULL;
    if (head && head->next) {
        last = find_last(head);
        node *temp = head;
        while (temp->next != last) {
            temp = temp->next;
        }
        temp->next = NULL;
        free(last);
        last = find_last(head);
    }

    return last;
}

void *clean(node *head) {
    if (head) {
        while (head->next) {
            node *next = head->next;
            free(head);
            head = next;
        }
        free(head);
    }

    return NULL;
}

node *find_last(node *head) {
    node *last = NULL;
    if (head) {
        last = head;
        while (last->next) {
            last = last->next;
        }
    }

    return last;
}

void push_n_pop(node *dest, node *src) {
    node *last_src = find_last(src);
    push(dest);
    node *last_dest = find_last(dest);
    last_dest->type = last_src->type;
    last_dest->sign = last_src->sign;
    pop(src);
}
