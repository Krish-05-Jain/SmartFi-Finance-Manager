from smartfi.manager import FinanceManager

def main():
    app = FinanceManager()
    app.run()

if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        print("\n\nExiting...")
