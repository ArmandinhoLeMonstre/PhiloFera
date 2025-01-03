/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 18:12:10 by armitite          #+#    #+#             */
/*   Updated: 2024/12/27 13:33:08 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int stock_args(t_data *data, int ac, char **av)
{
    data->p_total= ft_atoi(av[1]);
    data->starving_t = ft_atoi(av[2]);
    data->eating_t = ft_atoi(av[3]);
    data->sleeping_t = ft_atoi(av[4]);
    if (ac == 6)
        data->meals_nbr = ft_atoi(av[5]);
    else
		data->meals_nbr = -1;
	data->death = 0;
	data->meals_eaten = 0;
	data->mutex_print = malloc(sizeof(pthread_mutex_t) * 1);
	data->mutex_data = malloc(sizeof(pthread_mutex_t) * 1);
	if (pthread_mutex_init(data->mutex_print, (void *)data) != 0)
        return (1);
	if (pthread_mutex_init(data->mutex_data, (void *)data) != 0)
        return (1);
	return (0);
}

int	allocate_forks(t_data *data)
{
	int	i;

	i = 0;
	data->mutex_forks = malloc(sizeof(pthread_mutex_t) * data->p_total);
	while (i < data->p_total) 
	{
		if (pthread_mutex_init(&data->mutex_forks[i], NULL) != 0) 
		{
			perror("Mutex initialization failed");
			while (i > 0)
			{
				free(&data->mutex_forks[i]);
				i--;
			}
			return (free(data), 1);
		}
		usleep(1000);
		i++;
	}
	return (0);
}

int	init_philo(t_data *data)
{
	int	i;
	t_philo **philo;

	i = 0;
	philo = malloc(sizeof(t_philo) * data->p_total);
	while (i < data->p_total)
	{
		philo[i] = malloc(sizeof(t_philo));
		philo[i]->n = i + 1;
		philo[i]->time = 0;
		philo[i]->dead = 0;
		philo[i]->data = malloc(sizeof(t_data));
		philo[i]->data = data;
		philo[i]->left_fork = &data->mutex_forks[philo[i]->n - 1];
    	philo[i]->right_fork = &data->mutex_forks[philo[i]->n % data->p_total];
		i++;
	}
	create_philo(philo, data);
	return (0);
}

int main(int ac, char **av)
{
	t_data	data;

    if (ac != 5 && ac != 6)
		return (printf("Error args\n"), 2);
	if (ft_check_num(av, ac) == 1)
		return (printf("Error non numeric args\n"), 2);
    if (stock_args(&data, ac, av) == 1)
		return (printf("Mutex initialization failed\n"), 2);
	if (allocate_forks(&data) == 1)
		return (printf("Mutex initialization failed\n"), 2);
	init_philo(&data);
    return (0);
}
