from sys import stderr

def xor_word(block, block2):
    ciphered_bytes = bytearray()
    for j in range(len(block)):
        ciphered_byte = block[j] ^ block2[j]
        ciphered_bytes.append(ciphered_byte)
    return ciphered_bytes

def xor(mode, is_mode_b, message, key):
    if mode == "-g":
        exit(84)

    if mode == "-c":
        message_bytes = bytearray(message, "utf-8")
    else:
        message_bytes = bytearray.fromhex(message)
    key_bytes = bytearray.fromhex(key)

    if mode == "-c":
        key_bytes.reverse()

    ciphered_bytes = bytearray()
    key_len = len(key_bytes)
    message_len = len(message_bytes)

    if not is_mode_b:
        for i in range(0, message_len, key_len):
            block = message_bytes[i:i + key_len]
            block_len = len(block)
            if block_len < key_len:
                block += bytearray([0] * (key_len - block_len))
            temp_ciphered_bytes = xor_word(block, key_bytes)
            for byte in temp_ciphered_bytes:
                ciphered_bytes.append(byte)
    else:
        if message_len != key_len:
            print(f"tried to apply \"-b\" but message's len ({message_len}) != key's len ({key_len})", file=stderr)
            exit(84)

        for i in range(message_len):
            ciphered_byte = message_bytes[i] ^ key_bytes[i]
            ciphered_bytes.append(ciphered_byte)

    ciphered_bytes.reverse()

    return ciphered_bytes.hex() if mode == "-c" else ciphered_bytes.decode("utf-8") + "\n"
