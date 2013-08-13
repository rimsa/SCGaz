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

#include <random/RandomHandler.h>
#include <progress/ProgressHandler.h>
#include <synthetic/SyntheticContext.h>
#include <synthetic/HigherContext.h>

/*
 * Initialize Synthetic Context.
*/
HigherContext::HigherContext(int attr, int objc): SyntheticContext(attr, objc) {
  int i, j, pos;
  int *tmp;

  j = attr;
  tmp = new int [attr];
  for (i = 0; i < attr; i++)
    tmp[i] = i;

  optmap = new int [attr];

  for (i = 0; i < objc; i++) {
    pos = nextPositiveInt( ) % j;
    optmap[tmp[pos]] = i;
    tmp[pos] = tmp[--j];
  }

  while (j > 0)
   optmap[tmp[--j]] = nextPositiveInt( ) % objc;

  delete tmp;
}

/**
 * Destroy Synthetic Context.
*/
HigherContext::~HigherContext( ) {
  delete optmap;
}

/**
 * Calculate minimun density.
*/
float HigherContext::minDensity( ) {
  return (1.0 / objc);
}

/**
 * Calculate maximun density.
*/
float HigherContext::maxDensity( ) {
  return (((float) (objc - 1)) / objc);
}

/**
 * Get row object.
*/
Queue *HigherContext::getObject( ) {
  int i;

  object.obj = new Queue(attr);
  for (i = 0; i < attr; i++) {
    if (optmap[i] == object.n)
      object.obj->setValue(1, i);
  }

  return object.obj;
}
