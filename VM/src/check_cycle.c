/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cycle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmichel <hmichel@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 02:23:24 by hmichel           #+#    #+#             */
/*   Updated: 2020/05/28 02:23:24 by hmichel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
//ini next_check a 1536
//compter live au chariot meme quand l'ope live s'execute pas normalement
int			check_cycle(t_war *war, t_chariot *chariot)
{
	if (war->cycles < war->next_check)
	{
		if (update_visu(war) != -1)
			war->cycles++;
		return (SUCCESS);
	}
	else
	{
		v_alive_chariot(chariot, war);
		if (war->nb_lives < NBR_LIVE && war->check_cycles_to_die < MAX_CHECKS)
		{
			war->check_cycles_to_die++;
			war->next_check += war->cycle_to_die;
		}
		else
		{
			war->check_cycles_to_die = 0;
			war->cycle_to_die -= CYCLE_DELTA;
			if (war->begin == NULL || (war->cycle_to_die <= 0))
			{
				if (war->verbose[3] == 1)
					printf("It is now cycle [%d]\n", war->cycles);//on observe last live pour le vainqueur
				//printf("Contestant %d, \"%s\", has won !\n", war->lastlive, war->player[war->lastlive].header.prog_name);
				return (FAILURE);
			}
			war->next_check += war->cycle_to_die;
			war->nb_lives = 0;
			reset_lives_chariot(war);
		}
		if (update_visu(war) != -1)
			war->cycles++;
	}
	return (SUCCESS);
}
