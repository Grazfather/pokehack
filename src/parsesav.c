// Pokemon FR/LG/R/S/E .sav parser.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pokestructs.h>

unsigned short get_checksum(block* b)
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

char* parse_save(char *filename, char *savefile, block *blocks[NUM_BLOCKS_TOTAL])
{
	FILE *f;
	char *data;
	int i, newestSave;

	// Make sure we can open the file for reading
	if ((f = fopen(filename, "rb")) == NULL) {
		fprintf(stderr, "error: unable to open %s for reading.\n", filename);

		return NULL;
	}

	// Make sure we were able to read a full sav file
	if (fread(savefile, SAVEFILE_LEN, 1, f) != 1) {
		fprintf(stderr, "error: unable to read SRAM file data.\n");
		fclose(f);

		return NULL;
	}

	fclose(f);

	// Set up each block to point to a different 4kB segment
	// as well find the newest save in the file
	newestSave = 0;
	for (i = 0; i < NUM_BLOCKS_TOTAL; i++)
	{
		blocks[i] = (block*)(savefile + i*(sizeof(block)));
		//printf("Block %2.2d: validation: 0x%8.8X checksum: 0x%4.4X blocknum: 0x%2.2X savenumber: 0x%X\n",
		//		i, blocks[i]->footer.validation, blocks[i]->footer.checksum, blocks[i]->footer.blocknum, blocks[i]->footer.savenumber);
		if (blocks[i]->footer.savenumber > newestSave)
			newestSave = blocks[i]->footer.savenumber;
	}

	data = malloc(SAVESLOT_LEN);
	for (i = 0; i < NUM_BLOCKS_TOTAL; i++)
	{
		if (blocks[i]->footer.savenumber == newestSave)
			memcpy(data + BLOCK_DATA_LEN * blocks[i]->footer.blocknum, blocks[i]->data, BLOCK_DATA_LEN);
	}

	return data;

}