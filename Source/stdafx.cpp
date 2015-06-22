/*
 *  Cannon Fodder
 *  ------------------------
 *
 *  Copyright (C) 2008-2015 Robert Crossfield <robcrossfield@gmail.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

#include "stdafx.hpp"

int main(int argc, char *args[]) {

	cFodder* Fodder = new cFodder();

	Fodder->Prepare();
	Fodder->Start();

	delete Fodder;

    return 0;

}

std::string local_PathGenerate( std::string pFile, std::string pPath ) {
	std::stringstream	 filePathFinal;

	if( pPath.size() )
		filePathFinal << pPath << "/";

	filePathFinal << pFile;

	return filePathFinal.str();
}

uint8 *local_FileRead( std::string pFile, std::string pPath, size_t	&pFileSize ) {
	std::ifstream*		fileStream;
	uint8*				fileBuffer = 0;

	std::string finalPath = local_PathGenerate( pFile, pPath );

	// Attempt to open the file
	fileStream = new std::ifstream ( finalPath.c_str(), std::ios::binary );
	if (fileStream->is_open() != false) {

		// Get file size
		fileStream->seekg( 0, std::ios::end );
		pFileSize = (size_t)fileStream->tellg();
		fileStream->seekg( std::ios::beg );

		// Allocate buffer, and read the file into it
		fileBuffer = new uint8[pFileSize];
		fileStream->read( (char*)fileBuffer, pFileSize );
		if (!(*fileStream)) {
			delete fileBuffer;
			fileBuffer = 0;
		}

	} else {

	}

	// Close the stream
	fileStream->close();
	delete fileStream;

	// All done ;)
	return fileBuffer;
}

void tool_EndianSwap( uint8 *pBuffer, size_t pSize ) {
	uint8 *pDest = pBuffer;
	
	pSize /= 2;

	while( pSize-- ) {
		uint8 al = *pBuffer++;
		uint8 ah = *pBuffer++;

		*pDest++ = ah;
		*pDest++ = al;
	}
}