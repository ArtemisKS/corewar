/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 14:56:16 by vbrazas           #+#    #+#             */
/*   Updated: 2018/09/12 04:57:20 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

static inline void		end_the_game(t_vm *v)
{
	int		i;

	i = -1;
	get_winner(v);
	while (++i < v->player_amount)
	{
		close(P(i).fd);
	}
	ft_printf("Contestant %d, \"%s\", has won !\n",
	I.winner + 1, P(I.winner).prog_name);
}

static inline void		start_the_game(t_vm *v)
{
	int				i;

	i = -1;
	ft_putstr("Introducing contestants...\n");
	while (++i < v->player_amount)
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
		i + 1, P(i).prog_size,
		P(i).prog_name, P(i).comment);
}

void					pass_one_cycle(t_vm *v)
{
	t_car					*cur_car;
	static unsigned int		last_check = 0;

	!(A.verbose_value & 2) ? ++I.cur_cycle :
	ft_printf("It is now cycle %d\n", ++I.cur_cycle);
	last_check++;
	// if (I.cur_cycle == 25935 || I.cur_cycle == 25974)
	// 	ft_printf("");
	cur_car = v->head;
	while (cur_car)
	{
		perform_next_comm(cur_car, v);
		cur_car = cur_car->next;
	}
	if (last_check == I.cycle_to_die)
	{
		kill_process(&last_check, v);
		if (nbr_live_exec(v->head) || I.cycle_to_delta <= I.cur_cycle)
		{
			I.cycle_to_die -= CYCLE_DELTA;
			if (A.verbose_value & 2 && I.cycle_to_die > 0)
				ft_printf("Cycle to die is now %d\n", I.cycle_to_die);
			I.cycle_to_delta = I.cur_cycle + I.cycle_to_die * MAX_CHECKS;
		}
		make_live_nil(v);
	}
}

static inline void		play_the_game(t_vm *v)
{
	I.cycle_to_die = CYCLE_TO_DIE;
	I.cycle_to_delta = CYCLE_TO_DIE * MAX_CHECKS;
	if (A.is_ncurses)
		visualize_the_game(v);
	start_the_game(v);
	if (A.is_dump)
	{
		while (I.cycle_to_die > 0 && v->head && A.dump_value == I.cur_cycle)
			pass_one_cycle(v);
		dump_printer(v->arena, MEM_SIZE);
	}
	else
		while (I.cycle_to_die > 0 && v->head)
			pass_one_cycle(v);
}

int						main(int ac, char **av)
{
	t_vm		*v;

	v = ft_memalloc(sizeof(*v));
	check_and_obtain_args(ac, av, v);
	fill_players(v);
	fill_arena(v);
	play_the_game(v);
	end_the_game(v);
	return (0);
}
