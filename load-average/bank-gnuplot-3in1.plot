set terminal qt size 1920, 950
set grid xtics ytics mxtics mytics ls 12
set xtics 1
set ytics 1
set style line 12 lc rgb "black" lt 1 lw 1 
set grid 
set xrange [0:10] 
set yrange [-1:1]
set multiplot layout 3,1 columns


#plot    "./log.txt" using ($1/60.):5 title "busy time%" w linespoints lw 2 lc -1 
#plot "log.txt" using ($1/60.):2 title "r" w linespoints lw 2,  "log.txt" using ($1/60.):3 title "LA(1min)" w linespoints lw 2, "log.txt" using ($1/60.):4 title "sma(1min)" w linespoints lw 2 



plot    "bank-b.log"  using ($1/60):2 title 'R' w linespoint lw 2,  "bank-b.log"  using ((($1-0)/60)):($3) title 'Load average'   w linespoint lw 2  
plot    "bank-c.log"  using ($1/60):2 title 'R' w linespoint lw 2,  "bank-c.log"  using ((($1-0)/60)):($3) title 'Load average'   w linespoint lw 2
plot    "bank-bc.log" using ($1/60):2 title 'R' w linespoint lw 2,  "bank-bc.log" using ((($1-0)/60)):($3) title 'Load average'   w linespoint lw 2





unset multiplot

