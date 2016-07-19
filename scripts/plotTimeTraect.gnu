set term png
set terminal png enhanced size 1280, 1024
filename = 'traect.txt'

set style line 1 lc rgb "black"
set key box linestyle 1
set key width 1
set key height 1
set output "traect.png"
set xlabel "Time"
set ylabel "R"
plot filename using 1:2 title "Time dependency" with linespoints pointtype 3

set output "traectln.png"
set logscale y
plot filename using 1:2 title "Time dependency" with linespoints pointtype 3

set output "traectln2.png"
set logscale xy
plot filename using 1:2 title "Time dependency" with linespoints pointtype 3


