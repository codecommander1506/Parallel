#include "job.h"
#include "job_p.h"

#include <QtCore/qatomic.h>

/*!
 * \class Parallel::Job
 *
 * \brief This class represent a task that the thread must run.
 *
 * A Job is just an unit of work that aint to share thread usage betwen
 * many tasks, it represent a single task that must be run a many time or
 * just once depending on your use case.
 *
 * To use this class, you must reimplement the method run().
 *
 * \see Parallel::Thread
 *
 * \fn Parallel::Job::run()
 *
 * This method is called to process the Job's work.
 *
 * \note This method is called inside the Parallel thread.
 */

namespace Parallel {

/*!
 * Construct a Job.
 *
 * \note Since this class is abstract the constructor can't be called directly.
 */
Job::Job() :
    d(new JobPrivate(this))
{
}

Job::Job(JobPrivate *dd) :
    d(dd)
{
}

/*!
 * The destructor.
 */
Job::~Job()
{
}

/*!
 * Check wheter the job can loop again ie. the number of loop executed is
 * less than the total loop number.
 *
 * \return true if the job is still looping on the run() function,
 * false otherwise
 *
 * \see loop()
 */
bool Job::canLoop() const
{
    if (d->refJob)
        return d->refJob->canLoop();

    QMutexLocker locker(&d->mutex);
    switch (d->loopCount) {
    case LoopForever:
        return true;

    default:
        return d->loop < d->loopCount - 1;
    }
}

/*!
 * The number of loop already done.
 *
 * \return the number of loop done since call of Thread::run()
 */
int Job::loop() const
{
    if (d->refJob)
        return d->refJob->loop();

    QMutexLocker locker(&d->mutex);
    return d->loop;
}

/*!
 * The total loop count
 *
 * \return the number of loop to do in the thread.
 *
 * \see loop(), canLoop()
 */
int Job::loopCount() const
{
    if (d->refJob)
        return d->refJob->loopCount();

    QMutexLocker locker(&d->mutex);
    return d->loopCount;
}

void Job::setLoopCount(int count)
{
    if (d->refJob)
        return;

    QMutexLocker locker(&d->mutex);
    d->loopCount = (count > 0 ? count : LoopForever);
    d->loop = -1;
}

void Job::runJob()
{
    if (d->refJob)
        return;

    d->mutex.lock();
    d->loop++;
    d->mutex.unlock();

    run();
}

JobPrivate::JobPrivate(Job *qq) :
    q(qq),
    refJob(nullptr),
    loop(-1),
    loopCount(Job::LoopOnce)
{
}

JobPrivate::~JobPrivate()
{
}

JobGroup::JobGroup() :
    Job(new JobGroupPrivate(this))
{
}

JobGroup::~JobGroup()
{
}

void JobGroup::addJob(Job *job)
{
    QMutexLocker locker(&d->mutex);
    PARALLEL_D(JobGroup);
    if (!d->jobs.contains(job)) {
        d->jobs.append(job);
        job->d->refJob = this;
    }
}

void JobGroup::removeJob(Job *job)
{
    QMutexLocker locker(&d->mutex);
    PARALLEL_D(JobGroup);
    if (d->jobs.removeOne(job))
        job->d->refJob = nullptr;
}

void JobGroup::run()
{
    PARALLEL_D(JobGroup);

    d->mutex.lock();
    QVector<Job *> jobs = d->jobs;
    jobs.detach();
    d->mutex.unlock();

    for (Job *job : qAsConst(jobs))
        job->run();
}

JobGroupPrivate::JobGroupPrivate(JobGroup *qq) :
    JobPrivate(qq)
{
}

JobGroupPrivate::~JobGroupPrivate()
{
    while (!jobs.isEmpty())
        delete jobs.takeFirst();
}

}
