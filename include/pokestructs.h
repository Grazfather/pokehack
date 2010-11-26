struct pokemon_t
{
	unsigned int personality;
	unsigned int otid;
	unsigned char name[10];
	unsigned char font;
	unsigned char sanity;
	unsigned char otname[7];
	unsigned char mark;
	unsigned short int checksum;
	unsigned char x1; 				// unused
	unsigned char data[48];
	unsigned int status;
	unsigned char level;
	unsigned char x2; 				// unused
	unsigned short int currentHP;
	unsigned short int maxHP;
	unsigned short attack;
	unsigned short defense;
	unsigned short speed;
	unsigned short spatk;
	unsigned short spdef;
};

struct pokemon_growth_t
{
	unsigned short int species;
	unsigned short int held;
	unsigned int xp;
	unsigned char ppbonuses;
	unsigned char happiness;
	unsigned char x; 				// unused
};

struct pokemon_attacks_t
{
	unsigned short int atk1;
	unsigned short int atk2;
	unsigned short int atk3;
	unsigned short int atk4;
	unsigned char pp1;
	unsigned char pp2;
	unsigned char pp3;
	unsigned char pp4;
};

struct pokemon_effort_t
{
	unsigned char hp;
	unsigned char attack;
	unsigned char defense;
	unsigned char speed;
	unsigned char spatk;
	unsigned char spdef;
	unsigned char coolness;
	unsigned char beauty;
	unsigned char cuteness;
	unsigned char smartness;
	unsigned char toughness;
	unsigned char feel;
};

struct pokemon_misc_t
{
	unsigned char pokerus;
	unsigned char location;
	signed char level;
	unsigned char pokeball; 		// As well as trainer gender?
	unsigned int IVs; 				// TODO: Split into groups of 5 bytes + 2 for egg
	unsigned int ribbons;
};
