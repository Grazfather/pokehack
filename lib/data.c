#include <stdio.h>

#include <pokehack/data.h>

// Global variables
extern char* pokemon_species[];
extern char* items[];
extern char* natures[];
extern char* attacks[];

/*
 *	Encrypts/decrypts the 48 byte data buffer based on the xored pv and otid values
 */
unsigned short int encrypt(unsigned char *data, unsigned int pv, unsigned int otid) {
	int i;
	unsigned int xorkey = pv ^ otid;
	unsigned short int checksum = 0;

	for (i = 0; i < POKEMON_DATA_LENGTH; i+=4)
	{
		checksum += data[i+1]<<8 | data[i];
		checksum += data[i+3]<<8 | data[i+2];

		data[i] ^= (xorkey >> 0)&0xFF;
		data[i+1] ^= (xorkey >> 8)&0xFF;
		data[i+2] ^= (xorkey >> 16)&0xFF;
		data[i+3] ^= (xorkey >> 24)&0xFF;
	}

	return checksum;
}

int parse_pokemon(char* buf, int offset, void** pokemon, pokemon_attacks_t** pa, pokemon_effort_t** pe, pokemon_growth_t** pg, pokemon_misc_t** pm, int num, int size)
{
	int i;
	if (size != sizeof(belt_pokemon_t) && size != sizeof(box_pokemon_t)) {
		fprintf(stderr, "Pokemon size must be either 80 or 100 bytes\n");
		return -1;
	}

	// Parse pokemon
	for(i = 0; i < num; i++)
	{
		int o;

		// Read data on pokemon
		pokemon[i] = (buf + offset + (i * size));

		// Unencrypt pokemon's data
		// box and belt pokemon have these struct members all at
		// the same offset so we can cast to either type
		encrypt(((box_pokemon_t*)pokemon[i])->data, ((box_pokemon_t*)pokemon[i])->personality, ((box_pokemon_t*)pokemon[i])->otid);

		// Figure out the order
		o = ((box_pokemon_t*)pokemon[i])->personality % 24;
		pa[i] = (pokemon_attacks_t *)(((box_pokemon_t*)pokemon[i])->data + DataOrderTable[o][0] * sizeof(pokemon_attacks_t));
		pe[i] = (pokemon_effort_t *)(((box_pokemon_t*)pokemon[i])->data + DataOrderTable[o][1] * sizeof(pokemon_effort_t));
		pg[i] = (pokemon_growth_t *)(((box_pokemon_t*)pokemon[i])->data + DataOrderTable[o][2] * sizeof(pokemon_growth_t));
		pm[i] = (pokemon_misc_t *)(((box_pokemon_t*)pokemon[i])->data + DataOrderTable[o][3] * sizeof(pokemon_misc_t));
		if (pg[i]->species) {
			fprintf(stdout, "\nPokemon %d\n", i);
			print_pokemon(pokemon[i]);
		}
	}

	return 0;
}

void print_pokemon(box_pokemon_t* pokemon)
{
	pokemon_attacks_t *pa;
	pokemon_effort_t *pe;
	pokemon_growth_t *pg;
	pokemon_misc_t *pm;
	int o, totalIVs, totalEVs;

	// Figure out the order
	o = pokemon->personality % 24;
	pa = (pokemon_attacks_t *)(pokemon->data + DataOrderTable[o][0] * sizeof(pokemon_attacks_t));
	pe = (pokemon_effort_t *)(pokemon->data + DataOrderTable[o][1] * sizeof(pokemon_effort_t));
	pg = (pokemon_growth_t *)(pokemon->data + DataOrderTable[o][2] * sizeof(pokemon_growth_t));
	pm = (pokemon_misc_t *)(pokemon->data + DataOrderTable[o][3] * sizeof(pokemon_misc_t));

	totalIVs = pm->IVs.hp + pm->IVs.atk + pm->IVs.def + pm->IVs.spatk + pm->IVs.spdef + pm->IVs.spd;
	totalEVs = pe->hp + pe->attack + pe->defense + pe->spatk + pe->spdef + pe->speed;
	fprintf(stdout, "Species: %s, held: %s, Nature: %s\n", pokemon_species[pg->species], items[pg->held], natures[pokemon->personality % 25]);
	fprintf(stdout, "Attacks: 1:%s, 2:%s, 3:%s, 4:%s\n", attacks[pa->atk1], attacks[pa->atk2], attacks[pa->atk3], attacks[pa->atk4] );
	fprintf(stdout, "IVs:\tHP:%d\tAtk:%d\tDef:%d\tSpA:%d\tSpD:%d\tSpe:%d\tTotal:%d\n", pm->IVs.hp, pm->IVs.atk, pm->IVs.def, pm->IVs.spatk, pm->IVs.spdef, pm->IVs.spd, totalIVs );
	fprintf(stdout, "EVs:\tHP:%d\tAtk:%d\tDef:%d\tSpA:%d\tSpD:%d\tSpe:%d\tTotal:%d\n", pe->hp, pe->attack, pe->defense, pe->spatk, pe->spdef, pe->speed, totalEVs );
}
