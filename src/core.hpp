#ifndef CORE_HPP
#define CORE_HPP

#include <vector>

typedef unsigned int uint;

/**
 * @brief simple struct for storing tasks
 * 
 */
struct task{
    char type;
    uint time = 0;
};

/**
 * @brief simple struct for representing a CPU core
 * 
 */
struct core{
    uint p_time = 0; //predicted time
    char op_task; //optimal task
    std::vector<task> tasks;
};

/**
 * @brief One required format batch
 * 
 */
struct batch{
    task tasks[8];
};

/**
 * @brief class that's used to "simulate the CPU running"
 * 
 */
class Cpu
{
private:
    /**
     * @brief shows the simulated real-time runtime
     * 
     */
    uint real_time = 0;
    /**
     * @brief the 3 cores that are supposed to be assigned the tasks
     * 
     */
    core cores[3];
    /**
     * @brief Puts the task onto the core to do
     * 
     * @param task the task to be assigned
     * @param core_index the index of the core the task is supposed to get assigned to
     */
    void addTask(task &task, uint core_index);
    /**
     * @brief Wipes data of a batch so multiple batches can be simulated as required by the assignment so all
     * 
     */
    void wipeData();
    /**
     * @brief gets the real-time runtime of the batch and adds it to the real-time of the CPU
     * 
     * @return uint returns real-time runtime of the batch
     */
    uint batchTime();
public:
    /**
     * @brief uses round robin to assign tasks to cores as required by the assignment
     * 
     * @param batch the batch to be assigned
     * @return uint returns current real-time runtime of the CPU simulation 
     */
    uint roundRobin(batch &batch);
    /**
     * @brief custom algorithm for assigning tasks simple but still effective
     * 
     * @param batch the batch to be assigned
     * @return uint returns current real-time runtime of the CPU simulation
     */
    uint AsignBatch(batch &batch);
    /**
     * @brief gets the real-time runtime
     * 
     * @return uint returns real-time runtime of the CPU simulation
     */
    uint runTime();
    /**
     * @brief resets the CPU of all data into it's state it was in a after creation
     * 
     */
    void reset();
    /**
     * @brief Construct a new Cpu object using standard required settings required by the assignment
     * 
     */
    Cpu();
    /**
     * @brief Destroy the Cpu object defualt
     * 
     */
    ~Cpu() = default;
};

/**
 * @brief Converts a char array of 8 into a batch that the CPU can process
 * 
 * @param char_array The task difficulties
 * @return batch formatted
 */
batch toBatch(char char_array[8]);

#endif