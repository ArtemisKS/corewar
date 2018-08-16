/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:51:04 by vbrazas           #+#    #+#             */
/*   Updated: 2018/08/15 21:55:59 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void			ldi(t_car *self, t_vm *v)
{
	unsigned char	*pc;
	int				arg_sum;

	if (self->args[0] == T_IND)
	{
		self->arg_val[0] %= IDX_MOD;
		if (self->arg_val[0] > ft_strlen((char*)self->pc))
			pc = &v->arena[self->arg_val[0] - ft_strlen((char*)self->pc)];
		else
			pc = &self->pc[self->arg_val[0]];
		arg_sum = get_raw_num(pc, 4) + self->arg_val[1];
	}
	else
		arg_sum = self->arg_val[0] + self->arg_val[1];
	arg_sum %= IDX_MOD;
	if (arg_sum > ft_strlen((char*)self->pc))
		pc = &v->arena[arg_sum - ft_strlen((char*)self->pc)];
	else
		pc = &self->pc[arg_sum];
	self->arg_val[2] = get_raw_num(pc, 4);
}