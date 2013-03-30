/*
 * Pokemon Gen 3 Save-state editor
 * Copyright (C) 2010-2013 Grazfather
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pokestructs.h>

// Global variables

// Pokemon in belt
belt_pokemon_t *belt_pokemon[NUM_BELT_POKEMON];
pokemon_attacks_t *belt_pokemon_attacks[NUM_BELT_POKEMON];
pokemon_effort_t *belt_pokemon_effort[NUM_BELT_POKEMON];
pokemon_growth_t *belt_pokemon_growth[NUM_BELT_POKEMON];
pokemon_misc_t *belt_pokemon_misc[NUM_BELT_POKEMON];

// Pokemon in PC
box_pokemon_t *box_pokemon[NUM_BOX_POKEMON];
pokemon_attacks_t *box_pokemon_attacks[NUM_BOX_POKEMON];
pokemon_effort_t *box_pokemon_effort[NUM_BOX_POKEMON];
pokemon_growth_t *box_pokemon_growth[NUM_BOX_POKEMON];
pokemon_misc_t *box_pokemon_misc[NUM_BOX_POKEMON];

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
		fprintf(stderr, "syntax: pokeedit pokemonsave [outfile] <game>\n");
		fprintf(stderr, "0 for Emerald/Ruby/Sapphire. 1 for FireRed/LeafGreen\n");
		fprintf(stderr, "example: pokeedit PokemonFireRed.sav NewPokemonFireRed.sav 1\n");

		return -1;
	}

	if (argc > 3) // Supplied a file to write to
		game = atoi(argv[3]);
	else
		game = atoi(argv[2]);
	if (( game < 0) || ( game > 1)) {
		fprintf(stderr, "Game can only be 1 or 0\n");
		return -1;
	}

	unpackeddata = parse_save(argv[1], savefile, blocks);
	if (unpackeddata == NULL)
	{
		fprintf(stderr, "Could not parse save file.\n");
		return -1;
	}

	// Parse pokemon in belt
	for(i = 0; i < NUM_BELT_POKEMON; i++)
	{
		int o;

		// Read data on pokemon
		belt_pokemon[i] = (belt_pokemon_t *)(unpackeddata + offsets[game] + (i * sizeof(belt_pokemon_t)));

		// Unencrypt pokemon's data
		encrypt(belt_pokemon[i]->data, belt_pokemon[i]->personality, belt_pokemon[i]->otid);

		// Figure out the order
		o = belt_pokemon[i]->personality % 24;
		belt_pokemon_attacks[i] = (pokemon_attacks_t *)(belt_pokemon[i]->data + DataOrderTable[o][0] * sizeof(pokemon_growth_t));
		belt_pokemon_effort[i] = (pokemon_effort_t *)(belt_pokemon[i]->data + DataOrderTable[o][1] * sizeof(pokemon_growth_t));
		belt_pokemon_growth[i] = (pokemon_growth_t *)(belt_pokemon[i]->data + DataOrderTable[o][2] * sizeof(pokemon_growth_t));
		belt_pokemon_misc[i] = (pokemon_misc_t *)(belt_pokemon[i]->data + DataOrderTable[o][3] * sizeof(pokemon_growth_t));
		fprintf(stderr, "\nPokemon %d: hp %d/%d\n", i, belt_pokemon[i]->currentHP, belt_pokemon[i]->maxHP);
		fprintf(stderr, "Species %d, held: %d, experience: %d, ppb: %d, friendship: %d\n", belt_pokemon_growth[i]->species, belt_pokemon_growth[i]->held, belt_pokemon_growth[i]->xp, belt_pokemon_growth[i]->ppbonuses, belt_pokemon_growth[i]->happiness);
		fprintf(stderr, "Attacks: 1:%d, 2:%d, 3:%d, 4:%d, pp1:%d, pp2:%d, pp3:%d, pp4:%d\n", belt_pokemon_attacks[i]->atk1, belt_pokemon_attacks[i]->atk2, belt_pokemon_attacks[i]->atk3, belt_pokemon_attacks[i]->atk4, belt_pokemon_attacks[i]->pp1, belt_pokemon_attacks[i]->pp2, belt_pokemon_attacks[i]->pp3, belt_pokemon_attacks[i]->pp4 );
		fprintf(stderr, "IVs: hp:%d, atk:%d, def:%d, spatk:%d, spdef:%d, spd:%d\n", belt_pokemon_misc[i]->hpiv, belt_pokemon_misc[i]->atkiv, belt_pokemon_misc[i]->defiv, belt_pokemon_misc[i]->spatkiv, belt_pokemon_misc[i]->spdefiv, belt_pokemon_misc[i]->spdiv );
		fprintf(stderr, "EVs: hp:%d, atk:%d, def:%d, spatk:%d, spdef:%d, spd:%d\n", belt_pokemon_effort[i]->hp, belt_pokemon_effort[i]->attack, belt_pokemon_effort[i]->defense, belt_pokemon_effort[i]->spatk, belt_pokemon_effort[i]->spdef, belt_pokemon_effort[i]->speed );
	}

	// Parse pokemon in PC
	for(i = 0; i < NUM_BOX_POKEMON; i++)
	{
		int o;

		// Read data on pokemon
		box_pokemon[i] = (box_pokemon_t *)(unpackeddata + BOX_OFFSET + (i * sizeof(box_pokemon_t)));

		// Unencrypt pokemon's data
		encrypt(box_pokemon[i]->data, box_pokemon[i]->personality, box_pokemon[i]->otid);

		// Figure out the order
		o = box_pokemon[i]->personality % 24;
		box_pokemon_attacks[i] = (pokemon_attacks_t *)(box_pokemon[i]->data + DataOrderTable[o][0] * sizeof(pokemon_growth_t));
		box_pokemon_effort[i] = (pokemon_effort_t *)(box_pokemon[i]->data + DataOrderTable[o][1] * sizeof(pokemon_growth_t));
		box_pokemon_growth[i] = (pokemon_growth_t *)(box_pokemon[i]->data + DataOrderTable[o][2] * sizeof(pokemon_growth_t));
		box_pokemon_misc[i] = (pokemon_misc_t *)(box_pokemon[i]->data + DataOrderTable[o][3] * sizeof(pokemon_growth_t));
		if (box_pokemon_growth[i]->species)
			fprintf(stderr, "Pokemon %d: species:%d\n", i, box_pokemon_growth[i]->species);
	}

	// Make our edits here

	// Done edits

	// Re encrypt and set checksum
	for(i = 0; i < NUM_BELT_POKEMON; i++)
	{
		belt_pokemon[i]->checksum = encrypt(belt_pokemon[i]->data, belt_pokemon[i]->personality, belt_pokemon[i]->otid);
	}

	for(i = 0; i < NUM_BOX_POKEMON; i++)
	{
		box_pokemon[i]->checksum = encrypt(box_pokemon[i]->data, box_pokemon[i]->personality, box_pokemon[i]->otid);
	}

	if (argc > 3) {
		if (pack_save(argv[2], unpackeddata, blocks, savefile)) {
			fprintf(stderr, "Could not save changes!\n");
			return -1;
		} else {
			fprintf(stderr, "Saved!\n");
		}
	} else {
		free(unpackeddata);
	}

	return 0;
}
