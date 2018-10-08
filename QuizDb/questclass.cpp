/***************************************************************************
 *   Copyright (C) 2007 by Jeff Vogel   *
 *   vogeljh@gmail.com   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include <QSqlQueryModel>
#include <QSqlError>
#include "questclass.h"
//
questClass::questClass( QSqlRecord record ) 
{
	QSqlQueryModel typeModel;
	
	if( !record.isEmpty() )
	{
		qCverseIndex = record.value("VID").toInt();
		qCbookAbbrev = record.value("Abbrev").toString();
		qCbookChapter = record.value("Chap").toString();
		qCchapter = record.value("Chapter").toInt();
		qCverse = record.value("Verse").toInt();
		qCnumVerses = record.value("Verses").toInt();
		qCquestCode = record.value("Qtype").toInt();
		qCpreface = record.value("Header").toString(); 
		qCquestion = record.value("Qtext").toString(); 
		qCanswer = record.value("Answer").toString();
		qCcrossRef = record.value("CR").toString();
		qCused = record.value("Used").toInt();
		qCreference = record.value("Ref").toString();
		qCshowQuestion = true;
		qCshowAnswer = true;
//		qCshowKeyWords = true;
//		qCshowPreface = true;
//		qCLaTeX = true;
		qCshiftFtv = false;

		typeModel.setQuery( QString( "SELECT * FROM Types WHERE Questtype=%1" )
			.arg( qCquestCode ) );
		if( typeModel.lastError().isValid() )
		{
			qCshowPreface = true;
			qCrefq = qCsitq = qCftvq = false;
		}
		else
		{
			qCshowPreface = typeModel.record(0).value("Display").toBool();
			qCrefq = typeModel.record(0).value("Reference").toBool();
			qCsitq = typeModel.record(0).value("Situation").toBool();
			qCftvq = typeModel.record(0).value("Finish").toBool();
		}
	}
}

//
questClass::~questClass()
{
}
//

int questClass::verseIndex()
{
	return( qCverseIndex );
}

QString questClass::bookAbbrev()
{
	return( qCbookAbbrev );
}

QString questClass::bookChapter()
{
	return( qCbookChapter );
}

int questClass::chapter()
{
	return( qCchapter );
}

int questClass::verse()
{
	return( qCverse );
}

int questClass::numVerses()
{
	return( qCnumVerses );
}

int questClass::questCode()
{
	return( qCquestCode );
}

QString questClass::preface()
{
	return( qCpreface );
}

QString questClass::question()
{
	return( qCquestion );
}

QString questClass::answer()
{
	return( qCanswer );
}

QString questClass::crossRef()
{
	return( qCcrossRef );
}

int questClass::used()
{
	return( qCused );
}

QString questClass::reference()
{
	return( qCreference );
}

void questClass::showQuestion( bool flag )
{
	qCshowQuestion = flag;
}

void questClass::showAnswer( bool flag )
{
	qCshowAnswer = flag;
}

void questClass::setLaTeX( bool flag )
{
    qCLaTeX = flag;
}

void questClass::setHighlight( bool flag )
{
    qCshowKeyWords = flag;
}

void questClass::showKeyWords( bool flag )
{
	qCshowKeyWords = flag;
}

void questClass::showPreface( bool flag )
{
	qCshowPreface = flag;
}

void questClass::shiftFtv( bool flag )
{
	qCshiftFtv = flag;
}

bool questClass::isRefq()
{
	return( qCrefq );
}

bool questClass::isSitq()
{
	return( qCsitq );
}

bool questClass::isFtvq()
{
	return( qCftvq );
}

bool questClass::isSameWord( QString qst, int i )
{
	if( (qst.at(i).isLetterOrNumber() || (qst.at(i) == QChar('\'') && 
			qst.at(i+1).isLetter()) || qst.at(i) == QChar('-')) && 
			!(qst.at(i) == QChar('}')))
		return( true );
	else
		return( false );
}

QString questClass::formatted( int number )
{
	QString sql;
	
	if( qCquestion.length() == 0 )
		return( QString( "" ) );
	if( qCshowKeyWords )
	{
		sql = QString( "SELECT Word FROM KView WHERE VID>%3 AND VID<%4" )
			.arg( qCverseIndex-2 ).arg( qCverseIndex+qCnumVerses+2 );
		kModel.setQuery( sql );
	
		sql = QString( "SELECT Word FROM AView WHERE VID>%3 AND VID<%4" )
			.arg( qCverseIndex-2 ).arg( qCverseIndex+qCnumVerses+2 );
		aModel.setQuery( sql );
	}
	if( qCLaTeX )
		return( LaTeXformatted() );
	else
        return( RTFformatted( number ) );
}

QString questClass::LaTeXformatted()
{
	int i, j, k;
	QString str;

	if( qCshowQuestion )
		qCformatted = QString( "\\q" );
	else
		qCformatted = QString( "\\a" );

	if( qCpreface.length() > 0 && qCshowPreface && qCshowQuestion )
		qCformatted.append( "[" ).append( qCpreface ).append( "]" );
// was like this for ftb purposes I changed it. 
//		qCformatted.append( "[" ).append( qCpreface ).append( "]{" );
//	else
//		qCformatted.append( "{" );

	if( qCftvq && qCshiftFtv ) 
	{ // FTV: move a few words from the answer into the question (for quizzes)
		i = qCquestion.count( " " ); //i is 1 less than # of words in question
		j = ( i>4 ? 0 : 4-i ); //move j words, to get min 5 words in question
        if( j > 0 )
        {
            for( i=k=0; i<j; i++ )
                k = qCanswer.indexOf( " ", k+1 ); //find the jth space
            str = qCanswer.left( k ); //copy everything up to the jth space
            qCquestion.append( " " ).append( str ); //append copied text to question
            qCanswer.remove( 0, k+1 ); //delete copied text plus next space

        }
    }

	if( qCshowQuestion )
	{
// added this line for ftb change
		qCformatted.append( "{" );
		str = qCquestion;
		if( qCrefq )
			str = fixRefCapitalization( str );
		if( qCshowKeyWords )
			qCformatted.append( fixQuotes( LaTeXkey( str ) ) );
		else
			qCformatted.append( fixQuotes( str ) );
// added this line for ftb change
		qCformatted.append( "}" );
	}
//removed this for ftb change
//	qCformatted.append( "}{" );
	if( qCshowAnswer )
	{
// added this line for ftb change
		qCformatted.append( "{" );
		str = qCanswer;
		if( qCshowKeyWords )
			qCformatted.append( fixQuotes( LaTeXkey( str ) ) );
		else
			qCformatted.append( fixQuotes( str ) );
// the next 6 lines used to be outside the if(qCshowAnswer) block.
		if( !qCrefq )
			qCformatted.append( " (" ).append( qCreference ).append( ")" );
		if( qCcrossRef.length() > 0 )
		{
			if( qCcrossRef.compare("(") > 0 )
				qCformatted.append( " (cf " ).append( qCcrossRef ).append( ")" );
			else
				qCformatted.append( " " ).append( qCcrossRef );
		}
		
		qCformatted.append( "}\n" );
	}
// added this for ftb change
	else
		qCformatted.append( "\n" );

	return( qCformatted );
}

QString questClass::LaTeXkey( QString str )
{
	int i, j, l;
	QString word;
	bool iskey, isalmost;

	for( i=0; i<str.length(); i++ )
	{
		iskey = isalmost = false;
		if( str.at(i).isLetterOrNumber() )
		{
			for( j=0; j<kModel.rowCount(); j++ )
			{
				word = kModel.record( j ).value( "Word" ).toString(); 
				l = word.length();
                if( str.mid( i, l ).compare( word, Qt::CaseInsensitive ) == 0 )
				{
					iskey = true;
					str.insert( i, "{\\bf " );
					i += 5;
					break;
				}
			}
			if( !iskey )
			{
				for( j=0; j<aModel.rowCount(); j++ )
				{
					word = aModel.record( j ).value( "Word" ).toString(); 
					l = word.length();
                    if( str.mid( i, l ).compare( word, Qt::CaseInsensitive ) == 0 )
					{
						isalmost = true;
						str.insert( i, "{\\it " );
						i += 5;
						break;
					}
				}
			}
			for( i++; i<str.length(); i++ )
				if( !isSameWord( str, i ) )
					break;
			if( iskey || isalmost )
				str.insert( i, "}" );
		}
	}
	return( str );
}

QString questClass::fixQuotes( QString str )
{
	int i;

	i=0;	
	while( (i=str.indexOf( QChar( '\"' ), i )) > -1 )
	{
		str.remove( i, 1 );
		if( str.length() == i )
			str.insert( i, "\'\'" );
		else if( str.at(i).isLetter() || (str.at(i) == QChar ( '\'' )) || 
				(str.at(i) == QChar ( '{' )) )
			str.insert( i, "``" );
		else
			str.insert( i, "\'\'" );
	}
	return( str );
}

QString questClass::fixRefCapitalization( QString str )
{
	int i;
	QString qst;
	QString firstWord;
	QSqlQueryModel properModel;

	i = str.indexOf( ',' )+2;
	qst = str.section(',', 1, 1 ); //grab the section after the first comma
	qst.remove( 0, 1 ); // remove the first blank
	firstWord = qst.section( ' ', 0, 0 );
	properModel.setQuery( QString( "SELECT * FROM Proper WHERE Noun=\'%1\'" )
			.arg( firstWord ) );
	if( properModel.lastError().isValid() )
		str.replace( i, 1, firstWord.left(1).toLower() );
	else if( properModel.rowCount() < 1 )
		str.replace( i, 1, firstWord.left(1).toLower() );

	return( str );
}

QString questClass::RTFformatted( int number )
{
	QString starthead;
    QString startquest;
    QString startspecialquest;
    QString startans;
	QString str;
	
	if( qCshowAnswer )
	{
        if( number > 0 )
        {
//            starthead = QString( "\\fi-360\\li360\\par\\sa0\\keepn\\tab " );
            starthead = QString( "\\par \\pard\\plain\n")
                   .append( "\\keepn\\s0\\ql\\widctlpar{\\*\\hyphen2\\hyphlead2\\hyphtrail2\\hyphmax0}" )
                   .append( "\\ltrpar\\cf0\\hich\\af0\\langfe2052\\dbch\\af0\\afs24\\alang1025" )
                   .append( "\\loch\\f0\\fs24\\lang1033\\nowidctlpar\\tx90\\tx475\\tx835\\sb97" )
                   .append( "\\sa0{\\cf1\\b\\dbch\\af2\\ab\\rtlch \\ltrch\\loch\\loch\\f2\n" )
                   .append( "%1.}{\\dbch\\af2\\rtlch \\ltrch\\loch\\fs20\\loch\\f2\n\\tab }" )
                   .arg( number )
                   .append( "{\\cf1\\b\\dbch\\af2\\ab\\rtlch \\ltrch\\loch\\loch\\f2\n" );
            startspecialquest = QString( "\\par \\pard\\plain\n")
                    .append( "\\keepn\\s0\\ql\\widctlpar{\\*\\hyphen2\\hyphlead2\\hyphtrail2\\hyphmax0}" )
                    .append( "\\ltrpar\\cf0\\hich\\af0\\langfe2052\\dbch\\af0\\afs24\\alang1025" )
                    .append( "\\loch\\f0\\fs24\\lang1033\\nowidctlpar\\tx475\\tx835" )
                    .append( "\\li835\\ri0\\lin835\\rin0\\fi-835" )
                    .append( "{\\dbch\\af2\\rtlch \\ltrch\\loch\\fs20\\loch\\f2\n" )
                    .append( "\\tab }{\\cf1\\b\\dbch\\af2\\ab\\rtlch \\ltrch\\loch\\loch\\f2\n" )
                    .append( "Q:}{\\dbch\\af2\\rtlch \\ltrch\\loch\\fs20\\loch\\f2\n\\tab }" )
                    .append( "{\\cf1\\dbch\\af2\\rtlch \\ltrch\\loch\\loch\\f2\n");
            startquest = QString( "\\par \\pard\\plain\n")
                    .append( "\\keepn\\s0\\ql\\widctlpar{\\*\\hyphen2\\hyphlead2\\hyphtrail2\\hyphmax0}" )
                    .append( "\\ltrpar\\cf0\\hich\\af0\\langfe2052\\dbch\\af0\\afs24\\alang1025" )
                    .append( "\\loch\\f0\\fs24\\lang1033\\nowidctlpar\\tx90\\tx475\\tx835\\sb97" )
                    .append( "\\li835\\ri0\\lin835\\rin0\\fi-835" )
                    .append( "\\sa0{\\cf1\\b\\dbch\\af2\\ab\\rtlch \\ltrch\\loch\\loch\\f2\n" )
                    .append( "%1.}{\\dbch\\af2\\rtlch \\ltrch\\loch\\fs20\\loch\\f2\n\\tab }" )
                    .arg( number )
                    .append( "{\\cf1\\b\\dbch\\af2\\ab\\rtlch \\ltrch\\loch\\loch\\f2\nQ:}" )
                    .append( "{\\dbch\\af2\\rtlch \\ltrch\\loch\\fs20\\loch\\f2\n\\tab }" )
                    .append( "{\\cf1\\dbch\\af2\\rtlch \\ltrch\\loch\\loch\\f2\n");
            startans = QString( "\\par \\pard\\plain\n")
                    .append( "\\keep\\s0\\ql\\widctlpar{\\*\\hyphen2\\hyphlead2\\hyphtrail2\\hyphmax0}" )
                    .append( "\\ltrpar\\cf0\\hich\\af0\\langfe2052\\dbch\\af0\\afs24\\alang1025" )
//                    .append( "\\loch\\f0\\fs24\\lang1033\\nowidctlpar\\tx475\\tx835" )
                    .append( "\\loch\\f0\\fs24\\lang1033\\nowidctlpar\\tx475\\tx1310\\tx1670" )
//                    .append( "\\loch\\f0\\fs24\\lang1033\\nowidctlpar\\tx1310\\tx1670" )
//                    .append( "\\loch\\f0\\fs24\\lang1033\\nowidctlpar\\tx835\\tx1310" )
                    .append( "\\li835\\ri0\\lin835\\rin0\\fi-835" )
                    .append( "{\\dbch\\af2\\rtlch \\ltrch\\loch\\fs20\\loch\\f2\n\\tab }" )
                    .append( "{\\cf1\\b\\dbch\\af2\\ab\\rtlch \\ltrch\\loch\\loch\\f2\nA:}" )
                    .append( "{\\dbch\\af2\\rtlch \\ltrch\\loch\\fs20\\loch\\f2\n\\tab }")
                    .append( "{\\cf1\\dbch\\af2\\rtlch \\ltrch\\loch\\loch\\f2\n");
        }
        else
        {
//            startquest = QString( "\\fi-360\\li360\\par\\sa0\\keepn Q.\\tab " );
//            startans = QString( "\\pard\\par\\sa72\\keep\\fi-360\\li360 A.\\tab " );
            starthead = QString( "\\par \\pard\\plain\n")
                   .append( "\\keepn\\s0\\ql\\widctlpar{\\*\\hyphen2\\hyphlead2\\hyphtrail2\\hyphmax0}" )
                   .append( "\\ltrpar\\cf0\\hich\\af0\\langfe2052\\dbch\\af0\\afs24\\alang1025" )
                   .append( "\\loch\\f0\\fs24\\lang1033\\nowidctlpar\\tx90\\tx475\\tx835\\sb97" )
                   .append( "\\sa0{\\cf1\\b\\dbch\\af2\\ab\\rtlch \\ltrch\\loch\\loch\\f2\n" );
//            .append( "\\sa0{\\dbch\\af2\\rtlch \\ltrch\\loch\\fs20\\loch\\f2\n\\tab }" )
//            .append( "{\\cf1\\b\\dbch\\af2\\ab\\rtlch \\ltrch\\loch\\loch\\f2\n" );
            startspecialquest = QString( "\\par \\pard\\plain\n")
                   .append( "\\keepn\\s0\\ql\\widctlpar{\\*\\hyphen2\\hyphlead2\\hyphtrail2\\hyphmax0}" )
                   .append( "\\ltrpar\\cf0\\hich\\af0\\langfe2052\\dbch\\af0\\afs24\\alang1025" )
                   .append( "\\loch\\f0\\fs24\\lang1033\\nowidctlpar\\tx90\\tx475\\tx835" )
                   .append( "\\li475\\ri0\\lin475\\rin0\\fi-475" )
                   .append( "{\\dbch\\af2\\rtlch \\ltrch\\loch\\fs20\\loch\\f2\n" )
                   .append( "\\tab }{\\cf1\\b\\dbch\\af2\\ab\\rtlch \\ltrch\\loch\\loch\\f2\n" )
                   .append( "Q:}{\\dbch\\af2\\rtlch \\ltrch\\loch\\fs20\\loch\\f2\n\\tab }" )
                   .append( "{\\cf1\\dbch\\af2\\rtlch \\ltrch\\loch\\loch\\f2\n");
            startquest = QString( "\\par \\pard\\plain\n")
                   .append( "\\keepn\\s0\\ql\\widctlpar{\\*\\hyphen2\\hyphlead2\\hyphtrail2\\hyphmax0}" )
                   .append( "\\ltrpar\\cf0\\hich\\af0\\langfe2052\\dbch\\af0\\afs24\\alang1025" )
                   .append( "\\loch\\f0\\fs24\\lang1033\\nowidctlpar\\tx90\\tx475\\tx835\\sb97" )
                   .append( "\\li475\\ri0\\lin475\\rin0\\fi-475" )
                   .append( "\\sa0{\\dbch\\af2\\rtlch \\ltrch\\loch\\fs20\\loch\\f2\n\\tab }" )
                   .append( "{\\cf1\\b\\dbch\\af2\\ab\\rtlch \\ltrch\\loch\\loch\\f2\nQ:}" )
                   .append( "{\\dbch\\af2\\rtlch \\ltrch\\loch\\fs20\\loch\\f2\n\\tab }" )
                   .append( "{\\cf1\\dbch\\af2\\rtlch \\ltrch\\loch\\loch\\f2\n");
            startans = QString( "\\par \\pard\\plain\n")
                   .append( "\\keep\\s0\\ql\\widctlpar{\\*\\hyphen2\\hyphlead2\\hyphtrail2\\hyphmax0}" )
                   .append( "\\ltrpar\\cf0\\hich\\af0\\langfe2052\\dbch\\af0\\afs24\\alang1025" )
                   .append( "\\loch\\f0\\fs24\\lang1033\\nowidctlpar\\tx90\\tx475\\tx1310\\tx1670" )
                   .append( "\\li475\\ri0\\lin475\\rin0\\fi-475" )
                   .append( "{\\dbch\\af2\\rtlch \\ltrch\\loch\\fs20\\loch\\f2\n\\tab }" )
                   .append( "{\\cf1\\b\\dbch\\af2\\ab\\rtlch \\ltrch\\loch\\loch\\f2\nA:}" )
                   .append( "{\\dbch\\af2\\rtlch \\ltrch\\loch\\fs20\\loch\\f2\n\\tab }")
                   .append( "{\\cf1\\dbch\\af2\\rtlch \\ltrch\\loch\\loch\\f2\n");
        }
    }
	else
	{
//		starthead = QString( "\\fi-360\\li360\\par\\sa0\\keepn\\tab " );
//		startquest = QString( "\\pard\\par\\fi-360\\li360\\sa540\\keep Q.\\tab " );
        starthead = QString( "\\par \\pard\\plain\n")
               .append( "\\s0\\ql\\widctlpar{\\*\\hyphen2\\hyphlead2\\hyphtrail2\\hyphmax0}" )
               .append( "\\ltrpar\\cf0\\hich\\af0\\langfe2052\\dbch\\af0\\afs24\\alang1025" )
               .append( "\\loch\\f0\\fs24\\lang1033\\nowidctlpar\\tx90\\tx475\\tx835\\sb97" )
               .append( "\\sa0{\\cf1\\b\\dbch\\af2\\ab\\rtlch \\ltrch\\loch\\loch\\f2\n\\keepn " );
        startquest = QString( "\\par \\pard\\plain\n")
               .append( "\\s0\\ql\\widctlpar{\\*\\hyphen2\\hyphlead2\\hyphtrail2\\hyphmax0}" )
               .append( "\\ltrpar\\cf0\\hich\\af0\\langfe2052\\dbch\\af0\\afs24\\alang1025" )
               .append( "\\loch\\f0\\fs24\\lang1033\\nowidctlpar\\tx90\\tx475\\tx835\\sb97" )
               .append( "\\li475\\ri0\\lin475\\rin0\\fi-475" )
               .append( "\\sa540{\\dbch\\af2\\rtlch \\ltrch\\loch\\fs20\\loch\\f2\n\\tab }" )
               .append( "{\\cf1\\b\\dbch\\af2\\ab\\rtlch \\ltrch\\loch\\loch\\f2\n\\keep Q:}" )
               .append( "{\\dbch\\af2\\rtlch \\ltrch\\loch\\fs20\\loch\\f2\n\\tab }" )
               .append( "{\\cf1\\dbch\\af2\\rtlch \\ltrch\\loch\\loch\\f2\n");
        startspecialquest = QString( "\\par \\pard\\plain\n")
               .append( "\\keepn\\s0\\ql\\widctlpar{\\*\\hyphen2\\hyphlead2\\hyphtrail2\\hyphmax0}" )
               .append( "\\ltrpar\\cf0\\hich\\af0\\langfe2052\\dbch\\af0\\afs24\\alang1025" )
               .append( "\\loch\\f0\\fs24\\lang1033\\nowidctlpar\\tx90\\tx475\\tx835" )
               .append( "\\li475\\ri0\\lin475\\rin0\\fi-475" )
               .append( "\\sa540{\\dbch\\af2\\rtlch \\ltrch\\loch\\fs20\\loch\\f2\n" )
               .append( "\\tab }{\\cf1\\b\\dbch\\af2\\ab\\rtlch \\ltrch\\loch\\loch\\f2\n" )
               .append( "Q:}{\\dbch\\af2\\rtlch \\ltrch\\loch\\fs20\\loch\\f2\n\\tab }" )
               .append( "{\\cf1\\dbch\\af2\\rtlch \\ltrch\\loch\\loch\\f2\n");
    }
	if( qCpreface.length() > 0 )
	{
		qCformatted = starthead;
		qCformatted.append( qCpreface );
        qCformatted.append( " }\n" );
        qCformatted.append( startspecialquest );
    }
	else
    {
		qCformatted.clear();
        qCformatted.append( startquest );
    }
	
	str = qCquestion;
	if( qCrefq )
		str = fixRefCapitalization( str );
    qCformatted.append( RTFkey( str ) );
    qCformatted.append( "}\n" );
    if( qCshowAnswer )
	{
		qCformatted.append( startans );
		qCformatted.append( RTFkey( qCanswer ) );
		if( qCcrossRef.length() > 0 )
		{
			qCformatted.append( " " );
			qCformatted.append( qCcrossRef );
		}
		if( !qCrefq )
		{
			qCformatted.append( " " );
			qCformatted.append( qCreference );
		}
        qCformatted.append( "}\n" );
    }

	return( qCformatted );
}

QString questClass::RTFkey( QString qst )
{
	int i, j, l;
	QString sql, word;
	bool iskey, isalmost;
	
	for( i=0; i<qst.length(); i++ )
	{
		iskey = isalmost = false;
		if( qst.at(i).isLetterOrNumber() )
		{
			for( j=0; j<kModel.rowCount(); j++ )
			{
				word = kModel.record( j ).value( "Word" ).toString(); 
				l = word.length();
				if( qst.mid( i, l ).compare( word ) == 0 )
				{
					iskey = true;
                    qst.insert( i, "\\b " );
					i += 3;
					break;
				}
			}
			if( !iskey )
			{
				for( j=0; j<aModel.rowCount(); j++ )
				{
					word = aModel.record( j ).value( "Word" ).toString(); 
					l = word.length();
					if( qst.mid( i, l ).compare( word ) == 0 )
					{
						isalmost = true;
                        qst.insert( i, "\\i " );
						i += 3;
						break;
					}
				}
			}
			for( i++; i<qst.length(); i++ )
				if( !isSameWord( qst, i ) )
					break;
			if( i == qst.length() )
			{ //if string ends in a key word, e.g. FTV question
				if( isalmost )
                    qst.append( "\\i0 " );
				else if( iskey )
                    qst.append( "\\b0 " );
			}
			else
			{
//				if( !(qst.at(i).isPunct()) )
//					qst.insert( i, " " );
				if( isalmost )
                    qst.insert( i, "\\i0 " );
				else if( iskey )
                    qst.insert( i, "\\b0 " );
			}
		}
	}

	return( qst );
}
