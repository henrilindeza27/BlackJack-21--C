#include "../inc/bj.h"

HandNode *ft_create_hand_node(char **hand, size_t size_hand)
{
    HandNode *new_node = (HandNode *)malloc(sizeof(HandNode));
    if (!new_node)
    {
        perror("Erro ao alocar memória para o nó da mão");
        return NULL;
    }

    new_node->hand = hand;
    new_node->size_hand = 0;
    new_node->next = NULL;

    return new_node;
}

void	ft_save_card_played(HandNode *hand_node, char *card)
{
    if(!hand_node)
        return;

	hand_node->hand = (char **)realloc(hand_node->hand, (hand_node->size_hand + 1) * sizeof(char *));
	if (!hand_node->hand)
		return ;
	hand_node->hand[hand_node->size_hand] = strdup(card);
	if (!hand_node->hand[hand_node->size_hand])
		return ;
	hand_node->size_hand++;
}

int	ft_calculate_hand_points(HandNode *hand_node, int is_dealer, int is_firstplay)
{
	int		points = 0;
	int		ace_count = 0;
	size_t	start_index = 0;

	if (!hand_node || !hand_node->hand)
		return 0;

	if (is_dealer && is_firstplay)
		start_index = 1;

	for (size_t i = start_index; i < hand_node->size_hand; i++)
	{
		char *card = hand_node->hand[i];

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

void ft_print_played_cards(int first_play, HandNode *player_hand, HandNode *dealer_hand, char *nickname)
{
    printf("Dealer (%d)\n", ft_calculate_hand_points(dealer_hand, 1, first_play));
    
    for (size_t i = 0; i < dealer_hand->size_hand; i++) 
    {   
        if (first_play > 0)
        {   
            printf("%s ", "🂠"); 
            first_play--;
        }
        else
            printf("%s ", ft_convert_to_emoji(dealer_hand->hand[i])); 
    }
    printf("\n\n");

    printf("%s (%d)\n", nickname, ft_calculate_hand_points(player_hand, 0, 0));

    for (size_t i = 0; i < player_hand->size_hand; i++) 
        printf("%s ", ft_convert_to_emoji(player_hand->hand[i]));

    printf("\n");   
}

void ft_free_hand(HandNode *hand_list)
{
    while (hand_list)
    {
        HandNode *next = hand_list->next;

        for (size_t i = 0; i < hand_list->size_hand; i++)
        {
            free(hand_list->hand[i]);
        }
        free(hand_list->hand);
        free(hand_list);

        hand_list = next;
    }
}