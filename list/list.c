#include <stdlib.h>
#include "list.h"


TListItem *list_create() {
	TListItem *item;

	item = (TListItem*)malloc(sizeof(TListItem));
	if (item != NULL) {
		(*item).data = NULL;
		(*item).next = NULL;
	}

	return item;
}


TListItem *list_append(TListItem *head, void *data) {
	TListItem *item;

	while ((*head).next != NULL) {
		head = (*head).next;
	}

	item = (TListItem*)malloc(sizeof(TListItem));
	if (item != NULL) {
		(*item).data = data;
		(*item).next = NULL;

		(*head).next = item;
	}

	return item;
}

void list_traverse(TListItem *head, TFunc f) {
	head = head->next;
	while (head != NULL) {
		f(head->data);
		head = head->next;
	}
}


void list_free(TListItem **head) {
	TListItem *ptr, *next;

	ptr = *head;

	while (ptr != NULL) {
		next = (*ptr).next;
		if (ptr->data != NULL)
			free(ptr->data);
		free(ptr);
		ptr = next;
	} 

	*head = NULL;
}

TListItem* list_search(TListItem* head, double needle) {
	while (head != NULL)
	{
		if (head->data != NULL && *(double*)head->data == needle)
		{
			return head;
		}
		head = head->next;
	}
	return NULL;
}


void* list_delete(TListItem* head, TListItem* item) {
	while (head != NULL && head->next != item)
	{
		head = head->next;
	}
	if (head)
	{
		head->next = item->next;
		free(item->data);
		free(item);
	}
}

TListItem* list_insert(TListItem* item, void* data) {
	TListItem* ptr = (TListItem*)malloc(sizeof(TListItem));
	ptr->data = data;
	ptr->next = item->next;
	item->next = ptr;
	return ptr;
}