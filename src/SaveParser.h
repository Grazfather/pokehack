#include "../include/pokestructs.h"

class SaveParser
{
public:
	static SaveParser* Instance();
	unsigned short int encrypt(unsigned char *data, unsigned int pv, unsigned int otid);
	int load(const char *fn);
	int save(const char *fn);
	pokemon_t *pokemon[NUM_POKEMON];
	pokemon_attacks_t *pokemon_attacks[NUM_POKEMON];
	pokemon_effort_t *pokemon_effort[NUM_POKEMON];
	pokemon_growth_t *pokemon_growth[NUM_POKEMON];
	pokemon_misc_t *pokemon_misc[NUM_POKEMON];
	
private:
	SaveParser(){};	// Private constructor because this is a singleton
	char ram[STATE_SIZE];
	static SaveParser* spInstance;
};
