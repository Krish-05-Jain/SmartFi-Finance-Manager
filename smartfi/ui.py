import sys
from datetime import datetime

# ANSI Color Codes
RESET = "\033[0m"
BOLD = "\033[1m"
RED = "\033[31m"
GREEN = "\033[32m"
YELLOW = "\033[33m"
BLUE = "\033[34m"
MAGENTA = "\033[35m"
CYAN = "\033[36m"

def safe_read_int(prompt: str) -> int:
    while True:
        try:
            val = input(f"{CYAN}{BOLD}{prompt}{RESET}")
            return int(val)
        except ValueError:
            print(f"{RED} [!] Invalid number. Please try again.{RESET}")
        except EOFError:
            return None

def safe_read_float(prompt: str) -> float:
    while True:
        try:
            val = input(f"{CYAN}{BOLD}{prompt}{RESET}")
            return float(val)
        except ValueError:
            print(f"{RED} [!] Invalid amount. Please try again.{RESET}")
        except EOFError:
            return None

def safe_read_string(prompt: str) -> str:
    while True:
        try:
            val = input(f"{CYAN}{BOLD}{prompt}{RESET}").strip()
            if val:
                return val
            print(f"{RED} [!] Input cannot be empty.{RESET}")
        except EOFError:
            return None

def validate_date(date_str: str) -> bool:
    try:
        datetime.strptime(date_str, "%Y-%m-%d")
        return True
    except ValueError:
        return False
