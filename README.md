# Kesh Chess Engine README



## Table of Contents

- [Kesh Chess Engine README](#kesh-chess-engine-readme)
  - [Table of Contents](#table-of-contents)
  - [Introduction](#introduction)
  - [Features](#features)
  - [UCI Interface](#uci-interface)
  - [Move Generation](#move-generation)
  - [Search Algorithm](#search-algorithm)
  - [Evaluation](#evaluation)
  - [Getting Started](#getting-started)
  - [Contributing](#contributing)

## Introduction

Welcome to Kesh, a chess engine that plays chess intelligently. Kesh is designed to provide a strong and efficient chess-playing experience through the Universal Chess Interface (UCI) protocol.

## Features

- UCI (Universal Chess Interface) compliant, enabling seamless integration with various chess GUIs.
- Efficient move generation using bitboards, allowing for faster evaluation of legal moves.
- Negamax algorithm with alpha-beta pruning for a more intelligent and faster search.
- Quiescence search to address the horizon effect and avoid shallow tactics.
- Move ordering using principal variation, beta cutters, and alpha improvers to improve search efficiency.
- Basic evaluation using piece arrays, providing a rudimentary understanding of positions.

## UCI Interface

Kesh follows the UCI (Universal Chess Interface) standard, which means it can be easily used with any UCI-compatible chess GUI. The UCI protocol allows external programs to communicate with the engine to set up positions, start games, and receive moves.

To use Kesh with a GUI, simply follow the standard UCI commands for engine communication.

## Move Generation

Kesh employs an optimized move generation technique using bitboards. Bitboards are a compact representation of chess positions that allow for fast and efficient calculations of legal moves for each piece type. This approach enables Kesh to generate moves quickly, which is crucial for an effective chess-playing engine.

## Search Algorithm

The search algorithm implemented in Kesh is the Negamax algorithm with alpha-beta pruning. Negamax is a variant of the minimax algorithm and is used to find the best move in a game tree. Alpha-beta pruning efficiently prunes out branches that are not relevant to the final decision, reducing the number of nodes explored and significantly speeding up the search process.


## Evaluation

The current evaluation function in Kesh is basic and uses piece arrays. It assigns static values to each piece type and evaluates positions based on the material balance and piece locations. While this simple evaluation provides some understanding of positions, it can be improved in the future to make Kesh even stronger.

## Getting Started

To use Kesh, you'll need a UCI-compatible chess GUI. Here are the basic steps to get started:

1. Clone the github repository using the following command : 
   
```shell
git clone https://github.com/Raghav323 Kesh.git
```


2. Launch your preferred UCI-compatible chess GUI possibly [Arena](http://www.playwitharena.de/) . 
   
3. Configure the GUI to use Kesh as the chess engine.
   
**Instructions for Arena Chess GUI:**

1. Go to Engines > Manage 
2. Select the Details Tab 
3. Click New 
4. Locate the Kesh Folder and Select the `Kesh.sh` path inside it . For Example : `/home/user/Kesh/Kesh.sh`
5. Select UCI as the type of engine
6. Click on Apply and Ok
7. Start a new game or position, and Kesh will be ready to play.

## Contributing

We welcome contributions to Kesh to make it even better! If you have ideas for enhancements, bug fixes, or other improvements, feel free to open an issue or submit a pull request on the GitHub repository.

Please ensure that you follow the established coding conventions and practices in the project.

