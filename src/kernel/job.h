#ifndef PARALLEL_JOB_H
#define PARALLEL_JOB_H

#include <Parallel/global.h>

#include <QtCore/qscopedpointer.h>

namespace Parallel {

class JobPrivate;
class PARALLEL_EXPORT Job
{
public:
    enum LoopCount {
        LoopOnce = 1,
        LoopForever = -1
    };

    Job();
    virtual ~Job();

    bool canLoop() const;
    int loop() const;
    int loopCount() const;
    void setLoopCount(int count);

protected:
    Job(JobPrivate *dd);

    virtual void run() = 0;

    QScopedPointer<JobPrivate> d;

private:
    PARALLEL_DECLARE_PRIVATE(Job)

    Q_DISABLE_COPY(Job)

    void runJob();

    friend class Thread;
    friend class JobGroup;
};

class PARALLEL_EXPORT JobGroup : public Job
{
public:
    JobGroup();
    ~JobGroup();

    void addJob(Job *job);
    void removeJob(Job *job);

protected:
    void run() override;
};

}

#endif // PARALLEL_JOB_H
