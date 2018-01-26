//
// Created by duane on 1/23/18.
//

#ifndef CPU_SCHEDULER_PROCESS_H
#define CPU_SCHEDULER_PROCESS_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <exception>

class process{

public:

    process();
    process(int p_Num, float p_BurstTime);
    process(const process &p2);
    void set_p_Num(int procNum);
    void set_p_BurstTimes(float procBurstTime);
    void set_p_WaitTime(float procWaitTime);
    int get_p_Num();
    float get_p_BurstTime();
    float get_p_WaitTime();

    bool operator< (const process& other) const {
        return p_BurstTime < other.p_BurstTime;
    }

protected:
    int p_Num;
    float p_BurstTime;
    float p_WaitTime;
};

process::process() {p_Num = 0; p_BurstTime = 0.0;}
process::process(int procNum, float procBurstTime) {p_Num = procNum; p_BurstTime =  procBurstTime;}
process::process(const process &p2) {p_Num = p2.p_Num; p_BurstTime = p2.p_BurstTime;}
void process::set_p_Num(int procNum) {p_Num = procNum;}
void process::set_p_BurstTimes(float procBurstTime) {p_BurstTime = procBurstTime;}
void process::set_p_WaitTime(float procWaitTime) {p_WaitTime = procWaitTime;}
int process::get_p_Num(){return p_Num;}
float process::get_p_BurstTime() {return p_BurstTime;}
float process::get_p_WaitTime() {return p_WaitTime;}

class pri_process : public process{
public:
    pri_process();
    pri_process(int priority, int p_Num, float p_BurstTime);
    pri_process(const pri_process &p2);
    void set_p_priority(int priority);
    int get_p_priority();

    bool operator < (const pri_process& other) const {
        return p_priority < other.p_priority;
    }

protected:
    int p_priority;
};

pri_process::pri_process(){p_Num = 0; p_BurstTime = 0.0; p_priority = 0;}
pri_process::pri_process(int priority, int procNum, float procBurstTime){p_Num = procNum; p_BurstTime = procBurstTime; p_priority = priority;}
pri_process::pri_process(const process &p2)[p_Num = p2.p_Num; p_]
void pri_process::set_p_priority(int priority) {p_priority = priority;}
int pri_process::get_p_priority() {return p_priority;}



template<typename T> void printElement(T t, const int& width){
    std::cout << std::setw(width) << std::setfill(' ') << t;
}



#endif //CPU_SCHEDULER_PROCESS_H

