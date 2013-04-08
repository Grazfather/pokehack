#include "AttackComboBox.h"
#include "../include/pokestructs.h"

extern char* attacks[];

AttackComboBox::AttackComboBox( QWidget* parent ) : QComboBox( parent )
{
	for (int i = 0; i < NUM_ATTACKS; i++)
	{
		addItem(tr(attacks[i]), QVariant( i ));
	}
};
                                                        