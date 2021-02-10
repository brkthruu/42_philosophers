/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjung <hjung@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 23:16:08 by hjung             #+#    #+#             */
/*   Updated: 2021/02/10 18:43:35 by hjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int		msg(t_philo *philo, int msg, unsigned long current_time)
{
	t_table		*table;

	table = philo->table;
	sem_wait(table->write_msg);
	if ((msg != DEAD && someone_dead(philo, current_time)) || fully_eat(philo))
	{
		sem_post(table->write_msg);
		return (1);
	}
	printf("%lu %d", current_time - table->base_time, philo->nbr);
	if (msg == TAKEN_FORK)
		printf(" has taken a fork\n");
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
