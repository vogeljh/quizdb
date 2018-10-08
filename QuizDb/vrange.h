#ifndef VRANGE_H
#define VRANGE_H
#include <QString>
//

//
class vRange  
{

public:
	vRange(int=0, int=9999);
	virtual ~vRange();
//
	int startIndex();
	int startBook();
	int startChapter();
	int startVerse();
	int endIndex();
	int endBook();
	int endChapter();
	int endVerse();
	void setStartAddress( int, int, int );
	void setStartIndex( int );
	void setEndAddress( int, int, int );
	void setEndIndex( int );

protected:
	int start, end;
};
#endif
