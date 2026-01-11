# MyRaytracing

Sandbox for Ray Tracing in one weekend projects.

## Prerequisites

To build this project, you need:

- **CMake** (3.16 or higher)
- **Allegro 5** library installed and configured in your environment.
- A C++20 compatible compiler.

## Building the Project

1. Create a build directory:
   ```powershell
   mkdir build
   cd build
   ```

2. Configure the project:
   ```powershell
   cmake ..
   ```

3. Build the main executable:
   ```powershell
   cmake --build . --target MyRaytracing
   ```

## Running Unit Tests

This project uses **GoogleTest** for unit testing. The tests are located in the `tests/` directory.

1. Build the tests:
   ```powershell
   cmake --build <build-dir> --target unit_tests
   ```
   *(Replace `<build-dir>` with your actual build directory, e.g., `cmake-build-debug` or `build`)*

2. Run the tests:
   ```powershell
   .\<build-dir>\unit_tests.exe
   ```
   Or using CTest:
   ```powershell
   cd <build-dir>
   ctest
   ```

## Project Structure

- `src/`: Core logic and application code.
- `tests/`: Unit tests.
- `extern/`: External dependencies (e.g., Dear ImGui).
