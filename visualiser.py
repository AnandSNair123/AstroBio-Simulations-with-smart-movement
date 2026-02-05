import pygame
import csv
import sys
import time

# --- CONFIGURATION ---
GRID_SIZE = 50            # Must match your C++ simulation size
CELL_SIZE = 15            # Adjusted for 50x50 grid (Total 750x750 pixels)
WIDTH, HEIGHT = GRID_SIZE * CELL_SIZE, GRID_SIZE * CELL_SIZE
FILENAME = "results/vis_data.csv"

# --- COLORS ---
BLACK = (10, 10, 10)      
CYAN_GLOW = (0, 255, 255) # Alive Bacteria
RED_DEAD = (200, 50, 50)  # Dead Bacteria
YELLOW_NUTRIENT = (40, 40, 10) 

def create_glow_surface(radius, color):
    surf = pygame.Surface((radius * 2, radius * 2), pygame.SRCALPHA)
    pygame.draw.circle(surf, (*color[:3], 50), (radius, radius), radius)
    pygame.draw.circle(surf, (*color[:3], 255), (radius, radius), radius // 2)
    return surf

def main():
    pygame.init()
    screen = pygame.display.set_mode((WIDTH, HEIGHT))
    pygame.display.set_caption("SSPACE Bacteria Simulation - Slow Motion")
    clock = pygame.time.Clock()

    bacteria_surf = create_glow_surface(int(CELL_SIZE * 0.6), CYAN_GLOW)
    dead_surf = create_glow_surface(int(CELL_SIZE * 0.6), RED_DEAD)
    
    blur_surf = pygame.Surface((WIDTH, HEIGHT), pygame.SRCALPHA)
    blur_surf.fill((0, 0, 0, 60)) 

    print(f"Loading data from {FILENAME}...")
    frames = {}
    
    try:
        with open(FILENAME, 'r') as f:
            reader = csv.reader(f)
            for row in reader:
                if not row: continue
                try:
                    frame = int(row[0])
                    if frame not in frames: frames[frame] = []
                    frames[frame].append((int(row[1]), int(row[2]), int(row[3]), float(row[4])))
                except ValueError:
                    continue
    except FileNotFoundError:
        print("Error: Could not find 'results/vis_data.csv'.")
        sys.exit()

    sorted_frame_keys = sorted(frames.keys())
    if not sorted_frame_keys:
        print("Error: No data found.")
        sys.exit()

    max_frame_idx = len(sorted_frame_keys) - 1
    current_idx = 0
    
    running = True
    paused = False
    
    # --- CHANGED: Default Speed is now 5 FPS (Very Slow) ---
    fps = 5 

    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
            elif event.type == pygame.KEYDOWN:
                if event.key == pygame.K_SPACE:
                    paused = not paused
                elif event.key == pygame.K_RIGHT:
                    fps = min(60, fps + 1)  # Increase speed
                elif event.key == pygame.K_LEFT:
                    fps = max(1, fps - 1)   # Decrease speed
                elif event.key == pygame.K_r:
                    current_idx = 0
                    screen.fill(BLACK)

        if not paused:
            # 1. Blur previous frame
            screen.blit(blur_surf, (0, 0))

            # 2. Get Data
            frame_num = sorted_frame_keys[current_idx]
            entities = frames[frame_num]

            # 3. Draw Nutrients
            for etype, x, y, val in entities:
                if etype == 0 and val > 1.0: 
                    intensity = min(100, int(val * 5)) 
                    rect_color = (intensity, intensity, 10) 
                    pygame.draw.rect(screen, rect_color, 
                                   (x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE))

            # 4. Draw Bacteria
            for etype, x, y, val in entities:
                pos = (x * CELL_SIZE - CELL_SIZE//4, y * CELL_SIZE - CELL_SIZE//4)
                if etype == 2: # Alive
                    screen.blit(bacteria_surf, pos)
                elif etype == 3: # Dead
                    screen.blit(dead_surf, pos)

            # 5. UI Overlay
            font = pygame.font.SysFont("arial", 18)
            status = "PAUSED" if paused else "RUNNING"
            info = f"Frame: {frame_num} | Speed: {fps} FPS | Status: {status}"
            
            # Draw text background
            text_surf = font.render(info, True, (255, 255, 255))
            pygame.draw.rect(screen, (50, 50, 50), (5, 5, text_surf.get_width()+10, 25))
            screen.blit(text_surf, (10, 10))

            pygame.display.flip()

            # Advance Frame
            if current_idx < max_frame_idx:
                current_idx += 1
            else:
                print("Simulation finished. Resetting...")
                current_idx = 0 
                time.sleep(1)
                screen.fill(BLACK)

        # Control the speed here
        clock.tick(fps)

    pygame.quit()

if __name__ == "__main__":
    main()