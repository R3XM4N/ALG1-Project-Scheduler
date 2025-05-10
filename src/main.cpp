#include <vector>
#include <iostream>

typedef unsigned int uint;

struct task{
    char type;
    uint time = 0;
};

struct core{
    uint p_time = 0; //predicted time
    char op_task; //optimal task
    std::vector<task> tasks;
};

struct batch{
    task tasks[8];
};

class Cpu
{
private:
    uint real_time = 0;
    core cores[3];
    void addTask(task &task, uint core_index);
    void wipeData();
    uint batchTime();
public:
    uint roundRobin(batch &batch);
    uint runTime();
    void reset();
    Cpu(/* args */);
    ~Cpu() = default;
};

uint Cpu::roundRobin(batch &batch){
    int index = 0;
    for (size_t i = 0; i < 8; i++)
    {
        addTask(batch.tasks[i],index);
        index++;
        if (index > 2)
        {
            index = 0;
        }
    }
    batchTime();
    return runTime();
}

void Cpu::reset(){
    real_time = 0;
    wipeData();
}

uint Cpu::runTime(){
    return real_time;
}

uint Cpu::batchTime(){
    uint return_value;
    if (cores[0].p_time >= cores[1].p_time && cores[0].p_time >= cores[2].p_time )
    {
        real_time += cores[0].p_time;
        return_value = cores[0].p_time;
    }
    else if (cores[1].p_time >= cores[0].p_time && cores[1].p_time >= cores[2].p_time )
    {
        real_time += cores[1].p_time;
        return_value = cores[1].p_time;
    }
    else{
        real_time += cores[2].p_time;
        return_value = cores[2].p_time;
    }
    wipeData();
    return return_value;
}

void Cpu::wipeData(){
    for (size_t i = 0; i < 3; i++)
    {
        cores[i].p_time = 0;
        cores[i].tasks.clear();
    }
}

void Cpu::addTask(task &task, uint core_index){
    if (cores[core_index].op_task == task.type)
    {
        task.time = 1;
        cores[core_index].p_time += 1;
    }
    else{
        task.time = 2;
        cores[core_index].p_time += 2;
    }
    cores[core_index].tasks.push_back(task);
}

Cpu::Cpu(/* args */)
{
    cores[0].op_task = 'H';
    cores[1].op_task = 'M';
    cores[2].op_task = 'L';

}

batch toBatch(char char_array[8]){
    batch batch;
    for (size_t i = 0; i < 8; i++)
    {
        batch.tasks[i].type = char_array[i];
    }
    return batch;
}

int main(int argc, char** argv){
    Cpu* cpu = new Cpu();
    char arr[8] = {'H','M','L','H','M','L','H','M'};
    batch batch = toBatch(arr);
    std::cout << "Round robin: " << cpu->roundRobin(batch) << "\n";
    return 0;
}