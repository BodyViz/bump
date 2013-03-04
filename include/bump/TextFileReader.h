//
//  TextFileReader.h
//  Bump
//
//  Created by Joseph Holub on 2/1/13.
//  Copyright (c) 2012 Joseph Holub. All rights reserved.
//

#ifndef BUMP_TEXT_FILE_READER_H
#define BUMP_TEXT_FILE_READER_H


#include <bump/Export.h>
#include <bump/String.h>

namespace bump {
	
/**
 * The TextFileReader is a collection of static methods that
 * implement reading from a text file. The functions will
 * return the contents of the file as a bump::String or 
 * bump::StringList where each bump::String in the bump::StringList
 * is one line of data in the text file.
 *
 * File line counting starts at 1. So if you want to start
 * at the second line in the file, beginningLine should be
 * set to 2.
 */
namespace TextFileReader {
	
	/**
	 * Returns the entire contents of the text file.
	 *
	 * Each String in the returned StringList is one
	 * line of the text file.
	 *
	 * @param fileName The text file's name and/or path
	 * @return The entire contents of the file with each String being one line from the file
	 */
    BUMP_EXPORT StringList fileContents(const String& fileName) ;
	
	/**
	 * Returns the contents of the text file starting at
	 * the specified beginningLine and reading numLines.
	 *
	 * If the number of lines requested is more than the end
	 * of the file, this function will read until the end of
	 * file and then return.
	 *
	 * @param fileName The text file's name and/or path
	 * @param beginningLine The line to start reading from
	 * @param numLines The number of lines to read
	 * @return The requested contents of the file with each String being one line from the file
	 */
    BUMP_EXPORT StringList fileContents(const String& fileName, const int& beginningLine, const int& numLines);
	
	/**
	 * Returns the contents of the text file starting at
	 * the specified beginningLine and reading until end of
	 * file is reached.
	 *
	 * @param fileName The text file's name and/or path
	 * @param beginningLine The line to start reading from
	 * @return The requested contents of the file with each String being one line from the file
	 */
	BUMP_EXPORT StringList fileContents(const String& fileName, const int& beginningLine);
    
	/**
	 * Returns the first line of the text file
	 *
	 * @param fileName The text file's name and/or path
	 * @return The first line of the file
	 */
    BUMP_EXPORT String firstLine(const String& fileName) ;
    
	/**
	 * Returns the header of the file. The size of the file header
	 * must be specified.
	 *
	 * @param fileName The text file's name and/or path
	 * @param numLines The number of lines making up the header
	 * @return The header lines from the file with each String being one line
	 */
    BUMP_EXPORT StringList header(const String& fileName, const int& numLines);
	
	/**
	 * Returns the footer of the file. The size of the file footer
	 * must be specified.
	 *
	 * @param fileName The text file's name and/or path
	 * @param numLines The number of lines making up the footer
	 * @return The footer lines from the file with each String being one line
	 */
	BUMP_EXPORT StringList footer(const String& fileName, const int& numLines);

	/**
	 * Returns the number of line in the file or -1 if there was an error
	 *
	 * @param fileName The text file's name and/or path
	 * @return The number of lines in the file or -1 if an error occured
	 */
	BUMP_EXPORT int numberOfLines(const String& fileName);
    
}	// End of TextFileReader namespace
	
}	// End of bump namespace

#endif	// End of BUMP_TEXT_FILE_READER_H
