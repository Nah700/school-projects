from sys import stdin
from crypto_systems.xor import xor
from crypto_systems.aes.aes import aes
from crypto_systems.rsa import rsa

def pgp_xor(mode, is_mode_b, message, key):
    if mode == "-g":
        exit(84)
    return 0

def pgp_aes(mode, is_mode_b, message, key):
    if mode == "-g":
        exit(84)
    return 0

def run_crypto(crypto_system, mode, b_value, key):
    is_mode_b = b_value == "-b"

    available_modes = ["-c", "-d", "-g"]

    if mode not in available_modes:
        exit(84)

    if mode == "-g" and crypto_system == "rsa":
        message = ""
    else:
        message = stdin.read()

    match crypto_system:
        case "xor":
            return xor(mode, is_mode_b, message, key)
        case "aes":
            return aes(mode, is_mode_b, message, key)
        case "rsa":
            return rsa(mode, b_value, b_value, key, message, key)
        case "pgp-xor":
            return pgp_xor(mode, is_mode_b, message, key)
        case "pgp-aes":
            return pgp_aes(mode, is_mode_b, message, key)
    exit(84)
