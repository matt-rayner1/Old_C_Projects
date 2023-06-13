# globular-cluster-sims

My 3rd year N-body code project for Physics degree. Creates .gif animations of globular cluster dynamics. (This is my first attempt at putting up a public repository on github.)

Programs/tools required:
>C/C++ compiler

>gnuplot

>awk/gawk

Refer to N_body_final.pdf for an in-depth report on the science and method behind this project, with additional help executing each step in the process.
I have added some of my own animations to the repository as well. You can also find a selection of these with descriptions at https://imgur.com/a/ayMCGTS.
Note that you will have to compile the programs yourself using a compiler of your choice. (I personally used MinGW for windows.)
Also note that the units and maths used in this are not scaled.

------------------------------------------------------------------

# tl;dr step-by-step process:

1) Create a data file containing initial positions and velocities of points in a globular cluster (or pair of clusters), with the use of 'sph_gencluster.c' or 'double_gencluster.c'. Try values of 'a' between 0 and 5.

2) use "GravityLab" - 'nbody_sh1.C' (see: https://www.ids.ias.edu/~piet/act/comp/algorithms/starter/nbody_sh1.html and https://www.ids.ias.edu/~piet/act/comp/algorithms/starter/readme.html for details. NOTE: I DID NOT CODE THIS PROGRAM) with the generated cluster points to simulate interaction under gravity. Also note that this step takes a long time to simulate (several hours to days!) General form of usage for this program is:
    >nbody_sh1 -d 0.04 -o 0.04 -t 15 < input.in > output.out

3) a) reduce the output data to its x, y, and z position (or velocity) components using awk: 
    >awk '{print $2 " $3 " $4}' output.out> output.plot        for UNIX terminals,
    
    >awk "{print $2 """ $3 """ $4}" output.out> output.plot    for windows based terminals.
    
   b) use "splitter2.c" to generate snapshots of the data at each time interval. 

4) Animate the snapshots with awk scripts and gnuplot:
   (Note that the loop index is dependent on how many snapshots created in your own simulation. It may not be 0:374...)
    >(>gnuplot) load "gif_setup.awk" 
    
    >(>gnuplot) do for [i = 0:374]{splot sprintf("snap_%d.txt", i)pt 7 ps 1 notitle}


If done correctly, by now you should have produced a .gif of a globular cluster simulation!

------------------------------------------------------------------

# Concepts Explored

Monte Carlo rejection techniques for generating points.

Reading/writing to files, manipulating data in files.

Memory allocation

Pseudo-random number generation
