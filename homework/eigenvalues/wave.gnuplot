set terminal pngcairo size 800,600

# -------------------------
# Wavefunction plot
# -------------------------

set output "wave.png"

set xlabel "r"
set ylabel "f(r)"
set title "Hydrogen ground state radial wavefunction"

set grid

plot "wave.dat" using 1:2 with lines lw 2 title "numerical"


# -------------------------
# dr convergence
# -------------------------

set output "dr_convergence.png"

set xlabel "dr"
set ylabel "E0"
set title "Convergence of ground state energy vs dr"

set grid

plot "dr.dat" using 1:2 with linespoints lw 2 title "numerical", \
     -0.5 with lines lw 2 title "exact"


# -------------------------
# rmax convergence
# -------------------------

set output "rmax_convergence.png"

set xlabel "rmax"
set ylabel "E0"
set title "Convergence of ground state energy vs rmax"

set grid

plot "rmax.dat" using 1:2 with linespoints lw 2 title "numerical", \
     -0.5 with lines lw 2 title "exact"