/*# **************************************************************************** #*/
/*#                                                                              #*/
/*#                                                         :::      ::::::::    #*/
/*#    bite                                               :+:      :+:    :+:    #*/
/*#                                                     +:+ +:+         +:+      #*/
/*#    By: maegaspa <marvin@42.fr>                    +#+  +:+       +#+         #*/
/*#                                                 +#+#+#+#+#+   +#+            #*/
/*#    Created: 2020/03/06 21:57:36 by maegaspa          #+#    #+#              #*/
/*#    Updated: 2020/03/06 21:58:16 by maegaspa         ###   ########lyon.fr    #*/
/*#                                                                              #*/
/*# **************************************************************************** #*/

#include "../includes/asm.h"

void	convert_int(unsigned char **str, int nb)
{
	(*str)[0] = (nb >> 24) & 0xFF;
	(*str)[1] = (nb >> 16) & 0xFF;
	(*str)[2] = (nb >> 8) & 0xFF;
	(*str)[3] = nb & 0xFF;
}

void    write_binary_int(int nb, int fd)
{
	unsigned char	*str;

	str = (unsigned char *)ft_strnew(4);
	convert_int(&str, nb);
	write(fd, str, 4);
	free(str);
}

int		get_label_init(t_tab *tab)
{
	int		i;

	i = -1;
	ft_bzero(tab->tabyte, CHAMP_MAX_SIZE);
 	if (!(tab->n_label = (int *)malloc(sizeof(int) * tab->nb_instruction)))
		return (ERROR_MALLOC);
    if (!(tab->label_name = (char **)malloc(sizeof(char*) * tab->nb_instruction)))
		return (ERROR_MALLOC);
    i = -1;
    while(++i < tab->nb_instruction)
    {
    	if (!(tab->label_name[i] = (char *)malloc(sizeof(char) * 6)))
    		return (ERROR_MALLOC);
    	ft_bzero(tab->label_name[i], 6);
   		tab->n_label[i] = 0;
   	}
   	return (SUCCESS);
}

int		which_direct(t_tab *tab, int actual_inst)
{
    if (tab->info_ins[actual_inst].id_inst == 9 || tab->info_ins[actual_inst].id_inst == 10 || tab->info_ins[actual_inst].id_inst == 11
    	|| tab->info_ins[actual_inst].id_inst == 12 || tab->info_ins[actual_inst].id_inst == 15)
    	return (1);
   	if (tab->info_ins[actual_inst].id_inst == 1 || tab->info_ins[actual_inst].id_inst == 2 || tab->info_ins[actual_inst].id_inst == 6
   		|| tab->info_ins[actual_inst].id_inst == 7 || tab->info_ins[actual_inst].id_inst == 8 || tab->info_ins[actual_inst].id_inst == 13) //CAS : DIRECT LABEL CHAR DEFINI SUR 4 OCTETS
   		return (2);
   	return (0);
}

int		get_dir_pos(t_tab *tab, t_file *file)
{
	int		i;
	int		k;
	int		j;

	i = -1;
	k = 0;
	j = 0;
	if (!(tab->dir_pos = (int*)malloc(sizeof(int) * tab->nb_instruction)))
		return (ERROR_MALLOC);
	if (!(tab->r_pos = (int*)malloc(sizeof(int) * tab->nb_instruction)))
    	return (ERROR_MALLOC);
	while (++i < file->max_byte)
	{
		if (tab->tabyte[i] > 0 && tab->tabyte[i] != 5)
			tab->dir_pos[k++] = i;
		if (tab->tabyte[i] == 5)
			tab->r_pos[j++] = i;
	}
	return (SUCCESS);
}
