/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjung <hjung@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 16:06:56 by hjung             #+#    #+#             */
/*   Updated: 2021/02/13 10:23:56 by hjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void		init_philo(t_philo *philos)
{
	int		i;

	i = 0;
	while (i < philos->table->nbr_philos)
	{
		philos[i].last_meal = get_time();
		pthread_create(&philos[i].tid, NULL, philo_act, &philos[i]);
		i++;
	}
	i = 0;
	while (i < philos->table->nbr_philos)
	{
		pthread_join(philos[i].tid, NULL);
		i++;
	}
}

static void	assign_fork(t_philo *philo, int idx)
{
	philo->fork1 = idx - 1;
	if (idx == 0)
		philo->fork1 = philo->table->nbr_philos - 1;
	philo->fork2 = idx;
}

int			init_table(t_table *table, t_philo *philos)
{
	int		i;

	i = 0;
	if (!(table->fork = malloc(sizeof(pthread_mutex_t) * table->nbr_philos)))
		return (p_error("Error: malloc failed\n"));
	while (i < table->nbr_philos)
	{
		pthread_mutex_init(&table->fork[i], NULL);
		philos[i].table = table;
		philos[i].nbr = i + 1;
		philos[i].cnt_eat = 0;
		assign_fork(&philos[i], i);
		i++;
	}
	pthread_mutex_init(&table->write_msg, NULL);
	pthread_mutex_init(&table->m_eat, NULL);
	pthread_mutex_init(&table->m_dead, NULL);
	table->tot_eat = 0;
	table->is_dead = 0;
	table->base_time = get_time();
	init_philo(philos);
	return (0);
}
