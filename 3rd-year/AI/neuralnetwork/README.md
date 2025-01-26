# Explaining results of benchmarks

## Example of input values

6QR/p3r2p/1p2k1p1/2q2p2/2P1rP2/P6P/6P1/3R3K b - - 18 42 Check White
2r2rk1/6b1/5qpp/p2P4/bpp1B3/5P2/PPQ1N1PP/K1R3R1 w - - 2 26 Nothing
1qr5/3pkpQp/p3p3/5N2/B3bb2/P7/1PP2nPP/1K1RR3 b - - 3 20 Check White
8/p3k1pp/3npp2/8/2KP4/1N2P3/5PPP/8 w - - 14 33 Check Black
8/8/8/8/6p1/5p2/5KPk/8 w - - 0 59 Nothing
7k/7P/6K1/8/8/8/8/8 b - - 0 93 Stalemate

## Example of output values

Check White
Nothing
Check White
Check Black
Nothing
Stalemate

## Steps

1. First of all, we transform the **FEN (Forsyth-Edwards Notation)**, it's a notation for a chess board, into an 8x8 matrix.
    We have set up a protocol to assign an id to each chess piece:
        0 : empty square
        1 : white pawn
        2 : white knight
        3 : white bishop
        4 : white rook
        5: White queen
        6 : white king
        -1 : black pawn
        -2 : black knight
        -3 : black bishop
        -4 : black rook
        -5 : black queen
        -6 : black king

2. We trained our model using datasets retrieved and transformed randomly during each training session.
    Weights are saved in a .nn file.

3. We can then predict the outcome of an FEN given to the model using our prediction tool which uses our previously generated .nn file.

Average accuracy:

100 fen of each dataset file => 41.51%
500 fen of each dataset file => 42.87%
1000 fen of each dataset file => 43.88%