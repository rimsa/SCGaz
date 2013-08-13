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

#ifndef _DYNAMIC_CONTEXT_H
#define _DYNAMIC_CONTEXT_H

#include <control/ProcessControl.h>

/* dynamic options */
struct dynamic_options {
  int min_attr, max_attr, inc_attr; // min, max e increase attributes rate
  int min_objc, max_objc; // min and max number of objects
  bool objc_mode;         // objects increase strategy
  union {
    int inc_objc;         // fixed increase objects rate
    int sample_objc;      // number of objects samples
  };
  int *intervals;         // discretization intervals
  int total_intervals;    // total intervals count
  int sample_den;         // number of density samples
  float *den_values;      // density sample values
};

/**
 * Class to generate serveral synthetic contexts dynamicly.
*/
class DynamicContext: public ProcessControl {
  private:
    struct dynamic_options dopt; // options

    /**
     * Responsible to generate synthetic contexts based on the number of 
     * density samples.
    */
    void processDensity(int, int);
  public:
    /**
     * Set the options.
    */
    explicit DynamicContext(struct dynamic_options &);

    /**
     * Responsible to generate all choosen synthetic contexts.
    */
    void process( );
};

#endif
