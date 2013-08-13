/*
 *  SCGaz - generates artificial synthetic contexts
 *  Copyright (C) 2008 Andrei Rimsa Álvares and Luis Enrique Zárate
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <log/LogHandler.h>
#include <random/RandomHandler.h>
#include <control/ProcessControl.h>
#include <control/StaticContext.h>
#include <control/DynamicContext.h>
#include <exceptions/InputException.h>

using namespace std;

// type of simulation
enum smode {
  STATIC_MODE,
  DYNAMIC_MODE
};

void usage(char *);
enum smode read_opts(int, char **);

struct vars {
  char *ctxout;    // context base name
  bool verbose;    // verbose

  int min_attr;    // minimum number of attributes
  int max_attr;    // maximun number of attributes
  int rate_attr;   // increate attributes rate

  int min_objc;    // minimun number of objects
  int max_objc;    // maximun number of objects
  int rate_objc;   // increase objects rate
  int sample_objc; // number of sample objects

  int *intervals;       // discretization values
  int total_intervals;

  float density; // desired density
  bool minDensity; // use minimun density;
  bool maxDensity; // use maximun density;

  int sample_den; // how many density samples
  float *den_values; // the density values
} args = { // default start values
  NULL,         // ctxout
  false,        // verbose
  0,            // min_attr
  0,            // max_attr
  0,            // rate_attr

  0,            // min_objc
  0,            // max_objc
  0,            // rate_objc
  0,            // sample_objc

  NULL,         // intervals
  0,            // total_intervals

  0.0,          // density
  false,        // minDensity
  false,        // maxDensity
  0,            // sample_den
  NULL          // den_values
};

/**
 * Start function.
*/
int main(int argc, char **argv) {
  enum smode mode; // which mode
  ProcessControl *pc = NULL; // generic simulation mode
  StaticContext *sc = NULL; // static simulation
  DynamicContext *dc = NULL; // generic simulation
  struct dynamic_options dopt; // dynamic simulation options

  // output some banner
  cout << "Synthetic context generator" << endl;
  cout << "Authors: Andrei Rimsa Álvares and Luis Enrique Zárate" << endl;
  cout << "Applied Computational Intelligence Laboratory (LICAP) - PUC Minas" << endl;
  cout << endl;

  // show usage
  if (argc < 2)
    usage(argv[0]);

  // init random seed
  initRandom( );

  // catch input exceptions
  try {
    // read options
    mode = read_opts(argc, argv);

    // set context output base name
    if (args.ctxout)
      LogHandler::setContextOutput(args.ctxout);

    // catch all possible simulation exceptions
    try {
      // built process control
      switch (mode) {
        case STATIC_MODE: // static simulation
          if (args.total_intervals > 0) {
            // create static simulation object
            sc = new StaticContext(args.min_attr, args.min_objc,
                 args.intervals, args.total_intervals);
          } else {
            // create static simulation object
            sc = new StaticContext(args.min_attr, args.min_objc);
          }

          // is verbose
          if (args.verbose)
            // use verbose output
            sc->setVerbose( );

          // if density is defined, use it
          if (args.minDensity)
            sc->useMinDensity( );
          else if (args.maxDensity)
            sc->useMaxDensity( );
          else if (args.density > 0.0)
            sc->setDensity(args.density);

          // start table
          sc->init( );

          // define process control
          pc = sc;
          break;
        default: // DYNAMIC_MODE
          // built dynamic options
          dopt.min_attr = args.min_attr;
          dopt.max_attr = args.max_attr;
          dopt.inc_attr = args.rate_attr;

          dopt.min_objc = args.min_objc;
          dopt.max_objc = args.max_objc;

          if (args.rate_objc > 0) {
            dopt.objc_mode = true;
            dopt.inc_objc = args.rate_objc;
          } else {
            dopt.objc_mode = false;
            dopt.sample_objc = args.sample_objc;
          }

          dopt.intervals = args.intervals;
          dopt.total_intervals = args.total_intervals;

          dopt.sample_den = args.sample_den;
          dopt.den_values = args.den_values;

          // create dynamic simulation object
          dc = new DynamicContext(dopt);

          // is verbose
          if (args.verbose)
            // use verbose output
            dc->setVerbose( );

          // define process control
          pc = dc;
          break;
      }

      // simulate
      pc->process( );
    } catch (bad_alloc &b) { // memory problem
      cerr << "Unable to allocate memory" << endl;
    } catch (exception &e) { // generation problems
      cerr << e.what( ) << endl; // print error
    }

    // free memory
    if (pc)
      delete(pc);
  } catch (InputException &ie) { // catch input exceptions
    cerr << ie.what( ) << endl; // print error
  } catch (bad_alloc &x) { // memory problem
    cerr << "Unable to allocate memory" << endl;
  }

  // free memory
  if (args.intervals)
    delete args.intervals;

  cout << "Exiting..." << endl;

  return 0;
}

/**
 * Show program usage.
*/
void usage(char *prog) {
  cout << "Usage: " << prog << " <Options>" << endl;
  cout << "  -c   Context      Base file name output for synthetic context" << endl;
  cout << "  -h                This usage" << endl;
  cout << "  -v                Use for verbose" << endl;
  cout << endl;
  cout << "Attributes options" << endl;
  cout << "  -a   Attributes   Number of attributes" << endl;
  cout << "  -t   Attributes   Maximun number of attributes" << endl;
  cout << "  -r   Rate         Attributes increase rate" << endl;
  cout << endl;
  cout << "Objects options" << endl;
  cout << "  -b   Objects      Number of objects" << endl;
  cout << "  -j   Objects      Maximun number of objects" << endl;
  cout << "  -e   Rate         Objects increase rate" << endl;
  cout << "  -s   Sample       Number of objects sample" << endl;
  cout << endl;
  cout << "Discretization options" << endl;
  cout << "  -i   List         List of discretization intervals, " \
          "comma separated" << endl;
  cout << "  -f   Interval     Fixed discretization intervals" << endl;
  cout << endl;
  cout << "Density options" << endl;
  cout << "  -d   Density      Density" << endl;
  cout << "  -n   Sample       Number of densities sample" << endl;
  cout << "  -k   Values       List of density values, comma separated" << endl;
  cout << endl;

  exit(0);
}

/**
 * Read argument options.
*/
enum smode read_opts(int argz, char **argp) {
  int opt, tmp, n, x;
  float tmpf;
  char *ptr, *disc = NULL, *disc2 = NULL, *den_values = NULL;
  enum smode mode = STATIC_MODE; // default simulation mode

  // choose option
  while ((opt = getopt(argz, argp, "c:hva:t:r:b:j:e:s:i:f:d:n:k:")) != -1) {
    // process option
    switch (opt) {
      case 'c': // set context output base name
        args.ctxout = optarg;
        break;
      case 'v':
        args.verbose = true;
        break;
      case 'a': // minimun number of attributes
        args.min_attr = atoi(optarg);
        if (args.min_attr <= 0)
          throw InputException("Invalid number of attributes");

        break;
      case 't': // maximun number of attributes
        args.max_attr = atoi(optarg);
        if (args.max_attr <= 0)
          throw InputException("Invalid number of maximun attributes");

        mode = DYNAMIC_MODE; // can only be used in dynamic generation
        break;
      case 'r': // attributes increase rate
        args.rate_attr = atoi(optarg);
        if (args.rate_attr <= 0)
          throw InputException("Invalid attributes increase rate");

        mode = DYNAMIC_MODE; // can only be used in dynamic generation
        break;
      case 'b': // number of objects
        args.min_objc = atoi(optarg);
        if (args.min_objc <= 0)
          throw InputException("Invalid number of objects");

        break;
      case 'j':
        args.max_objc = atoi(optarg);
        if (args.max_objc <= 0)
          throw InputException("Invalid number of maximun objects");

        mode = DYNAMIC_MODE; // can only be used in dynamic generation
        break;
      case 'e':
        args.rate_objc = atoi(optarg);
        if (args.rate_objc <= 0)
          throw InputException("Invalid objects increase rate");

        mode = DYNAMIC_MODE; // can only be used in dynamic generation
        break;
      case 's':
        args.sample_objc = atoi(optarg);
        if (args.sample_objc <= 0)
          throw InputException("Invalid number of objects samples");

        mode = DYNAMIC_MODE; // can only be used in dynamic generation
        break;
      case 'i':
        disc = optarg;
        break;
      case 'f':
        disc2 = optarg;
        break;
      case 'd':
        if (!strcasecmp(optarg, "min")) {
          args.density = 0.0f;
          args.minDensity = true;
          args.maxDensity = false;
        } else if (!strcasecmp(optarg, "max")) {
          args.density = 0.0f;
          args.minDensity = false;
          args.maxDensity = true;
        } else {
          args.density = atof(optarg);
          if (args.density < 0.0f || args.density > 1.0f)
            throw InputException("Invalid density");
        }

        break;
      case 'n':
        args.sample_den = atoi(optarg);
        if (args.sample_den <= 0)
          throw InputException("Invalid number of densities sample");

        mode = DYNAMIC_MODE; // can only be used in dynamic generation
        break;
      case 'k':
        den_values = optarg;
        mode = DYNAMIC_MODE;
        break;
      case 'h':
      default:
        usage(argp[0]);
    }
  }

  // required option
  if (!args.min_attr)
    throw InputException("-a option is required");
  else if (!args.min_objc)
    throw InputException("-b option is required");

  if (disc && disc2)
    throw InputException("-i option cannot be combined with -f option");
  else {
    args.intervals = new int [args.min_attr];
    args.total_intervals = 0;

    if (disc) {
      n = 0;
      ptr = strtok(disc, " ,");
      while (ptr != NULL) {
        if (n >= args.min_attr)
          throw InputException("Too many discretizations intervals");
        else {
          tmp = atoi(ptr);
          if (tmp <= 0)
            throw InputException("Invalid discretization interval");

          args.intervals[n++] = tmp;
          args.total_intervals += tmp;

          ptr = strtok(NULL, " ,"); // next interval
        }
      }

      if (n != args.min_attr)
        throw InputException("Too few discretization intervals");
    } else if (disc2) {
      tmp = atoi(disc2);
      if (tmp <= 0)
        throw InputException("Invalid discretization interval");

      for (n = 0; n < args.min_attr; n++) {
        args.intervals[n] = tmp;
        args.total_intervals += tmp;
      }
    }
  }

  if (args.density > 0.0 || args.minDensity || args.maxDensity) {
    if (disc) // opt -i
      throw InputException("-d option cannot be combined with -i option");
    else if (disc2) // opt -f
      throw InputException("-d option cannot be combined with -f option");
  }

  if (args.sample_den > 0) {
    if (disc) // opt -i
      throw InputException("-n option cannot be combined with -i option");
    else if (disc2) // opt -f
      throw InputException("-n option cannot be combined with -f option");
  }

  if (den_values) {
    if (args.sample_den == 0)
      throw InputException("-k option must be combined with -n option");
    else {
      args.den_values = new float [args.sample_den];

      n = 0;
      ptr = strtok(den_values, " ,");
      while (ptr != NULL) {
        if (n >= args.sample_den)
          throw InputException("Too many density value");

        tmpf = atof(ptr);
        if (tmpf <= 0.0 || tmpf >= 1.0)
           throw InputException("Invalid density in density values");

        args.den_values[n++] = tmpf;
        for (x = (n - 1); x > 0; x--) {
          if (args.den_values[x] == args.den_values[x - 1])
            throw InputException("Densities must be different");
          else if (args.den_values[x] > args.den_values[x - 1]) 
            break;
          else {
            tmpf = args.den_values[x - 1];
            args.den_values[x - 1] = args.den_values[x];
            args.den_values[x] = tmpf;
          }
        }

        ptr = strtok(NULL, " ,");  
      }

      if (n != args.sample_den)
        throw InputException("Too few density values");
    }
  }

  if (mode == DYNAMIC_MODE) {
    // check consistency
    if (args.max_attr && !args.rate_attr)
      throw InputException("-t option must be combined with -r option");

    // check consistency
    if (args.rate_attr > 0 && !args.max_attr)
      throw InputException("-r option must be combined with -t option");

    // if not used set default values
    if (!args.max_attr) {
      args.max_attr = args.min_attr;
      args.rate_attr = 1;
    }

    // check consistency    
    if (args.rate_objc && args.sample_objc)
      throw InputException("-e options must not be combined with -s option");

    // check consistency
    if (args.max_objc && !args.rate_objc && !args.sample_objc)
      throw InputException("-j option must be combined with -e or " \
                           "-s option");

    // if not used set default values
    if (!args.max_objc) {
      args.max_objc = args.min_objc;
      args.rate_objc = 1;
    }

    // check consistency
    if (args.density > 0.0f || args.minDensity || args.maxDensity)
      throw InputException("-d options must not be used on dynamic " \
                           "simulation");

    // if not setted, use default sample value
    if (!args.sample_den)
      args.sample_den = 1;
  }

  return mode;
}
