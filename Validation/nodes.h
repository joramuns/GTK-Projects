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

/**
 * @brief A structure to implement linked list
 */
typedef struct node {
    int number; /**< Stores a serial number in list */
    int type; /**< A type of data in the list member, types defined in input_type enum */
    char sign; /**< In case of storing operator type, a char defines which exactly */
    double value; /**< In case of storing operand type, double defines the value of operand*/
    struct node *next; /**< Node pointer to the next list member */
} node;

/**
 * @brief Initializes linked list 
 *
 * @return A pointer to linked list head 
 */
node *init_node(void);
/**
 * @brief Pushes a new linked list member
 *
 * @param head A pointer to linked list head
 *
 * @return A pointer to the newly added linked list member 
 */
node *push(node *head);
/**
 * @brief Pops from a linked list a member
 *
 * @param head A pointer to linked list head
 *
 * @return A pointer to the last linked list member 
 */
node *pop(node *head);
/**
 * @brief Destroys linked list and frees all pointers included
 *
 * @param head A pointer to linked list head
 *
 */
void *clean(node *head);
/**
 * @brief A function to search for a pointer to last linked list member
 *
 * @param head A pointer to linked list head
 *
 * @return A pointer to the last linked list member 
 */
node *find_last(node *head);
/**
 * @brief A function to move a member from one to another link list
 *
 * @param dest Destination, where to add a new linked list member
 * @param src Source, from where to get a member and destroy it
 */
void push_n_pop(node *dest, node *src);

#endif  /* nodes_h */
