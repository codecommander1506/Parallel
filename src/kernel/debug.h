#ifndef PARALLEL_DEBUG_H
#define PARALLEL_DEBUG_H

#include <Parallel/global.h>

#include <QtCore/qloggingcategory.h>

#define parallelDebug()    qCDebug(parallel)
#define parallelInfo()     qCInfo(parallel)
#define parallelWarning()  qCWarning(parallel)
#define parallelCritical() qCritical(parallel)
#define parallelFatal()    qCFatal(parallel)

#ifdef QT_DEBUG
#   define PARALLEL_DEBUG
#   define PARALLEL_INFO
#   define PARALLEL_WARNING
#   define PARALLEL_CRITICAL
#   define PARALLEL_FATAL
#endif

PARALLEL_EXPORT Q_DECLARE_LOGGING_CATEGORY(parallel)

#endif // PARALLEL_DEBUG_H
