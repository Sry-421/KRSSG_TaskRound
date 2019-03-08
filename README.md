# KRSSG_TaskRound

# Task 1:
    Implementation of working of an elevator using FSM(Finite State Machine)

## Compiling and Running:

1.Compile the code using gcc compiler  
2.Execute the **a.out** file



# Task 2:
    Path Planning using RRT* and mimicing it on ROS TurtleSim
 
    
## Setup:

1. Add the package to your ROS workspace
2. Convert the python code into an executable file using **chmod +x /src/controller/con1.py**
3. Change the path of data.txt file in con1.py to same as rrt_file.cpp
4. Source the ros file using **source devel/setup.sh**

## Compiling:

1.`make rrt_file`

## **Running:**

1. `.\rrt_file test.jpg`
2. In a new terminal `roscore`
3. In a new terminal `rosrun turtlesim turtlesim_node`
4. In a new terminal (in your ROS workspace) `rosrun controller con1.py`

 ![RRT*](https://github.com/Sry-421/KRSSG_TaskRound/blob/master/show.jpg)
 ![ROS turtlesim](https://github.com/Sry-421/KRSSG_TaskRound/blob/master/show1.jpg)
 
 
 
# **Task 3"**
    Humanoid

## **Setup:**

1. Replace the strategy.cc in the **UTAustin Villa** codebase
2. Change the no. of players to **1**
3. In a copy of the original codebase, change the no. of players to **4**

## **Compiling:**
1.`cmake .`
2.`make`

## **Running:**
1. In a new terminal `rcssserver3d`
2. In a new terminal (roboviz directory) `./roboviz.sh`
3. In a new terminal (changed utaustin directory) `./start.sh`
4. In a new terminal (utaustin directory) `./start.sh`

![Roboviz](https://github.com/Sry-421/KRSSG_TaskRound/blob/master/show2.jpg)

---




    

    
