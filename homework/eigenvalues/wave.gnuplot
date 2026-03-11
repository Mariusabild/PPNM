set terminal pngcairo size 800,600
set output "wave.png"

set xlabel "r"
set ylabel "f(r)"
set title "Hydrogen s-wave radial functions"

set grid
set key left top

plot "wave.dat" using 1:2 with lines lw 2 title "ground state", \
     "wave.dat" using 1:3 with lines lw 2 title "1st excited", \
     "wave.dat" using 1:4 with lines lw 2 title "2nd excited"