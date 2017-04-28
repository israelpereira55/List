#include <stdio.h>
#include <stdlib.h>

#include "linkedlist.h"

typedef struct cell Cell;

struct cell {
	void* info;
	Cell *next,
	     *prev;
};
/*
struct iterator{
	void** elements;
	int cursor,
	    end;
};*/

struct list{
	Cell *first,
	     *last;
	int lenght;
};

List* list_create(){
	List* new_list = (List*) malloc(sizeof(List));
	new_list->first = NULL;
	new_list->last = NULL;
	new_list->lenght = 0;
	
	return new_list;
}

int list_is_empty(List* list) {
	return !list->lenght;
}

void list_insert_first(List* list, void* new_info) { 
	Cell* new = (Cell*) malloc(sizeof(Cell));
	new->info = new_info;
	new->next = NULL;
	new->prev = NULL;
	list->lenght++;

	if (list->first == NULL){
		list->first = new;
		list->last = new;
		return;
	}
	
	new->next = list->first;
	list->first->prev = new;
	list->first = new;
	return;
}

void list_insert_last(List* list, void* info) {
	Cell* new = (Cell*) malloc(sizeof(Cell));
	new->info = info;
	new->next = NULL;
	list->lenght++;

	if (list->first == NULL){
		list->first = new;
		list->last = new;

		new->prev = NULL;
		return;
	}
	
	new->prev = list->last;
	list->last->next = new;
	list->last = new;
	return;
}

/* Index should be high or equal 0.
 * The first position has 0 as index.
 * If the index are higher the list lenght, the info will be inserted in the last of the list.
 */
void list_insert(List* list, void* new_info, int index) {
	Cell* new = (Cell*) malloc(sizeof(Cell));
	new->info = new_info;
	int lenght = list->lenght;
	list->lenght++;

	if(index == 0) {
		new->prev = NULL;
		new->next = list->first;
		
		if(list->last == NULL) {
			list->first = new;
			list->last = new;
		} else {
			new->next = list->first;
			list->first = new;
		}
		return;
	}
	
	if(index == lenght) {
		new->next = NULL;
		new->prev = list->last;
		list->last->next = new;
		list->last = new;
		return;
	}
	
	Cell* aux = list->first;
	while(index>1 && aux->next != NULL) {
		aux = aux->next;
		index--;
	}
	
	new->prev = aux;
	new->next = aux->next;

	if(aux->next != NULL) {
		aux->next->prev = new;
	}
	
	aux->next = new;
	return;
}

void list_iterator1 (List* list, int(*callback) (void*, void*), void* info) {
	Cell* aux = NULL;
	int stop = 0;

	for(aux = list->first; aux != NULL; aux = aux->next) {
		stop = callback(aux->info, info);
		if(stop) return;
	}

	return;
}
/*
void list_iterator2 (List* list, int(*callback) (void*, void*, void*), void* info, void* info2) {
	Cell* aux = NULL;
	int stop = 0;

	for(aux = list->first; aux != NULL; aux = aux->next) {
		stop = callback(aux->info, info, info2);
		if(stop) return;
	}

	return;
}

int list_iterator3(List* list, int(*callback)(void*)) {
	Cell* aux = NULL;
	int value = 0;

	for(aux = list->first; aux != NULL; aux = aux->next)
		value = value + callback(aux->info);
	
	return value;
}

int list_iterator4(List* list, int(*callback) (void*, void*), void* info) {
	Cell* aux = NULL;
	int value = 0;
	
	for(aux = list->first; aux != NULL; aux = aux->next)
		value = value + callback(aux->info, info);
		
	return value;
}*/

List* list_complete_clear(List* list, void*(*callback) (void*)){
	Cell* aux = list->first;
	
	while (aux != NULL) {
		aux->info = callback(aux->info);
		aux = aux->next;
		free(list->first);
		list->first = aux;
	}

	list->first = NULL;
	list->last = NULL;
	free(list);
	return NULL;
}

List* list_clear(List* list){
	Cell* aux = list->first;
	
	while (aux != NULL) {
		list->first = list->first->next;
		free(aux);
		aux = list->first;
	}

	list->last = NULL;
	free(list);
	return NULL;
}

int list_size(List* list){
	if(list == NULL)
		return -1;
	
	return 	list->lenght;
}

void* list_get_first(List* list) {
	if(list->first == NULL){
		return NULL;
	} else  return list->first->info;
}

void* list_get_last(List* list){
	if(list->first == NULL) {
		return NULL;
	} else  return list->last->info;
}

void* list_get(List* list, int index){
	if(list->first == NULL) {
		return NULL;
	}
	Cell* aux = list->first;

	while(aux!=NULL && index>0){
		aux = aux->next;
		index--;
	}

	if(aux != NULL){
		return aux->info;
	}
	
	return NULL;
}

void* list_remove_first(List* list){
	void* info = NULL;
	list->lenght--;

	if(list->first == list->last) {
		info = list->first->info;
		list->last = NULL;
		list->first->prev = NULL;
		free(list->first);
		list->first = NULL;
		
		return info;
	}

	Cell* aux = list->first;
	list->first = list->first->next;
	list->first->prev = NULL;

	info = aux->info;
	free(aux);
	aux = NULL;
	
	return info;
}

void* list_remove_last(List* list){
	void* info = NULL;
	list->lenght--;

	if(list->first == list->last) {
		info = list->first->info;
		list->last = NULL;
		list->first->prev = NULL;
		free(list->first);
		list->first = NULL;

		return info;
	}

	Cell* aux = list->last;
	list->last = list->last->prev;
	list->last->next->prev = NULL;
	list->last->next = NULL;
	
	info = aux->info;
	free(aux);
	return info;
}

void* list_remove(List* list, int index) {
	if(index == 0)
		return list_remove_first(list);

	int end = list->lenght -1;
	
	if(index == end)
		return list_remove_last(list);

	if(index >= end)
		return NULL;
	
	list->lenght--;

	Cell* aux = list->first;
	int cursor = 1;
	Cell* cell2 = NULL;
	void* info = NULL;
	
	if(index < end - index) {
		while(cursor < index) {
			cursor++;
			aux = aux->next;
		}
		
		cell2 = aux->next;
		info = cell2->info;
		aux->next = aux->next->next;
		
		if(aux->next != NULL)
			aux->next->prev = aux;
		
		free(cell2);
		return info;
	} else {
		aux = list->last;
		end--;
		
		while(index < end) {
			index++;
			aux = aux->prev;
		}
		
		cell2 = aux->prev;
		info = cell2->info;
		aux->prev = aux->prev->prev;
		
		if(aux->prev != NULL)
			aux->prev->next = aux;
		
		free(cell2);
		return info;
	}
}

void* list_find(List* list, int (*callback) (void*, void*), void* info){
	if(list == NULL || list->first == NULL)
		return NULL;
	
	Cell* aux = list->first;
	while(aux !=NULL) {
		if( callback(aux->info, info) == 1)
			return aux->info;
	
		aux = aux->next;
	}
	
	return NULL;
}

int list_find_position(List* list, int (*callback) (void*, void*), void* info) {
	if(list == NULL || list->first == NULL)
		return -1;
	
	Cell* aux = list->first;
	int i = 0;
	while(aux !=NULL) {
		if( callback(aux->info, info) == 1)
			return i;
			
		aux = aux->next;
		i++;
	}
	
	return -1;
}

void* list_exchange_element(List* list, int index, void* info) {
	return NULL;
}

void list_exchange_two_elements(List* list, int index1, int index2) {
	int size = list->lenght -1;
	
	int smaller = 0 ;
	int larger = 0;
	
	if(index1 < index2) {
		smaller = index1;
		larger = index2;
	} else {
		smaller = index2;
		larger = index1;
	}
	
	Cell* aux = list->first;
	Cell* cell1 = NULL;
	Cell* cell2 = NULL;
	
	int position = 0;
	
	//Finding a better path for the first cell.
	   //smaller - first_position = smaller - 0 = smaller
	if(smaller < (size - larger) ) {
		position = smaller;
		while(position > 0) {
			aux = aux->next;
			position--;
		}
		
		cell1 = aux;
		 
		if( (larger - smaller) < (size - larger) ) {
			position = smaller;
			while (position < larger) {
				aux = aux->next;
				position++;
			}
			
			cell2 = aux;
		} else {
			aux = list->last;
			
			position = larger;
			while(position < size) {
				aux = aux->prev;
				position++;
			}
			
			cell2 = aux;
		}
	} else {
		aux = list->last;
		
		position = larger;
		while(larger < size) {
			aux = aux->prev;
			larger++;
		}
		
		cell1 = aux;
		
		if(smaller < (larger - smaller)) {
			aux = list->first;
			
			position = 0;
			while(position < smaller) {
				aux = aux->next;
				position++;
			}
			
			cell2 = aux;
		} else {
			position = smaller;
			while (position < larger) {
				aux = aux->prev;
				position++;
			}
			
			cell2 = aux;
		}
	}
	
	void* info = cell1->info;
	cell1->info = cell2->info;
	cell2->info = info;
	return;
}

void list_exchange_two_elements_in_lists(List* list1, List* list2, int index_list1, int index_list2) {
	Cell* cell1 = NULL;
	Cell* cell2 = NULL;
	
	Cell* aux = list1->first;
	int position = 0;
	
	int size_list1 = list1->lenght;
	int size_list2 = list2->lenght;
	
	if(index_list1 < (size_list1 - index_list1)) {
		position = 0;
		while(position < index_list1) {
			aux = aux->next;
			position++;
		}
		
		cell1 = aux;
		
	} else {
		aux = list1->last;
		
		position = index_list1;
		while(position < size_list1) {
			 aux = aux->prev;
			 position++;
		}
		
		cell1 = aux;
	}
	
	if(index_list2 < (size_list2 - index_list2)) {
		aux = list2->first;
		position = 0;
		while(position < index_list2) {
			aux = aux->next;
			position++;
		}
		
		cell2 = aux;
		
	} else {
		aux = list2->last;
		
		position = index_list2;
		while(position < size_list2) {
			 aux = aux->prev;
			 position++;
		}
		
		cell2 = aux;
	}
	
	void* info = cell1->info;
	cell1->info = cell2->info;
	cell2->info = info;
	
	return;
}

List* list_sort(List *list, int (*callback) (void*)) {
	return NULL;
}

List* list_clone(List* list){
	List* new_list = list_create();

	Cell* aux = list->first;
	void* info = NULL;
	
	while(aux != NULL) {
		info = aux->info;
		list_insert_last(new_list, info);
		aux = aux->next;
	}
	
	return new_list;
}

List* list_create_conected(List* list1, List* list2) {
	List* new_list = list_create();
	
	Cell* aux = list1->first;
	while(aux != NULL) {
		list_insert_last(new_list, aux->info);
		aux = aux->next;
	}
	
	aux = list2->first;
	while(aux != NULL) {
		list_insert_last(new_list, aux->info);
		aux = aux->next;
	}
	
	return new_list;
}

List* list_conect(List* list1, List* list2) {
	list2->first->prev = list1->last;
	list1->last->next = list2->first;
	free(list2);
	return list1;
}

Iterator* iterator_create(List* list){
	return list->first;
}

void* iterator_get_current(Iterator* iterator){
	return iterator->info;
}

int iterator_is_empty(Iterator* iterator) {
	if(iterator == NULL)
		return 1;

	return 0;
}

int iterator_has_next(Iterator* iterator) {
	if(iterator->next != NULL) {
		return 1;
	}
	return 0;
}

Iterator* iterator_next(Iterator* iterator) {
	return iterator->next;
}

int iterator_has_previous(Iterator* iterator) {
	if(iterator->prev != NULL) {
		return 1;
	}
	return 0;
}

Iterator* iterator_prev(Iterator* iterator){
	return iterator->prev;
}

/*
Iterator* iterator_create(List* list){
	Iterator* iterator = (Iterator*) malloc (sizeof(Iterator));
	
	int size = list->lenght;
	iterator->cursor = 0;
	iterator->end = size;
	iterator->elements = (void**) malloc (size * sizeof(void*));
	
	Cell *aux = list->first;
	int index = 0;
	while(index < size) {
		iterator->elements[index] = aux->info;
		aux = aux->next;
	}
	
	return iterator;
}

void* iterator_get_current_element(Iterator* iterator) {
	return iterator->elements[iterator->cursor];
}	

int iterator_has_next(Iterator* iterator) {
	if(iterator->cursor < iterator->end) {
		return 1;
	}
	
	return 0;
}

Iterator* iterator_next(Iterator* iterator) {
	iterator->cursor++;
	return iterator;
}

//Iterator should be in a valid current position.
int iterator_has_previous(Iterator* iterator) {
	if(iterator->cursor > 0) {
		return 1;
	}
	
	return 0;
}

Iterator* iterator_prev(Iterator* iterator){
	iterator->cursor--;
	return iterator;
}

Iterator* iterator_clear(Iterator* iterator) {
	free(iterator->elements);
	free(iterator);
	
	return NULL;
}*/
