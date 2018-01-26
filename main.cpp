#include "process.h"

int __algorithmChoice__();
std::vector<process> SJF_userInput();
std::vector<process> SJF_sort(std::vector<process> p);
std::vector<process> SJF_calcWaitTime(std::vector<process> p);
float __calcAvgWaitTime__(std::vector<process> p);

int main() {

    int userChoice = __algorithmChoice__();

    switch (userChoice){
        case (1): {
            std::vector<process> x = SJF_userInput();
            x = SJF_sort(x);
            x = SJF_calcWaitTime(x);
            std::cout << std::setw(20) << "Process " << std::setw(20) << "Burst Time "
                      << std::setw(20) << "Wait Time" << std::endl;

            for (int i = 0; i < x.size(); i++) {
                printElement(x[i].get_p_Num(), 20);
                printElement(x[i].get_p_BurstTime(), 20);
                printElement(x[i].get_p_WaitTime(), 20);
                std::cout << std::endl;
            }

            std::cout << "\n\n The average wait time is: " << __calcAvgWaitTime__(x) << std::endl;
            break;
        }

        //case (2):

    }

    return 0;
}

int __algorithmChoice__(){

    int choice = 0;
    std::cout << "Choose an algorithm.\n" << "     Type '1' for Shortest Job First.\n"
              << "     Type '2' for Priority Scheduling.\n";
    std::cin >> choice;

    return choice;
}

std::vector<process> SJF_userInput(){

    int n = 0; //n is the number of processes
    float burstTime = 0;

    //User input for n
    std::cout << "Enter the number of processes (Their index will begin at 0): ";
    std::cin >> n;

    //Constructs the object x then initializes the vector p with n copies of x.
    process x(0, 0.0);
    std::vector<process> p(n, x); //constructor

    //User input for burst time of each element in p
    for (int i = 0; i < p.size(); i++){

        p[i].set_p_Num(i);
        std::cout << "Enter process " << p[i].get_p_Num() << "'s burst time: ";
        std::cin >> burstTime;
        p[i].set_p_BurstTimes(burstTime);
    }

    return p;
}

std::vector<process> SJF_sort(std::vector<process> p){

    //Sorts objects based on their burst time.
    std::vector<process> p_copy = p;
    std::sort(p_copy.begin(), p_copy.end());

    return p;
}

//Receives the sorted vector as a parameter and then calculates the wait time
std::vector<process> SJF_calcWaitTime(std::vector<process> p){

    float waitTimeSum = 0;

    //Calculate the wait time
    for (int i = 0; i < p.size(); i++){

        if (i == 0){

            p[i].set_p_WaitTime(0);
            waitTimeSum = 0;
        }

        else {

            //Calculate the sum of burst times for indexes
            for (int j = 1; j < p.size(); j++){

                waitTimeSum += p[j].get_p_BurstTime();
                p[j].set_p_WaitTime(waitTimeSum);
            }
        }
    }

    return p;
}

std::vector<pri_process> PRI_userInput(){

    int n = 0; //n is the number of processes
    float burstTime = 0;
    int pri = 0;

    //User input for n
    std::cout << "Enter the number of processes (Their index will begin at 0): ";
    std::cin >> n;

    //Constructs and initializes y to an empty set of attributes, then creates a vector of n copies of y.
    pri_process y(0, 0, 0.0);
    std::vector<pri_process> p(n, y);

    //User input for burst time of each element in p
    for (int i = 0; i < p.size(); i++){

        pri = 0;
        p[i].set_p_Num(i);
        std::cout << "Enter process " << p[i].get_p_Num() << "'s burst time: ";
        std::cin >> burstTime;
        p[i].set_p_BurstTimes(burstTime);
        std::cout << "Enter process " << p[i].get_p_Num()
                                      << "'s priority. 1 is the highest, 5 is the lowest: ";
        std::cin >> pri;
    }

    return p;
}

std::vector<pri_process> PRI_sort(std::vector<pri_process> p){

    //Sorts objects based on their priority.
    std::vector<pri_process> p_copy = p;
    std::sort(p_copy.begin(), p_copy.end());
}

std::vector<pri_process> PRI_calcWaitTime(std::vector<pri_process> p){

    float waitTimeSum = 0;

    //Calculate the wait time
    for (int i = 0; i < p.size(); i++){

        if (i == 0){

            p[i].set_p_WaitTime(0);
            waitTimeSum = 0;
        }

        else {

            //Calculate the sum of burst times for indexes
            for (int j = 1; j < p.size(); j++){

                waitTimeSum += p[j].get_p_BurstTime();
                p[j].set_p_WaitTime(waitTimeSum);
            }
        }
    }

    return p;
}

float __calcAvgWaitTime__(std::vector<process> p){

    float waitTimeSum = 0;

    for (int i = 0; i < p.size(); i++)
        waitTimeSum += p[i].get_p_WaitTime();

    float avgWaitTime = waitTimeSum / p.size();

    return avgWaitTime;
}