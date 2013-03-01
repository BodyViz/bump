/**
 *  TextFileReader.h
 *  SOMViz
 *
 *  Created by Joseph Holub on 2/1/13.
 *  Copyright 2013 Iowa State University. All rights reserved.
 */

#ifndef BUMP_TEXT_FILE_READER_H
#define BUMP_TEXT_FILE_READER_H


#include <bump/Export.h>
#include <bump/String.h>
#include <boost/shared_ptr.hpp>

namespace bump {

/**
 * This class should be a collection of static methods that
 * implement reading in a file. Formating of the data should
 * not occur here, just the reading of the file and grabbing
 * of lines.
 *
 * The first line of the file should be requested as 1.
 **/
namespace TextFileReader {
	
	/* Read entire file and place in StringList and return pointer or ref */
    BUMP_EXPORT boost::shared_ptr<StringList> returnFileContents(const String fileName) ;
    
	/* Read first line of the file and return String */
    BUMP_EXPORT bump::String returnFirstLine(const String fileName) ;
    
	/* Read first numLines number of lines of a file and return */
    BUMP_EXPORT boost::shared_ptr<StringList> returnFirstNLines(const String fileName, const int numLines);
    
	/* Read numLines number of lines starting at line begginningLine (lines start at nuber 0) */
    BUMP_EXPORT boost::shared_ptr<StringList> returnNLinesStartingAtM(const String fileName, const int beginningLine, const int numLines);
	
	/* Read the rest of the file starting at line begginningLine through the end of the file */
	BUMP_EXPORT boost::shared_ptr<StringList> returnLineNThroughEnd(const String fileName, const int beginningLine);
	
	/* Returns the number of lines in the file or -1 if there was an error */
	BUMP_EXPORT int numberOfLines(const String fileName);
    
    
    /* Reads from the file at the beginning line for the number of lines (numLines = -1 for the entire file) */
    //static boost::shared_ptr<bump::StringList> readFileLines(const bump::String, const int beginningLine, const int numLines);
    
}	// End of TextFileReader namespace
	
}	// End of bump namespace

#endif  // End of __TextFileReader__
