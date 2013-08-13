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

#include <stdlib.h>
#include <time.h>
#include <random/RandomHandler.h>

void initRandom( ) {
  srand(time(NULL));
}

short nextShort( ) {
  return rand( );
}

short nextPositiveShort( ) {
  return (nextShort( ) & 0x7FFF);
}

int nextInt( ) {
#ifdef WIN32
  return (((rand( ) & 0xFFFF) << 16) | (rand( ) & 0xFFFF)); // low entropy, need FIX
#else
  return rand( );
#endif
}

int nextPositiveInt( ) {
  return (nextInt( ) & 0x7FFFFFFF);
}
