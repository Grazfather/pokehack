#include <pokehack/pokestructs.h>

class POKEHACK_API SaveParser
{
public:
	static SaveParser* Instance();
	int get_newest_save(block *[NUM_BLOCKS_TOTAL]);
	char* parse_save(const char*, char*, block*[NUM_BLOCKS_TOTAL]);
	unsigned short int get_block_checksum(block* b);
	int pack_save(const char *, char *, block *[NUM_BLOCKS_TOTAL], char[SAVEFILE_LEN]);
	void print_pokemon(box_pokemon_t*);
	int parse_pokemon(char*, int, void**, pokemon_attacks_t**, pokemon_effort_t**, pokemon_growth_t**, pokemon_misc_t**, int, int);
	unsigned short int encrypt(unsigned char*, unsigned int, unsigned int);
	int load(const char *, int);
	int save(const char *);
	belt_pokemon_t *pokemon[NUM_BELT_POKEMON];
	pokemon_attacks_t *pokemon_attacks[NUM_BELT_POKEMON];
	pokemon_effort_t *pokemon_effort[NUM_BELT_POKEMON];
	pokemon_growth_t *pokemon_growth[NUM_BELT_POKEMON];
	pokemon_misc_t *pokemon_misc[NUM_BELT_POKEMON];

private:
	SaveParser(){};	// Private constructor because this is a singleton
	char savefile[SAVEFILE_LEN];
	char *unpackeddata;
	block *blocks[NUM_BLOCKS_TOTAL];
	static SaveParser* spInstance;
};
