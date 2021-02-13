/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_all_philos.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjung <hjung@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 15:25:46 by hjung             #+#    #+#             */
/*   Updated: 2021/02/13 10:22:12 by hjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		someone_dead(t_philo *philo, unsigned long current_time)
{
	pthread_mutex_lock(&philo->table->m_dead);
	if (philo->table->is_dead > 0 ||
		current_time - philo->last_meal > philo->table->time_to_die)
	{
		pthread_mutex_unlock(&philo->table->m_dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->m_dead);
	return (0);
}

int		fully_eat(t_philo *philo)
{
	if (philo->table->nbr_eat == -1)
		return (0);
	pthread_mutex_lock(&philo->table->m_eat);
	if (philo->table->tot_eat == philo->table->nbr_philos)
	{
		pthread_mutex_unlock(&philo->table->m_eat);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->m_eat);
	return (0);
}
