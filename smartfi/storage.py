import os
from typing import List
from .models import User, Transaction

def save_data(file_path: str, users: List[User]):
    os.makedirs(os.path.dirname(file_path), exist_ok=True)
    with open(file_path, "w") as f:
        for u in users:
            f.write(f"USER|{u.name}|{u.balance}\n")
            for t in u.transactions:
                f.write(f"TRANS|{t.date}|{t.type}|{t.category}|{t.amount}\n")

def load_data(file_path: str) -> List[User]:
    users = []
    if not os.path.exists(file_path):
        return users
        
    current_user = None
    with open(file_path, "r") as f:
        for line in f:
            parts = line.strip().split("|")
            if not parts or not parts[0]:
                continue
            
            if parts[0] == "USER":
                name = parts[1]
                current_user = User(name)
                # Balance will automatically resolve when we load transactions
                users.append(current_user)
                
            elif parts[0] == "TRANS" and current_user:
                date = parts[1]
                type_ = parts[2]
                category = parts[3]
                try:
                    amount = float(parts[4])
                    current_user.add_transaction(Transaction(amount, category, type_, date))
                except ValueError:
                    pass
    return users
