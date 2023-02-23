#ifndef PARALLEL_GLOBAL_H
#define PARALLEL_GLOBAL_H

#include <Parallel/config.h>

#ifdef PARALLEL_SHARED
#   ifdef BUILD_PARALLEL_LIB
#       define PARALLEL_EXPORT Q_DECL_EXPORT
#   else
#       define PARALLEL_EXPORT Q_DECL_IMPORT
#   endif
#else
#    define PARALLEL_EXPORT
#endif

#define PARALLEL_DECLARE_PRIVATE(Class) friend class Class##Private;
#define PARALLEL_DECLARE_PUBLIC(Class) friend class Class;

#define PARALLEL_D(Class) Class##Private *d = static_cast<Class##Private *>(qGetPtrHelper(this->d));
#define PARALLEL_Q(Class) Class *q = static_cast<Class *>(this->q);

#endif // PARALLEL_GLOBAL_H
