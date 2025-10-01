#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "ancestry.h"

struct person_t *make_person(char *first_name, char *last_name, int year_born) {
    // TODO: Allokér plads til en `struct person_t`.
    struct person_t *new_person = malloc(sizeof(struct person_t));
    // TODO: Allokér også plads til kopier af `first_name` og `last_name`.
    new_person -> first_name = malloc(strlen(first_name)+1);
    new_person -> last_name = malloc(strlen(last_name)+1);
    // TODO: Kopiér indholdet fra `first_name` og `last_name` over i kopierne.
    strcpy(new_person->first_name, first_name);
    strcpy(new_person->last_name, last_name); 
    // TODO: Husk at gøre plads til både alle tegnene i navnene + 1 NUL-byte.
    
    return new_person;
}

void free_person(struct person_t *person) {
    // TODO: Der skal være et free()-kald for hver malloc() i make_person().
    free(person->first_name);
    free(person->last_name);
    free(person);
    person->first_name = NULL;
    person->last_name = NULL;
    person = NULL; 
    // TODO: Du må gerne sætte `first_name` og `last_name` til NULL *EFTER* de er free()'et.
}

struct ancestry_node_t *make_tree(struct person_t *person) {
    // TODO: Allokér plads til en `struct ancestry_node_t`.
    struct ancestry_node_t *tree = malloc(sizeof(struct ancestry_node_t));
    // TODO: Sæt `person` til input-personen.
    tree->person = person; 
    // TODO: Sæt `mom` og `dad` til NULL.
    tree->mom = NULL;
    tree->dad = NULL;
    return tree;
}

bool add_mom(struct ancestry_node_t *child_node, struct person_t *mom_person) {
    // TODO: Hvis der allerede er en mor-stamtavle, skal funktionen fejle.
    if(child_node->mom != NULL){
      return false; 
    } 
    // TODO: Hvis ikke, skal `mom_person` indsættes i en `mom_node` som først skal allokeres.
    struct ancestry_node_t *new_mom = malloc(sizeof(struct ancestry_node_t));
    new_mom->person = mom_person; 
    new_mom-> mom = NULL;
    new_mom-> dad = NULL; 
    child_node->mom = new_mom; 
    return true;
}

bool add_dad(struct ancestry_node_t *child_node, struct person_t *dad_person) {
    // TODO: Hvis der allerede er en far-stamtavle, skal funktionen fejle.
    if(child_node->dad !=NULL){
      return false;
    }
    // TODO: Hvis ikke, skal `dad_person` indsættes i en `dad_node` som først skal allokeres.
    struct ancestry_node_t *new_dad = malloc(sizeof(struct ancestry_node_t));
    new_dad->person = dad_person;
    new_dad->mom = NULL;
    new_dad->dad = NULL; 
    child_node->dad = new_dad;
    return true;
}

void free_tree(struct ancestry_node_t *node) {
    if(node == NULL){
      return; 
    }
    // TODO: Kald `free_person()` på personen i noden.
    free_person(node->person);
    // TODO: Kald `free_tree()` på begge forældre-stamtræer.
    free_tree(node->mom);
    free_tree(node->dad);
    // TODO: Sæt pointerne til NULL efter de er free()'et.
    node->person = NULL;
    node->mom = NULL;
    node->dad = NULL;
    free(node);
} 

void print_tree_recursive(struct ancestry_node_t *node, char *prefix, bool is_last) {
    if (node == NULL) {
        return;
    }

    printf("%s", prefix);
    printf("%s", is_last ? "└── " : "├── ");
    printf("%s %s\n", node->person->first_name, node->person->last_name);

    char new_prefix[1000];
    snprintf(new_prefix, sizeof(new_prefix), "%s%s", prefix, is_last ? "    " : "│   ");

    if (node->mom != NULL && node->dad != NULL) {
        print_tree_recursive(node->mom, new_prefix, false);
        print_tree_recursive(node->dad, new_prefix, true);
    } else if (node->mom != NULL) {
        print_tree_recursive(node->mom, new_prefix, true);
    } else if (node->dad != NULL) {
        print_tree_recursive(node->dad, new_prefix, true);
    }
}

void print_tree(struct ancestry_node_t *node) {
    print_tree_recursive(node, "", true);
}
