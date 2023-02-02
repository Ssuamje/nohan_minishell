#include "../include/utils.h"

void	print_split(char **split)
{
	int idx;

	idx = 0;
	if (split == NULL)
		return ;
	printf("*************printing split***********\n");
	while (split[idx] != NULL)
	{
		printf("_%s_ ", split[idx]);
		idx++;
	}
	printf("\n");
}