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

#include <cstdio>

#include <sys/time.h>
#include <time/TimeHandler.h>

#ifdef WIN32  
#include <sys/timeb.h>  
#endif

/**
 * Initialize time.
*/
TimeHandler::TimeHandler(int secounds, int msecounds) {
  tv.tv_sec = secounds;
  tv.tv_usec = msecounds;
}

/**
 * Destroy time handler.
*/
TimeHandler::~TimeHandler( ) {
}

TimeHandler TimeHandler::getCurrentTime( ) {
  struct timeval tv;

  gettimeofday(&tv, NULL);

  TimeHandler th(tv.tv_sec, tv.tv_usec);
  return th;
}

/**
 * Get secounds.
*/
int TimeHandler::getSecounds( ) {
  return tv.tv_sec;
}

/**
 * Get millisecounds.
*/
int TimeHandler::getMiliSecounds( ) {
  return tv.tv_usec;
}

/**
 * Get time of given class.
*/
double TimeHandler::getTime(TimeHandler *th) {
  double d = (double) th->getSecounds( );
  d += ((double) th->getMiliSecounds( )) / 1000000;

  return d;
}

/**
 * Get time of this class.
*/
double TimeHandler::getTime( ) {
  return this->getTime(this);
}

/**
 * Substract TimeHandler from this class.
*/
void TimeHandler::minus(TimeHandler *th) {
  if ((tv.tv_usec -= th->getMiliSecounds( )) < 0) {
    tv.tv_sec--;
    tv.tv_usec += 1000000;
  }

  tv.tv_sec -= th->getSecounds( );
}

/**
 * Subtract a time handler class from current class.
*/
TimeHandler &TimeHandler::operator-=(TimeHandler th) {
  minus(&th);
  return *this;
}

/**
 * Subtract a time handler pointer from current class.
*/
TimeHandler &TimeHandler::operator-=(TimeHandler *th) {
  minus(th);
  return *this;
}

/**
 * Print time on stream.
*/
ostream &operator<<(ostream &stream, TimeHandler th) {
  stream << TimeHandler::getTime(&th);

  return stream;
}

#ifdef WIN32  

/**
 * Windows compatible unix's gettimeofday.
*/
int gettimeofday(struct timeval *tv, struct timezone *tz) {
  struct _timeb tb;
   
  if (!tv)
    return -1;
 
  _ftime(&tb);
  tv->tv_sec  = tb.time;
  tv->tv_usec = tb.millitm * 1000 + 500;
  if (tz) {
    tz->tz_minuteswest = -60 * _timezone;
    tz->tz_minuteswest = -60 * _timezone;
    tz->tz_dsttime = _daylight;
  }

  return 0;   
}
  
#endif
