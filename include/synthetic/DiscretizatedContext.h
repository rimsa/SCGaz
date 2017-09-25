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

#ifndef _DISCRETIZATED_CONTEXT_H
#define _DISCRETIZATED_CONTEXT_H

#include <synthetic/SyntheticContext.h>

/**
 * Synthetic Context with attributes equal to objects.
*/
class DiscretizatedContext: public SyntheticContext {
  private:
    int attributes;       // discretization attributes
    int *intervals;       // the discretization intervals
    int total_intervals;  // discretization total count

    /**
     * Unique density.
    */
    float density( );
  public:
    /**
     * Initialize Synthetic Context.
    */
    explicit DiscretizatedContext(int, int, int *, int);

    /**
     * Destroy Synthetic Context.
    */
    ~DiscretizatedContext( );

    /**
     * Calculate minimun density.
    */
    float minDensity( );

    /**
     * Calculate maximun density.
    */
    float maxDensity( );

    /**
     * Get row object.
    */
    Queue *getObject( );

    /**
     * Special filling table.
    */
    void fillTable(float);
};

#endif
