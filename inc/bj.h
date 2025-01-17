#ifndef BJ_H
# define BJ_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>
# include <unistd.h>
#include <ctype.h>
#include <math.h>

#define file_name "users/players.txt"
//🂠

typedef struct HandNode
{
	char **hand;
	size_t size_hand;

	struct HandNode *next;
}			HandNode;

typedef struct player
{
	char	*nickname;
	double	balance;
	
	size_t total_games;
	size_t total_wins;
	size_t total_bets;
	size_t total_draw;

	double max_win;
	double max_lose;
	double total_win;
	double total_bet;

}			PLAYER;


char		***ft_creat_single_deck(void);
char		***ft_creat_full_deck(int number_decks);
void		ft_free_deck(char ***deck, int number_decks);
void		ft_print_decks(char ***decks, int number_decks);
void		ft_shuffle_deck(char ***full_deck, int number_decks);
void		ft_play_card(char ***full_deck, int number_decks, int *cards_played);
const char	*ft_convert_to_emoji(const char *card);
void ft_clear_player(PLAYER *player) ;

int ft_main_play(char ***deck, int *cards_played, int number_decks, PLAYER *player, double bet, int *split_flag, int *double_flag, double *side_bets, double **side_bet_win, double *total_bet);

PLAYER ft_create_player(int is_guest);
int ft_save_player(PLAYER *player);
void ft_play(char ***deck, int number_decks);

void ft_wait_enter(void);
void	ft_clean_input(void);

void ft_initial_banner(void);
int ft_player_menu(void);
void ft_load_bar(size_t size);
double ft_check_bust_win(double bet, HandNode *dealer);

int ft_player_menu_logic(PLAYER *player);
int ft_check_nickname(char *nickname);
int ft_load_player(char *nickname, PLAYER *player);
double ft_check_bet(int result, double bet, int split_flag, int double_flag);
void ft_update_stats(PLAYER *player, double total_win,double total_bet, int result);
int ft_double_length(double num);
int ft_main_menu(PLAYER player, int is_guest);
void ft_show_stats(PLAYER player);
void ft_add_balance(PLAYER *player);
void ft_print_char(int size, char ch);
int ft_ask_to_continue(void);
int ft_check_bj_player(HandNode *player_hand, HandNode *dealer_hand);
char ft_get_naipe(char *card);
double *ft_make_side_bet(PLAYER *player);
double *ft_check_side_bets_win(double *bets, PLAYER *player, HandNode *player_hand, HandNode *dealer_hand);
void ft_in_game_hud(PLAYER player,double *total_bet , double *side_bets, double *side_wins, double bet, int double_flag, double first_play);


HandNode 	*ft_create_hand_node(char **hand, size_t size_hand);
void	 	ft_save_card_played(HandNode *hand_node, char *card);
int			ft_calculate_hand_points(HandNode *hand_node, int is_dealer, int is_firstplay);
void 		ft_player_single_play(char ***deck, HandNode *player_hand, int *cards_played, int number_decks);
void 		ft_dealer_single_play(char ***deck, HandNode *dealer_hand, int *cards_played, int number_decks);
void 		ft_initial_play(char ***deck, int *cards_played, int number_decks, HandNode *player_hand, HandNode *dealer_hand);
void ft_print_played_cards(int first_play, HandNode *player_hand, HandNode *dealer_hand, PLAYER player, double *side_bets, double *side_wins, double bet, int double_flag, double *total_bet);
void 		ft_free_hand(HandNode *hand_list);
int 		ft_card_value(char *card);
int ft_total_hands(HandNode *hand_list);
int ft_check_result(HandNode *player_hand, HandNode *dealer_hand, int flag);
int ft_check_split(HandNode *player_hand);
int ft_ask_play(int flag, int can_split, int hand);
int ft_split(char ***deck, HandNode **player_hand, HandNode *dealer_hand, int *cards_played, int number_decks, PLAYER player, double *side_bets, double *side_wins, double bet, double *total_bet);

int ft_bust_it(HandNode *dealer_hand);
int ft_hot_3(HandNode *player_hand, HandNode *dealer_hand);
int ft_check_same_naipe(char **player_hand, char *dealer_card);
int ft_check_same_value(char **player_hand, char *dealer_card);
int ft_check_exist_side_bets(double *sidebets);

#endif