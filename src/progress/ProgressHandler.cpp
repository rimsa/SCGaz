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

using namespace std;

/**
 * Set total progress value.
*/
ProgressHandler::ProgressHandler(float total) {
  this->total = total;

  // print start progress
  cout << "\rDone: 0%" << flush;
}

/**
 * Destructor.
*/
ProgressHandler::~ProgressHandler( ) {
  // print final progress
  cout << "\rDone: 100%" << endl << flush;
}

/**
 * Calculate progress over total progress value.
*/
void ProgressHandler::run(float x) {
  int n;
  static int rate = MAX_RATE;

  if (!--rate) { // do not print every time on screen
    n = (int) ((x * 100) / total); // calculate progress
    if (n >= 0 && n <= 100) // check progress over 
      cout << "\rDone: " << n << "%" << flush; // print progress

    // recount max rate  
    rate = MAX_RATE;
  }
}
