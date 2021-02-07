/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjung <hjung@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 16:06:56 by hjung             #+#    #+#             */
/*   Updated: 2021/02/07 16:36:02 by hjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"
static void	assign_fork(t_philo *philo, int idx)
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
	table->cnt_tot_eat = 0;
	table->is_dead = 0;
	table->base_time = get_time();
	return (0);
}