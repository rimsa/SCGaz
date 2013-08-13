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

#ifndef _SYNTHETIC_CONTEXT_H
#define _SYNTHETIC_CONTEXT_H

#include <synthetic/sheet/Table.h>

// table rows
struct Object {
  Queue *obj;
  int n;
};

/**
 * The synthetic context.
 * Updates the table with given density.
*/
class SyntheticContext {
  protected:
    int attr; // number of attributes
    int objc; // number of objects

    float min; // minimun density
    float max; // maximun density

    Table *table; // the table representation

    struct Object object; // used to initialize table

    bool one; // at least one density used
    bool full; // table is full

    float lastden; // the last used density

    bool verbose; // verbose output
  public:
    /**
     * Initialize synthetic context.
    */
    explicit SyntheticContext(int, int);

    /**
     * Destroy synthetic context.
    */
    virtual ~SyntheticContext( );

    /**
     * Initializa table with minimun density.
    */
    void initTable( );

    /**
     * Fill table until reach choosen density.
    */
    virtual void fillTable(float);

    /**
     * Get table's calculated minimum density.
    */
    virtual float minDensity( ) = 0;

    /**
     * Get table's calculated maximun density.
    */
    virtual float maxDensity( ) = 0;

    /**
     * Get row object.
    */
    virtual Queue *getObject( ) = 0;

    /**
     * Inform to aquire next object.
    */
    void nextObject( );

    /**
     * Has more objects to get.
    */
    bool hasMoreObjects( );

    /**
     * Get attributes.
    */
    int getAttributes( );

    /**
     * Get objects.
    */
    int getObjects( );

    /**
     * Get density.
    */
    float getDensity( );

    /** 
     * Get synthetic context table representation.
    */
    Table *getTable( );

    /**
     * Use verbose output.
    */
    void setVerbose( );
};

#endif
