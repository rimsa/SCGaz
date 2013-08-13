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

#ifndef _DENSITY_EXCEPTION_H
#define _DENSITY_EXCEPTION_H

#include <exception>

#define MAX_MSG_SIZE 1024

/**
 * Handle density exceptions.
 */
class DensityException: public std::exception {
  private:
    char msg[MAX_MSG_SIZE]; // the error message
  public:
    /**
     * Define error message.
    */
    explicit DensityException(const char *, ...);

    /**
     * Exception destructor.
    */
    ~DensityException( ) throw( );

    /**
     * Get error message.
    */
    const char *what( ) const throw( );
};

#endif
