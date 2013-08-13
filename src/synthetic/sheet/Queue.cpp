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

#include <cstring>
#include <synthetic/sheet/Queue.h>

/**
 * Initializa the line with empty values.
*/
Queue::Queue(int width) {
  int x; // offset position on line

  // startup values
  this->width = width;
  this->filled = 0;

  // necessary array positions
  x = (width / 32) + 1;

  // threat each position as bits to perform better usage of memory
  line = new unsigned int [x];

  // fill it with empty values
  memset(line, 0, (sizeof(line) * x));

  // start as standart mode
  ctxMode = false;
}

/**
 * Create a new queue based on an image of another.
*/
Queue::Queue(const Queue &l) {
  int i, x;

  // same width and filled values
  width = l.width;
  filled = l.filled;

  // alocate
  x = (l.width / 32) + 1;
  line = new unsigned int [x];

  // copy
  for (i = 0; i < x; i++)
    line[i] = l.line[i];
}

/**
 * Destroy the line.
*/
Queue::~Queue( ) {
  delete line;
}

/**
 * Set a value in a position of line.
*/
int Queue::setValue(int value, int pos) {
  int which, offset, x;
  int ret = -1;
  unsigned int old;

  if (pos >= 0 && pos < width) { // is valid position
    // array position and offset
    which = pos / 32;
    offset = pos % 32;

    // save old
    old = line[which];

    // the bit in right position
    x = 1 << offset;

    if (value)
      line[which] |= x; // add value
    else
      line[which] &= ~x; // add not value

    // was really changed
    if (line[which] != old) {
      // updated filled counter
      filled += (value ? 1 : -1);
      ret = 0;
    }
  }

  // 0 mean no error
  return ret;
}

/**
 * Get the value of the position on line.
*/
int Queue::getValue(int pos) {
  int which, offset;

  if (pos >= 0 && pos < width) { // is valid position
    // array position and offset
    which = pos / 32;
    offset = pos % 32;

    // get the value
    return ((line[which] >> offset) & 1);
  } else {
    // error
    return -1;
  }
}

/**
 * Get the size of the line.
*/
int Queue::getSize( ) {
  return width;
}

/**
 * Get the number of used positions.
*/
int Queue::getFilled( ) {
  return filled;
}

/**
 * Get the density of the line.
*/
float Queue::getDensity( ) {
  // ration between filled positions and total positions.
  float f = (float) filled;
  return (f / width);
}

/**
 * All position are unused.
*/
int Queue::empty( ) {
  return (filled == 0);
}

/**
 * All positions are used.
*/
int Queue::full( ) {
  return (filled == width);
}

/**
 * Restart all used positions.
*/
void Queue::reset( ) {
  int x;

  // not filled
  this->filled = 0;

  // total array positions
  x = (width / 32) + 1;

  // clean up
  memset(line, 0, (sizeof(line) * x));
}

/**
 * Set output mode type.  
*/
void Queue::setContextMode(bool mode) {
  this->ctxMode = mode;
}

/**
 * Print line to stream.
 * If in context mode writes blank spaces for unused positions and "X"
 * for used, otherwise print "0" for unused and "1" for used.
*/
ostream &operator<<(ostream &stream, Queue &l) {
  int i, x;
  int which, offset;

  for (i = l.width; i > 0; i--) {
    // array position and offset
    which = (i - 1) / 32;
    offset = (i - 1) % 32;

    // get the value
    x = (l.line[which] >> offset) & 1;
    if (l.ctxMode) // for AFC output format
      stream << (x ? "X" : " ");
    else // otherwise just print the value
      stream << x;
  }

  return stream;
}

/**
 * Perform a queue copy.
*/
Queue &Queue::operator=(const Queue &l) {
  int i, x;

  if (this->width == l.width)
    x = (width / 32) + 1;
  else { // create a new line in image of the one desired
    delete line;

    x = (l.width / 32) + 1;
    line = new unsigned int [x];
  } 

  // perform copy
  for (i = 0; i < x; i++)
    line[i] = l.line[i];

  // update width size
  this->width = l.width;

  // update filled value
  this->filled = l.filled;

  return *this;
}

/**
 * Verifies two queues for equality.
*/
int equals(Queue *l1, Queue &l2) {
  int i, x;

  // they must match width and filled positions
  if (l1->width != l2.width || l1->filled != l2.filled) 
    return 0;
  else { // finer search
    x = (l1->width / 32) + 1;
    // search all array positions
    for (i = 0; i < x; i++) {
      if (l1->line[i] != l2.line[i]) // no match
        return 0;
    }

    return 1;
  }
}

/**
 * Check if equal.
*/ 

int Queue::operator==(Queue &l) {
  return equals(this, l);
}

/**
 * Check if not equal.  
*/
int Queue::operator!=(Queue &l) {
  return !equals(this, l);
}

/**
 * Threat the line as bits and do a bitwise incrementation.
*/
Queue &Queue::operator++( ) {
  int i, j, x, n, overflow;
  unsigned int old;

  if (filled < width) {
    x = (width / 32) + 1;
    overflow = 0;
    filled = 0;
    n = width;
    for (i = 0; i < x; i++) {
      if (!i || overflow) {
        old = line[i]++;
        if (line[i] < old)
          overflow = 1;
      }

      j = 0;
      while (n > 0 && j < 32) {
        filled += (line[i] >> j) & 1;
        n--;
        j++;
      }
    }
  }

  return *this;
}

/**
 * Threat the line as bits and do a bitwise decrementation.
*/
Queue &Queue::operator--( ) {
  int i, j, x, n, borrow;
  unsigned int old;

  if (filled > 0) {
    x = (width / 32) + 1;
    borrow = 0;
    filled = 0;
    n = width;
    for (i = 0; i < x; i++) {
      if (!i || borrow) {
        old = line[i]--;
        if (line[i] > old)
          borrow = 1;
      }

      j = 0;
      while (n > 0 && j < 32) {
        filled += (line[i] >> j) & 1;
        n--;
        j++;
      }
    }
  }

  return *this;
}

/**
 * Negate the line, every used position turns unused and vice-versa.
*/
Queue &Queue::operator~( ) {
  int i, x;

  x = (width / 32) + 1;

  // negate all array positions
  for (i = 0; i < x; i++)
    line[i] = ~line[i];

  // update the filled value
  filled = width - filled;

  return *this;
}
