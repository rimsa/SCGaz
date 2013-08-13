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

#include <iostream>

#include <random/RandomHandler.h>
#include <progress/ProgressHandler.h>
#include <synthetic/SyntheticContext.h>
#include <synthetic/DiscretizatedContext.h>
#include <exceptions/InputException.h>
#include <exceptions/DensityException.h>

/**
 * Initialize Synthetic Context.
*/
DiscretizatedContext::DiscretizatedContext(int attr, int objc, 
int *intervals, int total_intervals): SyntheticContext(total_intervals, objc) {
  int i;
  uint64_t tmp, big;

  // check valid levels
  if (total_intervals <= 0)
    throw InputException("Invalid number of discretization levels");

  // calculate total discretization levels and max permitted objects
  tmp = (uint64_t) 1;
  for (i = 0; i < attr; i++) {
    if (intervals[i] <= 0)
      throw InputException("Invalid discretization interval");

    tmp *= (uint64_t) intervals[i];
  }

  big = (uint64_t) objc;
  // check object correctness
  if (big > tmp)
    throw InputException("Invalid number of objects");

  // has used at least one table
  one = false;

  // define global values
  this->intervals = intervals;
  this->total_intervals = total_intervals;

  // attributes
  attributes = attr;
}

/**
 * Destroy Synthetic Context.
*/
DiscretizatedContext::~DiscretizatedContext( ) {
}

/**
 * Unique density.
*/
float DiscretizatedContext::density( ) {
  float f = (float) attributes;
  return (f / total_intervals);
}

/**
 * Calculate minimum density.
*/
float DiscretizatedContext::minDensity( ) {
  return density( );
}

/**
 * Calculate maximun density.
*/
float DiscretizatedContext::maxDensity( ) {
  return density( );
}

/**
 * Get row object.
*/
Queue *DiscretizatedContext::getObject( ) {
  int i;
  int pos, offset;

  /* return object */
  object.obj = new Queue(total_intervals);

  /* start position */
  pos = 0;

  /* fill a position in each discretization interval */
  for (i = attributes; i > 0; i--) {
    /* use a random position on discretization interval */
    offset = nextPositiveInt( ) % intervals[i - 1];

    /* set the value */
    object.obj->setValue(1, (pos + offset));

    /* next discretization interval */
    pos += intervals[i - 1];
  }

  /* return discretizated object */
  return object.obj;
}

/**
 * Special filling table.
*/
void DiscretizatedContext::fillTable(float den) {
  if (one)
    throw DensityException("Reached already the maximun possible density");

  one = true;
}
