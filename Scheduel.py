import pandas as pd
from  collections import deque

class Job:
    def __init__(self,num,reach_time,need_time,priority):
        self.num = num
        self.reach_time =reach_time
        self.need_time = need_time
        self.execute_time = need_time
        self.priority  =priority
        self.visit = 0
        self.wait_time =0
        self.turn_over_time = 0
        self.weight_turn_over =0

def  read_Jobdata():
    file = pd.read_csv("Job.csv",encoding="GBK")
    return file

def initial_jobs():
    job_list = []
    file = read_Jobdata()
    # create class for job
    for row in file.iterrows():
        job_list.append(Job(num = row[1]["作业ID"],reach_time=row[1]["到达时间"],need_time=row[1]["执行时间"],priority=row[1]["优先级"]))

    return job_list
# initial_jobs()

def findEarlyJob(jobs):
    min_time = float('inf')
    id = -1
    for job in jobs:
        if not job.visit and job.reach_time<=min_time:
            min_time = job.reach_time
            id = job.num
   # jobs[id-1].visit=1
    return id

def print_finish_job(id,wait_time,turn_over_time,weight_turn_over):
        print(f"执行完成的作业是: {id}号作业，等待时间为:{wait_time},周转时间为:{turn_over_time},带权周转时间为:{weight_turn_over:.2f}")

def FCFSschedulejob():
    print("-------------------------------------")
    print("先来先服务")
    jobs = initial_jobs()
    q = deque()
    count = len(jobs)
    while count:
        id = findEarlyJob(jobs)  # find the earliest job
        q.append(id)
        count-=1
    first_job =  jobs[q.popleft() - 1]
    cur_time =first_job.reach_time
    finish_time = cur_time+first_job.need_time
    wait_time = 0
    turnover_time = first_job.need_time

    print_finish_job(id= first_job.num,wait_time=wait_time,turn_over_time=turnover_time)

    while len(q)>0:    # while the length of q is more than 0
        cur_job = jobs[q.popleft() - 1]
        cur_time =max(finish_time,cur_job.reach_time)
        wait_time += cur_time - cur_job.reach_time  # current time - reach time of job
        finish_time = cur_time+cur_job.need_time   # current time + need time
        turnover_time += finish_time-cur_job.reach_time # finish time  - reach time
        weight_turn_over = (finish_time - cur_job.reach_time) / cur_job.need_time
        print_finish_job(id=cur_job.num,wait_time= cur_time - cur_job.reach_time,turn_over_time=finish_time-cur_job.reach_time,weight_turn_over=weight_turn_over)

    print("平均周转时间：", turnover_time/7)
    print("平均等待时间：", wait_time/7)
    print("-------------------------------------")



def findHighestPri(q):
    highest = 10
    id = -1
    for job in q:
        if  not job.visit and  job.priority<highest:
            id = job.num
            highest = job.priority
    return id




def HPFschedulejob():
    print("-------------------------------------")
    print("优先级高优先")
    jobs = initial_jobs()
    q = []
    count = len(jobs)
    first_id  = findEarlyJob(jobs)
    first_job =jobs[first_id-1]
    jobs[first_id-1].visit=1
    cur_time = first_job.reach_time
    finish_time = cur_time + first_job.need_time
    wait_time = 0
    turnover_time = first_job.need_time
    weight_turn_over =  turnover_time/first_job.need_time
    print_finish_job(id=first_job.num, wait_time=wait_time, turn_over_time=turnover_time,weight_turn_over=weight_turn_over)
    count-=1                       # means execute the first process


    for job in jobs:
        if not job.visit and job.reach_time<=finish_time:
            q.append(job)



    while count>0:                  # executing number of count
        if len(q)>0:
            id = findHighestPri(q=q)     # return the id of the highest priority job
        else:
            id = findEarlyJob(jobs)
        jobs[id-1].visit=1
        cur_job =jobs[id-1]
        cur_time = max(finish_time, cur_job.reach_time)
        wait_time += cur_time - cur_job.reach_time  # current time - reach time of job
        finish_time = cur_time + cur_job.need_time  # current time + need time
        turnover_time += finish_time - cur_job.reach_time  # finish time  - reach time
        weight_turn_over += (finish_time-cur_job.reach_time)/cur_job.need_time

        for job in jobs:
            if not job.visit and job.reach_time <= finish_time:
                q.append(job)

        print_finish_job(id=cur_job.num, wait_time=cur_time - cur_job.reach_time,
                         turn_over_time=finish_time - cur_job.reach_time,weight_turn_over=(finish_time-cur_job.reach_time)/cur_job.need_time)
        count -=1

    print("平均周转时间：", turnover_time / 7)
    print("平均等待时间：", wait_time / 7)
    print("平均带权周转时间： ",weight_turn_over/7)
    print("-------------------------------------")

def RR():
    print("-------------------------------------")
    print("RR算法")
    """initial time counting"""
    turnover_time = 0
    wait_time = 0
    weight_turn_over = 0
    time_slice = 10

    """"get the first reached job"""
    jobs = initial_jobs()
    ready_queue = deque()
    first_id = findEarlyJob(jobs)
    first_job = jobs[first_id - 1]
    first_job.visit=1
    ready_queue.append(first_job)
    count = len(jobs)

    cur_time = first_job.reach_time

    while count>0:
        """
        if ready_queue is not empty,then pop the head of the queue to execute,
        else there is no job in the ready queue,we need to get the next arriving job
        """
        if len(ready_queue) > 0:
            cur_job = ready_queue.popleft()
        else:
            id = findEarlyJob(jobs)
            cur_job=jobs[id-1]
        cur_job.visit = 1

        """executing process"""
        cur_time=max(cur_time,cur_job.reach_time)
        if cur_job.need_time >= time_slice:
            # cur_job.need_time -=time_slice
            cur_time += time_slice
        else:
            cur_time += cur_job.need_time
        cur_job.need_time -= time_slice


        for i in range(count):
            """find the job which arrived after the time slice"""
            id = findEarlyJob(jobs)
            if id ==-1:
                break
            job = jobs[id-1]

            if job.reach_time <= cur_time :
                ready_queue.append(job)
                job.visit=1

        if cur_job.need_time > 0:
            ready_queue.append(cur_job)
            print(cur_job.num, "号作业执行了", time_slice)
        else:
            print(cur_job.num, "号作业执行了", cur_job.need_time+time_slice)
            finish_time = cur_time
            cur_job.wait_time = finish_time-cur_job.reach_time-cur_job.execute_time
            cur_job.turn_over_time=finish_time - cur_job.reach_time
            cur_job.weight_turn_over=cur_job.turn_over_time/cur_job.execute_time
            turnover_time   +=   cur_job.turn_over_time
            wait_time       +=   cur_job.wait_time
            weight_turn_over+=   cur_job.weight_turn_over
            print_finish_job(id=cur_job.num, wait_time=   cur_job.wait_time,
                             turn_over_time= cur_job.turn_over_time,
                             weight_turn_over=cur_job.weight_turn_over)
            count -= 1


    print("平均等待时间：", wait_time / 7)
    print("平均周转时间：", turnover_time / 7)
    print("平均带权周转时间： ", weight_turn_over / 7)
    print("-------------------------------------")


if __name__ =="__main__":
    # FCFSschedulejob()
    #HPFschedulejob()
    RR()