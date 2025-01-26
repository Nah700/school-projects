import numpy as np

def sigmoid(x):
    return 1 / (1 + np.exp(-x))


def sigmoid_derivative(x):
    return x * (1 - x)

def fen_to_matrix(fen_string: str):
    piece_map = {
        'P': 1, 'N': 2, 'B': 3, 'R': 4, 'Q': 5, 'K': 6,
        'p': -1, 'n': -2, 'b': -3, 'r': -4, 'q': -5, 'k': -6
    }
    rows = fen_string.split(' ')[0].split('/')
    matrix = []
    for row in rows:
        matrix_row = []
        for char in row:
            if char.isdigit():
                matrix_row.extend([0] * int(char))
            else:
                matrix_row.append(piece_map[char])
        matrix.append(matrix_row)
    return matrix
