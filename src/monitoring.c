/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 11:36:27 by armitite          #+#    #+#             */
/*   Updated: 2024/12/27 13:39:25 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int philo_dead(t_philo *p, t_data *data)
{
	//long long last_meal;
	
	//pthread_mutex_lock(data->mutex_print);
	//pthread_mutex_lock(data->mutex_data);
	//last_meal = p->t_last_meal;
	//pthread_mutex_unlock(data->mutex_data);
    pthread_mutex_lock(data->mutex_print);
	if ((time_now() - p->t_last_meal) > data->starving_t)
	{
		p->dead = 1;
		pthread_mutex_unlock(data->mutex_print);
		return (1);
	}
    pthread_mutex_unlock(data->mutex_print);
    return (0);
}

// int check_death(t_philo *p, t_data *data)
// {
//     pthread_mutex_lock(data->mutex_print);
//     if (p->dead == 1)
//     {
//         data->death = 1;
//         printf("%lld %d is dead\n", (time_now() - p->time), p->n);
//         pthread_mutex_unlock(data->mutex_print);
//         return (1);
// 	}
//     pthread_mutex_unlock(data->mutex_print);
//     return (0);
// }

int check_meals(t_data *data)
{
    pthread_mutex_lock(data->mutex_data);
    if (data->meals_eaten == (data->meals_nbr * data->p_total))
    {
        data->death = 1;
		data->meals_check = 1;
        printf("%d meals have been eaten\n", data->meals_eaten);
        pthread_mutex_unlock(data->mutex_data);
        return (1);
    }
    pthread_mutex_unlock(data->mutex_data);
    return (0);
}

void	*monitoring(void *arg)
{
	t_philo **p = (t_philo **) arg;
    t_data  *data;
    int i;
	//long long last_meal;

    data = malloc(sizeof(t_data) * 1);
    data = p[0]->data;
    ft_usleep(150);
    while (1)
    {
        i = 0;
        while (i < data->p_total)
        {
            pthread_mutex_lock(data->mutex_print);
            if (p[i]->dead == 1)
			{
				data->death = 1;
				printf("%lld %d is dead\n", (time_now() - p[i]->time), p[i]->n);
				pthread_mutex_unlock(data->mutex_print);
				return (NULL);
			}
			if (data->meals_check == 1)
            {
            	pthread_mutex_unlock(data->mutex_print);
				return (NULL);
            }
			pthread_mutex_unlock(data->mutex_print);
            i++;
        }
    }
}