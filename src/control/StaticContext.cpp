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
#include <log/LogHandler.h>
#include <control/StaticContext.h>
#include <synthetic/SyntheticContext.h>
#include <synthetic/LowerContext.h>
#include <synthetic/EqualContext.h>
#include <synthetic/HigherContext.h>
#include <synthetic/DiscretizatedContext.h>
#include <synthetic/sheet/Table.h>
#include <exceptions/InitException.h>
#include <exceptions/InputException.h>
#include <exceptions/DensityException.h>

/**
 * Initialize synthetic context with attributes and objects.
*/
StaticContext::StaticContext(int attr, int objc): ProcessControl( ) {
  // choose type of table based on attributes and objects
  if (attr < objc)
    sc = new LowerContext(attr, objc);
  else if (attr == objc)
    sc = new EqualContext(attr);
  else
    sc = new HigherContext(attr, objc);

  // define min and max densities
  min = sc->minDensity( );
  max = sc->maxDensity( );

  // show some stats
  cout << "Attributes: " << attr << endl;
  cout << "Objects: " << objc << endl;
  cout << "Minimun density: " << min << endl;
  cout << "Maximun density: " << max << endl;
  cout << endl;

  // start the table with the min density
  den = min;

  // must be initialized
  initialized = false;
}

/**
 * Initialize synthetic context with attributes and objects with
 * discretizations.
*/
StaticContext::StaticContext(int attr, int objc, int *discretizations,
                             int levels): ProcessControl( ) {
  // initialize object
  sc = new DiscretizatedContext(attr, objc, discretizations, levels);

  // define min and max densities
  min = sc->minDensity( );
  max = sc->maxDensity( );

  // show some stats
  cout << "Attributes: " << attr << endl;
  cout << "Objects: " << objc << endl;
  cout << "Minimun density: " << min << endl;
  cout << "Maximun density: " << max << endl;
  cout << endl;

  // start the table with the min density
  den = min;

  // must be initialized
  initialized = false;
}

/**
 * Destroy synthetic context.
*/
StaticContext::~StaticContext( ) {
  delete sc;
}

/**
 * Initialize the synthetic context with minimum density.   
*/
void StaticContext::init( ) {
  if (verbose) {
    sc->setVerbose( );
    std::cout << "Initting table" << std::endl;
  }

  // initializa table
  sc->initTable( );

  // may be processed
  initialized = true;

  // print new line
  if (verbose)
    std::cout << std::endl;
}

/**
 * Set a new density.
*/
void StaticContext::setDensity(float den) {
  // check if density is valid
  if (den < (min - 0.000001) || den > (max + 0.000001))
    throw DensityException("Invalid density: %f", den);

  this->den = den;
}

/**
 * Use minimun density for the context.
*/
void StaticContext::useMinDensity( ) {
  this->den = min;
}

/**
 * Use minimun density for the context.
*/
void StaticContext::useMaxDensity( ) {
  this->den = max;
}

/**
 * Get synthetic context current density.
*/
float StaticContext::getDensity( ) {
  return den;
}

/**
 * Get the synthetic context minimun density.
*/
float StaticContext::getMinDensity( ) {
  return min;
}

/**
 * Get the synthetic context minimun density.
*/
float StaticContext::getMaxDensity( ) {
  return max;
}

/**
 * Fill the table until reach choosen density.
*/
void StaticContext::process( ) {
  Table *t;

  // must be initialized
  if (!initialized)
    throw InitException("Uninitialized context table");

  if (verbose) {
    std::cout << "Filling table" << std::endl;
  }

  // fill the table
  sc->fillTable(den);

  // print new line
  if (verbose) 
    std::cout << std::endl;

  // get the table
  t = sc->getTable( );

  // write the context table in the FCA format
  LogHandler::writeContext(*t);

  // print some output information
  std::cout << "Filled table with " << t->getWidth( ) << " attributes and ";
  std::cout << t->getHeight( ) << " objects with density of ";
  std::cout << t->getDensity( ) << std::endl;
  std::cout << std::endl;
}
