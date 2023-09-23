#include <stdio.h>
#include <stdlib.h>

// Define a struct to represent a patient
struct Patient {
    char name;
    int arrival_time;
    int treatment_time;
    int urgency;
    int remaining_time; // Used for RR
};

// Function to calculate the average waiting time
float calculateAverageWaitingTime(int waiting_time[], int num_patients) {
    int total_waiting_time = 0;
    for (int i = 0; i < num_patients; i++) {
        total_waiting_time += waiting_time[i];
    }
    return (float)total_waiting_time / num_patients;
}

// Function to implement FCFS scheduling
void fcfsScheduling(struct Patient patients[], int num_patients) {
    int waiting_time[num_patients];
    waiting_time[0] = 0;

    for (int i = 1; i < num_patients; i++) {
        waiting_time[i] = waiting_time[i - 1] + patients[i - 1].treatment_time;
    }

    printf("FCFS Order: ");
    for (int i = 0; i < num_patients; i++) {
        printf("%c ", patients[i].name);
    }

    printf("\nAverage Waiting Time (FCFS): %.2f\n", calculateAverageWaitingTime(waiting_time, num_patients));
}

// Function to implement SJF scheduling
void sjfScheduling(struct Patient patients[], int num_patients) {
    // Sort patients by treatment time (shortest treatment first)
    for (int i = 0; i < num_patients - 1; i++) {
        for (int j = 0; j < num_patients - i - 1; j++) {
            if (patients[j].treatment_time > patients[j + 1].treatment_time) {
                struct Patient temp = patients[j];
                patients[j] = patients[j + 1];
                patients[j + 1] = temp;
            }
        }
    }

    int waiting_time[num_patients];
    waiting_time[0] = 0;

    for (int i = 1; i < num_patients; i++) {
        waiting_time[i] = waiting_time[i - 1] + patients[i - 1].treatment_time;
    }

    printf("SJF Order: ");
    for (int i = 0; i < num_patients; i++) {
        printf("%c ", patients[i].name);
    }

    printf("\nAverage Waiting Time (SJF): %.2f\n", calculateAverageWaitingTime(waiting_time, num_patients));
}

// Function to implement Priority Scheduling (PS)
void priorityScheduling(struct Patient patients[], int num_patients) {
    // Sort patients by urgency level (higher urgency first)
    for (int i = 0; i < num_patients - 1; i++) {
        for (int j = 0; j < num_patients - i - 1; j++) {
            if (patients[j].urgency < patients[j + 1].urgency) {
                struct Patient temp = patients[j];
                patients[j] = patients[j + 1];
                patients[j + 1] = temp;
            }
        }
    }

    int waiting_time[num_patients];
    waiting_time[0] = 0;

    for (int i = 1; i < num_patients; i++) {
        waiting_time[i] = waiting_time[i - 1] + patients[i - 1].treatment_time;
    }

    printf("Priority Order: ");
    for (int i = 0; i < num_patients; i++) {
        printf("%c ", patients[i].name);
    }

    printf("\nAverage Waiting Time (Priority): %.2f\n", calculateAverageWaitingTime(waiting_time, num_patients));
}

// Function to implement Round Robin (RR) Scheduling
void roundRobinScheduling(struct Patient patients[], int num_patients, int time_quantum) {
    int waiting_time[num_patients];
    int remaining_time[num_patients];
    int total_waiting_time = 0;

    for (int i = 0; i < num_patients; i++) {
        remaining_time[i] = patients[i].treatment_time;
    }

    int time = 0;
    int done = 0;

    printf("RR Order: ");
    while (done < num_patients) {
        for (int i = 0; i < num_patients; i++) {
            if (remaining_time[i] > 0) {
                int min_time = (remaining_time[i] < time_quantum) ? remaining_time[i] : time_quantum;
                remaining_time[i] -= min_time;
                time += min_time;

                printf("%c ", patients[i].name);

                if (remaining_time[i] == 0) {
                    done++;
                    waiting_time[i] = time - patients[i].arrival_time - patients[i].treatment_time;
                    total_waiting_time += waiting_time[i];
                }
            }
        }
    }

    float average_waiting_time = (float)total_waiting_time / num_patients;
    printf("\nAverage Waiting Time (RR): %.2f\n", average_waiting_time);
}

int main() {
    struct Patient patients[] = {
        {'A', 0, 30, 3},
        {'B', 10, 20, 5},
        {'C', 15, 40, 2},
        {'D', 20, 15, 4}
    };

    int num_patients = sizeof(patients) / sizeof(patients[0]);
    int time_quantum = 10; // Time quantum for RR

    fcfsScheduling(patients, num_patients);
    sjfScheduling(patients, num_patients);
    priorityScheduling(patients, num_patients);
    roundRobinScheduling(patients, num_patients, time_quantum);

    return 0;
}