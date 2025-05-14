#include <core.hpp>

batch toBatch(char char_array[8]){
    batch batch;
    for (size_t i = 0; i < 8; i++)
    {
        batch.tasks[i].type = char_array[i];
    }
    return batch;
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

Cpu::Cpu()
{
    cores[0].op_task = 'H';
    cores[1].op_task = 'M';
    cores[2].op_task = 'L';
    
}

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

uint Cpu::AsignBatch(batch &batch){
    for (size_t i = 0; i < 8; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (this->cores[j].op_task == batch.tasks[i].type)
            {
                int indexes_lmao[3] = {j,j,j};
                //std::cout << indexes_lmao[0] << indexes_lmao[1] << indexes_lmao[2];
                if (++indexes_lmao[1] > 2)
                {
                    indexes_lmao[1] -= 3;
                }
                indexes_lmao[2] = indexes_lmao[1];
                if (++indexes_lmao[2] > 2)
                {
                    indexes_lmao[2] -= 3;
                }
                //std::cout << "0-" << indexes_lmao[0] << " 1-" << indexes_lmao[1] << " 2-" << indexes_lmao[2] << "\n";
                if (this->cores[indexes_lmao[0]].p_time + 1 <= this->cores[indexes_lmao[1]].p_time + 2 && this->cores[indexes_lmao[0]].p_time + 1 <= this->cores[indexes_lmao[2]].p_time + 2)
                {
                    addTask(batch.tasks[i],indexes_lmao[0]);
                }
                else if (this->cores[indexes_lmao[1]].p_time + 2 <= this->cores[indexes_lmao[2]].p_time + 2)
                {
                    addTask(batch.tasks[i],indexes_lmao[1]);
                }
                else{
                    addTask(batch.tasks[i],indexes_lmao[2]);
                }
            }
        }
    }
    batchTime();
    return runTime();
}