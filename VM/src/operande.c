/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operande.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmichel <hmichel@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 21:49:44 by hmichel           #+#    #+#             */
/*   Updated: 2020/02/28 20:40:33 by hmichel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"


int			ft_get_op(t_war *war, t_chariot *chariot)
{
	int		pos;

	if (chariot->ope != -1)
		return (0);
	pos = chariot->start_pos + chariot->pc;
	if (pos >= MEM_SIZE - 1)
	{
		chariot->pc = -1;
		chariot->start_pos = 0;
	}
	if (war->arena[pos] > 16 || war->arena[pos] <= 0)
	{
		chariot->pc++;
		return (0);
	}
	else
		chariot->ope = war->arena[pos];
	return (1);
}

int			is_conform(char ocp, int param, int ope)
{
	if (ocp == 0)
		return (FAILURE);
	if (ocp == 1 && (0x01 & g_op_tab[ope].params_type[param])) // <=> (g_op_tab[ope].params_type[param] % 2) == 1
		return (T_REG);
	if (ocp == 2 && (0x02 & g_op_tab[ope].params_type[param])) // <=> (g_op_tab[ope].params_type[param] % 4) >= 2
	{
		if (g_op_tab[ope].label_size)
			return (T_DIR_TWO);
		return (T_DIR_FOUR);
	}
	if (ocp == 3 && (0x04 & g_op_tab[ope].params_type[param])) // <=> (g_op_tab[ope].params_type[param] % 8) >= 4
		return (2);
	return (FAILURE);
}

int			ft_tcheck_ocp(t_chariot *chariot, t_war *war)//return jump
{
	unsigned char		ocp;
	int					jump;

	if (chariot->ope == 1)
		return (5);
	if (g_op_tab[chariot->ope - 1].acb == 0)
		return (3);
	jump = 2;
	ocp = war->arena[chariot->start_pos + chariot->pc + 1];
	if (!(jump += is_conform((ocp >> 6), 0, chariot->ope - 1)))
		return (FAILURE);
	if (g_op_tab[chariot->ope - 1].nb_params >= 2)
		if (!(jump += is_conform(((ocp & 0x30) >> 4), 1, chariot->ope - 1)))
			return (FAILURE);
	if (g_op_tab[chariot->ope - 1].nb_params == 3)
		if (!(jump += is_conform(((ocp & 0x0C) >> 2), 2, chariot->ope - 1)))
			return (FAILURE);
	return (jump);
}

void		ft_exec_opp(t_chariot *chariot, t_war *war, t_opp *opp_tab)
{
	int		jump;

	jump = 0;
	if (chariot->wait > 0)
		chariot->wait--;
	if ((chariot->wait == 0) && chariot->ope > 0)
	{
		if ((jump = ft_tcheck_ocp(chariot, war)))
		{
			opp_tab[chariot->ope - 1](war, chariot);
			if (war->back_pc == 0)
				chariot->pc += jump;
			war->back_pc = 0;
		}
		chariot->ope = -1;
	}
	if (ft_get_op(war, chariot) == 1) //&& chariot->ope >= 1) //on tcheck si on lit une nouvelle operande, si oui on init "wait"
		chariot->wait = war->op_cycle[chariot->ope - 1];
}

