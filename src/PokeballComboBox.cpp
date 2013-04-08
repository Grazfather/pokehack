#include "PokeballComboBox.h"

PokeballComboBox::PokeballComboBox( QWidget* parent ) : QComboBox( parent )
{
	// Add all pokeball types available in Gen 3 ) );
	addItem(tr("Pokeball"), QVariant( 0 ));
	addItem(tr("Master Ball"), QVariant( 1 ));
	addItem(tr("Ultra Ball"), QVariant( 2 ));
	addItem(tr("Great Ball"), QVariant( 3 ));
	addItem(tr("Poke Ball?"), QVariant( 4 ));
	addItem(tr("Safari Ball"), QVariant( 5 ));
	addItem(tr("Net Ball?"), QVariant( 6 ));
	addItem(tr("Dive Ball"), QVariant( 7 ));
	addItem(tr("Nest Ball"), QVariant( 8 ));
	addItem(tr("Repeat Ball"), QVariant( 9 ));
	addItem(tr("Timer Ball"), QVariant( 10 ));
	addItem(tr("Luxury Ball"), QVariant( 11 ));
	addItem(tr("Premiere Ball"), QVariant( 12 ));
	addItem(tr("Poke Ball?"), QVariant( 13 ));
	addItem(tr("Poke Ball?"), QVariant( 14 ));
	addItem(tr("Poke Ball?"), QVariant( 15 ));
};
