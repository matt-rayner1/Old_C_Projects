# banana-traders

Programs/tools required:
>C/C++ compiler

>gnuplot

>awk/gawk

This project simulates a very simple game played by pairs of traders:
1) Each trader starts with an equal amount of 'bananas' (e.g. 10)
2) Each pair of traders flips a coin. If heads, the 1st trader takes a banana from the 2nd. If tails, the 2nd trader takes a banana from the 1st. This step is repeated for a set amount of time.
3) If a trader reaches 0 'bananas', they are out of the game and can no longer play. 

This is an example of a rather well known phenomenon of many names: "The Pareto Distribution", "The Matthew Principle", "Zipf's Law", "The 80/20 rule".
You may have heard "20% of the population owns 80% of the world's wealth", or "For to every one who has will more be given, and he will have abundance; but from him who has not, even what he has will be taken away." (Matthew 25:29, RSV).

I made this project after I listened to Jordan Peterson speaking about wealth distribution. He described the game above, and I thought that it would be interesting to simulate it properly to see the outcome for myself.

This phenomenon pops up universally on many different scales: 20% of stars contain 80% of the (non-dark) matter. 20% of workers in a company/environment do 80% of the work (works on human species and ant species alike!). 20% of criminals commit 80% of crimes. 20% of words are used 80% of the time. The list goes on and on. The idea has fascinated me since I first heard it.

--------------------------------------------------------------------

# Method

1) Use "banana_traders.c" to generate a data file ("trader_data.txt"). You can change the 3 main parameters (number of traders, starting bananas, total sim time) in the INITIALISE section of the code if you wish.
2) Use "data_split.c" to split the output file into snapshots, each containing 1 time frame for the simulation. TIP: you may want to create a new folder and put the "trader_data.txt" and "data_split.c" in there, as many small snap files will be created.
3) Load gnuplot (in the directory containing the "snap" files). Modify the "gif_setup.awk" file if needed (use trial and error).

    Type >(gnuplot) load "gif_setup.awk", 
    
    followed by >do for[i = 0:999] {plot sprintf("snap_%d.txt", i) u 1:2:(($3)*scale + 0.5) w p ps variable pt 6 notitle}
    
    This will create a .gif with point size dependent on how large/wealthy the trader is.
    (note that the index will be different depending on how many snaps you have).
4) Enjoy your .gif :) [I have provided an example .gif in the repository]
