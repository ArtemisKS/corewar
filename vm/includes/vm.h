/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 14:57:01 by vbrazas           #+#    #+#             */
/*   Updated: 2018/10/17 19:18:56 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include <curses.h>
# include <time.h>
# include <libftprintf.h>
# include <op.h>

typedef struct s_args			t_args;
typedef struct s_player			t_player;
typedef struct s_corewar		t_vm;
typedef struct s_operations		t_op;
typedef struct s_carriage		t_car;
typedef struct s_info			t_info;
typedef struct s_curses			t_curses;
typedef struct s_colors			t_colors;
typedef struct s_widgets		t_widgets;
typedef struct s_music			t_music;

/*
** Music structure
*/

# define M					v->music
# define VENOM_START_DUR	14
# define SKIBIDI_START_DUR	8
# define VENOM_DIE_DUR		14
# define SKIBIDI_DIE_DUR	4
# define MSTART				1
# define MDIE				2
# define MEND				4

struct				s_music
{
	unsigned char	is_music : 1;
	unsigned char	is_venom : 1;
	unsigned char	is_skibidi : 1;
	unsigned char	to_wait;
	char			*play_start;
	char			*play_die;
	char			*play_end;
	time_t			playing;
};

/*
** Color pair defines
*/

# define BORDER						31
# define MAIN						32
# define INFO						33
# define COLOR_REDDY				34
# define COLOR_DARK					40
# define COLOR_ORANGE				41
# define STAT						42
# define COLOR_DELTA				10
# define CLR_CYCTOWAIT				50

/*
** ncurses visualizer info
*/

# define EXIT_KEY					27
# define RUN						' '
# define PASS_OVER					's'
# define RUN_SLOWER					'q'
# define RUN_QUICKER				'r'
# define RUN_SLOWER2				'w'
# define RUN_QUICKER2				'e'

# define BORDC						'*'
# define SQMAX_VAL					777
# define TOT_LIVES_TERM				1000
# define SQBIG_VAL					10
# define SQSMALL_VAL				1
# define COLOR_AMOUNT				(MAX_PLAYERS + 1)
# define COMMON_HEIGHT				(MEM_SIZE / 64 + 4)
# define MW_WIDTH					(64 * 3 + 7)
# define IW_WIDTH					(MW_WIDTH / 3)
# define SW_WIDTH					(MW_WIDTH + IW_WIDTH - 1)
# define START_CYCLES_PER_SEC		50
# define START_ROW					2

# define ALIGN_CENTER(width, len)	(((width)-(len))?(((width)-(len))/2):0)

struct				s_widgets
{
	int				totliv_in_cp;
	int				totliv_in_lp;

	int				pval[MAX_PLAYERS];
	int				last_pval[MAX_PLAYERS];
};

struct				s_colors
{
	unsigned char	main;
	unsigned char	bold;
	unsigned char	undrln;
};

# define N			v->ncurses

struct				s_curses
{
	bool			is_run;
	char			c;
	int				cycpersec;
	clock_t			t;

	WINDOW			*mainw;
	WINDOW			*infow;
	WINDOW			*statw;

	t_colors		clr[MEM_SIZE];

	short			ccolors[COLOR_AMOUNT];
	short			pcolors[COLOR_AMOUNT];
	short			scolors[COLOR_AMOUNT];

	t_widgets		w;
};

void				visualize_the_game(t_vm *v);
void				init_windows(t_vm *v);
void				set_start_vis_cycle(t_vm *v);
void				put_car_color_to_arena(t_vm *v);
void				print_one_cycle(t_vm *v, const bool is_pass_cycle);
void				print_widgets(t_vm *v, int *row);
void				print_info(t_vm *v, const bool is_print_full_info);
void				print_stats(t_vm *v);
void				deinit_windows(t_vm *v);
void				put_border(WINDOW *win);
void				play_music(t_vm *v, int flag);

/*
** Info structure
*/

# define I			v->info
# define PC_IND		(self->pc - v->arena)

struct				s_info
{
	unsigned int	cursors;
	unsigned int	cur_cycle;
	int				cycle_to_delta;
	int				cycle_to_die;
	unsigned int	winner;
};

/*
** Structure of passed args
*/

# define A			v->args

struct				s_args
{
	unsigned int	is_ncurses : 1;
	unsigned int	is_nostat : 1;
	unsigned int	is_dump : 1;
	unsigned int	is_stealth : 1;
	unsigned int	vis_start_value;
	unsigned int	dump_value;
	unsigned int	verbose_value;
};

/*
** Operations structure
*/

struct				s_operations
{
	char			*name;
	unsigned char	nb_arg;
	unsigned char	args[3];
	unsigned char	opcode;
	unsigned int	cycles;
	char			*description;
	bool			octal;
	bool			label;
	void			(*f)(t_car *car, t_vm *v);
};

/*
** Structure of the single player
*/

# define P(x)		v->player[x]

struct				s_player
{
	bool			is_alive;
	int				fd;

	unsigned int	name;
	unsigned int	lives_in_cp;
	unsigned int	magic;
	unsigned int	points;
	unsigned int	prog_size;
	unsigned int	total_lives;

	char			*filename;
	char			prog_name[PROG_NAME_LENGTH + 1];
	char			comment[COMMENT_LENGTH + 1];
	char			source_code[MEM_SIZE];
};

/*
** Carriage structure
*/

# define PL_IND(t_car)	(((int)(t_car)->name * -1) - 1)

struct				s_carriage
{
	bool			carry;
	unsigned int	name;
	int				cycles_to_wait;
	int				cur_operation;
	int				nb_lives;
	int				pc_padding;
	int				id;
	int				live_cycle;

	unsigned char	*pc;
	unsigned int	reg[REG_NUMBER + 1];
	unsigned int	args[3];
	unsigned int	arg_val[3];

	t_car			*prev;
	t_car			*next;
};

t_car				*get_last_car(t_vm *v);
void				copy_car(t_car *cc, t_vm *v, unsigned char *pc);
void				delete_this_car(t_car **cur_car, t_vm *v);
void				init_car(unsigned char *where, unsigned int whom, t_vm *v,
	bool are_initialized_colors);
void				print_arena(unsigned char *arena, unsigned char to_equate,
	t_car *self, t_vm *v);
void				move_pc(t_car *self, t_vm *v, unsigned int padding,
	bool is_jump_car);

/*
** Main corewar structure
*/

struct				s_corewar
{
	int				player_amount;
	t_player		player[MAX_PLAYERS];

	unsigned char	arena[MEM_SIZE];

	t_car			*head;
	t_curses		*ncurses;

	t_args			args;
	t_info			info;
	t_music			music;
};

void				check_and_obtain_args(int ac, char **av, t_vm *v);
void				fill_players(t_vm *v);
void				fill_arena(t_vm *v);

void				pass_one_cycle(t_vm *v);
void				perform_next_comm(t_car *self, t_vm *v);
int					vnp_codage(t_car *self, const t_op *cur, t_vm *v);
void				get_winner(t_vm *v);

/*
** Operations functions
*/

# define PUMPKIN		(res << (8 * i)) >> (8 * (size - 1))
# define SPACE_TO_END	(MEM_SIZE - PC_IND)
# define SHORT_RANGE	(USHRT_MAX + 1)
# define FPOS			16962
# define TNTZEROS		2900
# define FPOS1			21530

void				add(t_car *self, t_vm *v);
void				aff(t_car *self, t_vm *v);
void				and(t_car *self, t_vm *v);
void				ld(t_car *self, t_vm *v);
void				ldi(t_car *self, t_vm *v);
void				lfork(t_car *self, t_vm *v);
void				live(t_car *self, t_vm *v);
void				lld(t_car *self, t_vm *v);
void				lldi(t_car *self, t_vm *v);
void				op_fork(t_car *self, t_vm *v);
void				or(t_car *self, t_vm *v);
void				st(t_car *self, t_vm *v);
int					set_val_neg(t_car *self, t_vm *v, long arg_sum);
int					set_val(t_car *self, t_vm *v, long arg_sum);
void				sti(t_car *self, t_vm *v);
void				sub(t_car *self, t_vm *v);
void				xor(t_car *self, t_vm *v);
void				zjmp(t_car *self, t_vm *v);

/*
** Utils
*/

int					meta_reader(const int fd, void *read_in, const int nbytes);
void				dump_printer(const void *to_print, const int nbytes);
unsigned int		read_raw_num(const int fd, const int chars_to_read);
unsigned int		get_raw_num(const unsigned char *arena,
	const int bytes_to_read, const t_vm *v);

/*
** Put Error functions
*/

bool				put_usage(const int errnum);
bool				put_error(const int errnum, const char *errstr,
	const int i1, const int i2);

/*
** do al stuf; if you nkow da wae!
*/

void				kill_process(unsigned int *last_check, t_vm *v);
bool				nbr_live_exec(t_car *car);
void				make_live_nil(t_vm *v);
int					ft_abs(int x);

#endif
