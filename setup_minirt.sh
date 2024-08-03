#!/bin/bash

# Create directory structure
mkdir -p miniRT/{src/{parse,render,geometry,utils},include,lib/minilibx,scenes}

# Main file
echo "/* 
 * main.c
 * Main entry point of the program
 * Initializes the raytracer, parses command-line arguments, and manages the main rendering loop
 */" > miniRT/src/main.c

# Parse files
echo "/*
 * scene_parser.c
 * Functions to parse the .rt scene description files
 * Reads and interprets scene elements (objects, lights, camera)
 */" > miniRT/src/parse/scene_parser.c

echo "/*
 * config_reader.c
 * Handles reading and parsing of configuration files
 * Manages any additional settings or parameters
 */" > miniRT/src/parse/config_reader.c

# Render files
echo "/*
 * raytracer.c
 * Core raytracing logic
 * Implements the main raytracing algorithm
 */" > miniRT/src/render/raytracer.c

echo "/*
 * camera.c
 * Defines camera properties and operations
 * Handles ray generation from camera viewpoint
 */" > miniRT/src/render/camera.c

echo "/*
 * lighting.c
 * Implements lighting calculations
 * Manages ambient, diffuse, and shadow computations
 */" > miniRT/src/render/lighting.c

# Geometry files
echo "/*
 * vector.c
 * Defines vector operations (addition, subtraction, dot product, cross product, etc.)
 */" > miniRT/src/geometry/vector.c

echo "/*
 * sphere.c
 * Implements sphere intersection and normal calculations
 */" > miniRT/src/geometry/sphere.c

echo "/*
 * plane.c
 * Implements plane intersection and normal calculations
 */" > miniRT/src/geometry/plane.c

echo "/*
 * cylinder.c
 * Implements cylinder intersection and normal calculations
 */" > miniRT/src/geometry/cylinder.c

# Utils files
echo "/*
 * color.c
 * Defines color operations and conversions
 */" > miniRT/src/utils/color.c

echo "/*
 * math_utils.c
 * Contains general mathematical utilities used across the project
 */" > miniRT/src/utils/math_utils.c

# Include files
echo "/*
 * miniRT.h
 * Main header file including all other headers
 * Defines common structs and constants used throughout the project
 */" > miniRT/include/miniRT.h

echo "/*
 * parser.h
 * Declarations for scene parsing functions
 */" > miniRT/include/parser.h

echo "/*
 * render.h
 * Declarations for rendering and raytracing functions
 */" > miniRT/include/render.h

echo "/*
 * geometry.h
 * Declarations for geometric operations and object-specific functions
 */" > miniRT/include/geometry.h

echo "/*
 * utils.h
 * Declarations for utility functions (color operations, math utils)
 */" > miniRT/include/utils.h

# Scene files
echo "# Example scene 1" > miniRT/scenes/scene1.rt
echo "# Example scene 2" > miniRT/scenes/scene2.rt

# Makefile
echo "# Makefile
# Defines compilation rules and targets for building the project" > miniRT/Makefile

# README
echo "# miniRT

This is a simple ray tracing project.

## Setup and Usage

[Add setup and usage instructions here]

## Project Structure

[Add brief description of project structure here]

## Authors

[Add author names here]" > miniRT/README.md

echo "Directory structure and files created successfully!"
