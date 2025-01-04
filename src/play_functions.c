#include "../inc/bj.h"


void ft_player_single_play(char ***deck, char ***player_hand, size_t *player_hand_size, int *cards_played, int number_decks)
{
    ft_save_card_played(player_hand, player_hand_size, deck[0][0]);
    ft_play_card(deck, number_decks, cards_played);
}

void ft_dealer_single_play(char ***deck, char ***dealer_hand, size_t *dealer_hand_size, int *cards_played, int number_decks)
{
    ft_save_card_played(dealer_hand, dealer_hand_size, deck[0][0]);
    ft_play_card(deck, number_decks, cards_played);
}

void ft_initial_play(char ***deck, int *cards_played, int number_decks, char ***player_hand, char ***dealer_hand, size_t *p_hand_size, size_t *d_hand_size)
{
    
    ft_player_single_play(deck, player_hand, p_hand_size, cards_played, number_decks);
    ft_dealer_single_play(deck, dealer_hand, d_hand_size, cards_played, number_decks);
    ft_player_single_play(deck, player_hand, p_hand_size, cards_played, number_decks);
    ft_dealer_single_play(deck, dealer_hand, d_hand_size, cards_played, number_decks);
}

int ft_ask_play()
{
    int option;

    printf("1- Hit | 2- Double | 3 - Stop \n");
    while(scanf("%d", &option) <= 0 || (option < 1 || option > 3))
        ft_clean_input();

    return option;
}

int ft_player_play(char ***deck, char ***player_hand, size_t *player_hand_size, char **dealer_hand, size_t dealer_hand_size ,int *cards_played, int number_decks, char *nickname, int *flag)
{
    int option;
    do
    {
        option = ft_ask_play();
        if(option == 1)
        {    
            system("clear");
            ft_player_single_play(deck, player_hand, player_hand_size, cards_played, number_decks);
            ft_print_played_cards(1, *player_hand, dealer_hand, *player_hand_size, dealer_hand_size, nickname);
            if(ft_calculate_hand_points(*player_hand, *player_hand_size, 0 , 0) > 21)
                return 1;
                
        }
        else if(option == 2)
        {
            *flag = 2;
            system("clear");
            ft_player_single_play(deck, player_hand, player_hand_size, cards_played, number_decks);
            ft_print_played_cards(1, *player_hand, dealer_hand, *player_hand_size, dealer_hand_size, nickname);
            if(ft_calculate_hand_points(*player_hand, *player_hand_size, 0 , 0) > 21)
                return 1;
            break;
        }
    } while(option != 3);
    return 0;
}

int ft_dealer_play(char ***deck, char ***dealer_hand, size_t *dealer_hand_size,char **player_hand, size_t player_hand_size ,int *cards_played, int number_decks, char *nickname)
{

    usleep(50000);
    system("clear"); 
    ft_print_played_cards(0, player_hand, *dealer_hand, player_hand_size, *dealer_hand_size, nickname);

    while (ft_calculate_hand_points(*dealer_hand, *dealer_hand_size, 1, 0) < 17)
    {
        usleep(700000); 
        system("clear");
        ft_dealer_single_play(deck, dealer_hand, dealer_hand_size, cards_played, number_decks);
        ft_print_played_cards(0, player_hand, *dealer_hand, player_hand_size, *dealer_hand_size, nickname);
        if(ft_calculate_hand_points(*dealer_hand, *dealer_hand_size, 1, 0) > 21)
            return 1;
    }
    return 0;    
}
int ft_main_play(char ***deck, int *cards_played, int number_decks, char *nickname)
{
    char **player_hand = (char **)malloc(0 * sizeof(char *));
    char **dealer_hand = (char **)malloc(0 * sizeof(char *));

    size_t player_hand_size = 0;
    size_t dealer_hand_size = 0;
    int option;
    int flag = 1;

    ft_shuffle_deck(deck, number_decks);
    ft_initial_play(deck, cards_played, number_decks, &player_hand, &dealer_hand, &player_hand_size, &dealer_hand_size);
    ft_print_played_cards(1, player_hand, dealer_hand, player_hand_size, dealer_hand_size, nickname);
    if(ft_calculate_hand_points(player_hand, player_hand_size, 0 , 0) == 21)
    {
        printf("\n[ BLACKJACK ]");
        ft_clean_input();
        ft_wait_enter(); 
        return 1 * 3;
    }

    if(ft_player_play(deck, &player_hand, &player_hand_size, dealer_hand, dealer_hand_size, cards_played, number_decks, nickname, &flag))
    {    
        printf("\n[ PERDEU ]");
        ft_clean_input();
        ft_wait_enter();
        return -1 * flag;
    }
    else
    {        
        if(ft_dealer_play(deck, &dealer_hand, &dealer_hand_size, player_hand, player_hand_size, cards_played, number_decks, nickname))
        {   
            printf("\n[ GANHOU ]");
            ft_clean_input();
            ft_wait_enter(); 
            return 1 * flag;
        }
        else
        {
            int player_points = ft_calculate_hand_points(player_hand, player_hand_size, 0 , 0);
            int dealer_points = ft_calculate_hand_points(dealer_hand, dealer_hand_size, 1, 0);
            if(player_points > dealer_points)
            {   
                printf("\n[ GANHOU ]");
                ft_clean_input();
                ft_wait_enter();
                return 1 * flag;
            }
            else if(player_points < dealer_points)
            {
                printf("\n[ PERDEU ]");
                ft_clean_input();
                ft_wait_enter();
                return -1 * flag;
            }
            else
            {   
                printf("\n[ EMPATE ]");
                ft_clean_input();
                ft_wait_enter();
                return 0;
            }
        }
    }
    ft_free_hand(player_hand, player_hand_size);
    ft_free_hand(dealer_hand, dealer_hand_size);
}

void ft_print_played_cards(int player_play, char **p_hand, char **d_hand, size_t player_hand_size, size_t dealer_hand_size, char *nickname)
{
    printf("Dealer (%d)\n", ft_calculate_hand_points(d_hand, dealer_hand_size, 1, player_play));
    for (size_t i = 0; i < dealer_hand_size; i++) 
    {   
        if(player_play)
        {   
            printf("%s ", "🂠");
            player_play--;
        }
        else
            printf("%s ", ft_convert_to_emoji(d_hand[i]));
    }
    printf("\n\n");

    printf("%s (%d)\n", nickname, ft_calculate_hand_points(p_hand, player_hand_size, 0, 0));
    for (size_t i = 0; i < player_hand_size; i++) 
        printf("%s ", ft_convert_to_emoji(p_hand[i]));
    printf("\n");   
    
}

void ft_free_hand(char **hand, int hand_size) 
{
    for (int i = 0; i < hand_size; i++) 
        free(hand[i]);
    free(hand);
}

double ft_make_bet(double balance)
{
    double tmp;

    printf(" 💰 %.2lf €\n", balance);
    printf(" ⛃ Bet: ");
    while (scanf("%lf", &tmp) <= 0 || tmp <= 0 || tmp > balance)
    {
        printf("[ Valor de aposta inválido ]\n");
        printf(" ⛃ Bet: ");
        ft_clean_input();
    }
    system("clear");
    return tmp;
}

void ft_update_balance(int result, PLAYER *player, double bet)
{
    if(result == 1)
        player->balance += bet;
    else if(result == 2)
        player->balance += 2 * bet;
    else if(result == -1)
        player->balance -= bet;
    else if(result == -2)
        player->balance -= 2 * bet;
    else if(result == 3)
        player->balance += bet * 1.5;
}

void ft_play(char ***deck, int number_decks)
{
    int cards_played = 0;
    PLAYER jogador = ft_create_player();
    double aposta;
    int option =  ft_show_status(jogador);

    while (option != 2)
    {
        system("clear");

        aposta = ft_make_bet(jogador.balance);

        int res = ft_main_play(deck, &cards_played, number_decks, jogador.nickname);

        ft_update_balance(res, &jogador, aposta);

        option = ft_show_status(jogador);
    }
    
}