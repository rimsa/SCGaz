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

#ifndef _TIME_HANDLER_H
#define _TIME_HANDLER_H

#include <fstream>
#include <sys/time.h>

#ifdef WIN32
#include <sys/timeb.h>

// unix timezone compactible struct
struct timezone {
  int tz_minuteswest; /* minutes west of Greenwich */
  int tz_dsttime;     /* type of dst correction */
};

/**
 * Windows compatible unix's gettimeofday.
*/
int gettimeofday (struct timeval *tv, struct timezone *tz);

#endif

using namespace std;

class TimeHandler {
  private:
    struct timeval tv; // hold time info

    /**
     * Substract TimeHandler from this class.
    */
    void minus(TimeHandler *);

  public:
    /**
     * Initialize time.
    */
    TimeHandler(int, int);

    /**
     * Destroy time handler.
    */
    ~TimeHandler( );

    /**
     * Get secounds.
    */
    int getSecounds( );

    /**
     * Get millisecounds.
    */
    int getMiliSecounds( );

    /**
     * Get time of given class.
    */
    static double getTime(TimeHandler *);

    /**
     * Get time of this class.
    */
    double getTime( );

    /**
     * Get system time.
    */
    static TimeHandler getCurrentTime( );

    /**
     * Subtract a time handler class from current class.
    */
    TimeHandler &operator-=(TimeHandler);

    /**
     * Subtract a time handler pointer from current class.
    */
    TimeHandler &operator-=(TimeHandler *);

    /**
     * Print time on stream.
    */
    friend ostream &operator<<(ostream &, TimeHandler);
};

#endif
