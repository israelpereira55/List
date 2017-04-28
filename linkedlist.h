#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

typedef struct cell Iterator;

typedef struct list List;


List* list_create();

List* list_clear(List* list);

List* list_complete_clear(List* list, void*(*callback) (void*));


int list_is_empty(List* list);

void list_insert_first(List* list, void* info);

void list_insert_last(List* list, void* new_info);

void list_insert(List* list, void* info, int index);

void list_iterator1(List* list, int(*callback) (void*, void*), void* info);

void list_iterator2 (List* list, int(*callback) (void*, void*, void*), void* info, void* info2);

int list_iterator3(List* list, int(*callback)(void*));

int list_iterator4(List* list, int(*callback) (void*, void*), void* info);

int list_size(List* list);

void* list_get_first(List* list);

void* list_get_last(List* list);

void* list_get(List* list, int index);

void* list_remove_first(List* list);

void* list_remove_last(List* list);

void* list_remove(List* list, int index);

List* list_remove_all (List* list);

void* list_find(List* list, int (*callback) (void*, void*), void* info);

int list_find_position(List* list, int (*callback) (void*, void*), void* info);

void* list_exchange_element(List* list, int index, void* info);

void list_exchange_two_elements(List* list, int index1, int index2);

void list_exchange_two_elements_in_lists(List* list1, List* list2, int index_list1, int index_list2);

List* list_sort(List *list, int (*callback) (void*));

List* list_clone(List* list);

List* list_create_conected(List* list1, List* list2);

List* list_conect(List* list1, List* list2);

Iterator* iterator_create(List* list);


void* iterator_get_current(Iterator* iterator);

int iterator_is_empty(Iterator* iterator);

int iterator_has_next(Iterator* iterator);

Iterator* iterator_next(Iterator* iterator);

int iterator_has_previous(Iterator* iterator);

Iterator* iterator_prev(Iterator* iterator);

Iterator* iterator_clear(Iterator* iterator);

#endif /*LINKEDLIST_H_*/
