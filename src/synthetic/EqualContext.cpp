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

#include <progress/ProgressHandler.h>
#include <synthetic/SyntheticContext.h>
#include <synthetic/EqualContext.h>

/**
 * Initialize Synthetic Context.
*/
EqualContext::EqualContext(int attr): SyntheticContext(attr, attr) {
}

/**
 * Destroy Synthetic Context.
*/
EqualContext::~EqualContext( ) {
}

/**
 * Calculate maximun density.
*/
float EqualContext::minDensity( ) {
  return (1.0 / attr);
}

/**
 * Calculate maximun density.
*/
float EqualContext::maxDensity( ) {
  return (((float) (attr - 1)) / attr);
}

/**
 * Get row object.
*/
Queue *EqualContext::getObject( ) {
  object.obj = new Queue(attr);
  object.obj->setValue(1, object.n);
  return object.obj;
}
