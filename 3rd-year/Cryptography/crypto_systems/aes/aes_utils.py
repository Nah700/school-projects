from crypto_systems.sbox import sbox
from crypto_systems.xor import xor_word

def sub_byte(byte):
    row = (byte >> 4) & 0x0F
    col = byte & 0x0F
    return sbox[row][col]

def sub_word(state):
    for i in range(4):
        state[i] = sub_byte(state[i])
    return state

def sub_matrix(matrix):
    for i in range(4):
        matrix[i] = sub_word(matrix[i])
    return matrix

def rot_word(word):
    return word[1:] + word[:1]

def shift_rows(matrix_):
    for i in range(4):
        for j in range(i):
            matrix_[i] = rot_word(matrix_[i])
    return matrix_

def mix_columns(matrix):
    return matrix

def add_round_key(state, subkey):
    return xor_matrix(state, subkey)

def xor_matrix(message_matrix, key_matrix):
    output_matrix = [[0 for _ in range(4)] for _ in range(4)]

    for i in range(4):
        for j in range(4):
            output_matrix[i][j] = message_matrix[i][j] ^ key_matrix[i][j]
    return output_matrix

def get_word_by_index(matrix, index):
    return [b[index] for b in matrix]

def get_rcon(word, round_index):
    rcon_values = [0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1B, 0x36]
    word[0] = word[0] ^ rcon_values[round_index]
    return word
