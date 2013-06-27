// Pokemon FR/LG/R/S/E .sav parser.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pokehack/pokestructs.h>

static unsigned short int get_block_checksum(block* b)
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

int get_newest_save(block *blocks[NUM_BLOCKS_TOTAL])
{
	int i, newestSave = 0;

	for (i = 0; i < NUM_BLOCKS_TOTAL; i++)
	{
		if (blocks[i]->footer.savenumber > newestSave)
			newestSave = blocks[i]->footer.savenumber;
	}

	return newestSave;
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
		//printf("Block %2.2d: validation: 0x%8.8X checksum: 0x%4.4X blocknum: 0x%2.2X savenumber: 0x%X\n",
		//		i, blocks[i]->footer.validation, blocks[i]->footer.checksum, blocks[i]->footer.blocknum, blocks[i]->footer.savenumber);
	}

	newestSave = get_newest_save(blocks);

	data = malloc(SAVESLOT_LEN);
	for (i = 0; i < NUM_BLOCKS_TOTAL; i++)
	{
		if (blocks[i]->footer.savenumber == newestSave)
			memcpy(data + BLOCK_DATA_LEN * blocks[i]->footer.blocknum, blocks[i]->data, BLOCK_DATA_LEN);
	}

	return data;

}

int pack_save(char *filename, char *unpackeddata, block *blocks[NUM_BLOCKS_TOTAL], char savefile[SAVEFILE_LEN])
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
