set terminal pngcairo size 800,600
set output "wave.png"

set xlabel "r"
set ylabel "f(r)"
set title "Hydrogen ground state radial wavefunction"

set grid

plot "wave.dat" using 1:2 with lines lw 2 title "numerical"