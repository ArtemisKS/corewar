/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:48:33 by vbrazas           #+#    #+#             */
/*   Updated: 2018/08/16 15:19:18 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void		sub(t_car *self, t_vm *v)
{
	self->arg_val[2] = self->args[0] - self->args[1];
	self->carry = self->arg_val[2] ? false : true;
}