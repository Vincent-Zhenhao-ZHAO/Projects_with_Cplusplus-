# Flappy birds game

This is a simple game of Flappy Birds. I have implemented this game using C++ 11 and SFML library.

## How to run

1. Install SFML library
2. Clone this repository
3. Go to 00_Flappy_Birds folder
4. Run the following commands
```bash
mkdir build
cd build
cmake -S . -B build
cmake --build build
./build/FlappyBirds
```
5. *(Optional)* If you want to run the game with Docker, you can run the following commands
```bash
docker build -t flappy_birds .
docker run -it flappy_birds
```

## How to play

- Press `Space` to jump
- Avoid the pipes
- Try to get the highest score

## License
This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details.