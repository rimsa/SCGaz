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

#ifndef _LOWER_CONTEXT_H
#define _LOWER_CONTEXT_H

#include <synthetic/SyntheticContext.h>

/**
 * Synthetic Context with more objects than attributes.
*/
class LowerContext: public SyntheticContext {
  private:
    /**
     * Calculate a combination.
    */
    int combination(int, int);

    /**
     * Calculate fatorial.
    */
    long long fatorial(int);
  public:
    /*
     * Initialize Synthetic Context.
    */
    explicit LowerContext(int, int);

    /**
     * Destroy Synthetic Context.
    */
    ~LowerContext( );

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
};

#endif
