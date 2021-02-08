/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjung <hjung@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 18:31:33 by hjung             #+#    #+#             */
/*   Updated: 2021/02/08 19:18:32 by hjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	ft_atoi(const char *str)
{
	int cnt_minus;
	int res;

	cnt_minus = 1;
	res = 0;
	while (*str == '\t' || *str == '\n' || *str == '\v' ||
			*str == '\f' || *str == '\r' || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			cnt_minus *= (-1);
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = (res * 10) + (*str - '0');
		str++;
	}
	return (res * cnt_minus);
}

unsigned long	get_time(void)
{
	struct timeval		tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void		vsleep(unsigned long itime)
{
	unsigned long		stime;
	unsigned long		ctime;

	stime = get_time();				//base time
	while (1)
	{
		ctime = get_time();			//current time
		if (ctime - stime > itime)	//현재시간과 기준 시간의 차이가 itime 보다 크면 그냥 리턴하고 
			return ;
		usleep(100);				//아니면 100ms 쉰다. 이 부분은 없어도 되긴함.
	}
	/* 왜?
	** usleep()을 작동시키기까지 시간이 오래 걸리기도 하고, usleep(n)은 정확히 n 밀리초만큼 쉬는걸 보장하는게 아니라
	** 최소한 n 밀리초만큼 쉬는걸 보장하는 것이다. 
	** 여기서 ctime-stime 은 이 함수에 진입한 후 지난 시간을 계산할 것이고, 목표 대기시간인 itme 보다 커지면 반환된다.
	** 이렇게 하면 정확히 쉬고싶은 만큼 쉴 수 있게 됨.
	*/
}

void	clean_table(t_table *table, t_philo *philos)
{
	int		i;

	i = 0;
	while (i < table->nbr_philos)
	{
		pthread_mutex_destroy(&table->fork[i]);
		// pthread_mutex_destroy(&philos[i].lock);
		i++;
	}
	pthread_mutex_destroy(&table->write_msg);
	pthread_mutex_destroy(&table->m_eat);
	pthread_mutex_destroy(&table->m_dead);
	free(table->fork);
	free(philos);
}