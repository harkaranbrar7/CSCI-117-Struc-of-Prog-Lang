// Practice for Concurrent programming with Java Threads
// Serially reusable resource management for concurrent processes.
// there exist two types of serially reusable resources (SR1 and SR2) with 3
// units and 2 units, respectively, and 6 concurrent processes in the system.
// Each process acquires both SR1 and SR2 (one unit each), performs operation, and
// releases SR1 and SR2 units after the operation.

// Created by Harkaranjeet Singh on 11/27/17.
// Copyright © 2017 Harkaranjeet Singh. All rights reserved.


import java.util.Random; //for random numbers
import java.util.Vector; //for vector

// This is main class of the program
// It will created the resources and send to new Process via thread
public class sr_manager    //main class
{

    //creating resources
    static sr1 r1 = new sr1();
    static sr2 r2 = new sr2();

    public static void main(String args[])
    {
        //create and start 6 threads for 6 concurrent Processes
        System.out.println("========= Checked Successful =========");

        //vector for Process
        Vector<process> my_process = new Vector<process>();

        // for loop
        for(int i=0; i<6 ;i++)
        {
            //to create process and start process
            my_process.add(new process(i, r1, r2));
            my_process.get(i).start();

        }

    }
}


//sr1 is resource class, it is giving out three resources.
//acquiring and releasing a resources

class sr1 //class for shared resource r1
{
    //available resources
    private static int avail1 = 3;

    private static String name = "myResources1";

    //display
    private static final int set = 1;

    //synchronized method cannot be interrupted
    //only one thread can access at a time
    public synchronized void acquire(int id)
    {
        int display_id;
        display_id = id + set;

        if(avail1<1)
        {
            try{
                System.out.println("Process-" + display_id + " waiting for " +sr1.name);
                wait();
            }
            catch (InterruptedException  IE)
            {
                System.out.println("Get an ERROR"+IE.getMessage());
            }
        }
        avail1 --;
        System.out.println("Process- "+display_id+" acquires "+sr1.name);
    }
    //synchronized method cannot be interrupted
    //only one thread can access at a time
    public synchronized void release(int id)
    {
        int display_id;
        display_id = id + set;
        avail1 ++;
        System.out.println("Process - " + display_id + " releases " + sr1.name);
        notify();
    }
}//class sr1

class sr2 //class for shared resource r2
{ //available resources
    private static int avail2 = 2;

    private static String name = "myResources2";

    //display
    private static final int set = 1;

    //synchronized method cannot be interrupted
    //only one thread can access at a time
    public synchronized void acquire(int id)
    {
        int display_id;
        display_id = id + set;

        if(avail2<1)
        {
            try{
                System.out.println("Process- " + display_id + " waiting for " +sr2.name);
                wait();
            }
            catch (InterruptedException IE)
            {
                System.out.println("Get an ERROR"+IE.getMessage());
            }
        }
        avail2 --;
        System.out.println(" Process- "+display_id+" acquires "+sr2.name);
    }
    //synchronized method cannot be interrupted
    //only one thread can access at a time
    public synchronized void release(int id)
    {
        int display_id;
        display_id = id + set;
        avail2 ++;
        System.out.println(" Process- " + display_id + " releases " + sr2.name);
        notify();
    }
} //class sr2

// Process class extends the Thread class
// So concurrent process running at the same time.

class process extends Thread //thread class name is "process"
{   static sr1 r1;
    static sr2 r2;
    private int id;

    private static final int set = 1;

    public process(int i,sr1 r1, sr2 r2) //constructor
    {

        this.r1 = r1;
        this.r2 = r2;
        int display_id;
        this.id =i;
        display_id = this.id+set;
        System.out.println("Thread for Process - " +  display_id + " is created ");
    }

    public void run()
    {
        //acquire r1 and r2
        //display "Process_i is working"
        //release r1 and r2

        int display_id;
        display_id = this.id + set;

        int random_wait;
        int random_wait_1;
        
        Random randGenerator = new Random();
        random_wait = (randGenerator.nextInt() % 2000) + 200 + 1;
        random_wait_1 = (randGenerator.nextInt() % 1000) + 500;

        if(random_wait < 0)
            random_wait *= -1;
        if(random_wait_1 < 0)
            random_wait_1 *= -1;




        try
        {
            Thread.sleep(random_wait_1);
        }catch(InterruptedException IE)
        {
            System.out.println("Get an ERROR " + IE.getMessage());
        }

        r1.acquire(this.id);  //acquire

        try
        {
            Thread.sleep(random_wait_1);
        }
        catch(InterruptedException IE)
        {
            System.out.println("Get an ERROR " + IE.getMessage());
        }
        r2.acquire(this.id); //acquire


        System.out.println("Procces - " + display_id + " is working ");

        try{
            Thread.sleep(random_wait);
        }catch(InterruptedException IE){
            System.out.println("Get an ERROR " + IE.getMessage());
        }
        try{
            Thread.sleep(random_wait_1);
        }catch(InterruptedException IE){
            System.out.println("Get an ERROR " + IE.getMessage());
        }
        r1.release(this.id); //release
        try
        {
            Thread.sleep(random_wait_1);
        }
        catch(InterruptedException IE)
        {
            System.out.println("Get an ERROR " + IE.getMessage());
        }
        r2.release(this.id); //release

    }
}//class Process
