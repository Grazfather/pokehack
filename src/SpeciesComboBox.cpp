#include "SpeciesComboBox.h"
#include "../include/pokestructs.h"

extern char* pokemon_species[];

SpeciesComboBox::SpeciesComboBox( QWidget* parent ) : QComboBox( parent )
{
	for (int i = 0; i < NUM_POKEMON_SPECIES; i++)
	{
		addItem(tr(pokemon_species[i]), QVariant( i ));
	}
};
