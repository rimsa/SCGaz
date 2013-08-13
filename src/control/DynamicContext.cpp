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

#include <control/DynamicContext.h>
#include <control/StaticContext.h>
#include <exceptions/InputException.h>

/**
 * Set the options.
*/
DynamicContext::DynamicContext(struct dynamic_options &dopt):
                ProcessControl( ) {

  // check every choosen option
  if (dopt.min_attr <= 0)
    throw InputException("Invalid number of minimun attributes"); 
  else if (dopt.max_attr < dopt.min_attr)
    throw InputException("Invalid number of maximun attributes");
  else if (dopt.inc_attr <= 0)
    throw InputException("Invalid number of increase attributes");
  else if (dopt.min_objc <= 0)
    throw InputException("Invalid number of minimum objects");   
  else if (dopt.max_objc < dopt.min_objc)
    throw InputException("Invalid number of maximum objects");
  else if (dopt.objc_mode && dopt.inc_objc <= 0)
    throw InputException("Invalid objects increase rate");
  else if (!dopt.objc_mode && dopt.sample_objc <= 0)
    throw InputException("Invalid objects sample");
  else if (dopt.sample_den <= 0)
    throw InputException("Invalid density sample");
  else if (!dopt.intervals)
    throw InputException("Invalid discretization intervals");

  this->dopt = dopt;
}

/**
 * Responsible to generate all choosen synthetic contexts.
*/
void DynamicContext::process( ) {
  int i, j, n, o;
  float tmp, objc;

  // every attributes possible
  for (i = dopt.min_attr; i <= dopt.max_attr; i += dopt.inc_attr) {
    if (dopt.objc_mode) { // incremental mode
      // every object possible
      for (j = dopt.min_objc; j <= dopt.max_objc; j += dopt.inc_objc) {
        try {
          // make tables with all choosen densities
          processDensity(i, j);
        } catch (bad_alloc &b) {
          cerr << "Unable to allocate memory" << endl;
        } catch (exception &e) {
          cerr << e.what( ) << endl;
        }
      }
    } else { // sample mode
      // if only one sample, use a simple object average
      if (dopt.sample_objc == 1)
        processDensity(i, ((dopt.min_objc + dopt.max_objc) / 2));
      else { // otherwise generate the densities based on how many samples
        tmp = (float) (dopt.max_objc - dopt.min_objc);
        tmp /= (dopt.sample_objc - 1);

        // start with the initial object
        objc = (float) dopt.min_objc;
        o = 0;

        try {
          // every object possible
          for (j = 0; j < (dopt.sample_objc - 1); j++) {
            n = (int) objc;
            if (n > o) {
              // make tables with all choosen densities
              processDensity(i, n);
              o = n;
            }

            // next object
            objc += tmp;
          }

          // process the last object
          if (dopt.max_objc > o)
            processDensity(i, dopt.max_objc);
        } catch (bad_alloc &b) {
          cerr << "Unable to allocate memory" << endl;
        } catch (exception &e) {
          cerr << e.what( ) << endl;
        }
      }
    }
  }
}

/**
 * Responsible to generate synthetic contexts based on the number of
 * density samples.
*/
void DynamicContext::processDensity(int attr, int objc) {
  int i;
  float min, max, tmp, den;
  StaticContext *sc;

  sc = (dopt.total_intervals > 0 ? 
        new StaticContext(attr, objc, dopt.intervals, dopt.total_intervals) :
        new StaticContext(attr, objc) );

  // define verbose mode
  if (verbose)
    sc->setVerbose( );

  // init table
  sc->init( );

  min = sc->getMinDensity( );
  max = sc->getMaxDensity( );

  if (!dopt.den_values) {
    if (dopt.sample_den == 1) {
      sc->setDensity(min);
      sc->process( );
    } else {
      tmp = (max - min) / (dopt.sample_den - 1);
      if (tmp > 0.0) {
        den = min;
        for (i = 0; i < (dopt.sample_den - 1); i++) {
          sc->setDensity(den);
          sc->process( );
          den += tmp;
        }
      }

      sc->setDensity(max);
      sc->process( );
    }
  } else {
    for (i = 0; i < dopt.sample_den; i++) {
      den = dopt.den_values[i];
      if (den >= min && den <= max) {
        sc->setDensity(den);
        sc->process( );
      }
    }
  }
}

