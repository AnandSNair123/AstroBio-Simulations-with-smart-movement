Skip to content
AnandSNair123
AstroBio-Simulations
Repository navigation
Code
Issues
Pull requests
Actions
Projects
Wiki
Security
Insights
Settings
AstroBio-Simulations
/
README.md
in
main

Edit

Preview
Indent mode

Spaces
Indent size

2
Line wrap mode

Soft wrap
Editing README.md file contents
Selection deleted
52
53
54
55
56
57
58
59
60
61
62
63
64
65
66
67
68
69
70
71
72
73
74
75
76
77
78
79
80
81
82
83
84
85
86
87
88
89
90
91
92
93
94
95
96
97
98
99
100
101
102
103
104
105
106
107
108
109
110
111
112
113
114
115
116
117
118
119
120
121
122
123
124
125
126
127
128
129
130

### Core Classes

- **`Environment`**: Manages the 3D spatial grid of nutrient patches, including
nutrient distribution, acetate levels, CO2 concentration, and diffusion
mechanics
- **`Bacterium` (Species.h)**: Individual organism class that handles movement,
eating, reproduction, death, and adaptation behaviors
- **`Cluster`**: Main simulation controller that inherits from both Environment
and Bacterium, manages populations of bacteria and orchestrates the simulation
lifecycle

### Key Inheritance Relationships

- `Cluster` inherits from `Environment` (public) and `Bacterium` (protected)
- This design allows Cluster to manage both environmental conditions and bacterial behaviors

### Simulation Flow

1. Initialize environment with configurable 3D grid (default 50x50x50 patches)
2. Populate with initial bacteria at random positions with random energy levels
3. Run simulation loop:
   - Each bacterium performs: move → eat → potentially reproduce → live/die
   - Environment handles nutrient diffusion and chemical level updates
   - Track population metrics and environmental changes
4. Export results to CSV and generate visualizations


## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/your-username/biotic-growth-simulation.git
   cd biotic-growth-simulation


2. To compile the code, run this command in the terminal
   g++ -O3 -I include apps/main.cpp src/Cluster.cpp src/Environment.cpp src/Random.cpp src/Species.cpp -o bin/main.out.exe
3. To run the code, first change directory using
   cd bin
   Then run the simulation using
   .\main.out.exe
4. To see the graphs, run "plot graphs.py".
5. To see the animation, run "visualiser.py".
### Development Workflow

```bash
# Full build and run cycle
cd build && make && ../bin/main.out

# Check for build configuration changes
cd build && cmake .. && make
```


## Data Output and Visualization

- Simulations generate CSV files in `results/` with columns: TimeElapsed, AliveBacteria, TotalBacteria, NetCO2, TotalNutrient, TotalAcetate
- Python visualization script (`utils/plot.py`) automatically generates three plots:
  - Bacteria population over time
  - Nutrient levels over time  
  - CO2 levels over time
- Plots are saved as pickle files for later analysis


## Key Configuration Parameters

### Environment Parameters
- Grid size (default: 50x50x50 patches)  
- Initial nutrient levels
- Temporal resolution (simulation time step)
- Diffusion constants

### Bacterial Parameters (in Species.h)
- Energy thresholds (min: 0, max: 500, reproduction: 300)
- Movement speed (1.0 μm/s)
- Consumption rates
- Acidic tolerance limits

Use Control + Shift + m to toggle the tab key moving focus. Alternatively, use esc then tab to move to the next interactive element on the page.
No file chosen
Attach files by dragging & dropping, selecting or pasting them.
