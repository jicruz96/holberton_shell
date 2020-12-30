#include "shell.h"

/**
 * free_command_chain - free command structs before exiting
 * @head: head of command linked list
 **/
 void free_command_chain(command_t *head)
 {
	 /* Must free path and node itself */
	 free(head->path);
	 free(head->input);
	 free(head->output));
	 free(head);
	 free_command_chain(head->next);
 }