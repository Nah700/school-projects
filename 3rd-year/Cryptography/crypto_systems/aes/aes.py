from crypto_systems.aes.key_expansion import generate_key_expansion
from crypto_systems.aes.aes_utils import xor_matrix, shift_rows, sub_matrix, mix_columns, add_round_key

def aes(mode, is_mode_b, message, key):
    if mode == "-g":
        exit(84)
    keys = generate_key_expansion(key)

    message = bytearray(message, "utf-8")
    message = [[message[i + 4 * j] for i in range(4)] for j in range(4)]
    key = bytearray.fromhex(key)
    key = [[key[j + 4 * i] for i in range(4)] for j in range(4)]

    output = xor_matrix(key, message)
    for i in range(10):
        output = sub_matrix(output)
        output = shift_rows(output)
        if i < 9:
            output = mix_columns(output)
        key_matrix = bytearray.fromhex(keys[i + 1])
        key_matrix = [[key_matrix[j + 4 * i] for i in range(4)] for j in range(4)]
        output = add_round_key(key_matrix, output)

        #print(f"output n°{i} = {output}")
    #print(f"output = {output}")
    hex_string = ""
    for col in range(4):
        for row in range(4):
            hex_string += format(output[row][col], '02x')
    return hex_string
