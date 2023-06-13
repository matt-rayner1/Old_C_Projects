set terminal gif animate delay 1
set output "animate_RENAME.gif"
set xrange [-2:2]
set yrange [-1:1]
set zrange [-1:1]
#set view equal xyz
set ticslevel 0

#do for [i = 0:14] {splot sprintf("snap_%d.txt", i) pt 7 ps 1 lc rgb 'black' notitle}