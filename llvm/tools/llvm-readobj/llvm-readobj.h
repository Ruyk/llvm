//===-- llvm-readobj.h ----------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_TOOLS_LLVM_READOBJ_LLVM_READOBJ_H
#define LLVM_TOOLS_LLVM_READOBJ_LLVM_READOBJ_H

#include "llvm/Support/CommandLine.h"
#include "llvm/Support/Compiler.h"
#include "llvm/Support/ErrorOr.h"
#include "llvm/Support/Error.h"
#include <string>

namespace llvm {
  namespace object {
    class RelocationRef;
  }

  // Various helper functions.
  LLVM_ATTRIBUTE_NORETURN void reportError(Error Err, StringRef Input); 
  LLVM_ATTRIBUTE_NORETURN void reportError(std::error_code EC, StringRef Input);
  void reportWarning(Error Err, StringRef Input);

  template <class T> T unwrapOrError(StringRef Input, Expected<T> EO) {
    if (EO)
      return *EO;
    reportError(EO.takeError(), Input);
  }
} // namespace llvm

namespace opts {
  extern llvm::cl::opt<bool> SectionRelocations;
  extern llvm::cl::opt<bool> SectionSymbols;
  extern llvm::cl::opt<bool> SectionData;
  extern llvm::cl::opt<bool> ExpandRelocs;
  extern llvm::cl::opt<bool> RawRelr;
  extern llvm::cl::opt<bool> CodeViewSubsectionBytes;
  extern llvm::cl::opt<bool> Demangle;
  enum OutputStyleTy { LLVM, GNU };
  extern llvm::cl::opt<OutputStyleTy> Output;
} // namespace opts

#define LLVM_READOBJ_ENUM_ENT(ns, enum) \
  { #enum, ns::enum }

#define LLVM_READOBJ_ENUM_CLASS_ENT(enum_class, enum) \
  { #enum, std::underlying_type<enum_class>::type(enum_class::enum) }

#endif
