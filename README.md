==========================================================================
                               *** SCGaz ***
                  Synthetic Context Generator from A to Z
                               Package v1.0
==========================================================================

Preface
=======

  SCGaz (Synthetic Context Generator from A to Z) is a generator that can generate artificial formal contexts to be used in simulations for FCA algorythms. It can generate partially irreducible contexts with selectable density ranging from minimun to maximun. It also mantain the number of atributos and objects choosen without futher reduction, taking the user in the control of the contexts he/she wants to simulate. The software generates contexts in the BurMeister format, according to ConImp input/output. This format can also be used on ConExp.


  Andrei Rimsa Álvares
  rimsa@live.com

  Luis Enrique Zárate
  zarate@pucminas.br




Instalation
===========

The simplest way to compile this program is:

  1. `cd' to the directory containing the package's source code.

  2. Type `make' to compile the package.

  3. Type `make install' to install the program.

  4. You can remove the program binaries and object files from the
     source code directory by typing `make clean'. You can uninstall the 
     program also issuing `make uninstall'.

Using
=====

  To use this software:
    1. Open a terminal window.
    2. Type `scg' and it will show a usage menu.
    3. Choose the desired options and run it again.

  SCGaz may generate a single synthetic context or several upon arguments used. Every synthetic context must have a number of attributes and objects and also one type of density option. One can variate the attributes in an increasing rate and for objects as well. It's possible to variate the amount of objects too using a fixed number of samples. Fixed density can be used only in single context mode and you can choose a number of density samples to generate.
