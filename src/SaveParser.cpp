#include <stdio.h>
#include "SaveParser.h"

SaveParser* SaveParser::spInstance = NULL;

SaveParser* SaveParser::Instance()
{
	if (!spInstance) // If an instance hasn't already been created, so do
		spInstance = new SaveParser();

	return spInstance;
}

int SaveParser::load(const char *fn)
{
	FILE *f;
	printf("In load\n");
	// Make sure we can open the file for reading
	if ((f = fopen(fn, "rb")) == NULL) {
		fprintf(stderr, "error: unable to open %s for reading.\n", fn);

		return -1;
	}

	// Make sure we were able to read a full SRAM file
	if (fread(ram, STATE_SIZE, 1, f) != 1) {
		fprintf(stderr, "error: unable to read SRAM file data.\n");
		fclose(f);

		return -1;
	}

	fclose(f);

	for(int i = 0; i < NUM_POKEMON; i++)
	{
		int o;

		// Read data on pokemon
		pokemon[i] = (pokemon_t *)(ram + BELT_OFFSET + (i * sizeof(pokemon_t)));

		// Unencrypt pokemon's data
		encrypt(pokemon[i]->data, pokemon[i]->personality, pokemon[i]->otid);

		// Figure out the order
		o = pokemon[i]->personality % 24;
		pokemon_attacks[i] = (pokemon_attacks_t *)(pokemon[i]->data + DataOrderTable[o][0] * sizeof(pokemon_growth_t));
		pokemon_effort[i] = (pokemon_effort_t *)(pokemon[i]->data + DataOrderTable[o][1] * sizeof(pokemon_growth_t));
		pokemon_growth[i] = (pokemon_growth_t *)(pokemon[i]->data + DataOrderTable[o][2] * sizeof(pokemon_growth_t));
		pokemon_misc[i] = (pokemon_misc_t *)(pokemon[i]->data + DataOrderTable[o][3] * sizeof(pokemon_growth_t));
	}

	return 0;
}

int SaveParser::save(const char *fn)
{
	FILE *f;

	// Re encrypt and set checksum
	// TODO: This should be handled by the encrypt function
	for(int i = 0; i < NUM_POKEMON; i++)
	{
		pokemon[i]->checksum = encrypt(pokemon[i]->data, pokemon[i]->personality, pokemon[i]->otid);
	}

	// re-write to file
	// TODO: Make it write to a different file instead of overwriting the input file
	if ((f = fopen(fn, "wb")) == NULL) {
		fprintf(stderr, "error: unable to open %s for writing.\n", fn);

		return -1;
	}

	if (fwrite(ram, STATE_SIZE, 1, f) != 1) {
		fprintf(stderr, "error: unable to write SRAM file data.\n");
		fclose(f);

		return -1;
	}

	fclose(f);

	// re-decrypt the file so we can work with it again
	for(int i = 0; i < NUM_POKEMON; i++)
	{
		pokemon[i]->checksum = encrypt(pokemon[i]->data, pokemon[i]->personality, pokemon[i]->otid);
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

	for (i = 0; i < DATA_LENGTH; i+=4)
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
