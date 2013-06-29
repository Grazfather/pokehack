#include "SpeciesComboBox.h"
#include <pokehack/pokestructs.h>

SpeciesComboBox::SpeciesComboBox( QWidget* parent ) : QComboBox( parent )
{
	for (int i = 0; i < NUM_POKEMON_SPECIES; i++)
	{
		addItem(tr(pokemon_species[i]), QVariant( i ));
	}
};
