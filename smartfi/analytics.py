from collections import defaultdict
from .models import User
from .ui import RED, GREEN, YELLOW, CYAN, BLUE, MAGENTA, BOLD, RESET

class Analytics:
    @staticmethod
    def detect_anomalies(user: User, year: int, month: int):
        category_map = user.get_category_wise_expense(year, month)
        print(f"{RED}{BOLD}\n[!] Anomaly Detection{RESET}")
        found = False
        for category, spent in category_map.items():
            if spent > 1000:
                print(f"  {YELLOW}High spend in {category}: {RED}${spent:.2f}{RESET}")
                found = True
        if not found:
            print(f"  {GREEN}No high spending detected.{RESET}")

    @staticmethod
    def suggest_budget(user: User, year: int, month: int):
        category_map = user.get_category_wise_expense(year, month)
        total_expense = sum(category_map.values())

        print(f"{CYAN}{BOLD}\n[#] Budget Suggestion{RESET}")
        if total_expense <= 0 or user.balance <= 0:
            print(f"  {YELLOW}Not enough data/balance for a budget.{RESET}")
            return

        for category, spent in category_map.items():
            suggested = (spent / total_expense) * user.balance
            print(f"  {category:<15} : {GREEN}${suggested:.2f}{RESET}")

    @staticmethod
    def generate_report(user: User, year: int, month: int):
        print(f"\n{MAGENTA}{BOLD}>>> Transactions for {user.name} in {year}-{month:02d} <<<{RESET}")
        print("-" * 53)
        for t in user.transactions:
            try:
                y, m, d = map(int, t.date.split("-"))
                if y == year and m == month:
                    t.display()
            except ValueError:
                pass
        print("-" * 53)
        print(f"{BOLD}Current Balance: {GREEN}${user.balance:.2f}{RESET}\n")

        category_map = user.get_category_wise_expense(year, month)
        if not category_map:
            print(f"{YELLOW}  No expenses this month.{RESET}")
            return

        print(f"{BLUE}{BOLD}📊 Category Expenses (Visual){RESET}")
        max_val = max(category_map.values()) if category_map else 0

        for category, spent in category_map.items():
            bar_len = int((spent / max_val) * 40) if max_val > 0 else 0
            bar = f"{MAGENTA}{'█' * bar_len}{RESET}"
            print(f"  {category:<15} | {bar} {RED}${spent:.2f}{RESET}")

    @staticmethod
    def predict_next_month(user: User, current_year: int, current_month: int):
        print(f"{CYAN}{BOLD}\n[~] Predicted Spend for Next Month{RESET}")
        historical = defaultdict(list)

        for m in range(current_month - 2, current_month + 1):
            if m <= 0:
                continue
            for category, spent in user.get_category_wise_expense(current_year, m).items():
                historical[category].append(spent)

        if not historical:
            print(f"  {YELLOW}Not enough historical data to predict.{RESET}")
            return

        for category, amounts in historical.items():
            avg = sum(amounts) / len(amounts)
            print(f"  {category:<15} : {YELLOW}${avg:.2f}{RESET}")
