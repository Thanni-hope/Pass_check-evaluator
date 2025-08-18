# C++ Password Generator & Strength Evaluator

This project is a console-based C++ program that generates secure random passwords based on user preferences and evaluates the strength of any given password using entropy and pattern analysis.

---

## Features

- **Customizable password generation** with options to include:
  - Uppercase letters
  - Lowercase letters
  - Digits
  - Symbols
- **Password length selection** with validation (between 6 to 100 characters)
- **Password strength evaluation** using:
  - Length and character variety
  - Estimated entropy calculation
  - Checks for repeated characters and sequential patterns
  - Comparison against a list of common weak passwords
- Ability to **evaluate user-provided passwords** for strength
- Friendly user interaction with input validation and repetitive use support

---

## How to Build

Compile with a C++11 (or later) compatible compiler:

```bash
g++ -std=c++11 -o password_generator main.cpp
```

Replace `main.cpp` with your source file name.

---

## How to Run

Run the executable:

```bash
./password_generator
```

You will be prompted to:

- Choose to generate a password or evaluate an existing one.
- Enter password length (if generating).
- Select which character types to include.
- See the generated password and its strength.
- Or enter any password to evaluate its strength.
- Continue or exit as desired.

---

## Example Usage

```
Do you want to check your password strength or generate a new password? (e/g): g
Enter desired password length: 12
Include uppercase letters? (y/n): y
Include lowercase letters? (y/n): y
Include digits? (y/n): y
Include symbols? (y/n): n
Your requested password: aB7hDj2mXkP3
Password Strength: Strong (Entropy: 72 bits)
Do you want to check another password's strength or generate another password?(y/n): n
Hope youre satisfied with our pass checker/evaluator :0
```

---

## Notes

- The entropy estimate is a rough guide based on password length and character set.
- Password evaluation includes simple heuristics and a small common password blacklist.
- For strongest security, use longer passwords with multiple character types.
- Symbols used are: `!@#$%^&*()-_=+[]{};:,.<>?`

---

## License

This project is open-source and available under the MIT License.

---

## Contact

For questions or suggestions, please open an issue on the GitHub repository or contact me directly.
