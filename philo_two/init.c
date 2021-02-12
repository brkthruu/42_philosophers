/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjung <hjung@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 16:06:56 by hjung             #+#    #+#             */
/*   Updated: 2021/02/12 13:03:19 by hjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

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

void		clear_sem(void)
{
	sem_unlink("/enter");
	sem_unlink("/fork");
	sem_unlink("/write_msg");
	sem_unlink("/m_eat");
	sem_unlink("/m_dead");
}

void		init_sem(t_table *table)
{
	table->enter = sem_open("/enter", O_CREAT | O_EXCL, 0644,
		table->nbr_philos / 2);
	table->fork = sem_open("/fork", O_CREAT | O_EXCL, 0644, table->nbr_philos);
	table->write_msg = sem_open("/write_msg", O_CREAT | O_EXCL, 0644, 1);
	table->m_eat = sem_open("/m_eat", O_CREAT | O_EXCL, 0644, 1);
	table->m_dead = sem_open("/m_dead", O_CREAT | O_EXCL, 0644, 1);
}

int			init_table(t_table *table, t_philo *philos)
{
	int		i;

	i = 0;
	while (i < table->nbr_philos)
	{
		philos[i].table = table;
		philos[i].nbr = i + 1;
		philos[i].cnt_eat = 0;
		i++;
	}
	init_sem(table);
	table->tot_eat = 0;
	table->is_dead = 0;
	table->base_time = get_time();
	clear_sem();
	init_philo(philos);
	return (0);
}
