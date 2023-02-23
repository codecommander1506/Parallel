#ifndef PARALLEL_THREAD_P_H
#define PARALLEL_THREAD_P_H

#include "thread.h"

#include <QtCore/qmutex.h>

namespace Parallel {

class ThreadPrivate
{
public:
    ThreadPrivate(Thread *qq);
    ~ThreadPrivate();

    bool hasPendingJobs();
    Job *nextPendingJob();
    void removeJob();

    Thread *q;

    QVector<Job *> jobs;
    QMutableVectorIterator<Job *> job;
    QMutex mutex;

private:
    PARALLEL_DECLARE_PUBLIC(Thread)
};

}

#endif // PARALLEL_THREAD_P_H
