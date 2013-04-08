/*
 * File: sample.h
 *
 *      This is a sample header file that is global to the entire project.
 *      It is located here so that everyone will find it.
 */
#include "llvm/Support/CommandLine.h"

extern int compute_sample (int a);

//A option category for command line options offered by this library.
//It is made available here so that others can use the category if the
//want to.
extern llvm::cl::OptionCategory SampleLibCat;

