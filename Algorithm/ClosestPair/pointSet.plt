set nokey
set size square
set xrange[-550:550]
set yrange[-550:550]
set palette defined (0 "blue", 1 "red")
unset colorbox
plot "output.txt" w p pt 7 ps 0.1 lc palette