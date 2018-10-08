#include "order.h"
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlQueryModel>
//
order::order( QWidget * parent, Qt::WindowFlags f ) 
	: QWidget( parent, f )
{
	QSqlQueryModel filterModel;
	QString primary, secondary;
	
	setupUi(this);
    pwin = (MainWindow *)parent;
//	QWidget::setWindoWindowFlags( f );
	filterModel.setQuery( "SELECT ORDER1, ORDER2 FROM Qfilter" );
	if( filterModel.lastError().isValid() )
	{
		pwin->Err( filterModel.lastError().text() );
		return;
	}
	primary = filterModel.record( 0 ).value( "ORDER1" ).toString();
	secondary = filterModel.record( 0 ).value( "ORDER2" ).toString();

	if( primary.compare( "VID" ) == 0 )
		versebutton->setChecked( true );
	else if( primary.compare( "Qtype" ) == 0 )
		typebutton->setChecked( true );
	else if( primary.compare( "Qsort" ) == 0 )
		alphabutton->setChecked( true );

	if( secondary.compare( "VID" ) == 0 )
		versebutton_2->setChecked( true );
	else if( secondary.compare( "Qtype" ) == 0 )
		typebutton_2->setChecked( true );
	else if( secondary.compare( "Qsort" ) == 0 )
		alphabutton_2->setChecked( true );
/*
	switch( primary )
	{
		case ORDERBYVERSE: versebutton->setChecked( true ); break;
		case ORDERBYTYPE: typebutton->setChecked( true ); break;
		case ORDERBYALPHA: alphabutton->setChecked( true ); break;
	}
	switch( secondary )
	{
		case ORDERBYVERSE: versebutton_2->setChecked( true ); break;
		case ORDERBYTYPE: typebutton_2->setChecked( true ); break;
		case ORDERBYALPHA: alphabutton_2->setChecked( true ); break;
	}
*/
	connect( OK, SIGNAL(clicked()), this, SLOT(OK_clicked()) );
	connect( Cancel, SIGNAL(clicked()), this, SLOT(close()) );
}
//
/*$SPECIALIZATION$*/
void order::OK_clicked()
{
	QString order1, order2;
	
	if( versebutton->isChecked() )
		order1 = QString( "VID" );//ORDERBYVERSE;
	else if( typebutton->isChecked() )
		order1 = QString( "Qtype" );//ORDERBYTYPE;
	else/*  if( alphabutton->isChecked() )*/
		order1 = QString( "Qsort" );//ORDERBYALPHA;
	
	if( versebutton_2->isChecked() )
		order2 = QString( "VID" );//ORDERBYVERSE;
	else if( typebutton_2->isChecked() )
		order2 = QString( "Qtype" );//ORDERBYTYPE;
	else/* if( alphabutton_2->isChecked() )*/
		order2 = QString( "Qsort" );//ORDERBYALPHA;
	
	pwin->setOrder( order1, order2 );
	close();
}

