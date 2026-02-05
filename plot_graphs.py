import pandas as pd
import matplotlib.pyplot as plt
import os

# --- CONFIGURATION ---
FILENAME = "results/trial1.csv" 

def main():
    # 1. Check for File
    file_path = FILENAME
    if not os.path.exists(FILENAME):
        if os.path.exists("bin/trial1.csv"):
            file_path = "bin/trial1.csv"
            print("Found data in bin/trial1.csv...")
        else:
            print(f"Error: Could not find '{FILENAME}'.")
            return

    # 2. Read Data
    try:
        data = pd.read_csv(file_path)
    except Exception as e:
        print(f"Error reading CSV: {e}")
        return

    print("Data loaded. Opening 4 separate windows...")

    # --- PAGE 1: POPULATION OVERVIEW ---
    plt.figure("Page 1: Bacterial Population", figsize=(10, 6))
    plt.plot(data['TimeElapsed'], data['TotalBacteria'], label='Total (Cumulative)', color='black', linestyle='--')
    plt.plot(data['TimeElapsed'], data['AliveBacteria'], label='Currently Alive', color='green', linewidth=2)
    plt.title("Page 1: Bacterial Population Growth")
    plt.xlabel("Time (s)")
    plt.ylabel("Count")
    plt.grid(True, alpha=0.3)
    plt.legend()

    # --- PAGE 2: FOOD SUPPLY ---
    plt.figure("Page 2: Nutrient Levels", figsize=(10, 6))
    plt.plot(data['TimeElapsed'], data['TotalNutrient'], label='Total Nutrients', color='gold', linewidth=2)
    plt.title("Page 2: Environmental Resources (Food)")
    plt.xlabel("Time (s)")
    plt.ylabel("Nutrient Units")
    plt.grid(True, alpha=0.3)
    plt.legend()

    # --- PAGE 3: ACETATE (TOXICITY) ---
    plt.figure("Page 3: Acetate Toxicity", figsize=(10, 6))
    plt.plot(data['TimeElapsed'], data['TotalAcetate'], label='Total Acetate (Waste)', color='brown', linewidth=2)
    plt.title("Page 3: Acetate Accumulation (Toxicity)")
    plt.xlabel("Time (s)")
    plt.ylabel("Acetate Concentration")
    plt.grid(True, alpha=0.3)
    plt.legend()

    # --- PAGE 4: CO2 EMISSIONS ---
    plt.figure("Page 4: CO2 Production", figsize=(10, 6))
    plt.plot(data['TimeElapsed'], data['NetCO2'], label='Net CO2 Produced', color='blue', linewidth=2)
    plt.title("Page 4: CO2 Emissions")
    plt.xlabel("Time (s)")
    plt.ylabel("CO2 Units")
    plt.grid(True, alpha=0.3)
    plt.legend()

    # Show all windows
    plt.show()

if __name__ == "__main__":
    main()