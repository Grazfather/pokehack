/*
 * Pokemon Gen 3 Save-state editor
 * Copyright (C) 2010-2013 Grazfather
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pokestructs.h>

// Global variables
pokemon_t *pokemon[NUM_POKEMON];
pokemon_attacks_t *pokemon_attacks[NUM_POKEMON];
pokemon_effort_t *pokemon_effort[NUM_POKEMON];
pokemon_growth_t *pokemon_growth[NUM_POKEMON];
pokemon_misc_t *pokemon_misc[NUM_POKEMON];

int offsets[] = { BELT_OFFSET_RSE, BELT_OFFSET_FRLG };

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

int main(int argc, char * argv[])
{
	char savefile[SAVEFILE_LEN];
	char *unpackeddata;
	block *blocks[NUM_BLOCKS_TOTAL];
	int i, game;

	// Check for the .sav file argument
	if (argc < 3) {
		fprintf(stderr, "syntax: pokeedit pokemonsavestate <game>\n");
		fprintf(stderr, "0 for Emerald/Ruby/Sapphire. 1 for FireRed/LeafGreen\n");
		fprintf(stderr, "example: pokeedit PokemonFireRed.sav 1\n");

		return -1;
	}

	game = atoi(argv[2]);
	if (( game < 0) || ( game > 1)) {
		fprintf(stderr, "Game can only be 1 or 0\n");
	}

	unpackeddata = parse_save(argv[1], savefile, blocks);
	if (unpackeddata == NULL)
	{
		fprintf(stderr, "Could not parse save file.\n");
		return -1;
	}

	for(i = 0; i < NUM_POKEMON; i++)
	{
		int o;

		// Read data on pokemon
		pokemon[i] = (pokemon_t *)(unpackeddata + offsets[game] + (i * sizeof(pokemon_t)));

		// Unencrypt pokemon's data
		encrypt(pokemon[i]->data, pokemon[i]->personality, pokemon[i]->otid);

		// Figure out the order
		o = pokemon[i]->personality % 24;
		pokemon_attacks[i] = (pokemon_attacks_t *)(pokemon[i]->data + DataOrderTable[o][0] * sizeof(pokemon_growth_t));
		pokemon_effort[i] = (pokemon_effort_t *)(pokemon[i]->data + DataOrderTable[o][1] * sizeof(pokemon_growth_t));
		pokemon_growth[i] = (pokemon_growth_t *)(pokemon[i]->data + DataOrderTable[o][2] * sizeof(pokemon_growth_t));
		pokemon_misc[i] = (pokemon_misc_t *)(pokemon[i]->data + DataOrderTable[o][3] * sizeof(pokemon_growth_t));
		fprintf(stderr, "\nPokemon %d: hp %d/%d\n", i, pokemon[i]->currentHP, pokemon[i]->maxHP);
		fprintf(stderr, "Species %d, held: %d, experience: %d, ppb: %d, friendship: %d\n", pokemon_growth[i]->species, pokemon_growth[i]->held, pokemon_growth[i]->xp, pokemon_growth[i]->ppbonuses, pokemon_growth[i]->happiness);
		fprintf(stderr, "Attacks: 1:%d, 2:%d, 3:%d, 4:%d, pp1:%d, pp2:%d, pp3:%d, pp4:%d\n", pokemon_attacks[i]->atk1, pokemon_attacks[i]->atk2, pokemon_attacks[i]->atk3, pokemon_attacks[i]->atk4, pokemon_attacks[i]->pp1, pokemon_attacks[i]->pp2, pokemon_attacks[i]->pp3, pokemon_attacks[i]->pp4 );
		fprintf(stderr, "IVs: hp:%d, atk:%d, def:%d, spatk:%d, spdef:%d, spd:%d\n", pokemon_misc[i]->hpiv, pokemon_misc[i]->atkiv, pokemon_misc[i]->defiv, pokemon_misc[i]->spatkiv, pokemon_misc[i]->spdefiv, pokemon_misc[i]->spdiv );
		fprintf(stderr, "EVs: hp:%d, atk:%d, def:%d, spatk:%d, spdef:%d, spd:%d\n", pokemon_effort[i]->hp, pokemon_effort[i]->attack, pokemon_effort[i]->defense, pokemon_effort[i]->spatk, pokemon_effort[i]->spdef, pokemon_effort[i]->speed );
	}

	/*
	// Re encrypt and set checksum
	for(i = 0; i < NUM_POKEMON; i++)
	{
		pokemon[i]->checksum = encrypt(pokemon[i]->data, pokemon[i]->personality, pokemon[i]->otid);
	}

	// Re-split into blocks and place over buffer
	// pack_save(...)

	for(i = 0; i < NUM_BLOCKS_TOTAL; i++)
	{
		if (blocks[i]->footer.savenumber == newestSave) {
			memcpy(blocks[i]->data, unpackeddata + BLOCK_DATA_LEN * blocks[i]->footer.blocknum, BLOCK_DATA_LEN);
			// Re-calculate and set this blocks checksum
			blocks[i]->footer.checksum = get_checksum(blocks[i]);
			tempCount++;
		}
	}

	// Save back into argv[2]
	if (argc == 3) {
		if ((f = fopen(argv[2], "wb")) == NULL) {
			printf("ERROR: Unable to open %s for writing.\n", argv[1]);

			return -1;
		}

		if (fwrite(savefile, SAVESLOT_LEN, 1, f) != 1) {
			printf("ERROR: Unable to write to file.\n");
			fclose(f);

			return -1;
		}
		fclose(f);
	}

	*/
	return 0;
}
