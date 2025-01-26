from crypto_systems.aes.aes_utils import get_word_by_index, rot_word, sub_word, get_rcon
from crypto_systems.xor import xor_word


def generate_key_expansion(key_string):
    keys = [key_string]

    for i in range(10):
        key_matrix_ = bytearray.fromhex(keys[-1])
        key = [[key_matrix_[j + 4 * i] for i in range(4)] for j in range(4)]

        current_key = []

        word = get_word_by_index(key, 3)
        word = rot_word(word)
        word = sub_word(word)
        word = get_rcon(word, i)
        word = xor_word(get_word_by_index(key, 0), word)

        current_key.append(word)

        for j in range(1, 4):
            temp_word = xor_word(current_key[-1], get_word_by_index(key, j))
            current_key.append(temp_word)

        keys.append("".join([k.hex() for k in current_key]))
    return keys
