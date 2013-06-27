/*
 * Pokemon Gen 3 Save-state editor
 * Copyright (C) 2010-2013 Grazfather
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pokehack/data.h>
#include <pokehack/pokestructs.h>

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

	parse_pokemon(unpackeddata, belt_offsets[game], (void**)belt_pokemon, belt_pokemon_attacks, belt_pokemon_effort, belt_pokemon_growth, belt_pokemon_misc, NUM_BELT_POKEMON, sizeof(belt_pokemon_t));
	parse_pokemon(unpackeddata, BOX_OFFSET, (void**)box_pokemon, box_pokemon_attacks, box_pokemon_effort, box_pokemon_growth, box_pokemon_misc, NUM_BOX_POKEMON, sizeof(box_pokemon_t));

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
			fprintf(stdout, "Saved!\n");
		}
	} else {
		free(unpackeddata);
	}

	return 0;
}
