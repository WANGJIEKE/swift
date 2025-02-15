#ifndef TEST_INTEROP_CXX_FOREIGN_REFERENCE_INPUTS_REFERENCE_COUNTED_H
#define TEST_INTEROP_CXX_FOREIGN_REFERENCE_INPUTS_REFERENCE_COUNTED_H

#include <stdlib.h>

#include "visibility.h"

inline void *operator new(size_t, void *p) { return p; }

SWIFT_BEGIN_NULLABILITY_ANNOTATIONS

static int finalLocalRefCount = 100;

namespace NS {

struct __attribute__((swift_attr("import_as_ref")))
__attribute__((swift_attr("retain:LCRetain")))
__attribute__((swift_attr("release:LCRelease"))) LocalCount {
  int value = 0;

  static LocalCount *create() {
    return new (malloc(sizeof(LocalCount))) LocalCount();
  }
};

}

inline void LCRetain(NS::LocalCount *x) { x->value++; }
inline void LCRelease(NS::LocalCount *x) {
  x->value--;
  finalLocalRefCount = x->value;
}

static int globalCount = 0;

struct __attribute__((swift_attr("import_as_ref")))
__attribute__((swift_attr("retain:GCRetain")))
__attribute__((swift_attr("release:GCRelease"))) GlobalCount {
  static GlobalCount *create() {
    return new (malloc(sizeof(GlobalCount))) GlobalCount();
  }
};

inline void GCRetain(GlobalCount *x) { globalCount++; }
inline void GCRelease(GlobalCount *x) { globalCount--; }

SWIFT_END_NULLABILITY_ANNOTATIONS

#endif // TEST_INTEROP_CXX_FOREIGN_REFERENCE_INPUTS_REFERENCE_COUNTED_H
