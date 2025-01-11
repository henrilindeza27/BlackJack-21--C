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
    new_node->size_hand = size_hand;
    new_node->next = NULL;

    return new_node;
}

void ft_add_hand_node(HandNode **hand_list, HandNode *new_node)
{
    if (!new_node)
        return;

    if (!*hand_list)
        *hand_list = new_node; 
    
    else
    {
        HandNode *current = *hand_list;
        while (current->next)
            current = current->next; 
        current->next = new_node; 
    }
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

int ft_total_hands(HandNode *hand_list)
{
    int total = 0;
    while (hand_list)
    {
        total++;
        hand_list = hand_list->next;
    }
    return total;
    
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

int ft_card_value(char *card)
{
    int points = 0;

    if (card[0] >= '2' && card[0] <= '9')
        points += card[0] - '0';
    else if (card[0] == '1' && card[1] == '0') 
        points += 10;
    else if (card[0] == 'J' || card[0] == 'Q' || card[0] == 'K')
        points += 10;
    else if (card[0] == 'A')
        points += 11;

    return points;
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
        int value = ft_card_value(card);
        if(value == 11)
            ace_count++;
		points += value;
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

    if(ft_total_hands(player_hand) != 2)
    {
        printf("%s (%d)\n", nickname, ft_calculate_hand_points(player_hand, 0, 0));

        for (size_t i = 0; i < player_hand->size_hand; i++) 
            printf("%s ", ft_convert_to_emoji(player_hand->hand[i]));
    }
    else
    {
        printf("%s \n", nickname);

        for (size_t i = 0; i < player_hand->size_hand; i++) 
            printf("%s ", ft_convert_to_emoji(player_hand->hand[i]));
        printf(" (%d)     ", ft_calculate_hand_points(player_hand, 0, 0));

        player_hand = player_hand->next;
        for (size_t i = 0; i < player_hand->size_hand; i++) 
            printf("%s ", ft_convert_to_emoji(player_hand->hand[i]));
        printf(" (%d)\n", ft_calculate_hand_points(player_hand, 0, 0));
    }

    printf("\n");   
}

int ft_split(char ***deck, HandNode **player_hand, HandNode *dealer_hand, int *cards_played, int number_decks, char *nickname)
{

    char **temp = (*player_hand)->hand; 
    
    char **hand1 = (char **)malloc(sizeof(char *));
    char **hand2 = (char **)malloc(sizeof(char *));
    if (!hand1 || !hand2)
    {
        perror("Erro ao alocar memória para as novas mãos");
        free(hand1);
        free(hand2);
        return 1;
    }
    hand1[0] = strdup(temp[0]);
    hand2[0] = strdup(temp[1]);

    HandNode *new_hand1 = ft_create_hand_node(hand1, 1);
    HandNode *new_hand2 = ft_create_hand_node(hand2, 1);
    if (!new_hand1 || !new_hand2)
    {
        perror("Erro ao criar os nós das novas mãos");
        ft_free_hand(new_hand1);
        ft_free_hand(new_hand2);
        return 1;
    }

    ft_free_hand(*player_hand);

    *player_hand = NULL; // Começar uma nova lista
    ft_add_hand_node(player_hand, new_hand1);
    ft_add_hand_node(player_hand, new_hand2);

    // Adicionar uma nova carta a cada mão
    ft_player_single_play(deck, new_hand1, cards_played, number_decks);
    ft_player_single_play(deck, new_hand2, cards_played, number_decks);

    system("clear");
    ft_print_played_cards(1, *player_hand, dealer_hand, nickname);

    int option;
    int flag_hand = 1;
    int bust = 0;
    int total_bust = 0;
    while (flag_hand < 3)
    {
        do
        {
            option = ft_ask_play(0, 0, flag_hand);
            
            if(option == 1 && flag_hand == 1)
            {
                system("clear");
                ft_player_single_play(deck, new_hand1, cards_played, number_decks);
                ft_print_played_cards(1, *player_hand, dealer_hand, nickname);
                
                if(ft_calculate_hand_points(new_hand1, 0, 0) > 21)
                {
                    bust++;  
                    total_bust++;
                    break;   
                }
            }
            else if(option == 1 && flag_hand == 2)
            {
                bust = 0;
                system("clear");
                ft_player_single_play(deck, new_hand2, cards_played, number_decks);
                ft_print_played_cards(1, *player_hand, dealer_hand, nickname);
                
               
                if(ft_calculate_hand_points(new_hand2, 0, 0) > 21)
                {
                    bust++;  
                    total_bust++;
                    break;   
                }
            }

        } while (option != 2 && bust == 0);  

        flag_hand++; 
        system("clear");
        ft_print_played_cards(1, *player_hand, dealer_hand, nickname);
    }
    
    return total_bust;
}
