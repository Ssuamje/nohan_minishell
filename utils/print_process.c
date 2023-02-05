#include "../include/utils.h"

void	print_process(t_process *proc, int idx)
{
	printf("**********process %d**********\n", idx);
	print_redir_list(proc->redir_in);
	print_redir_list(proc->redir_out);
	print_split(proc->cmd);
}

void	print_processes_list(t_list *processes)
{
	t_list		*tmp;
	int			idx;
	t_process	*cur;

	tmp = processes->next;
	idx = 0;
	while (tmp != NULL && tmp->content != NULL)
	{
		cur = tmp->content;

		print_process(cur, idx);
		idx++;
		tmp = tmp->next;
	}
}