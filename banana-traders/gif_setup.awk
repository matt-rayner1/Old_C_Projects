set terminal gif animate delay 1
scale = 0.05
set key off
set output "animate_RENAME.gif"
set yrange [0:100]
#change yrange to around the max value of wealth your richest trader has
set ylabel "wealth"

#EXAMPLE GNUPLOT INPUT TO CREATE A GIF AFTER load "gif_setup.awk":
#do for [i = 0:999] {plot sprintf("snap_%d.txt", i) u 1:2:(($3)*scale + 0.5) w p ps variable pt 6 notitle}
#               ^
#               change this based on how many snapshots you created.