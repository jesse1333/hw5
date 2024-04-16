#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here

// Add your implementation of schedule() and other helper functions here

// Helper function to check if a worker has exceeded the maximum number of shifts


bool scheduleHelper(const AvailabilityMatrix& avail, size_t dailyNeed, size_t maxShifts,
                    DailySchedule& schedule, size_t day, size_t shiftCount, vector<int> shifts, int workerIndex) {
    // if all of the days are filled
    if (day == avail.size()) {
        return true;
    }

    if (shiftCount == dailyNeed) {
        return scheduleHelper(avail , dailyNeed, maxShifts, schedule, day + 1, 0, shifts, 0);
    }

    if (workerIndex == avail[0].size()) {
        return false;
    }

    if (avail[day][workerIndex] && shifts[workerIndex] < maxShifts) {
        // assigns worker & updates shift
        schedule[day].push_back(workerIndex);
        shiftCount++;
        shifts[workerIndex]++;

        // moves onto next day
        if(scheduleHelper(avail, dailyNeed, maxShifts, schedule, day, shiftCount, shifts, workerIndex + 1)) {
            return true;
        }

        schedule[day].pop_back();
        shiftCount--;
        shifts[workerIndex]--;
        if (scheduleHelper(avail, dailyNeed, maxShifts, schedule, day, shiftCount, shifts, workerIndex + 1)) {
            return true;
        }
    }

    else {
        if (scheduleHelper(avail, dailyNeed, maxShifts, schedule, day, shiftCount, shifts, workerIndex + 1)) {
            return true;
        }
    }

    return false;
}


bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
    int workerIndex = 0;
    vector<int> shifts;
    for (int i = 0; i < avail[0].size(); i++) {
        shifts.push_back(0);
    }

    // resize the matrix to the same as available size
    sched.resize(avail.size());   

    return scheduleHelper(avail, dailyNeed, maxShifts, sched, 0, 0, shifts, workerIndex);
}


