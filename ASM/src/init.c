#include "../includes/asm.h"
#include <stdio.h>

int 	init_param(t_tab *tab, t_file *file)
{
	int 	i;

	i = -1;
	while (++i < tab->nb_instruction)
	{
		tab->info_ins[i].registre = 0;
		tab->info_ins[i].direct_str = NULL;
		tab->info_ins[i].direct = 0;
		tab->info_ins[i].indirect_str = NULL;
		tab->info_ins[i].indirect = 0;
		if (!(tab->info_ins[i].type_param = malloc(sizeof(int) * tab->info_ins[i].nb_parameter)))
				return (ERROR_MALLOC);
		tab->info_ins[i].check = 1;
		file->k = -1;
		while (++file->k < tab->info_ins[i].nb_parameter)
			tab->info_ins[i].type_param[file->k] = -1;
	}
	return (SUCCESS);
}

void 	init_struct_file(t_file *file)
{
	file->name = 0;
	file->comment = 0;
	file->count = -1;
	file->error = 0;
}

int 		init_instruction_tab(t_tab *tab, t_file *file)
{
	int i;

	i = -1;
	tab->nb_instruction = file->nb_instruction;
	if (!(tab->info_ins = malloc(sizeof(t_instruction) * tab->nb_instruction)))
		return (ERROR_MALLOC);
	while (++i < tab->nb_instruction)
		tab->info_ins[i].nb_parameter = 0;
	return (SUCCESS);
}