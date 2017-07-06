# Voronoi Path Planning
The Robot Revolution already is happening. It has been happening for decades. Today we are can see more of robots around. The packBot from iRobot, TUG Autonomous mobile robots from aethon, Baxter fromrethink robotics and many more like them. These days, there are robots helping scientists at the highly technical labs, and there might be one mowing your lawn. All of the convenience that we already enjoy took decades of hard work by scientists. Some of the problems that robotics engineers were struggling with fifty years ago still have not been solved, so there is a whole lot of history that went into the robots that we rely on today, and it just might help you understand why we do not have robots taking care of our every need. Technically speaking, a robot is just a machine designed to accomplish a task. When we talk about robots, we are really talking about machines that use their programming to make decisions.

In real life, finding path is easy, as our mind processes the image acquired by our eyes, and find an obstacle free path depending on the environment. The same sequence is followed by robots. They need to process the image or data acquired by their sensors and act accordingly. Path planning problem is considered a novel problem in AI. In our case we are trying to solve the problem of moving the robot in best way possible taking into consideration multiple objective. We are also taking a constraint and checking for feasibility of a particular path.

## 1. Process input Image to convert it to bitmap image 
![realimage](/project/results/image.jpg?raw=true "Real Image")
![processedImage](/project/results/out.jpg?raw=true "Processed Image")

## 2. Create paths randomly as input for optimization function
We generate upto 5 random points on given image and use them for optimizaing our optiization function. Now, we have set of points (x<sub>0</sub> , y<sub>0</sub> ), (x<sub>1</sub> , y<sub>1</sub> ), ..., (x<sub>n</sub> , y<sub>n</sub> ) for a function y = f(x) where the values of x are in ascending order and our objective is to find the values of (x<sub>i</sub> , y<sub>i</sub> ) where i is such that the value of x i lies in between the adjacent points say x<sub>j</sub> and x<sub>(j+1)</sub>; j = 1, 2. . . n. We use cubic spline interpolation for getting smooth path from random points. As we can only interpolate sequentially increasing value of any one axis value. We converted the path points in reference to X-axis as well as Y-axis. Below is an illustration of getting spline interpolation of path to X vs Path Length and Y vs Path Length.

![spline](https://github.com/adarshnair01/Voronoi-Path-Planning/blob/master/figures/path.jpg?raw=true "Spline Interpolation")
![spline](https://github.com/adarshnair01/Voronoi-Path-Planning/blob/master/figures/x_spline.jpg?raw=true "Spline Interpolation")
![spline](https://github.com/adarshnair01/Voronoi-Path-Planning/blob/master/figures/y_spline.jpg?raw=true "Spline Interpolation")
