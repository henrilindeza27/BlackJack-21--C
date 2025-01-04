#include "../inc/bj.h"

char	*dup_string(const char *str)
{
	char *new_str = (char *)malloc(strlen(str) + 1); 
	if (new_str != NULL)
		strcpy(new_str, str);
	return (new_str);
}

char	***ft_creat_single_deck(void)
{
	char	***deck;
	char	*values[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J","Q", "K"};
	char	*naipes[] = {"♥", "♠", "♦", "♣"};
	char card[10];

	deck = (char ***)malloc(sizeof(char **) * 4);

	for (int i = 0; i < 4; i++)
	{
		deck[i] = (char **)malloc(sizeof(char *) * 13);
		for (int j = 0; j < 13; j++)
		{
			snprintf(card, sizeof(card), "%s%s", values[j], naipes[i]);
			deck[i][j] = dup_string(card);
		}
	}
	return (deck);
}

void	ft_free_deck(char ***deck, int number_decks)
{
	for (int i = 0; i < 4 * number_decks; i++)
	{
		for (int j = 0; j < 13; j++)
			free(deck[i][j]);
		free(deck[i]);
	}
	free(deck);
}

char	***ft_creat_full_deck(int number_decks)
{
	char	***full_deck;
	char	***tmp_deck;

	full_deck = (char ***)malloc(sizeof(char **) * (4 * number_decks));
	if (full_deck == NULL)
	{
		printf("Erro ao alocar memória para o full_deck.\n");
		exit(1);
	}
	for (int i = 0; i < (4 * number_decks); i++)
	{
		full_deck[i] = (char **)malloc(sizeof(char *) * 13);
		if (full_deck[i] == NULL)
		{
			printf("Erro ao alocar memória para o deck %d.\n", i);
			exit(1);
		}
	}
	tmp_deck = ft_creat_single_deck();
	for (int k = 0; k < number_decks; k++)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 13; j++)
				full_deck[k * 4 + i][j] = dup_string(tmp_deck[i][j]);
		}
	}
	ft_free_deck(tmp_deck, 1);
	return (full_deck);
}

void	ft_shuffle_deck(char ***full_deck, int number_decks)
{
	int		total_cards;
	int		j;
	int		i_deck;
	int		i_card;
	int		j_deck;
	int		j_card;
	char	*temp;

	srand(time(NULL));
	total_cards = 4 * 13 * number_decks;
	for (int i = total_cards - 1; i > 0; i--)
	{
		j = rand() % (i + 1);
		i_deck = i / 13;
		i_card = i % 13;
		j_deck = j / 13;
		j_card = j % 13;
		temp = full_deck[i_deck][i_card];
		full_deck[i_deck][i_card] = full_deck[j_deck][j_card];
		full_deck[j_deck][j_card] = temp;
	}
}

void	ft_print_decks(char ***decks, int number_decks)
{
	for (int i = 0; i < 4 * number_decks; i++)
	{
		for (int j = 0; j < 13; j++)
			printf("%2s ", ft_convert_to_emoji(decks[i][j]));
		printf("\n");
	}
}

void	ft_play_card(char ***full_deck, int number_decks, int *cards_played)
{
	int			total_cards;
	static int	delimiter = 0;
	char		*played_card;

	total_cards = 4 * 13 * number_decks;

	int min_delimiter = total_cards * 70 / 100; // 70% do total
	int max_delimiter = total_cards * 75 / 100; // 75% do total

	if (delimiter == 0)
	{
		srand(time(NULL));
		delimiter = min_delimiter + rand() % (max_delimiter - min_delimiter + 1);
	}

	if (*cards_played >= delimiter)
	{
		printf("\nBaralho embaralhado após %d cartas jogadas e atingir o delimiter.\n", *cards_played);
		ft_shuffle_deck(full_deck, number_decks);

		*cards_played = 0;
		delimiter = min_delimiter + rand() % (max_delimiter - min_delimiter + 1);
		ft_clean_input();
		ft_wait_enter();
	}

	played_card = full_deck[0][0];

	for (int i = 0; i < total_cards - 1; i++)
	{
		int current_deck = i / 13;    // Linha atual
		int current_card = i % 13;    // Coluna atual
		int next_deck = (i + 1) / 13; // Próxima linha
		int next_card = (i + 1) % 13; // Próxima coluna
		
		full_deck[current_deck][current_card] = full_deck[next_deck][next_card];
	}

	full_deck[(total_cards - 1) / 13][(total_cards - 1) % 13] = played_card;

	(*cards_played)++;
}


const char	*ft_convert_to_emoji(const char *card)
{
	if (strcmp(card, "A♠") == 0)
		return ("🂡");
	if (strcmp(card, "2♠") == 0)
		return ("🂢");
	if (strcmp(card, "3♠") == 0)
		return ("🂣");
	if (strcmp(card, "4♠") == 0)
		return ("🂤");
	if (strcmp(card, "5♠") == 0)
		return ("🂥");
	if (strcmp(card, "6♠") == 0)
		return ("🂦");
	if (strcmp(card, "7♠") == 0)
		return ("🂧");
	if (strcmp(card, "8♠") == 0)
		return ("🂨");
	if (strcmp(card, "9♠") == 0)
		return ("🂩");
	if (strcmp(card, "10♠") == 0)
		return ("🂪");
	if (strcmp(card, "J♠") == 0)
		return ("🂫");
	if (strcmp(card, "Q♠") == 0)
		return ("🂭");
	if (strcmp(card, "K♠") == 0)
		return ("🂮");
	if (strcmp(card, "A♥") == 0)
		return "🂱";
	if (strcmp(card, "2♥") == 0)
		return "🂲";
	if (strcmp(card, "3♥") == 0)
		return "🂳";
	if (strcmp(card, "4♥") == 0)
		return "🂴";
	if (strcmp(card, "5♥") == 0)
		return "🂵";
	if (strcmp(card, "6♥") == 0)
		return "🂶";
	if (strcmp(card, "7♥") == 0)
		return "🂷";
	if (strcmp(card, "8♥") == 0)
		return "🂸";
	if (strcmp(card, "9♥") == 0)
		return "🂹";
	if (strcmp(card, "10♥") == 0)
		return "🂺";
	if (strcmp(card, "J♥") == 0)
		return "🂻";
	if (strcmp(card, "Q♥") == 0)
		return "🂽";
	if (strcmp(card, "K♥") == 0)
		return "🂾";
	if (strcmp(card, "A♦") == 0)
		return "🃁";
	if (strcmp(card, "2♦") == 0)
		return "🃂";
	if (strcmp(card, "3♦") == 0)
		return "🃃";
	if (strcmp(card, "4♦") == 0)
		return "🃄";
	if (strcmp(card, "5♦") == 0)
		return "🃅";
	if (strcmp(card, "6♦") == 0)
		return "🃆";
	if (strcmp(card, "7♦") == 0)
		return "🃇";
	if (strcmp(card, "8♦") == 0)
		return "🃈";
	if (strcmp(card, "9♦") == 0)
		return "🃉";
	if (strcmp(card, "10♦") == 0)
		return "🃊";
	if (strcmp(card, "J♦") == 0)
		return "🃋";
	if (strcmp(card, "Q♦") == 0)
		return "🃍";
	if (strcmp(card, "K♦") == 0)
		return "🃎";
	if (strcmp(card, "A♣") == 0)
		return "🃑";
	if (strcmp(card, "2♣") == 0)
		return "🃒";
	if (strcmp(card, "3♣") == 0)
		return "🃓";
	if (strcmp(card, "4♣") == 0)
		return "🃔";
	if (strcmp(card, "5♣") == 0)
		return "🃕";
	if (strcmp(card, "6♣") == 0)
		return "🃖";
	if (strcmp(card, "7♣") == 0)
		return "🃗";
	if (strcmp(card, "8♣") == 0)
		return "🃘";
	if (strcmp(card, "9♣") == 0)
		return "🃙";
	if (strcmp(card, "10♣") == 0)
		return "🃚";
	if (strcmp(card, "J♣") == 0)
		return "🃛";
	if (strcmp(card, "Q♣") == 0)
		return "🃝";
	if (strcmp(card, "K♣") == 0)
		return "🃞";
	return "??"; 
}


void	ft_save_card_played(char ***hand, size_t *hand_size, char *card)
{
	*hand = (char **)realloc(*hand, (*hand_size + 1) * sizeof(char *));
	if (!*hand)
		return ;
	(*hand)[*hand_size] = strdup(card);
	if (!(*hand)[*hand_size])
		return ;
	(*hand_size)++;
}

int	ft_calculate_hand_points(char **hand, size_t hand_size, int is_dealer, int is_firstplay)
{
	int		points;
	int		ace_count;
	size_t start_index = 0;

	points = 0;
	ace_count = 0;
    if(is_dealer && is_firstplay)
        start_index = 1;

	for (size_t i = start_index; i < hand_size; i++)
	{
		char *card = hand[i];
		
		if (card[0] >= '2' && card[0] <= '9')
			points += card[0] - '0';
		else if (card[0] == '1' && card[1] == '0')
			points += 10;
		else if (card[0] == 'J' || card[0] == 'Q' || card[0] == 'K')
			points += 10;
		else if (card[0] == 'A')
		{
			ace_count++;
			points += 11; 
		}
	}
	
	while (points > 21 && ace_count > 0)
	{
		points -= 10; 
		ace_count--;
	}

	return points;
}
