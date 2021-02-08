/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjung <hjung@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 16:06:56 by hjung             #+#    #+#             */
/*   Updated: 2021/02/08 15:12:51 by hjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	init_philo(t_philo *philos)
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

static void	assign_fork(t_philo *philo, int idx)	// 여기선 잡을 수 있는 포크를 할당만 하는거지 포크를 잡는 것은 아님
{
	philo->fork1 = idx - 1;							//철학자는 자신의 오른쪽 포크를 먼저 할당받고
	if (idx == 0)									// 첫번째 철학자면 마지막번호의 포크를 할당.
		philo->fork1 = philo->table->nbr_philos - 1;
	philo->fork2 = idx;								// 그다음 자신의 왼쪽 포크를 할당 받음.
}	

int			init_table(t_table *table, t_philo *philos)
{
	int		i;
	
	i = 0;
	if (!(table->fork = malloc(sizeof(pthread_mutex_t) * table->nbr_philos)))
		return(p_error("Error: malloc failed\n"));
	while (i < table->nbr_philos)
	{
		pthread_mutex_init(&table->fork[i], NULL);
		pthread_mutex_init(&philos[i].lock, NULL);
		philos[i].table = table;
		philos[i].nbr = i;
		philos[i].cnt_eat = 0;
		assign_fork(&philos[i], i);
	}
	pthread_mutex_init(&table->write_msg, NULL);
	table->tot_eat = 0;
	table->is_dead = 0;
	table->base_time = get_time();
	init_philo(philos);
	return (0);
}