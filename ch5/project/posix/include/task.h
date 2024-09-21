/**
 * Representation of a task in the system.
 */

#ifndef TASK_H
#define TASK_H

// representation of a task
typedef struct task
{
    /** A human-readable name for the task */
    char *name;
    /** An unique ID for the Task */
    int tid;
    /** The CPU priority of the task */
    int priority;
    /** The CPU burst the task takes to execute */
    int burst;
    /** The remaining burst for a task to be completed */
    int remaining_burst;
} Task;

#endif
