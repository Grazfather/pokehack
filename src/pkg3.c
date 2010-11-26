/*
 * Pk Gen 3 Save-state
 * Copyright (C) 2010 Grazfather
 */

#include <stdio.h>
#include "pokestructs.h"

#define STATE_SIZE 0xB49FE

// Either compile for each game, allow a choice, or detect automatically
#define BELT_OFFSET 0x2C863 // Uncompressed save state for Pokemon FireRed

#define NUM_POKEMON 6 // This will never change, but whater.
#define DATA_LENGTH 48

#define DEBUG

/* Order:
	00. GAEM	 06. AGEM	 12. EGAM	 18. MGAE
	01. GAME	 07. AGME	 13. EGMA	 19. MGEA
	02. GEAM	 08. AEGM	 14. EAGM	 20. MAGE
	03. GEMA	 09. AEMG	 15. EAMG	 21. MAEG
	04. GMAE	 10. AMGE	 16. EMGA	 22. MEGA
	05. GMEA	 11. AMEG	 17. EMAG	 23. MEAG
*/

struct pokemon_t * pokemon[6];

unsigned short int encrypt(char *data, unsigned int pv, unsigned int otid) {
	unsigned int xorkey = pv ^ otid;
	unsigned int checksum = 0;
	unsigned char i;
	
	for (i = 0; i < DATA_LENGTH; i+=4)
	{
		checksum += data[i+1]<<8 | data[i];
		checksum += data[i+3]<<8 | data[i+2];
		
		data[i] ^= (xorkey >> 24)&0xFF;
		data[i+1] ^= (xorkey >> 16)&0xFF;
		data[i+2] ^= (xorkey >> 8)&0xFF;
		data[i+3] ^= (xorkey >> 0)&0xFF;
		
	}
	
	
	return (unsigned short int)(checksum & 0xFFFF);

}

int main(int argc, char *argv[]) {
    FILE *f;
    char ram[STATE_SIZE];
	int i;
    
    /* check for the SRAM argument */
    if (argc != 2) {
        fprintf(stderr, "syntax: stateedit pokemonsavestate\n");
        fprintf(stderr, "example: stateedit PokemonFireRed1\n");
        
        return -1;
    }
    
    /* make sure we can open the file for reading */
    if ((f = fopen(argv[1], "rb")) == NULL) {
        fprintf(stderr, "error: unable to open %s for reading.\n", argv[1]);
        
        return -1;
    }
    
    /* make sure we were able to read a full SRAM file */
    if (fread(ram, STATE_SIZE, 1, f) != 1) {
        fprintf(stderr, "error: unable to read SRAM file data.\n");
        fclose(f);
        
        return -1;
    }
    
    fclose(f);
    
	for(i = 0; i < NUM_POKEMON; i++)
	{
        // Read data on pokemon
        pokemon[i] = /*(*(struct pokemon_t))*/(ram + BELT_OFFSET + (i * sizeof(struct pokemon_t)));
        
		//printf("Got pokemon %d\n",i);
		//printf("Personality: 0x%X\n", pokemon[i]->personality);
        
		// Unencrypt pokemon's data
        encrypt(pokemon[i]->data, pokemon[i]->personality, pokemon[i]->otid);

    }
	
	/**
	 * Modifiy pokemon data here
	 * 1. Figure out the order (AEGM)
	 * 2. Modify what we need
	 * 3. Re-encrypt
	 * 4. Set new checksum
	 */
	 //printf("pk0 hp %d\n", pokemon[0]->currentHP);
	 //printf("pk5 hp %d\n", pokemon[5]->currentHP);
	 pokemon[0]->currentHP = 13;

    
    // re-write 
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
