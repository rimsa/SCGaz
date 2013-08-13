/**
 * This file is part of SCGaz.
 *
 * SCGaz is free software; you can redistribute it and/or modify it under 
 * the terms of the GNU General Public License as published by the Free 
 * Software Foundation; either version 2 of the License, or (at your option) 
 * any later version.
 *
 * SCGaz is distributed in the hope that it will be useful, but WITHOUT ANY 
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS 
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more 
 * details.
 * 
 * You should have received a copy of the GNU General Public License along 
 * with SCGaz; if not, write to the Free Software Foundation, Inc., 51 
 * Franklin St, Fifth Floor, Boston, MA 02110-1301 USA 
*/

#include <cstdio>
#include <iostream>
#include <log/LogHandler.h>
#include <synthetic/sheet/Table.h>

#define MAX_FILE_SIZE 1024

using namespace std;

char *LogHandler::ctxName = NULL;  // context base name
int LogHandler::ctxCount = 1;      // number of generated contexts (for dynamic usage)

/**   
 * Set the base name of the context output.
*/
void LogHandler::setContextOutput(char *ctxName) {
  if (ctxName) { // if valid name
    LogHandler::ctxName = ctxName;
    ctxCount = 1;
  }
}

/**
 * Write the context output.
 * with the name: "{ctxName}{ctxCount}.ctx".
*/
void LogHandler::writeContext(Table &t) {
  int i;
  char name[MAX_FILE_SIZE];

  if (ctxName) {
    // output the format
    snprintf(name, MAX_FILE_SIZE, "%s%d.cxt", ctxName, ctxCount);

    // create the output
    ofstream *ofs = new ofstream(name, (ios_base::out | ios_base::trunc));

    // write it
    *ofs << "B" << endl;
    *ofs << endl;
    *ofs << t.getHeight( ) << endl;
    *ofs << t.getWidth( ) << endl;
    *ofs << endl;

    // insert the names of objects
    for (i = 0; i < t.getHeight( ); i++)
      *ofs << "object[" << i << "]" << endl;

    // insert the name of attributes
    for (i = 0; i < t.getWidth( ); i++)
      *ofs << "attribute[" << i << "]" << endl;

    // define the print mode and print it on file
    t.setContextMode(true);
    *ofs << t;
    t.setContextMode(false);

    // close the file
    ofs->close( );

    delete ofs;

    // increment to create the new output file
    ctxCount++;
  }
}
