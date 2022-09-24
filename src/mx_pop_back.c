#include "list.h"

void mx_pop_back(t_list **list) {
    t_list *current = *list;
    
    if (*list == NULL) {
        return;
    }
    if ((*list)->next == NULL) {
        free(*list);
        *list = NULL;
    }
    
    while (current->next->next != NULL) {
        current = current->next;
    }
    
    free(current->next);
    current->next = NULL;
}
