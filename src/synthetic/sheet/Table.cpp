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
#include <synthetic/sheet/Table.h>
#include <synthetic/sheet/Queue.h>

/**
 * Startup the table.
*/
Table::Table(int width, int height) {
  int i;

  // start table values
  this->width = width;
  this->height = height;

  // create the rows
  lines = new Queue *[height];

  // initializa the rows with empty values
  for (i = 0; i < height; i++)
    lines[i] = new Queue(width);

  // not valid
  validated = false;

  // standart output mode
  ctxMode = false;
}

/**
 * Free table.
*/
Table::~Table( ) {
  int i;

  // free all rows
  for (i = 0; i < height; i++)
    delete lines[i];

  delete lines;
}

/**
 * Get the width of table.
*/
int Table::getWidth( ) {
  return width;
}

/**
 * Get height of table.
*/
int Table::getHeight( ) {
  return height;
}

/**
 * Get table density.
*/
float Table::getDensity( ) {
  int i;
  float den = 0;

  // get all rows density
  for (i = 0; i < height; i++)
    den += lines[i]->getDensity( );

  // proportion
  return (den / height);
}

/**
 * Get row density.
*/
float Table::getDensity(int row) {
  if (row >= 0 && row < height)
    return lines[row]->getDensity( );
  else
    return -1.0;
}

/**
 * Get row filled values.
*/
int Table::getFilled(int row) {
  if (row >= 0 && row < height)
    return lines[row]->getFilled( );
  else
    return -1;
}

/**
 * Get value in row and column.
*/ 
int Table::getValue(int row, int col) {
  if (row >= 0 && row < height)
    return lines[row]->getValue(col);
  else
    return -1;
}

/**
 * Set value in row and column.
*/
int Table::setValue(int value, int row, int col) {
  int pos;
  int ret = -1;

  if (validated && row >= 0 && row < height) {
    // was the value added
    if (!lines[row]->setValue(value, col)) {
      // check if not violates table
      if ((value ? fullRow(row) : emptyRow(row)) || 
          (value ? fullColumn(col) : emptyColumn(col)) ||
          duplicatedRow(row, &pos))
        lines[row]->setValue((value ? 0 : 1), col);
      else
        ret = 0; // no error
    }
  }

  return ret;
}

/**
 * Set value in a randomly picked column.
*/
int Table::setValue(int value, int row) {
  int i, n = 0;
  int *tmp, pos;
  int ret = -1;

  if (validated && row >= 0 && row < height) {
    tmp = new int [width];

    // get all possible positions
    for (i = 0; i < width; i++) {
      if (lines[row]->getValue(i) != value)
        tmp[n++] = i; // add to possibles list
    }

    // verify randomly if possible to use
    while (n && ret < 0) {
      pos = nextPositiveInt( ) % n;

      // try changing value
      ret = this->setValue(value, row, tmp[pos]);

      // decrease random search space
      tmp[pos] = tmp[--n];
    }

    // free memory
    delete tmp;
  }

  return ret;
}

/**
 * Set value in randomly picked column and row.
*/ 
int Table::setValue(int value) {
  int i, n;
  int *tmp, pos;
  int ret = -1;

  if (validated) {
    // get all possible rows
    tmp = new int [height];
    for (i = 0; i < height; i++)
      tmp[i] = i;

    // verify randomly if possible to use
    n = height;
    while (n && ret < 0) {
      pos = nextPositiveInt( ) % n;

      // try changing value
      ret = this->setValue(value, tmp[pos]);

      // decrease random search space
      tmp[pos] = tmp[--n];
    }

    // free memory
    delete tmp;
  }

  return ret;
}

/**
 * Set a line in a row.
*/ 
int Table::setLine(Queue &q, int row) {
  int pos;
  int ret = -1;

  // check if valid row
  if (row >= 0 && row < height) {
    // check if lines has the same width and aren't equal
    if (lines[row]->getSize( ) == q.getSize( ) && *lines[row] != q) {
      // save old
      Queue old(*lines[row]);

      // update line
      *lines[row] = q;

      // check if possible to use
      if (duplicatedRow(row, &pos))
        *lines[row] = old; // backwards old value
      else {
        // must be revaliated
        validated = false;

        // return no error
        ret = 0;
      }
    }
  }

  return ret;
}

/**
 * Validate table check if it has empty or full column and rows.
*/
bool Table::validate( ) {
  int i, x;

  // must be invalidated to validate
  if (!validated) {
    i = x = 0;

    // check rows
    while (i < height && !x) {
      x = lines[i]->empty( ) | lines[i]->full( );
      i++;
    }

    i = 0;
    // check columns
    while (i < width && !x) {
      x = emptyColumn(i) | fullColumn(i);
      i++;
    }

    // validate
    if (!x)
      validated = true;
  }

  return validated;
}

/**
 * Check whenever table is valid.
*/
bool Table::isValid( ) {
  return validated;
}

/**
 * Check if column is empty.
*/
int Table::emptyColumn(int col) {
  int i;

  if (col >= 0 && col < width) {
    // search all rows for column position
    for (i = 0; i < height; i++) {
      // has value
      if (lines[i]->getValue(col))
        return 0;
    }

    return 1;
  }

  return -1;
}

/**
 * Check if column is full.
*/
int Table::fullColumn(int col) {
  int i;

  if (col >= 0 && col < width) {
    // search all rows for column position
    for (i = 0; i < height; i++) {
      // hasn't value
      if (!lines[i]->getValue(col))
        return 0;
    }

    return 1;
  }

  return -1;
}

/**
 * Check if row is empty.
*/
int Table::emptyRow(int row) {
  // is valid row
  if (row >= 0 && row < height)
    // check empty
    return lines[row]->empty( );
  else
    // error
    return -1;
}

/**
 * Check if row is full.
*/
int Table::fullRow(int row) {
  // is valid row
  if (row >= 0 && row < height)
    // check full
    return lines[row]->full( );
  else
    // error
    return -1;
}

/**
 * Check if table has a duplicated row.
*/
int Table::duplicatedRow(int row, int *pos) {
  int i;

  // search all rows
  for (i = 0; i < height; i++) {
    if (i != row && // check all other row
        lines[row]->getFilled( ) == lines[i]->getFilled( ) && // otimization
        *lines[row] == *lines[i]) { // check if match
      *pos = i; // which position
      return 1; // found
    }
  }

  // not duplicated
  return 0;
}

/**
 * Type of output.
*/
void Table::setContextMode(bool mode) {
  ctxMode = mode;
}

/**
 * Print the output on stream.
*/
ostream &operator<<(ostream &stream, Table &t) {
  int i;

  // print each line
  for (i = 0; i < t.height; i++) {
    // set the type of output
    t.lines[i]->setContextMode(t.ctxMode);

    // print it
    stream << *t.lines[i] << endl;

    // restore print mode
    if (t.ctxMode)
      t.lines[i]->setContextMode(false);
  }

  return stream;
}
