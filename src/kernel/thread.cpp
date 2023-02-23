#include "thread.h"
#include "thread_p.h"

#include "job.h"

/*!
 * \class Parallel::Thread
 *
 * \brief A Parallel Thread.
 *
 * This class represent a Thread unit to use for assynchronous operations.
 *
 * \see Parallel::Job
 */

namespace Parallel {

/*!
 * The constructor, the parent object is passed to QThread constructor.
 *
 * \param parent is the parent object
 *
 * \note The thread termination is disabled at this point.
 */

Thread::Thread(QObject *parent) :
    QThread(parent),
    d(new ThreadPrivate(this))
{
    setTerminationEnabled(false);
}

/*!
 * The destructor stop the thread in a safely maner if it is still running.
 */
Thread::~Thread()
{
    if (isRunning()) {
        requestInterruption();
        wait();
    }
}

/*!
 * \return The time betwen 2 job run, usualy 10ms.
 */
int Thread::sleepTime() const
{
    return 10;
}

/*!
 * Run a job inside the thread.
 * If the thread is not running, it is started.
 *
 * \param job is the job to process
 *
 * \note the job will not always run instantly, it is just added in a qeueue and will
 * be executed in a certain point in time.
 *
 * \warning Running the same job on multiple threads is dangerous and
 * unsupported !
 */
void Thread::runJob(Job *job)
{
    d->mutex.lock();
    d->job.insert(job);
    d->mutex.unlock();

    if (!isRunning())
        start();
}

/*!
 * \reimp QThread::run()
 */
void Thread::run()
{
    do {
        bool processed = false;

        if (d->hasPendingJobs()) {
            Job *job = d->nextPendingJob();
            if ((processed = job->canLoop()))
                job->runJob();
            else
                d->removeJob();
        }

        msleep(sleepTime() / (processed ? 1 : 2));
    } while (!isInterruptionRequested());
}

ThreadPrivate::ThreadPrivate(Thread *qq) :
    q(qq),
    job(jobs)
{
}

ThreadPrivate::~ThreadPrivate()
{
}

bool ThreadPrivate::hasPendingJobs()
{
    QMutexLocker locker(&mutex);
    return !jobs.isEmpty();
}

Job *ThreadPrivate::nextPendingJob()
{
    QMutexLocker locker(&mutex);
    if (!job.hasNext())
        job.toFront();
    return job.next();
}

void ThreadPrivate::removeJob()
{
    QMutexLocker locker(&mutex);
    job.remove();
}

}
