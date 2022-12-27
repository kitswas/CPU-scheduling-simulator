#ifndef SCHEDULER_CLASS
#define SCHEDULER_CLASS

#include "min_heap.hpp"
#include "rbtree.hpp"
#include "logger.hpp"

/**
 * @brief Abstract class for all scheduler types
 *
 */
class Scheduler
{
protected:
public:
	virtual std::vector<std::unique_ptr<Process>> schedule(time_unit &currentTime, std::shared_ptr<Logger> logger, time_unit quantum) = 0;
	virtual bool addToReadyQueue(std::unique_ptr<Process> &process, time_unit currentTime) = 0;
	// virtual void printSchedule() = 0;
};

class FCFS : public Scheduler
{
private:
	MinHeap<std::unique_ptr<Process>> ready_queue;

public:
	FCFS();
	~FCFS();
	std::vector<std::unique_ptr<Process>> schedule(time_unit &currentTime, std::shared_ptr<Logger> logger, time_unit quantum = -1);
	bool addToReadyQueue(std::unique_ptr<Process> &process, time_unit _currentTime = -1);
};

struct RRProcess
{
	std::unique_ptr<Process> process;
	time_unit remainingBurstTime;
	time_unit reentryTime;
	RRProcess(std::unique_ptr<Process> process, time_unit remainingBurstTime, time_unit &reentryTime) : process(std::move(process)), remainingBurstTime(remainingBurstTime), reentryTime(reentryTime) {}
};

std::ostream &operator<<(std::ostream &os, const RRProcess &rrprocess);

class RR : public Scheduler
{
private:
	MinHeap<std::unique_ptr<RRProcess>> ready_queue;

public:
	RR();
	~RR();
	std::vector<std::unique_ptr<Process>> schedule(time_unit &currentTime, std::shared_ptr<Logger> logger, time_unit quantum);
	bool addToReadyQueue(std::unique_ptr<Process> &process, time_unit currentTime);
};

struct CFSProcess
{
	std::unique_ptr<Process> process;
	time_unit vruntime;
	time_unit remainingBurstTime;
	time_unit reentryTime;
	CFSProcess(std::unique_ptr<Process> process, time_unit vruntime) : process(std::move(process)), vruntime(vruntime) {}
};

std::ostream &operator<<(std::ostream &os, const CFSProcess &cfsprocess);

class CFS : public Scheduler
{
private:
	RBTree<std::unique_ptr<CFSProcess>> ready_queue;

public:
	CFS();
	~CFS();
	std::vector<std::unique_ptr<Process>> schedule(time_unit &currentTime, std::shared_ptr<Logger> logger, time_unit quantum);
	bool addToReadyQueue(std::unique_ptr<Process> &process, time_unit _currentTime = -1);
};

#endif // SCHEDULER_CLASS
