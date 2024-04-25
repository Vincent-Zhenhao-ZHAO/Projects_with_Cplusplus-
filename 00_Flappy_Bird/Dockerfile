FROM gcc:latest
LABEL authors="vincentzhao"

# Install cmake
RUN apt-get update && apt-get install -y cmake

# install SFML
RUN apt-get install -y libsfml-dev

# Set the working directory
WORKDIR /app

# Copy the current directory contents into the container at /app
COPY CMakeLists.txt /app/
COPY main.cpp /app/

# Run cmake
RUN cmake -S . -B build

# Build the project
RUN cmake --build build/

# Run the program
 CMD ["./build/main"]