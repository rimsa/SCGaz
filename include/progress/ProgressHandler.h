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

#ifndef _PROGRESS_HANDLER_H
#define _PROGRESS_HANDLER_H

#define MAX_RATE 100

/**
 * Handler progress of table operations like initting and filling.
*/
class ProgressHandler {
  private:
    float total; // progress full value
  public:
    /**
     * Set total progress value.
    */
    explicit ProgressHandler(float);

    /**
     * Destructor.
    */
    ~ProgressHandler( );

    /**
     * Calculate progress over total progress value.
    */
    void run(float);
};

#endif
