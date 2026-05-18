import os
from .models import User, Transaction
from .analytics import Analytics
from .storage import load_data, save_data
from .ui import (
    safe_read_int, safe_read_float, safe_read_string, validate_date,
    BLUE, CYAN, BOLD, RESET, GREEN, RED
)

class FinanceManager:
    DATA_FILE = os.path.join("data", "data.txt")

    def __init__(self):
        self.users = load_data(self.DATA_FILE)

    def find_user(self, name: str) -> User:
        for u in self.users:
            if u.name == name:
                return u
        return None

    def run(self):
        # Enable ANSI colors for Windows
        if os.name == 'nt':
            os.system('color')

        while True:
            print(f"\n{BLUE}{BOLD}  =========================================={RESET}")
            print(f"{CYAN}{BOLD}         🌟 SMARTFI FINANCE MANAGER 🌟      {RESET}")
            print(f"{BLUE}{BOLD}  =========================================={RESET}")
            print(f"{BOLD}  1. Add User   2. Add Transaction   3. Report   4. Predict   5. Exit{RESET}\n")

            choice = safe_read_int("  Select > ")
            if choice is None:
                self._save()
                break

            if choice == 1:
                name = safe_read_string("  Name: ")
                if name:
                    if self.find_user(name):
                        print(f"{RED}  [!] User already exists.{RESET}")
                    else:
                        self.users.append(User(name))
                        print(f"{GREEN}{BOLD}\n  [✓] User added!{RESET}")
                        self._save()

            elif choice == 2:
                name = safe_read_string("  Name: ")
                if not name: continue
                u = self.find_user(name)
                if not u:
                    print(f"{RED}  [!] User not found!{RESET}")
                    continue

                type_ = ""
                while type_ not in ["Income", "Expense"]:
                    type_ = safe_read_string("  Type (Income/Expense): ")
                    if type_ is None: break
                if type_ is None: continue

                category = safe_read_string("  Category: ")
                if not category: continue
                
                amount = safe_read_float("  Amount: ")
                if amount is None: continue

                date = ""
                while not validate_date(date):
                    date = safe_read_string("  Date (YYYY-MM-DD): ")
                    if date is None: break
                if date is None: continue

                u.add_transaction(Transaction(amount, category, type_, date))
                print(f"{GREEN}  [✓] Transaction Added!{RESET}")
                self._save()

            elif choice == 3:
                name = safe_read_string("  Name: ")
                if not name: continue
                year = safe_read_int("  Year: ")
                if year is None: continue
                month = safe_read_int("  Month: ")
                if month is None: continue
                
                u = self.find_user(name)
                if u:
                    Analytics.generate_report(u, year, month)
                    Analytics.suggest_budget(u, year, month)
                    Analytics.detect_anomalies(u, year, month)
                else:
                    print(f"{RED}  [!] User not found!{RESET}")

            elif choice == 4:
                name = safe_read_string("  Name: ")
                if not name: continue
                year = safe_read_int("  Current Year: ")
                if year is None: continue
                month = safe_read_int("  Current Month: ")
                if month is None: continue
                
                u = self.find_user(name)
                if u:
                    Analytics.predict_next_month(u, year, month)
                else:
                    print(f"{RED}  [!] User not found!{RESET}")

            elif choice == 5:
                print(f"{GREEN}\n  Saving data and exiting... Goodbye!{RESET}")
                self._save()
                break

    def _save(self):
        save_data(self.DATA_FILE, self.users)
