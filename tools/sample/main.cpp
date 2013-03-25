#include "sample.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include "llvm/Support/CommandLine.h"
#include <string>

#include "sample.h"

using std::string;
using namespace llvm;

OPT_GRP(TestOptions,Test Options, These options are to be used when running tests)

cl::opt<string> OutputFilename("o", cl::desc("Specify output filename"),
    cl::value_desc("filename"),
    cl::init("testfile.cpp"),
    cl::grp<TestOptions>() );

cl::opt<string> path("p", cl::desc("Specify output path"),
    cl::value_desc("a path"),
    cl::init("testfile.cpp"),
    cl::grp<cl::GeneralOption>() );

int
main (int argc, char ** argv)
{
  llvm::cl::extrahelp("This is more help!\n");
  llvm::cl::extrahelp("And even more!\n");

  cl::ParseCommandLineOptions(argc, argv, "This is a small program to demo the LLVM CommandLine API");

  /* It is necessary to call this. Even if -print-all-options is called
  *  this function needs to be called as it is not called automatically.
  *  I guess this is useful as it is nice to let the programmer decide
  *  when to print option values
  */
  llvm::cl::PrintOptionValues();
  std::cout << "Finished parsing, continuing to run program" << std::endl; 
  printf ("%d\n", compute_sample (5));
  exit (0);
}

