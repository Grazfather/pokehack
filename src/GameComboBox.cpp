#include "GameComboBox.h"

GameComboBox::GameComboBox( QWidget* parent ) : QComboBox( parent )
{
	// Add all items available in Gen 3 ) );
	addItem(tr("FireRed"), QVariant( 0 ));
	addItem(tr("LeafGreen"), QVariant( 1 ));
	addItem(tr("Ruby"), QVariant( 2 ));
	addItem(tr("Sapphire"), QVariant( 3 ));
	addItem(tr("Emerald"), QVariant( 4 ));
};
                                                        
