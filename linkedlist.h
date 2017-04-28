#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

typedef struct cell Iterator;

typedef struct list List;

/* THE CLIENT SHOULD IMPLEMENT:
 * - A function to clear their info to use the "list_complete_clear" function. 
 * 	This functions won't be used if the client don't use the function "list_complete_clear".
 *	Is possible to pass NULL on that parameter, however a segmentation fault will be sent if 
 *	"list_complete_clear" function was used.
 *	The function "list_clear" will free all the memory used by the List but the client info will remains.
 *
 * ANNOTATIONS:
 * - Before use any function, the list should be created with "list_create".
 * - The first element on the list has index 0.
 */


List* list_create();


/* Free all the memory allocated by list.
 * Output:
 * 	NULL (In purpose clear the client pointer).
 */
List* list_clear(List* list);


/* Free all the memory allocated by list and the client info.
 * Output:
 * 	NULL (In purpose clear the client pointer).
 */
List* list_complete_clear(List* list, void*(*callback) (void*));


/* Output:
 * 	1, if the list is empty.
 * 	0, otherwise.
 */
int list_is_empty(List* list);


void list_insert_first(List* list, void* info);

void list_insert_last(List* list, void* info);


/* index should be higher or equal 0.
 * the first position on the list has index 0.
 *
 * ANNOTATIONS:
 * - If the index are higher than the list lenght, the element will be inserted in the end of the list.
 */
void list_insert(List* list, void* info, int index);

void list_iterator1(List* list, int(*callback) (void*, void*), void* info);


/* Output:
 * 	-1, if the list was not created.
 * 	0, if the list is empty .
 * 	n, where n is the number of elements on the list.
 */
int list_size(List* list);


/* Output:
 * 	void pointer to the client info, if the list has at least one element.
 * 	NULL, otherwise.
 */
void* list_get_first(List* list);


/* Output:
 * 	void pointer to the client info, if the list has at least one element.
 * 	NULL, otherwise.
 */
void* list_get_last(List* list);


/* The first element has index 0.
 *
 * Output:
 * 	void pointer to the client info, if the list has at least one element.
 * 	NULL, otherwise.
 */
void* list_get(List* list, int index);


/* Output:
 * 	the info removed from the list if it was there.
 * 	NULL, otherwise.
 *
 * ANNOTATIONS:
 * - The list should have at least one element.
 */
void* list_remove_first(List* list);


/* Output:
 * 	the info removed from the list if it was there.
 * 	NULL, otherwise.
 *
 * ANNOTATIONS:
 * - The list should have at least one element.
 */
void* list_remove_last(List* list);


/* Output:
 * 	the info removed from the list if it was there.
 * 	NULL, otherwise.
 *
 * ANNOTATIONS:
 * - The list should have at least one element.
 */
void* list_remove(List* list, int index);


/* Output:
 * 	void pointer to the selected element if it is on the list.
 * 	NULL, otherwise.
 */
void* list_find(List* list, int (*callback) (void*, void*), void* info);

int list_find_position(List* list, int (*callback) (void*, void*), void* info);


/* Not implemented yet.
 */
void* list_exchange_element(List* list, int index, void* info);

void list_exchange_two_elements(List* list, int index1, int index2);

void list_exchange_two_elements_in_lists(List* list1, List* list2, int index_list1, int index_list2);


/* Not implemented yet.
 */
List* list_sort(List *list, int (*callback) (void*));


/* Output:
 * 	A new list as the one passed in the function.
 */
List* list_clone(List* list);

List* list_create_conected(List* list1, List* list2);

List* list_conect(List* list1, List* list2);


Iterator* iterator_create(List* list);

int iterator_is_empty(Iterator* iterator);

void* iterator_get_current(Iterator* iterator);

Iterator* iterator_next(Iterator* iterator);

int iterator_has_next(Iterator* iterator);

int iterator_has_previous(Iterator* iterator);

Iterator* iterator_prev(Iterator* iterator);

Iterator* iterator_clear(Iterator* iterator);

#endif /*LINKEDLIST_H_*/
