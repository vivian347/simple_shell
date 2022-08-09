#include "shell.h"

void free_list(list_t *ptr);
void aliaslist_free(alias_t *ptr);
list_t *endnode_add(list_t **head, char *dir);
alias_t *endalias_add(alias_t **head, char *identifier, char *val);

/**
 * free_list - frees list_t
 * @ptr: head of list_t
 * Return: void
 */
void free_list(list_t *ptr)
{
    list_t *n;

    while (head)
    {
        n = ptr->next;
        free(ptr->dir);
        free(ptr);
        ptr = n;
    }
}

/**
 * aliaslist_free - frees alias_t
 * @ptr: head of alias_t
 * Return: void
 */
void aliaslist_free(alias_t *ptr)
{
    alias_t *n;

    while (ptr)
    {
        n = ptr->n;
        free(ptr->name);
        free(ptr->value);
        free(ptr);
        ptr = n;
    }
}
/**
 * endnode_add - adds node at end of list_t
 * @head: head of list_t
 * @dir: dir path of added node
 * Return: pointer to node, NULL on error
 */
list_t *endnode_add(list_t **head, char *dir)
{
    list_t *end;
	list_t *node = malloc(sizeof(list_t));

	if (!node)
		return (NULL);
	node->dir = dir;
	node->next = NULL;
	if (*head)
	{
		end = *head;
		while (end->next != NULL)
			end = end->next;
		end->next = node;
	}
	else
		*head = node;

	return (node);
}
/**
 * endalias_add - adds node at end of alias_t
 * @head: head of alias_t
 * @identifier: name of node added
 * @val: value of node
 * Return: pointer to added node,
 * NULL on error
 */
alias_t *endalias_add(alias_t **head, char *identifier, char *val)
{
    alias_t *end;
	alias_t *node = malloc(sizeof(alias_t));

	if (!node)
		return (NULL);

	node->next = NULL;
	node->name = malloc(sizeof(char) * (_strlen(name) + 1));
	if (!node->name)
	{
		free(node);
		return (NULL);
	}
	node->value = val;
	cpy_str(node->name, identifier);

	if (*head)
	{
		end = *head;
		while (end->next != NULL)
			end = last->next;
		end->next = node;
	}
	else
		*head = node;

	return (node);
}