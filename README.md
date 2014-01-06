# Conqueror

Conqueror is a strategy board game where each players must own as much cells of
the board as possible.

For the moment the game can only be played in CLI mode.

## Rules

### Environment

The board can be represented as a [graph](http://en.wikipedia.org/wiki/Graph_%28mathematics%29).
Each player starts on a randomly chosen cell.

### Turns

On each turn, the current player must move some of his pawns from one of his
cells to a neighbour cell.
The turn is separated in 3 steps:

Selection of the cell to leave (source cell):

First, the player must choose a cell among those he owns.
For that the player can do the following commands:
- cells: to list the cells he owns,
- neighbours #: to list the neighbour cells of the cell #,
- cell #: to choose the cell # as source cell.

Examples:
```

```

Selection of the cell to go to (destination cell):

Then, the player must choose a cell where he'll move pawns. The destination cell
must be a neighbour of the source cell.
For that the player can do the following commands:
- cells: to list the neighbour cells of the source cell,
- cell #: to choose the cell # as destination cell.

Examples:
```

```

Selection of the number of pawns to move:

Thirdly,  the player must select the number of pawns he wants to move.
This number must be higher than 1 and lower than the number of pawns being on
the source cell.
Here, the player just has to type a number.

### Fights

### End of the game

The game ends when no player can play anymore or if one player is remaining in
the game.

## Usage

To compile the game, run:
```
make
```

To play, run:
```
./bin/conqueror
```
