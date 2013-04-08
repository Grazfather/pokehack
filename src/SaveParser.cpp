#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "SaveParser.h"

// Global variables
extern char* pokemon_species[];
extern char* items[];
extern char* natures[];
extern char* attacks[];

SaveParser* SaveParser::spInstance = NULL;

int SaveParser::get_newest_save(block *blocks[NUM_BLOCKS_TOTAL])
{
	int i, newestSave = 0;

	for (i = 0; i < NUM_BLOCKS_TOTAL; i++)
	{
		if (blocks[i]->footer.savenumber > newestSave)
			newestSave = blocks[i]->footer.savenumber;
	}

	return newestSave;
}

unsigned short int SaveParser::get_block_checksum(block* b)
{
	int checksum = 0;
	int i;
	for (i = 0; i < BLOCK_DATA_LEN; i+=4)
	{
		checksum += *((int*)b+i/4);
	}
	checksum += checksum >> 16;
	checksum &= 0xFFFF;

	return (unsigned short int)checksum;
}

char* SaveParser::parse_save(const char *filename, char *savefile, block *blocks[NUM_BLOCKS_TOTAL])
{
	FILE *f;
	char *data;
	int i, newestSave;

	// Make sure we can open the file for reading
	if ((f = fopen(filename, "rb")) == NULL) {
		fprintf(stderr, "error: unable to open %s for reading.\n", filename);

		return NULL;
	}

	// Make sure we can read a full .sav file
	if (fread(savefile, SAVEFILE_LEN, 1, f) != 1) {
		fprintf(stderr, "error: unable to read SRAM file data.\n");
		fclose(f);

		return NULL;
	}

	fclose(f);

	for (i = 0; i < NUM_BLOCKS_TOTAL; i++)
	{
		blocks[i] = (block*)(savefile + i*(sizeof(block)));
	}

	newestSave = get_newest_save(blocks);

	data = (char*)malloc(SAVESLOT_LEN);
	for (i = 0; i < NUM_BLOCKS_TOTAL; i++)
	{
		if (blocks[i]->footer.savenumber == newestSave)
			memcpy(data + BLOCK_DATA_LEN * blocks[i]->footer.blocknum, blocks[i]->data, BLOCK_DATA_LEN);
	}

	return data;
}

int SaveParser::pack_save(const char *filename, char *unpackeddata, block *blocks[NUM_BLOCKS_TOTAL], char savefile[SAVEFILE_LEN])
{
	FILE *f;
	int i, newestSave;
	int tempCount = 0;

	newestSave = get_newest_save(blocks);

	// Re-split into blocks and place over buffer
	for(i = 0; i < NUM_BLOCKS_TOTAL; i++)
	{
		if (blocks[i]->footer.savenumber == newestSave) {
			memcpy(blocks[i]->data, unpackeddata + BLOCK_DATA_LEN * blocks[i]->footer.blocknum, BLOCK_DATA_LEN);
			// Re-calculate and set this block's checksum
			blocks[i]->footer.checksum = get_block_checksum(blocks[i]);
			tempCount++;
		}
	}
	free(unpackeddata);

	// Save back to file
	if ((f = fopen(filename, "wb")) == NULL) {
		printf("ERROR: Unable to open %s for writing.\n", filename);

		return -1;
	}

	if (fwrite(savefile, SAVEFILE_LEN, 1, f) != 1) {
		printf("ERROR: Unable to write to file.\n");
		fclose(f);

		return -1;
	}
	fclose(f);

	return 0;
}

void SaveParser::print_pokemon(box_pokemon_t* pokemon)
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

int SaveParser::parse_pokemon(char* buf, int offset, void** pokemon, pokemon_attacks_t** pa, pokemon_effort_t** pe, pokemon_growth_t** pg, pokemon_misc_t** pm, int num, int size)
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
		SaveParser::Instance()->encrypt(((box_pokemon_t*)pokemon[i])->data, ((box_pokemon_t*)pokemon[i])->personality, ((box_pokemon_t*)pokemon[i])->otid);

		// Figure out the order
		o = ((box_pokemon_t*)pokemon[i])->personality % 24;
		pa[i] = (pokemon_attacks_t *)(((box_pokemon_t*)pokemon[i])->data + DataOrderTable[o][0] * sizeof(pokemon_attacks_t));
		pe[i] = (pokemon_effort_t *)(((box_pokemon_t*)pokemon[i])->data + DataOrderTable[o][1] * sizeof(pokemon_effort_t));
		pg[i] = (pokemon_growth_t *)(((box_pokemon_t*)pokemon[i])->data + DataOrderTable[o][2] * sizeof(pokemon_growth_t));
		pm[i] = (pokemon_misc_t *)(((box_pokemon_t*)pokemon[i])->data + DataOrderTable[o][3] * sizeof(pokemon_misc_t));
		if (pg[i]->species) {
			fprintf(stdout, "\nPokemon %d\n", i);
			print_pokemon((box_pokemon_t*)pokemon[i]);
		}
	}

	return 0;
}

SaveParser* SaveParser::Instance()
{
	if (!spInstance) // If an instance hasn't already been created, so do
		spInstance = new SaveParser();

	return spInstance;
}

int SaveParser::load(const char *fn, int game)
{
	// Parse save
	unpackeddata = parse_save(fn, savefile, blocks);
	if (unpackeddata == NULL)
	{
		fprintf(stderr, "Could not parse save file.\n");
		return -1;
	}

	// Decode belt part
	parse_pokemon(unpackeddata, belt_offsets[game], (void**)pokemon, pokemon_attacks, pokemon_effort, pokemon_growth, pokemon_misc, NUM_BELT_POKEMON, sizeof(belt_pokemon_t));

	return 0;
}

int SaveParser::save(const char *fn)
{
	// Re encrypt and set checksum
	for(int i = 0; i < NUM_BELT_POKEMON; i++)
	{
		pokemon[i]->checksum = encrypt(pokemon[i]->data, pokemon[i]->personality, pokemon[i]->otid);
	}

	if (pack_save(fn, unpackeddata, blocks, savefile)) {
		fprintf(stderr, "Could not save changes!\n");
		return -1;
	} else {
		fprintf(stdout, "Saved!\n");
	}

	return 0;
}

/*
 *	Encrypts/decrypts the 48 byte data buffer based on the xored pv and otid values
 *  TODO: Make it encrypt its own data/not need arguments
 */
unsigned short int SaveParser::encrypt(unsigned char *data, unsigned int pv, unsigned int otid) {
	unsigned int xorkey = pv ^ otid;
	unsigned short int checksum = 0;
	unsigned int i;

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
