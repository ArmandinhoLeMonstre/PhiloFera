/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 19:15:07 by armitite          #+#    #+#             */
/*   Updated: 2024/12/14 20:55:40 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	sleep_n_think(t_philo *p)
// {
// 	pthread_mutex_lock(p->data->mutex_meals);
// 	printf("%ld %d is sleeping\n", time_now() - p->time, p->n);
// 	ft_usleep(p->data->sleeping_t);
// 	printf("%ld %d is thinking\n", time_now() - p->time, p->n);
// 	pthread_mutex_unlock(p->data->mutex_meals);
// }

void	eat(t_philo	*p)
{
	pthread_mutex_lock(p->left_fork);
	pthread_mutex_lock(p->right_fork);
	printf("%ld %d is taking fork\n", time_now() - p->time, p->n);
	printf("%ld %d is taking fork\n", time_now() - p->time, p->n);
	printf("%ld %d is eating\n", time_now() - p->time, p->n);
	ft_usleep(p->data->eating_t);
	pthread_mutex_unlock(p->left_fork);
	pthread_mutex_unlock(p->right_fork);
}

void    *routine(void *arg)
{
	t_philo *p = (t_philo *)arg;
	t_data *data;
	pthread_mutex_t *left_fork = p->data->mutex_forks[p->n - 1];
    pthread_mutex_t *right_fork = p->data->mutex_forks[p->n % p->data->p_total];
	data = p->data;
	// if (p->n % 2 == 0)
	//     ft_usleep(150);
	p->t_last_meal = time_now();
	while (1)
	{
		//eat(p);
	pthread_mutex_lock(left_fork);
	pthread_mutex_lock(right_fork);
	//pthread_mutex_lock(data->mutex_death);
	printf("%ld %d is taking fork\n", time_now() - data->time, p->n);
	printf("%ld %d is taking fork\n", time_now() - data->time, p->n);
	printf("%ld %d is eating\n", time_now() - data->time, p->n);
	ft_usleep(p->data->eating_t);
	pthread_mutex_unlock(left_fork);
	pthread_mutex_unlock(right_fork);
	printf("%ld %d is sleeping\n", time_now() - data->time, p->n);
	ft_usleep(p->data->sleeping_t);
	printf("%ld %d is thinking\n", time_now() - data->time, p->n);
	//pthread_mutex_unlock(data->mutex_death);
		// printf("%ld %d is sleeping\n", time_now() - data->time, p->n);
		// ft_usleep(p->data->sleeping_t);
		// printf("%ld %d is thinking\n", time_now() - data->time, p->n);
	}
}

int create_philo(t_philo **philo, t_data *data)
{
    int i;

    pthread_t th[data->p_total];
    //pthread_t monitor;
	data->time = time_now();
    for (i = 0; i < data->p_total; i++) 
    {
        if (pthread_create(th + i, NULL, &routine, (void *)philo[i]) != 0) {
            perror("Failed to create thread");
            return 1;
        }
    }
    // if (pthread_create(&monitor, NULL, &monitoring, (void *)philo) != 0) 
    // {
    //     perror("Failed to create thread");
    //     return 1;
    // }
    for (i = 0; i < data->p_total; i++) 
    {
        if (pthread_join(th[i], NULL) != 0) {
            return 3;
        }
        printf("Thread %d has finished execution\n", i);
    }
    // if (pthread_join(monitor, NULL) != 0) 
    // {
    //     return 2;
    // }
    // for (i = 0; i < data->p_total; i++)
    //     pthread_mutex_destroy(&data->mutex_forks[i]);
	// pthread_mutex_destroy(data->mutex_death);
    return (0);
}