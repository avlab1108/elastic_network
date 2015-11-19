set style data lines
set grid

set xlabel "u12"
set ylabel "u23"
set zlabel "u13"

splot "/home/minas/elastic_network/utests/trajectory/sample/trajectory1.txt" using 1:2:3 with lines, \
      "/home/minas/elastic_network/utests/trajectory/sample/trajectory2.txt" using 1:2:3 with lines, \
      "/home/minas/elastic_network/utests/trajectory/sample/trajectory3.txt" using 1:2:3 with lines, \
      "/home/minas/elastic_network/utests/trajectory/sample/trajectory4.txt" using 1:2:3 with lines, \
      "/home/minas/elastic_network/utests/trajectory/sample/trajectory5.txt" using 1:2:3 with lines, \
      "/home/minas/elastic_network/utests/trajectory/sample/trajectory6.txt" using 1:2:3 with lines, \
      "/home/minas/elastic_network/utests/trajectory/sample/trajectory7.txt" using 1:2:3 with lines, \
      "/home/minas/elastic_network/utests/trajectory/sample/trajectory8.txt" using 1:2:3 with lines, \
      "/home/minas/elastic_network/utests/trajectory/sample/trajectory9.txt" using 1:2:3 with lines

set label at 0, 0, 0 "" point pointtype 5 pointsize 1

pause -1
