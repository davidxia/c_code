#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "clist.h"


void clist_init(CList *list, void (*destroy)(void *data)) {
    list->size = 0;
    list->destroy = destroy;
    list->head = NULL;
    return;
}


void clist_destroy(CList *list) {
    void *data;

    while (clist_size(list) > 0) {
        if (clist_rem_next(list, list->head, (void **)&data) == 0
            && list->destroy != NULL) {
            list->destroy(data);
        }
    }

    /* Clear structure as precaution */
    memset(list, 0, sizeof(CList));
    return;
}


int clist_ins_next(CList *list, CListElmt *element, const void *data) {
    CListElmt *new_element;

    if ((new_element = (CListElmt *) malloc(sizeof(CListElmt))) == NULL)
        return -1;

    new_element->data = (void *) data;

    if (clist_size(list) == 0) {
        new_element->next = new_element;
        list->head = new_element;
    } else {
        new_element->next = element->next;
        element->next = new_element;
    }

    list->size++;
    return 0;
}


int clist_rem_next(CList *list, CListElmt *element, void **data) {
    CListElmt *old_element;

    /* Don't allow removal from empty list */
    if (clist_size(list) == 0)
        return -1;

    *data = element->next->data;

    if (element->next == element) {
        old_element = element->next;
        list->head = NULL;
    } else {
        old_element = element->next;
        element->next = element->next->next;
        if (old_element == clist_head(list))
            list->head = old_element->next;
    }

    free(old_element);
    list->size--;
    return 0;
}


int main() {
    CList list;
    CListElmt *element;
    clist_init(&list, free);

    int elements_left;
    int data1 = 4;
    int data2 = 9;
    clist_ins_next(&list, NULL, &data1);
    clist_ins_next(&list, clist_head(&list), &data2);
    elements_left = clist_size(&list);

    for (element = clist_head(&list); element != NULL && elements_left;
         element = clist_next(element), elements_left--) {
        printf("element->data = %d\n", *((int *) element->data));
    }

    return 0;
}

