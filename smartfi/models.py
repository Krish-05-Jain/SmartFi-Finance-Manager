from typing import List, Dict
from collections import defaultdict
from .ui import GREEN, RED, YELLOW, BOLD, RESET

class Transaction:
    def __init__(self, amount: float, category: str, type_: str, date: str):
        self.amount = amount
        self.category = category
        self.type = type_
        self.date = date

    def display(self):
        color = GREEN if self.type == "Income" else RED
        print(f"  {YELLOW}{self.date}{RESET} | {color}{self.type:<8}{RESET} | {self.category:<12} | {BOLD}${self.amount:.2f}{RESET}")

class User:
    def __init__(self, name: str):
        self.name = name
        self.balance = 0.0
        self.transactions: List[Transaction] = []

    def add_transaction(self, t: Transaction):
        self.transactions.append(t)
        if t.type == "Income":
            self.balance += t.amount
        elif t.type == "Expense":
            self.balance -= t.amount

    def get_category_wise_expense(self, year: int, month: int) -> Dict[str, float]:
        category_map = defaultdict(float)
        for t in self.transactions:
            if t.type == "Expense":
                try:
                    y, m, d = map(int, t.date.split("-"))
                    if y == year and m == month:
                        category_map[t.category] += t.amount
                except ValueError:
                    pass
        return dict(category_map)
