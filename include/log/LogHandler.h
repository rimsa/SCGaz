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

#ifndef _LOG_HANDLER_H
#define _LOG_HANDLER_H

#include <fstream>
#include <synthetic/sheet/Table.h>

using namespace std;

/**
 * Log context output and log BDD information.
*/
class LogHandler {
  private:
    static char *ctxName; // context base name
    static int ctxCount;  // number of generated contexts (for dynamic usage)
  public:
    /**
     * Set the base name of the context output.
    */
    static void setContextOutput(char *);

    /**
     * Write the context output.
     * with the name: "{ctxName}{ctxCount}.ctx".
    */
    static void writeContext(Table &);
};

#endif
