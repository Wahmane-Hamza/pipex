i = 1;
		len1 = 0;
		len2 = 0;
		while (av[1][i])
		{
			if(av[1][i] != ' ' && (av[1][i + 1] == ' ' || av[1][i + 1] == '\0'))
				len1++;
			i++;
		}
		first_arg = malloc((len1 + 1) * sizeof(char *));
		if (!first_arg)
			return 0;

		if (av[2])
		{
			i = 1;
			while (av[2][i])
			{
				if(av[2][i] != ' ' && (av[2][i + 1] == ' ' || av[2][i + 1] == '\0'))
				len2++;
				i++;
			}
		}
		if (len2 > 0)
		{
			second_arg = malloc((len2 + 1) * sizeof(char *));
			if (!second_arg)
				return 0;
		}

		i = 0;
		j = 0;
		while (av[1][i])
		{
			if (av[1][i] == ' ')
				i++;
			first_arg[j] = copy_str(&av[1][i]);
			while (av[1][i] && av[1][i] != ' ')
				i++;
			j++;
		}
		first_arg[j] = NULL;
		if (len2 > 0)
		{
			i = 0;
			j = 0;
			while (av[2][i])
			{
				if (av[2][i] == ' ')
					i++;
				second_arg[j] = copy_str(&av[2][i]);
				while (av[1][i] && av[2][i] != ' ')
					i++;
				j++;
			}
			second_arg[j] = NULL;
		}