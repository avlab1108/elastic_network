set style data lines

set grid x
set grid y
set grid z

set view 60,45

set style line 5 lt rgb "blue" lw 1 pt 6

set xlabel "{/Symbol D}u_{12}/u_{12}^{(0)}"
set ylabel "{/Symbol D}u_{13}/u_{13}^{(0)}"
set zlabel "{/Symbol D}u_{23}/u_{23}^{(0)}"

splot for [i=1:20] "/home/minas/elastic_network/utests/trajectory/sample/trajectory".i.".txt" using 1:2:3 with lines notitle ls 5

set label at 0, 0, 0 "" point pointtype 7 pointsize 1 lc rgb "red" front
replot

pause -1
