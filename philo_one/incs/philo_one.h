/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjung <hjung@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 23:03:24 by hjung             #+#    #+#             */
/*   Updated: 2021/02/07 01:13:07 by hjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct		s_table
{
	int				nbr_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_eat;
	pthread_mutex_t	*fork;

}					t_table;

typedef struct		s_philo
{
	int				nbr;
	int				fork1;
	int				fork2;
	int				eat;
}					t_philo;

int		parse(t_table *table, char **argv);
int		ft_atoi(const char *str);

int		p_error(char *str);

#endif