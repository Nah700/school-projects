import math
import random
from sys import stderr

def inverseMod(primeNumber, euler):
    def egcd(a, b):
        if a == 0:
            return (b, 0, 1)
        else:
            g, y, x = egcd(b % a, a)
            return (g, x - (b // a) * y, y)

    g, x, y = egcd(primeNumber, euler)
    if g != 1:
        raise Exception('No modular inverse')
    else:
        return x % euler

def closest_prime(euler):
    primer = [65537, 257, 17, 5, 3]
    for prime in primer:
        if euler > prime:
            return prime


def encryption(public_key, message: str) -> bytes:
    key, n = public_key

    key = int(key, 16)
    n = int(n, 16)
    key = int.from_bytes(key.to_bytes((key.bit_length() + 7) // 8, byteorder='little'), byteorder='big')
    n = int.from_bytes(n.to_bytes((n.bit_length() + 7) // 8, byteorder='little'), byteorder='big')

    message = message.rstrip('\n')

    message = bytes(message, 'utf-8')
    message = int.from_bytes(message, byteorder='little')
    result = pow(message, key, n)
    return result.to_bytes((result.bit_length() + 7) // 8, byteorder='little')


def decryption(private_key, crypte: str) -> str:
    key, n = private_key

    key = int(key, 16)
    n = int(n, 16)
    key = int.from_bytes(key.to_bytes((key.bit_length() + 7) // 8, byteorder='little'), byteorder='big')
    n = int.from_bytes(n.to_bytes((n.bit_length() + 7) // 8, byteorder='little'), byteorder='big')

    crypte = crypte.rstrip('\n')

    decryptee = bytes.fromhex(crypte)
    decryptee = int.from_bytes(decryptee, byteorder='little')
    decryptee = pow(decryptee, key, n)
    decryptee_bytes = decryptee.to_bytes((decryptee.bit_length() + 7) // 8, byteorder='little')
    return decryptee_bytes.decode('utf-8', errors='ignore')

def rsa(mode, b_value, P, Q, message, key):
    message_len = 0
    key_len = 0
    if mode == '-c':
        public_key = key.split('-')
        result = encryption(public_key, message)
        key_len = len(result)
    if mode == '-d':
        private_key = key.split('-')
        result = decryption(private_key, message)
        message_len = len(message)
    if mode == '-g':
        p = int(P, 16)
        q = int(Q, 16)
        p = int.from_bytes(p.to_bytes((p.bit_length() + 7) // 8, byteorder='little'), byteorder='big')
        q = int.from_bytes(q.to_bytes((q.bit_length() + 7) // 8, byteorder='little'), byteorder='big')

        n = p * q
        euler = (p - 1) * (q - 1)
        primeNumber = closest_prime(euler)
        private = inverseMod(primeNumber, euler)

        primeNumber_bytes = primeNumber.to_bytes((primeNumber.bit_length() + 7) // 8, byteorder='little')
        private_bytes = private.to_bytes((private.bit_length() + 7) // 8, byteorder='little')
        n_bytes = n.to_bytes((n.bit_length() + 7) // 8, byteorder='little')

        primeNumber_hex = primeNumber_bytes.hex()
        private_hex = private_bytes.hex()
        n_hex = n_bytes.hex()

        print(f"public key: {primeNumber_hex}-{n_hex}")
        print(f"private key: {private_hex}-{n_hex}")
    if b_value and message_len != 0 and key_len != 0:
        if message_len != key_len:
            print(f"tried to apply \"-b\" but message's len ({message_len}) != key's len ({key_len})", file=stderr)
            exit(84)
    return result.hex() if mode == '-c' else (result + '\n') if mode == '-d' else 0
