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

OPT_CAT(TestOptions,Test Options, These options are to be used when running tests)
OPT_CAT(SpecialOptions,Special Options, These options are special options)

cl::opt<string> OutputFilename("o", cl::desc("Specify output filename"),
    cl::value_desc("filename"),
    cl::init("testfile.cpp"),
    cl::cat<TestOptions>() );

cl::opt<string> path("p", cl::desc("Specify output path"),
    cl::value_desc("a path"),
    cl::init("testfile.cpp"),
    cl::cat<cl::GeneralOption>() );

cl::opt<bool> testManualHelp ("manual-help", cl::desc("Show help output in categories"),
    cl::init(false),
    cl::cat<TestOptions>() );

enum OptLevel {
  g, O1, O2, O3
};

cl::opt<OptLevel> OptimizationLevel(cl::desc("Choose optimization level:"),
  cl::values(
    clEnumVal(g , "No optimizations, enable debugging"),
    clEnumVal(O1, "Enable trivial optimizations"),
    clEnumVal(O2, "Enable default optimizations"),
    clEnumVal(O3, "Enable expensive optimizations"),
   clEnumValEnd),
   cl::cat<TestOptions>() );

enum Opts {
  // 'inline' is a C++ keyword, so name it 'inlining'
  dce, constprop, inlining, strip
};

cl::list<Opts> OptimizationList(cl::desc("Available Optimizations:"),
  cl::values(
    clEnumVal(dce               , "Dead Code Elimination"),
    clEnumVal(constprop         , "Constant Propagation"),
   clEnumValN(inlining, "inline", "Procedure Integration"),
    clEnumVal(strip             , "Strip Symbols"),
  clEnumValEnd),
  cl::cat<SpecialOptions>()
  );

cl::opt<int> thingy("abc",cl::desc("I don't really do anything"),cl::cat<SpecialOptions>());

int
main (int argc, char ** argv)
{
  llvm::cl::extrahelp("\nThis is more help!\n");
  llvm::cl::extrahelp("And even more!\n");

  //Hack the options
  StringMap<llvm::cl::Option*> hack; 
  llvm::cl::getRegisteredOptions(hack);
  assert(hack.count("help") > 0);
  hack["help"]->setDescription("Hahah! I've hack the help. muahahaha!");
  hack["help"]->setArgStr("help-list");

  assert(hack.count("help-cat") > 0);
  hack["help-cat"]->setArgStr("help");

  assert(hack.count("print-all-options") >0);
  hack["print-all-options"]->setHiddenFlag(llvm::cl::NotHidden);
  hack["print-all-options"]->setOptionCategory<TestOptions>();

  cl::ParseCommandLineOptions(argc, argv, "This is a small program to demo the LLVM CommandLine API");

  /* It is necessary to call this. Even if -print-all-options is called
  *  this function needs to be called as it is not called automatically.
  *  I guess this is useful as it is nice to let the programmer decide
  *  when to print option values
  */
  llvm::cl::PrintOptionValues();

  if(testManualHelp)
    llvm::cl::PrintHelpMessage(true,true);

  std::cout << "Finished parsing, continuing to run program" << std::endl; 
  printf ("%d\n", compute_sample (5));
  exit (0);
}

