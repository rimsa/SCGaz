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

#ifndef _TABLE_H
#define _TABLE_H

#include <synthetic/sheet/Queue.h>

/**
 * The synthetic context table.
*/
class Table {
  private:
    int width;       // width of table
    int height;      // height of table
    bool validated;  // indicates if the table is valid conform AFC
    bool ctxMode;    // type of stream print

    Queue **lines;   // heights

    /**
     * Check if column is empty.
    */
    int emptyColumn(int);

    /**
     * Check if column is full.
    */
    int fullColumn(int);

    /**
     * Check if row is empty.
    */
    int emptyRow(int);

    /**
     * Check if row is full.
    */
    int fullRow(int);

    /**
     * Check if table has a duplicated row.
    */
    int duplicatedRow(int, int *);
  public:
    /**
     * Startup the table.
    */
    explicit Table(int, int);

    /**
     * Free table.
    */
    ~Table( );

    /**
     * Get the width of table.
    */
    int getWidth( );

    /**
     * Get height of table.
    */
    int getHeight( );

    /**
     * Get table density.
    */
    float getDensity( );

    /**
     * Get row density.
    */
    float getDensity(int);

    /**
     * Get row filled values.
    */
    int getFilled(int);

    /**
     * Get value in row and column.
    */
    int getValue(int, int);

    /**
     * Set value in row and column.
    */
    int setValue(int, int, int);

    /**
     * Set value in a randomly picked column.
    */
    int setValue(int, int);

    /**
     * Set value in randomly picked column and row.
    */
    int setValue(int);

    /**
     * Set a line in a row.
    */
    int setLine(Queue &, int);

    /**
     * Validate table if it's without empty column or rows.
    */
    bool validate( );

    /**
     * Check whenever table is valid.
    */
    bool isValid( );

    /**
     * Type of output.
    */
    void setContextMode(bool);

    /**
     * Print the output on stream.
    */
    friend ostream &operator<<(ostream &, Table &);
};

#endif
