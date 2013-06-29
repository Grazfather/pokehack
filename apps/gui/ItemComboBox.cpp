#include "ItemComboBox.h"
#include <pokehack/pokestructs.h>

ItemComboBox::ItemComboBox( QWidget* parent ) : QComboBox( parent )
{
	for (int i = 0; i < NUM_ITEMS; i++)
	{
		addItem(tr(items[i]), QVariant( i ));
	}
};
