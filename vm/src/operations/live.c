/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:47:10 by vbrazas           #+#    #+#             */
/*   Updated: 2018/09/06 21:55:51 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void		live(t_car *self, t_vm *v)
{
	int i;

	i = -1;
	self->nb_lives++;
	self->live_cycle = I.cur_cycle;
	while (++i < v->player_amount)
	{
		if (self->arg_val[0] == v->player[i].name)
		{
			P(i).is_alive = true;
			P(i).points = I.cur_cycle;
			P(i).lives_in_cp++;
		}
	}
	if (v->args.verbose_value & 4)
		ft_printf("P    %d | live %d\n", self->id, self->arg_val[0]);
	move_pc(self, v, self->pc_padding, false);
	self->pc_padding = 0;
}
