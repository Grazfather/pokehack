#include <pokehack/pokestructs.h>

unsigned short int POKEHACK_API encrypt(unsigned char *data, unsigned int pv, unsigned int otid);
int POKEHACK_API parse_pokemon(char* buf, int offset, void** pokemon, pokemon_attacks_t** pa, pokemon_effort_t** pe, pokemon_growth_t** pg, pokemon_misc_t** pm, int num, int size);
void POKEHACK_API print_pokemon(box_pokemon_t* pokemon);
