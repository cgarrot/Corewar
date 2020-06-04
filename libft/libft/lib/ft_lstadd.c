/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lstadd.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: cgarrot <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/13 15:42:39 by cgarrot      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/13 16:17:16 by cgarrot     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../inc/libft.h"

void	ft_lstadd(t_list **alst, t_list *new)
{
	if (new != 0)
	{
		new->next = *alst;
		*alst = new;
	}
}
