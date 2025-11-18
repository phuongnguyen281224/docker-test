#!/bin/bash
set -e

# Start the docker-compose services in detached mode and build if necessary
echo "Starting Docker environment..."
docker compose up -d --build

# Execute the build script inside the container
echo "Running build script inside the container..."
docker compose exec stm32_dev ./build.sh

echo "Build complete. Binaries are in the build/ directory."
