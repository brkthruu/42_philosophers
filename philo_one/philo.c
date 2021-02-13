/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjung <hjung@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 16:46:29 by hjung             #+#    #+#             */
/*   Updated: 2021/02/13 10:26:19 by hjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*philo_act(void *phi)
{
	t_philo		*philo;
	pthread_t	tid;

	philo = (t_philo *)phi;
	if (philo->nbr % 2 == 0)
		vsleep(1);
	pthread_create(&tid, NULL, philo_monitor, philo);
	while (1)
	{
		if (eat(philo))
			break ;
		if (msg(philo, SLEEPING, get_time()))
			break ;
		vsleep(philo->table->time_to_sleep);
		if (msg(philo, THINKING, get_time()))
			break ;
	}
	pthread_join(tid, NULL);
	return (NULL);
}

void	*philo_monitor(void *phi)
{
	t_philo			*philo;
	unsigned long	current_time;

	philo = (t_philo *)phi;
	while (1)
	{
		if (philo->cnt_eat == philo->table->nbr_eat)
			break ;
		current_time = get_time();
		if (current_time - philo->last_meal > philo->table->time_to_die)
		{
			pthread_mutex_lock(&philo->table->m_dead);
			if (philo->table->is_dead == 0)
			{
				msg(philo, DEAD, current_time);
				philo->table->is_dead += 1;
			}
			pthread_mutex_unlock(&philo->table->m_dead);
			return (NULL);
		}
		vsleep(1);
	}
	return (NULL);
}

int		eat(t_philo *philo)
{
	t_table		*table;

	table = philo->table;
	pthread_mutex_lock(&table->fork[philo->fork1]);
	msg(philo, TAKEN_FORK, get_time());
	pthread_mutex_lock(&table->fork[philo->fork2]);
	msg(philo, TAKEN_FORK, get_time());
	msg(philo, EATING, get_time());
	vsleep(table->time_to_eat);
	pthread_mutex_unlock(&table->fork[philo->fork1]);
	pthread_mutex_unlock(&table->fork[philo->fork2]);
	philo->cnt_eat += 1;
	pthread_mutex_lock(&philo->table->m_eat);
	if (table->nbr_eat != -1 && philo->cnt_eat == table->nbr_eat)
	{
		table->tot_eat += 1;
		pthread_mutex_unlock(&philo->table->m_eat);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->m_eat);
	return (0);
}
