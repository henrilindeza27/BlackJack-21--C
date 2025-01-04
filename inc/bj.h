#ifndef BJ_H
# define BJ_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>
# include <unistd.h>

//🂠

typedef struct player
{
	char	*nickname;
	double	balance;
}			PLAYER;

char		***ft_creat_single_deck(void);
char		***ft_creat_full_deck(int number_decks);
void		ft_free_deck(char ***deck, int number_decks);
void		ft_print_decks(char ***decks, int number_decks);
void		ft_shuffle_deck(char ***full_deck, int number_decks);
void		ft_play_card(char ***full_deck, int number_decks, int *cards_played);
void		ft_initial_play(char ***deck, int *cards_played, int number_decks, char ***player_hand, char ***dealer_hand, size_t *p_hand_size, size_t *d_hand_size);
const char	*ft_convert_to_emoji(const char *card);
void		ft_save_card_played(char ***hand, size_t *hand_size, char *card);
void		ft_print_played_cards(int player_play, char **p_hand, char **d_hand, size_t player_hand_size, size_t dealer_hand_size, char *nickname);
int 		ft_main_play(char ***deck, int *cards_played, int number_decks, PLAYER player, double bet);
int			ft_calculate_hand_points(char **hand, size_t hand_size, int is_dealer, int is_firstplay);
void		ft_player_single_play(char ***deck, char ***player_hand, size_t *player_hand_size, int *cards_played, int number_decks);
void		ft_dealer_single_play(char ***deck, char ***dealer_hand, size_t *dealer_hand_size, int *cards_played, int number_decks);
void		ft_free_hand(char **hand, int hand_size);

PLAYER ft_create_player();
int ft_show_status(PLAYER player);
void ft_play(char ***deck, int number_decks);

void ft_wait_enter(void);
void	ft_clean_input(void);

void ft_initial_banner(void);

#endif