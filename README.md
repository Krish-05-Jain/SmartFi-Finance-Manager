<div align="center">
  <img src="https://img.icons8.com/color/96/000000/finance-document.png" alt="SmartFi Logo"/>
  <h1>🌟 SmartFi Finance Manager (Python Edition) 🌟</h1>
  <p><i>Empowering your financial decisions with CLI-based analytics & budget tracking.</i></p>
  
  [![Python](https://img.shields.io/badge/Python-3.8+-blue.svg?style=for-the-badge&logo=python)](https://python.org/)
  [![License](https://img.shields.io/badge/License-MIT-orange.svg?style=for-the-badge)](LICENSE)
</div>

<hr/>

## 📖 Overview

**SmartFi Finance Manager** is a lightning-fast, terminal-based personal finance management application written in Python. It features a stunning, color-rich CLI interface that allows users to seamlessly track expenses, visualize spending through ASCII charts, and utilize predictive analytics to forecast future financial trends.

This project uses an **Intermediate Python Architecture** relying on packages, modules, classes, and static methods for robust separation of concerns.

## ✨ Key Features

- 🎨 **Beautiful CLI Interface**: Modern ANSI color-coded terminal outputs for a rich user experience.
- 📊 **Intelligent Analytics**: Auto-generates monthly reports with visual ASCII bar charts.
- 🔮 **Predictive Spending**: Analyzes historical spending patterns to forecast next month's expenses.
- 🚨 **Anomaly Detection**: Automatically flags unusual high-spending categories.
- 💾 **Local Persistence**: Securely saves and loads user data locally using customized object serialization (No database required).

## 📂 Project Structure

```text
SmartFi-Finance-Manager/
├── smartfi/               # Core Python Package
│   ├── __init__.py
│   ├── analytics.py       # Math and prediction algorithms
│   ├── manager.py         # App lifecycle and main controller
│   ├── models.py          # Data definitions (User, Transaction)
│   ├── storage.py         # File I/O operations
│   └── ui.py              # CLI printing and safe inputs
├── data/
│   └── data.txt           # Persistent storage for transactions
├── main.py                # Main entry script
└── README.md              # Project documentation
```

## 🚀 Getting Started

### Prerequisites
- **Python 3.8+**

### Run Instructions

1. **Clone & Navigate**
   ```bash
   git clone <your-repo-url>
   cd SmartFi-Finance-Manager
   ```

2. **Run the Application**
   ```bash
   python main.py
   ```

## 🤝 Contributing
Contributions, issues, and feature requests are welcome!

## 📝 License
This project is licensed under the MIT License.
