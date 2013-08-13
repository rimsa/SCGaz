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

#ifndef _STATIC_CONTEXT_H
#define _STATIC_CONTEXT_H

#include <control/ProcessControl.h>
#include <synthetic/SyntheticContext.h>

/**
 * Class responsible for generating a synthetic context base on atributes,
 * objects and density.
*/
class StaticContext: public ProcessControl {
  private:
    float min, max, den; // table densities
    SyntheticContext *sc; // the synthetic context
    bool initialized; // check wherever synthetic context was initialized
  public:
    /**
     * Initialize synthetic context with attributes and objects.
    */
    StaticContext(int, int);

    /**
     * Initialize synthetic context with attributes and objects with 
     * discretization.
    */
    StaticContext(int, int, int *, int);
    

    /**
     * Destroy synthetic context.
    */
    ~StaticContext( );

    /**
     * Initialize the synthetic context with minimum density.
    */
    void init( );

    /**
     * Set a new density.
    */
    void setDensity(float);

    /**
     * Use minimun density for the context.
    */
    void useMinDensity( );

    /**
     * Use minimun density for the context.
    */
    void useMaxDensity( );

    /**
     * Get synthetic context current density.
    */
    float getDensity( );

    /**
     * Get the synthetic context minimun density.
    */
    float getMinDensity( );

    /**
     * Get the synthetic context minimun density.
    */
    float getMaxDensity( );

    /**
     * Fill the table until reach choosen density.
    */
    void process( );
};

#endif
