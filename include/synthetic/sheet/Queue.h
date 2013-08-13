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

#ifndef _QUEUE_H
#define _QUEUE_H

#include <iostream>

using namespace std;

/**
 * Represents a line on a table.
*/
class Queue {
  private:
    int width;          // the width of the line
    int filled;         // how many elements are present
    unsigned int *line; // the line

    bool ctxMode;       // used to know how to print on stream

    /**
     * Verifies two queues for equality.
    */
    friend int equals(Queue *, Queue &);
  public:
    /**
     * Initializa the line with empty values.
    */
    Queue(int);

    /**
     * Create a new queue based on an image of another.
    */
    Queue(const Queue &);

    /**
     * Destroy the line.
    */
    ~Queue( );

    /**
     * Set a value in a position of line.
    */
    int setValue(int, int);

    /**
     * Get the value of the position on line.
    */
    int getValue(int);

    /**
     * Get the size of the line.
    */
    int getSize( );

    /**
     * Get the number of used positions.
    */
    int getFilled( );

    /**
     * Get the density of the line.
    */
    float getDensity( );

    /**
     * All position are unused.
    */
    int empty( );

    /**
     * All positions are used.
    */
    int full( );

    /**
     * Restart all used positions.
    */
    void reset( );

    /**
     * Set output mode type.
    */
    void setContextMode(bool);

    /**
     * Print line to stream.
     * If in context mode writes blank spaces for unused positions and "X"
     * for used, otherwise print "0" for unused and "1" for used.
    */
    friend ostream &operator<<(ostream &, Queue &);

    /**
     * Perform a queue copy.
    */
    Queue &operator=(const Queue &);

    /**
     * Check if equal.
    */
    int operator==(Queue &);

    /**
     * Check if not equal.
    */
    int operator!=(Queue &);

    /**
     * Threat the line as bits and do a bitwise incrementation.
    */
    Queue &operator++( );

    /**
     * Threat the line as bits and do a bitwise decrementation.
    */
    Queue &operator--( );

    /**
     * Negate the line, every used position turns unused and vice-versa.
    */
    Queue &operator~(void);
};


#endif
