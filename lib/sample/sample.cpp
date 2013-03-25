/*
 * File: sample.c
 *
 * Description:
 *  This is a sample source file for a library.  It helps to demonstrate
 *  how to setup a project that uses the LLVM build system, header files,
 *  and libraries.
 */

#include <stdio.h>
#include <stdlib.h>

/* LLVM Header File
#include "llvm/Support/DataTypes.h"
*/

/* Header file global to this project */
#include "sample.h"

#include "llvm/Support/CommandLine.h"
using namespace llvm;



enum LOpts {
  // 'inline' is a C++ keyword, so name it 'inlining'
  ldce, lconstprop, linlining, lstrip
};


cl::bits<LOpts> OptimizationBits(cl::desc("Stuff in library"),
  cl::values(
    clEnumVal(ldce               , "Dead Code Elimination"),
    clEnumVal(lconstprop         , "Constant Propagation"),
   clEnumValN(linlining, "linline", "Procedure Integration"),
    clEnumVal(lstrip             , "Strip Symbols"),
  clEnumValEnd));

int
compute_sample (int a)
{
  return a;
}

