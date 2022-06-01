#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<queue>
#include<algorithm>

using namespace std;
void travese_jobs();
void visitCheck();

struct Job{
    int id;
    int reach_time;
    int need_time;  // every time execute a time slice,need time minus a time slice
    int execute_time;   // the total executing time that a job needs
    int priority;
    int visit;
    int is_reach;
    int wait_time;
    int turn_over_time;
    float weight_turn_over;

}Jobs[10];
int cnt =0; // gobal jobs counter

void initial_jobs(){
    fstream input("data.txt");
    string line;
    if (!input) cout<<"open fail"<<endl;
  
    while(getline(input,line)){
        stringstream ss;
        ss<<line;
        ss>>Jobs[cnt].id>>Jobs[cnt].reach_time>>Jobs[cnt].need_time>>Jobs[cnt].priority;
    /*  reverse the total need time because 
        every time execute a time slice,need time minus a time slice*/
        Jobs[cnt].execute_time=Jobs[cnt].need_time;        
        cnt++;
    }
}

int findEarlyJob(){
    int min_time =1000;
    int id=-1;
    for (int i=0;i<cnt;i++){
        Job job = Jobs[i];
        if (!job.visit && job.reach_time<=min_time){
            min_time=job.reach_time;
            id =job.id;
        }
    }
    return id;
}

void print_finish_job(int id, int wait_time, int turn_over_time,float weight_turn_over){
    cout<<"finished job is: "<<id<<","<<" wait time is: "<<wait_time \
    <<", turn over time is: "<<turn_over_time<<", weighted turn over time is: "<<weight_turn_over<<endl;
}



void FCFSschedule(){
    cout<<"----------------------------------------------"<<endl;
    cout<<"First come first serve"<<endl;
    cout<<endl;
    initial_jobs();
    //travese_jobs();
    deque<int> q;
    int count =cnt;  // count the number of jobs remaining
    // cout<<"cnt:"<<cnt<<endl;
    while (count>0){
        int id = findEarlyJob();
        Job &cur_job = Jobs[id-1];
        cur_job.visit=1;
        q.push_back(id);
        count--;
    }
    Job &first_job= Jobs[q.front()-1];
    q.pop_front();
    first_job.visit=1;
    int cur_time = first_job.reach_time;
    int finish_time = first_job.reach_time;
    int wait_time =0;
    int turn_over_time = first_job.need_time;
    float weight_turn_over = float(turn_over_time)/first_job.need_time;

    print_finish_job(first_job.id,wait_time,turn_over_time,weight_turn_over);

    while(!q.empty()){
        Job &cur_job = Jobs[q.front()-1];
        q.pop_front();
        cur_job.visit=1;
        cur_time =max(finish_time,cur_job.reach_time);
        wait_time+=cur_time-cur_job.reach_time;
        finish_time = cur_time+cur_job.need_time;
        turn_over_time +=finish_time-cur_job.reach_time;
        weight_turn_over += float(finish_time-cur_job.reach_time)/cur_job.need_time;
        print_finish_job(cur_job.id,cur_time-cur_job.reach_time,finish_time-cur_job.reach_time,(finish_time-cur_job.reach_time)/cur_job.need_time);

    }
    cout<<endl;
    cout<<"Average turn over time : "<<float(turn_over_time)/cnt<<endl;
    cout<<"Average wait time : "<<float(wait_time)/cnt<<endl;
    cout<<"Average weighted wait time : "<<weight_turn_over/cnt<<endl;
    cout<<"----------------------------------------------"<<endl;

}

deque<Job> jobs_q;

int findHighPri(){  // we need transfer the quote method  else it wouldn't change
    int high =10;
    int id =-1;
    int order =-1;
    for (int i=0;i<jobs_q.size();i++){ // we need change the visit  state in in the deque 
        Job &job = jobs_q[i];
        //cout<<"job id"<<job.id<<" is visit?"<<job.visit<<endl;
        if (!job.visit && job.priority<high){
            id =job.id;
            high =job.priority;
            order =i;
        }
    }
    jobs_q[order].visit=1;
    return id;
}

void HPfschedule(){
    cout<<"----------------------------------------------"<<endl;
    cout<<"High priority first "<<endl;
    cout<<endl;
    initial_jobs();
    //travese_jobs();
    // deque<Job> q;
    int count =cnt;  // count the number of jobs remaining
    int first_id = findEarlyJob();
    Job &first_job =Jobs[first_id-1];

    first_job.is_reach=1;
    first_job.visit=1;
    
    int cur_time =first_job.reach_time;
    int finish_time = cur_time+first_job.need_time;
    int wait_time =0;
    float turn_over_time = first_job.need_time;
    float weight_turn_over =turn_over_time/first_job.need_time;
    print_finish_job(first_id,wait_time,turn_over_time,weight_turn_over);
    count-=1;

   for (int i=0;i<cnt;i++){
        Job &job = Jobs[i];
        if (!job.is_reach && job.reach_time<=finish_time){
            jobs_q.push_back(job);
            job.is_reach=1;
        }
   }

    while (count>0){
        int id;
        if(!jobs_q.empty()) id =findHighPri(); // return the id of highest priority job
        else  id = findEarlyJob();
        Job &cur_job = Jobs[id-1];
        cur_job.visit=1;
        cur_time =max(finish_time,cur_job.reach_time);
        finish_time = cur_time+cur_job.need_time;
       

        cur_job.wait_time=cur_time-cur_job.reach_time;
        cur_job.turn_over_time=finish_time-cur_job.reach_time;
        cur_job.weight_turn_over=float(finish_time-cur_job.reach_time)/cur_job.need_time;
        
        wait_time +=   cur_job.wait_time;
        turn_over_time +=cur_job.turn_over_time;
        weight_turn_over += cur_job.weight_turn_over;

        for (int i=0;i<cnt;i++){
            Job &job = Jobs[i];  // joh has been visit but they don't 
            if (!job.is_reach && job.reach_time<=finish_time){
                jobs_q.push_back(job);
                job.is_reach=1;
            }
        }

        print_finish_job(cur_job.id,cur_job.wait_time,cur_job.turn_over_time,cur_job.weight_turn_over);
        count--;
    }


    cout<<endl;
    cout<<"Average turn over time : "<<float(turn_over_time)/cnt<<endl;
    cout<<"Average wait time : "<<float(wait_time)/cnt<<endl;
    cout<<"Average weighted wait time : "<<weight_turn_over/cnt<<endl;
    cout<<"----------------------------------------------"<<endl;

}

deque<Job> ready_queue;

void RR(){
    cout<<"----------------------------------------------"<<endl;
    cout<<"Round Robin "<<endl;
    cout<<endl;
    /*""" initial time counting """*/
    float turn_over_time=0;
    float weight_turn_over=0;
    int wait_time=0;
    int time_slice=10;

    /*"""get the first reached job"""*/
    initial_jobs();
    int first_id=findEarlyJob();
    Job& first_job=Jobs[first_id-1];
    first_job.visit=1;
    ready_queue.push_back(first_job);
    int count =cnt;

    int cur_time =first_job.reach_time;

    while (count>0){
        /*
        if ready_queue is not empty,the pop the head of the queue to execute,
        else there is no job in the ready queue,we should call findEarlyjob to get the next arriving job
        */
        Job cur_job;
        int id;
        if (!ready_queue.empty()){
            cur_job=ready_queue.front();
            id =cur_job.id;
            ready_queue.pop_front();
            //cout<<"id: "<<cur_job.id<<endl;
        }
        else{
            id = findEarlyJob();
            cur_job=Jobs[id-1];
        }
        Jobs[id-1].visit=1;

        /*executing process*/
        cur_time = max(cur_time,cur_job.reach_time);
        if (cur_job.need_time>=time_slice)
            cur_time+=time_slice;
        else{
            cur_time+=cur_job.need_time;
        }
        cur_job.need_time-=time_slice;
        for(int i=0;i<count;i++){
            /*find the job which have arrived after executing a time slice*/
            int id = findEarlyJob();
            if(id==-1) break;
            Job& job=Jobs[id-1];
            if (job.reach_time<=cur_time){
                ready_queue.push_back(job);
                job.visit=1;
                job.is_reach=1;
            }
        }
        if (cur_job.need_time>0){
            ready_queue.push_back(cur_job);
            cout<<cur_job.id<<" is running: "<<time_slice<<" ms"<<endl;
        }
        else{
            cout<<cur_job.id<<" is running: "<<cur_job.need_time+time_slice<<" ms"<<endl;
            int finish_time =cur_time;
            cur_job.wait_time=finish_time-cur_job.reach_time-cur_job.execute_time;
            cur_job.turn_over_time=finish_time-cur_job.reach_time;
            cur_job.weight_turn_over=float(cur_job.turn_over_time)/cur_job.execute_time;
            
            wait_time +=   cur_job.wait_time;
            turn_over_time +=cur_job.turn_over_time;
            weight_turn_over += cur_job.weight_turn_over;

            print_finish_job(cur_job.id,cur_job.wait_time,cur_job.turn_over_time,cur_job.weight_turn_over);
            count--;  
        }
    }

    cout<<endl;
    cout<<"Average turn over time : "<<float(turn_over_time)/cnt<<endl;
    cout<<"Average wait time : "<<float(wait_time)/cnt<<endl;
    cout<<"Average weighted wait time : "<<weight_turn_over/cnt<<endl;
    cout<<"----------------------------------------------"<<endl; 
}

int main(){
   // FCFSschedule();
   // HPfschedule();
   RR();
    return 0;
}

void visitCheck(){
      for(int i=0;i<cnt;i++) cout<<"id: "<<i+1<<" visit :? "<<Jobs[i].visit<<endl;
}

void travese_jobs(){
    for (int i=0;i<cnt;i++){
        Job job= Jobs[i];
        cout<<"id : "<<job.id<<" reach_time :"<<job.reach_time<<" need time is :"<<job.need_time<<" priority is:"<<job.priority<<endl;
    }
}
