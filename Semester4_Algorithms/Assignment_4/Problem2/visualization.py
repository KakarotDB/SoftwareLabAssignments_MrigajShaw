import matplotlib.pyplot as plt
import numpy as np

# --- 1. DATA FROM YOUR SCREENSHOT ---
N_measured = 120000

# Median of Medians (MoM) Data
time_mom_measured = 0.005000
comps_mom_measured = 1065166

# Quickselect (QS) Data
time_qs_measured = 0.001000
comps_qs_measured = 440745

# --- 2. EXTRAPOLATION LOGIC ---
# We create a range of input sizes from 10k to 1 Million households
# to visualize how the difference scales.
n_values = np.linspace(10000, 1000000, 50)

# Calculate the "Slope" (Constant Factor) based on your run
# Slope = Measured Value / 120,000
slope_time_mom = time_mom_measured / N_measured
slope_time_qs = time_qs_measured / N_measured
slope_comps_mom = comps_mom_measured / N_measured
slope_comps_qs = comps_qs_measured / N_measured

# Generate projected y-values (Linear Projection O(n))
time_mom_projected = n_values * slope_time_mom
time_qs_projected = n_values * slope_time_qs
comps_mom_projected = n_values * slope_comps_mom
comps_qs_projected = n_values * slope_comps_qs

# Theoretical Worst Case for Quickselect (Quadratic O(n^2))
# Scaled dramatically to fit on graph for visual comparison
# This represents what happens if data is sorted/malicious
time_qs_worst_case = (n_values ** 2) * (slope_time_qs / N_measured * 10) 

# --- 3. PLOTTING ---
plt.figure(figsize=(14, 6))

# PLOT 1: Execution Time vs Input Size
plt.subplot(1, 2, 1)
plt.plot(n_values, time_mom_projected, label='Median of Medians (Deterministic)', color='blue', linewidth=2)
plt.plot(n_values, time_qs_projected, label='Quick Select (Randomized)', color='green', linewidth=2)
# Add the measured point marker
plt.scatter([N_measured], [time_mom_measured], color='blue', zorder=5)
plt.scatter([N_measured], [time_qs_measured], color='green', zorder=5)
plt.text(N_measured, time_mom_measured, f'  Measured (N={N_measured})', fontsize=9)

plt.title('Execution Time Analysis', fontsize=14)
plt.xlabel('Input Size (Number of Households)', fontsize=12)
plt.ylabel('Time (Seconds)', fontsize=12)
plt.legend()
plt.grid(True, linestyle='--', alpha=0.6)

# PLOT 2: Number of Comparisons vs Input Size
plt.subplot(1, 2, 2)
plt.plot(n_values, comps_mom_projected, label='Median of Medians', color='blue', linewidth=2)
plt.plot(n_values, comps_qs_projected, label='Quick Select', color='green', linewidth=2)
# Add the measured point marker
plt.scatter([N_measured], [comps_mom_measured], color='blue', zorder=5)
plt.scatter([N_measured], [comps_qs_measured], color='green', zorder=5)

plt.title('Computational Cost (Comparisons)', fontsize=14)
plt.xlabel('Input Size (Number of Households)', fontsize=12)
plt.ylabel('Total Comparisons', fontsize=12)
plt.legend()
plt.grid(True, linestyle='--', alpha=0.6)

plt.tight_layout()
plt.show()
