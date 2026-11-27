# 🔌 Arduino Tinkercad Projects

Arduino circuits I designed, programmed and simulated in **Tinkercad Circuits**.

---

## 🔐 PIN Vault Lock System

A 4-digit PIN lock with an alarm, built on an Arduino Uno.

<img width="1491" height="706" alt="Screenshot 2026-11-27 150439" src="https://github.com/user-attachments/assets/afb076c1-3dda-48d9-b144-23d9cdcb98b6" />

**▶ [Try the simulation on Tinkercad](https://www.tinkercad.com/things/dR4XnJqehzw-arduino-lcd-alarm-system)**

### How it works
- **Four buttons** each set one digit of the PIN. Press to count 0–9, or hold to scroll quickly.
- The **Enter** button checks the PIN against the stored code.
- ✅ **Correct PIN:** the green LED turns on and the LCD shows *"Vault Open!"*
- ❌ **Wrong PIN:** the red LED flashes, the LCD shows the attempt count (*"Try: 1/3"*), and the digits reset.
- 🚨 **3 wrong attempts:** the alarm goes off (red LED + buzzer) and the system locks.

### Components
| Component | Pin |
|---|---|
| Arduino Uno | — |
| 16x2 LCD (I2C, address 0x27) | SDA / SCL |
| 4 × digit push buttons | D2, D3, D4, D5 |
| Enter push button | D6 |
| Green LED | D7 |
| Red LED | D8 |
| Buzzer | D9 |
| Breadboard + resistors for the LEDs | — |

### Programming concepts used
- **Edge detection** to register one press per click instead of repeating
- **Non-blocking timing** with `millis()` for the hold-to-scroll feature
- **`INPUT_PULLUP`** buttons (no external resistors needed)
- **State handling** for the open, locked and entering-PIN modes
- **I2C communication** with the LCD using `Wire` and `LiquidCrystal_I2C`

### Screenshots
<p align="center">
  <img width="49%" alt="Wrong PIN: Pin Rejected, Try 1/3" src="https://github.com/user-attachments/assets/7dcdf121-5617-4c8d-ae66-a2954d88a6eb" />
  <img width="49%" alt="Correct PIN: Vault Open" src="https://github.com/user-attachments/assets/4ab0920d-b2a0-4b2e-8b90-6e57a0567207" />
</p>

📄 Code: [`pin_vault_lock.ino`](pin_vault_lock.ino)

---

## 👤 Author
**Ziad Elmeligy** · CS student at the German International University (GIU)
[GitHub](https://github.com/XnD8R) · [LinkedIn](https://linkedin.com/in/Ziad-M-Elmeligy)
