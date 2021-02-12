/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjung <hjung@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 16:49:34 by hjung             #+#    #+#             */
/*   Updated: 2021/02/12 16:52:14 by hjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int		msg(t_philo *philo, int msg, unsigned long current_time)
{
	t_table			*table;

	table = philo->table;
	sem_wait(table->write_msg);
	if (table->is_dead)
	{
		sem_post(table->write_msg);
		return (1);
	}
	printf("%lu %d", current_time - table->base_time, philo->nbr);
	(msg == TAKEN_FORK) && printf(" has taken a fork\n");
	if (msg == EATING)
	{
		printf(" is eating\n");
		philo->last_meal = current_time;
	}
	(msg == SLEEPING) && printf(" is sleeping\n");
	(msg == THINKING) && printf(" is thinking\n");
	(msg == DEAD) && printf(" died\n");
	sem_post(table->write_msg);
	return (0);
}

int		p_error(char *str)
{
	printf("%s", str);
	return (1);
}
