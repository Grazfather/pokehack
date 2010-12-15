#include "StatusComboBox.h"

StatusComboBox::StatusComboBox( QWidget* parent ) : QComboBox( parent )
{
	// Add all pokeball types available in Gen 3 ) );
	addItem(tr("Normal"), QVariant( 0 ));
	addItem(tr("Sleep (1)"), QVariant( 1 ));
	addItem(tr("Sleep (2)"), QVariant( 2 ));
	addItem(tr("Sleep (3)"), QVariant( 3 ));
	addItem(tr("Sleep (3)"), QVariant( 4 ));
	addItem(tr("Sleep (3)"), QVariant( 8 ));
	addItem(tr("Sleep (3)"), QVariant( 6 ));
	addItem(tr("Sleep (3)"), QVariant( 7 ));
	addItem(tr("Poison"), QVariant( 8 ));
	addItem(tr("Burn"), QVariant( 16 ));
	addItem(tr("Frozen"), QVariant( 32 ));
	addItem(tr("Paralysis"), QVariant( 64 ));
	addItem(tr("Bad Poison"), QVariant( 128 ));
};
                                                        