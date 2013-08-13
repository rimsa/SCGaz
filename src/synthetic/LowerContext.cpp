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
#include <synthetic/LowerContext.h>
#include <synthetic/sheet/Queue.h>

/* 
 * Initialize Synthetic Context.
*/
LowerContext::LowerContext(int attr, int objc): SyntheticContext(attr, objc) {
}

/**
 * Destroy Synthetic Context.
*/
LowerContext::~LowerContext( ) {
}

/**
 * Calculate minimun density.   
*/
float LowerContext::minDensity( ) {
  int c;
  int elements = 1;
  int objects = attr;
  int total = attr;
  float den;

  while (objc > objects) {
    elements++;
    c = combination(attr, elements);
    objects += c;
    total += c * elements;
  }

  total -= (objects - objc) * elements;
  den = ((float) total) / (attr * objc);

  return den;
}

/**
 * Calculate maximun density.
*/
float LowerContext::maxDensity( ) {
  int c;
  int elements = attr;
  int objects = 0;
  int total = 0;
  float den;

  while (objc > objects) {
    elements--;
    c = combination(attr, elements);
    objects += c;
    total += c * elements;
  }

  total -= (objects - objc) * elements;
  den = ((float) total) / (attr * objc);

  return den;
}

/**
 * Get row object.
*/
Queue *LowerContext::getObject( ) {
  int i, k;
  int x, c;

  c = x = 0;
  do {
    x += combination(attr, ++c);
  } while (x <= object.n);

  object.obj = new Queue(attr);

  i = 0;
  while (i < c) {
    k = nextPositiveInt( ) % attr;
    if (!object.obj->getValue(k)) {
      if (!object.obj->setValue(1, k))
        i++;
    }
  }

  return object.obj;
}

/**
 * Calculate a combination.
*/
int LowerContext::combination(int n, int p) {
  int tmp, high, low;
  long long up, down;
  
  tmp = n - p;
  high = (tmp > p) ? tmp : p;
  low = (tmp <= p) ? tmp : p;
  
  up = 1;
  while (n > high)
    up *= n--;
  
  down = fatorial(low);
    
  return ((int) (up / down));
}

/**
 * Calculate fatorial.
*/
long long LowerContext::fatorial(int n) {
  long long ret = n;
  if (!n) ret = 1;
  else {
    while ((n - 1) > 0)
      ret *= --n;
  } 
  
  return ret;
} 
