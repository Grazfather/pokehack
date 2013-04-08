#include "ItemComboBox.h"
#include "../include/pokestructs.h"

extern char* items[];

ItemComboBox::ItemComboBox( QWidget* parent ) : QComboBox( parent )
{
	for (int i = 0; i < NUM_ITEMS; i++)
	{
		addItem(tr(items[i]), QVariant( i ));
	}
};
