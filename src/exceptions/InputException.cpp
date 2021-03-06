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

#include <exceptions/InputException.h>

/**
 * Define error message.
*/
InputException::InputException(const char *msg) {
  this->msg = msg;
}

/**
 * Exception destructor.
*/
InputException::~InputException( ) throw( ) {
}

/**
 * Get error message.
*/
const char *InputException::what( ) const throw( ) {
  return msg;
}
