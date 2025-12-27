#!/usr/bin/env python3
"""
Simple visualization of simulation results

Usage: 
    python3 visualize.py output.txt
"""

import sys
import re
import matplotlib.pyplot as plt
import matplotlib.patches as patches

def parse_simulation_output(filename):
    """Parsing simulation log file"""
    particles = []
    
    with open(filename, 'r') as f:
        content = f.read()
        
        # Extract area size
        area_match = re.search(r'Area: ([\d.]+)x([\d.]+)', content)
        if area_match:
            area_width = float(area_match.group(1))
            area_height = float(area_match.group(2))
        else:
            area_width, area_height = 100, 100
        
        # Extract particles
        pattern = r'(\d+): (\w+) at \(([\d.]+), ([\d.]+)\)'
        matches = re.finditer(pattern, content)
        
        for match in matches:
            idx = int(match.group(1))
            shape_type = match.group(2)
            x = float(match.group(3))
            y = float(match.group(4))
            
            particles.append({
                'id': idx,
                'type': shape_type,
                'x': x,
                'y': y
            })
    
    return particles, area_width, area_height

def visualize_particles(particles, area_width, area_height):
    """Visualization of particles"""
    fig, ax = plt.subplots(1, 1, figsize=(10, 10))
    
    # draw each particle
    colors = {
        'Circle': 'blue',
        'Square': 'red',
        'Rectangle': 'green'
    }
    
    for p in particles:
        color = colors.get(p['type'], 'gray')
        
        if p['type'] == 'Circle':
            radius = 1.0
            circle = plt.Circle((p['x'], p['y']), radius, 
                              color=color, alpha=0.5, ec='black', linewidth=1)
            ax.add_patch(circle)
        elif p['type'] == 'Square':
            size = 3.0
            square = patches.Rectangle((p['x'] - size/2, p['y'] - size/2), 
                                      size, size,
                                      color=color, alpha=0.5, ec='black', linewidth=1)
            ax.add_patch(square)
        elif p['type'] == 'Rectangle':
            width, height = 4.0, 2.0
            rect = patches.Rectangle((p['x'] - width/2, p['y'] - height/2), 
                                    width, height,
                                    color=color, alpha=0.5, ec='black', linewidth=1)
            ax.add_patch(rect)
        
        # Particle ID
        ax.text(p['x'], p['y'], str(p['id']), 
               ha='center', va='center', fontsize=8)
    
    # Setup
    ax.set_xlim(0, area_width)
    ax.set_ylim(0, area_height)
    ax.set_aspect('equal')
    ax.grid(True, alpha=0.3)
    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    ax.set_title(f'Particle Packing ({len(particles)} particles)')
    
    # Legend
    legend_elements = [
        plt.Circle((0, 0), 1, color='blue', alpha=0.5, label='Circle'),
        patches.Rectangle((0, 0), 1, 1, color='red', alpha=0.5, label='Square'),
        patches.Rectangle((0, 0), 1, 1, color='green', alpha=0.5, label='Rectangle')
    ]
    ax.legend(handles=legend_elements, loc='upper right')
    
    plt.tight_layout()
    plt.savefig('simulation_result.png', dpi=150)
    print("Plot saved as 'simulation_result.png'")
    plt.show()

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print("  python3 visualize.py output.txt")
        sys.exit(1)
    
    filename = sys.argv[1]
    
    try:
        particles, area_width, area_height = parse_simulation_output(filename)
        print(f"Found {len(particles)} particles")
        print(f"Area: {area_width}x{area_height}")
        
        if particles:
            visualize_particles(particles, area_width, area_height)
        else:
            print("No particles found in output file")
    except FileNotFoundError:
        print(f"Error: File '{filename}' not found")
        sys.exit(1)
    except Exception as e:
        print(f"Error: {e}")
        sys.exit(1)
