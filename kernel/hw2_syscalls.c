#include <linux/kernel.h>
#include <linux/sched.h>

int sys_is_SHORT(int pid) {
	struct task_struct *task;
	int ret_value = -EINVAL;
	
	if (pid < 0) {
		return ret_value;
    }

    if (pid == 0) {
        task = &init_task;
    } else {
        task = find_task_by_pid(pid);
    }

	if (!task) {
        return ret_value;
    }

	if(task->policy == SCHED_SHORT) {
		if(!task->trial_num){
			ret_value = 0;
		}
		ret_value = 1;
	}
	return ret_value;
}

int sys_remaining_time(int pid)	{
	struct task_struct *task;
	int ret_value = -EINVAL;	
	
	if (pid < 0) {
		return ret_value;
    }

    if (pid == 0) {
        task = &init_task;
    } else {
        task = find_task_by_pid(pid);
    }

	if (!task) {
        return ret_value;
    }
	
	if (task->policy == SCHED_SHORT) {
		ret_value = (task->time_slice) * (1000/HZ);
		if(!task->trial_num) {
			ret_value = 0;
		}
	}
	return ret_value;
}

int sys_remaining_trials(int pid) {
	struct task_struct *task;
	int ret_value = -EINVAL;	
	
	if (pid < 0) {
		return ret_value;
    }
	
    if (pid == 0) {
        task = &init_task;
    } else {
        task = find_task_by_pid(pid);
    }
	
	if (!task) {
        return ret_value;
    }
	
	if(task->policy == SCHED_SHORT) {
		ret_value = task->trial_num;
	}
	return ret_value;
}
