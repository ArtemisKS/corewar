/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:50:06 by vbrazas           #+#    #+#             */
/*   Updated: 2018/09/05 23:28:17 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void		op_fork(t_car *self, t_vm *v)
{
	const int		to_subtract = self->pc - v->arena;
	unsigned char	*pc;
	t_car			tmp;

	//ft_dprintf(fd, "self->arg_val[0]: %d | IDX_MOD: %d | mod(self->arg_val[0] - IDX_MOD) : %d | to_subtract: %d\n", self->arg_val[0], IDX_MOD, (mod(self->arg_val[0] - IDX_MOD)), to_subtract);
	if (self->arg_val[0] > IDX_MOD)
	{
		self->arg_val[0] %= IDX_MOD;
		if (mod((int)self->arg_val[0] - IDX_MOD) > to_subtract)
		{
			//ft_dprintf(fd, "%d | %d | MOD : %d | to_subtract: %d\n", self->arg_val[0], IDX_MOD, (mod(self->arg_val[0] - IDX_MOD)), to_subtract);
			pc = &v->arena[MEM_SIZE + (self->arg_val[0] - IDX_MOD) - to_subtract];
		}
		else
			pc = &v->arena[to_subtract + (self->arg_val[0] - IDX_MOD)];
	}
	else
	{
		if (self->arg_val[0] == IDX_MOD)
			self->arg_val[0] %= IDX_MOD;
		if (self->arg_val[0] > to_subtract)
			pc = &v->arena[self->arg_val[0] - to_subtract];
		else
			pc = &self->pc[self->arg_val[0]];
	}
	copy_car(self, v, pc);
	move_pc(self, v, self->pc_padding);
	self->pc_padding = 0;
}
