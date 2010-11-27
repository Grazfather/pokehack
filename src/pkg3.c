/*
 * Pokemon Gen 3 Save-state editor
 * Copyright (C) 2010 Grazfather
 */

#include <stdio.h>
#include <pokestructs.h>

#define STATE_SIZE 0xB49FE

// Either compile for each game, allow a choice, or detect automatically
#define BELT_OFFSET 0x2C863 // Uncompressed save state for Pokemon FireRed

#define NUM_POKEMON 6 // This will never change, but whatever.
#define DATA_LENGTH 48

// Global variables
pokemon_t * pokemon[6];
pokemon_attacks_t * pokemon_attacks[6];
pokemon_effort_t * pokemon_effort[6];
pokemon_growth_t * pokemon_growth[6];
pokemon_misc_t * pokemon_misc[6];

// Simply print out a buffer in hex. Used for debugging
void dumpbuf(unsigned char * buf, unsigned int size)
{
	for (; size > 0; size--)
	{
		printf("%2.2X ", *buf++);
	}
	printf("\n");
}

/*
 *	Encrypts/decrypts the 48 byte data buffer based on the xored pv and otid values
 */
unsigned short int encrypt(unsigned char *data, unsigned int pv, unsigned int otid) {
	unsigned int xorkey = pv ^ otid;
	unsigned short int checksum = 0;
	unsigned char i;
	
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

int main(int argc, char *argv[]) {
    FILE *f;
    char ram[STATE_SIZE];
	int i;
    
    // Check for the save state file argument
    if (argc != 2) {
        fprintf(stderr, "syntax: stateedit pokemonsavestate outfile\n");
        fprintf(stderr, "example: stateedit PokemonFireRed1 NewFireRed\n");
        
        return -1;
    }
    
    // Make sure we can open the file for reading
    if ((f = fopen(argv[1], "rb")) == NULL) {
        fprintf(stderr, "error: unable to open %s for reading.\n", argv[1]);
        
        return -1;
    }
    
    // Make sure we were able to read a full SRAM file
    if (fread(ram, STATE_SIZE, 1, f) != 1) {
        fprintf(stderr, "error: unable to read SRAM file data.\n");
        fclose(f);
        
        return -1;
    }
    
    fclose(f);
    
	for(i = 0; i < NUM_POKEMON; i++)
	{
		int o;
		
        // Read data on pokemon
        pokemon[i] = (pokemon_t *)(ram + BELT_OFFSET + (i * sizeof(pokemon_t)));
        
		// Unencrypt pokemon's data
        encrypt(pokemon[i]->data, pokemon[i]->personality, pokemon[i]->otid);
		
		// Figure out the order
		o = pokemon[i]->personality % 24; // TODO: See if we need to switch the order for endianness
		pokemon_attacks[i] = (pokemon_attacks_t *)(pokemon[i]->data + DataOrderTable[o][0] * sizeof(pokemon_growth_t));
		pokemon_effort[i] = (pokemon_effort_t *)(pokemon[i]->data + DataOrderTable[o][1] * sizeof(pokemon_growth_t));
		pokemon_growth[i] = (pokemon_growth_t *)(pokemon[i]->data + DataOrderTable[o][2] * sizeof(pokemon_growth_t));
		pokemon_misc[i] = (pokemon_misc_t *)(pokemon[i]->data + DataOrderTable[o][3] * sizeof(pokemon_growth_t));
    }
	
	// Modify whatever we want
	pokemon_growth[0]->species = pokemon_growth[0]->species + 1;
	
	// Re encrypt and set checksum
	for(i = 0; i < NUM_POKEMON; i++)
	{
		pokemon[i]->checksum = encrypt(pokemon[i]->data, pokemon[i]->personality, pokemon[i]->otid);
	}

    // re-write to file
	// TODO: Make it write to a different file instead of overwriting the input file
    if ((f = fopen(argv[1], "wb")) == NULL) {
        fprintf(stderr, "error: unable to open %s for writing.\n", argv[1]);
        
        return -1;
    }
    
    if (fwrite(ram, STATE_SIZE, 1, f) != 1) {
        fprintf(stderr, "error: unable to write SRAM file data.\n");
        fclose(f);
        
        return -1;
    }
    
    fclose(f);

    return 0;
}
