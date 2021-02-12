/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjung <hjung@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 12:19:11 by hjung             #+#    #+#             */
/*   Updated: 2021/02/12 19:44:32 by hjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>

# define TAKEN_FORK	0
# define EATING		1
# define SLEEPING	2
# define THINKING	3
# define DEAD		4

typedef struct		s_table
{
	int				nbr_philos;
	unsigned long	time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_eat;
	int				tot_eat;
	int				is_dead;
	unsigned long	base_time;
	sem_t			*enter;
	sem_t			*fork;
	sem_t			*write_msg;
	sem_t			*m_eat;
	sem_t			*m_dead;
}					t_table;

typedef struct		s_philo
{
	int				nbr;
	int				fork1;
	int				fork2;
	int				cnt_eat;
	unsigned long	last_meal;
	pid_t			pid;
	t_table			*table;
}					t_philo;

int					parse(t_table *table, char **argv);
int					init_table(t_table *table, t_philo *philos);
void				init_sem(t_table *table);
void				clear_sem(void);
void				close_sem(t_table *table);
void				init_philo(t_philo *philos);

void				*philo_act(void *phi);
void				*philo_monitor(void *phi);
int					eat(t_philo *philo);
int					msg(t_philo *philo, int msg, unsigned long current_time);
int					kill_process(t_philo *philos);
void				process_monitor(t_philo *philos);
int					p_error(char *str);

int					ft_atoi(const char *str);
unsigned long		get_time(void);
void				vsleep(unsigned long itime);

#endif
