#include "list.h"

void mx_pop_front(t_list **list) {
    t_list *temp = *list;

    if (temp == NULL) {
        return;
    }

    *list = temp->next;
    free(temp);
}
