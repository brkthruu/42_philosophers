/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjung <hjung@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 23:16:08 by hjung             #+#    #+#             */
/*   Updated: 2021/02/08 19:18:24 by hjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		msg(t_philo *philo, int msg, unsigned long current_time)
{
	t_table			*table;

	table = philo->table;
	pthread_mutex_lock(&table->write_msg);
	if ((msg != DEAD && someone_dead(philo, current_time)) || fully_eat(philo))
	{
		pthread_mutex_unlock(&table->write_msg);
		return (1);
	}
	printf("%lu %d", current_time - table->base_time, philo->nbr);
	if (msg == TAKEN_FORK)
		printf(" has taken a fork\n");
	if (msg == EATING)
	{
		printf(" is eating\n");
		// pthread_mutex_lock(&philo->lock);
		philo->last_meal = current_time;
		// pthread_mutex_unlock(&philo->lock);
	}
	(msg == SLEEPING) && printf(" is sleeping\n");
	(msg == THINKING) && printf(" is thinking\n");
	(msg == DEAD) && printf(" died\n");
	pthread_mutex_unlock(&table->write_msg);
	return (0);
}

int		p_error(char *str)
{
	printf("%s", str);
	return (1);
}
