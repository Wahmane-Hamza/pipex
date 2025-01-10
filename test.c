/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 12:09:27 by hwahmane          #+#    #+#             */
/*   Updated: 2025/01/03 16:17:05 by hwahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

int main()
{
    int id = fork();
    int i;
    int j;

    if (id == 0)
        i = 1;
    else
        i = 5;

    wait(NULL);
    
    j = i;
    while (i < j + 5)
    {
        printf(" %d",i);
        fflush(stdout);
        i++;
    }
    printf("\n");
    

}
