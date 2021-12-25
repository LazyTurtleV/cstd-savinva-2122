#define SUCCESS 0
#define OUT_OF_BOUNDS 1
#define CELL_IS_OCCUPIED 2
#define SAVE_REQUEST 0xFF
#define LOAD_REQUEST 0xFA

#define EMPTY_CELL '_'

#define GAME_CONTINUES 0
#define WINNER_FOUND 1
#define DRAW 2

#define MAN_vs_MAN 0

void init_game(char *_load_info);
void end_game();
char receive_mode();

int make_move(unsigned int _i, unsigned int _j);
int game_status();
char** get_board();
void announce_player();
char resolve_winner_player();
char resolve_current_player();
char resolve_opponent_player(char _p);