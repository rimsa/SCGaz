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
#include <cmath>

#include <random/RandomHandler.h>
#include <progress/ProgressHandler.h>
#include <synthetic/SyntheticContext.h>
#include <exceptions/InputException.h>
#include <exceptions/DensityException.h>
#include <exceptions/ValidationException.h>

#define MAX_RAND_TRIES 1000

/**
 * Initialize synthetic context.
*/
SyntheticContext::SyntheticContext(int attr, int objc) {
  float max;

  // check attributesd
  if (attr <= 0) {
    throw InputException("Invalid number of attributes");
  } else if (objc <= 0) { // check objects
    throw InputException("Invalid number of objects");
  } else if (objc < attr) {
    if (objc < 2)
      throw InputException("Invalid number of objects");
  } else if (objc > attr) {
    max = pow(2.0, attr) - 2; // check objects limit
    if (objc > max)
      throw InputException("Invalid number of objects");
  }

  // set values
  this->attr = attr;
  this->objc = objc;

  // create table
  table = new Table(attr, objc);

  // first row
  object.obj = NULL;
  object.n = 0;

  // not used at least one density
  one = false;

  // table not full
  full = false;

  // first density
  lastden = 0.0;

  // not verbosed
  verbose = false;
}

/**
 * Destroy synthetic context. 
*/
SyntheticContext::~SyntheticContext( ) {
  delete table;
}

/**
 * Initializa table with minimun density.
*/
void SyntheticContext::initTable( ) {
  int pos;
  Queue *q;
  bool used[objc];
  ProgressHandler *ph = NULL;

  if (verbose)
    // start progress info
    ph = new ProgressHandler(objc);

  // clean up
  memset(used, 0, (sizeof(bool) * objc));

  // while has more rows
  while (this->hasMoreObjects( )) {
    do {
      // random position
      pos = nextPositiveInt( ) % objc;
    } while (used[pos]); // until find an unused

    // get row
    q = this->getObject( );

    // try adding row
    if (!table->setLine(*q, pos)) {
      used[pos] = true;
      this->nextObject( );
    }

    if (verbose)
      ph->run(object.n);

    // free object
    delete q;
  }

  // delete progress info
  if (verbose)
    delete ph;

  // validate table
  if (!table->validate( ))
    throw ValidationException("Unable to validate table");

  // set min and max densities
  min = this->minDensity( );
  max = this->maxDensity( );
}

/**
 * Fill table until reach choosen density.
*/
void SyntheticContext::fillTable(float den) {
  int n;
  int row, col;
  bool found, changed;
  float act;
  ProgressHandler *ph = NULL;

  // must be valid
  if (!table->isValid( ))
    throw ValidationException("Invalid table");

  // check density
  if (den < (min - 0.000001) || den > (max + 0.000001))
    throw DensityException("Invalid density: %f", den);

  // is already full
  if (full)
    throw DensityException("Reached already the maximun possible density");

  // was density already used
  if (den <= lastden)
    throw DensityException("Already achieved density");

  // update last density
  lastden = den;

  if (verbose)
    // start progress info
    ph = new ProgressHandler(den - min);

  // was table changed
  changed = false;

  // fill table until reach density or until is full
  while ((table->getDensity( ) + 0.000001) < den && !full) {
    n = 0; // number of tries
    found = false;

    // give a try to randomly choose a row and a column to fill
    // this optimizates the filling process
    do {
      // select random row and col
      row = nextPositiveInt( ) % objc;
      col = nextPositiveInt( ) % attr;

      // is possible to fill
      if (!table->getValue(row, col))
        // try filling
        found = (table->setValue(1, row, col) >= 0);

      // update counter
      n++;
    } while (n < MAX_RAND_TRIES && !found); // until found or exaust possibilities

    // brute time
    if (!found) {
      // try finding row and column to fill
      if (table->setValue(1) < 0) // unable to find
        full = true; // table is full
      else
        found = true;
    }

    // filled a position
    if (found) {
      // the table is changed
      changed = true;

      if (verbose) {
        // show some output
        act = table->getDensity( );
        if (act < den)
          ph->run(act - min);
      }
    }
  }

  if (verbose)
    // delete progress info
    delete ph;

  // check if full
  if (!changed && full && one)
    throw DensityException("Reached already the maximun possible density");

  // one done
  one = true;
}

/**
 * Inform to aquire next object.
*/
void SyntheticContext::nextObject( ) {
  object.n++;
}

/**
 * Has more objects to get.
*/
bool SyntheticContext::hasMoreObjects( ) {
  return (object.n < objc);
}  

/**
 * Get attributes.
*/
int SyntheticContext::getAttributes( ) {
  return attr;
}

/**
 * Get objects.
*/
int SyntheticContext::getObjects( ) {
  return objc;
}

/**
 * Get density.   
*/
float SyntheticContext::getDensity( ) {
  return table->getDensity( );
}

  
/**
 * Get synthetic context table representation.
*/
Table *SyntheticContext::getTable( ) {
  return table;
}

/**
 * Use verbose output.
*/
void SyntheticContext::setVerbose( ) {
  verbose = true;
}
