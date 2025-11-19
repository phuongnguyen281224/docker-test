@echo off
echo Cleaning previous build artifacts...
if exist build rmdir /s /q build
mkdir build
echo Starting Docker environment...
docker compose up -d --build
if %errorlevel% neq 0 (
    echo Failed to start Docker environment. Please make sure Docker Desktop is running.
    pause
    exit /b %errorlevel%
)

echo Running build script inside the container...
echo Running build script inside the container...
echo Fixing line endings for build.sh...
docker compose exec stm32_dev sed -i "s/\r$//" build.sh
docker compose exec stm32_dev ./build.sh
if %errorlevel% neq 0 (
    echo Build failed inside the container.
    pause
    exit /b %errorlevel%
)

echo Build complete. Binaries are in the build/ directory.
pause
