#include "vrange.h"
//
vRange::vRange( int a, int b ) 
{
	start = a;
	end = b;
}

vRange::~vRange()
{
}
//
int vRange::startIndex()
{
	return( start );
}

int vRange::startBook()
{
	return( start / 4096 );
}

int vRange::startChapter()
{
	return( (start % 4096) / 128 );
}

int vRange::startVerse()
{
	return( start % 128 );
}

int vRange::endIndex()
{
	return( end );
}

int vRange::endBook()
{
	return( end / 4096 );
}

int vRange::endChapter()
{
	return( (end % 4096) / 128 );
}

int vRange::endVerse()
{
	return( end % 128 );
}

void vRange::setStartAddress( int book, int chapter, int verse )
{
	start = 128*(book*32+chapter)+verse;
}

void vRange::setStartIndex( int index )
{
	start = index;
}

void vRange::setEndAddress( int book, int chapter, int verse )
{
	end = 128*(book*32+chapter)+verse;
}

void vRange::setEndIndex( int index )
{
	end = index;
}
