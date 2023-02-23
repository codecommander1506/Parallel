#ifndef PARALLEL_JOB_P_H
#define PARALLEL_JOB_P_H

#include "job.h"

#include <QtCore/qmutex.h>
#include <QtCore/qvector.h>

namespace Parallel {

class JobPrivate
{
public:
    JobPrivate(Job *qq);
    virtual ~JobPrivate();

    Job *q;
    Job *refJob;

    int loop;
    int loopCount;

    QMutex mutex;

private:
    PARALLEL_DECLARE_PUBLIC(Job)
};

class JobGroupPrivate : public JobPrivate
{
public:
    JobGroupPrivate(JobGroup *qq);
    ~JobGroupPrivate();

    QVector<Job *> jobs;
};

}

#endif // PARALLEL_JOB_P_H
