#include "GameComboBox.h"

GameComboBox::GameComboBox( QWidget* parent ) : QComboBox( parent )
{
	addItem(tr("E/R/S"), QVariant( 0 ));
	addItem(tr("FR/LG"), QVariant( 1 ));
};
