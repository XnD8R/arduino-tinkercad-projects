# 🔌 Arduino Tinkercad Projects

Arduino circuits I designed, programmed and simulated in **Tinkercad Circuits**.

---

## 🔐 PIN Vault Lock System

A 4-digit PIN lock with an alarm, built on an Arduino Uno.

![PIN Vault Lock circuit](circuit.png)

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
  <img width="49%" alt="Wrong PIN: Pin Rejected, Try 1/3" src="pin-rejected.png" />
  <img width="49%" alt="Correct PIN: Vault Open" src="vault-open.png" />
</p>

📄 Code: [`pin_vault_lock.ino`](pin_vault_lock.ino)

---

## 👤 Author
**Ziad Elmeligy** · CS student at the German International University (GIU)
[GitHub](https://github.com/XnD8R) · [LinkedIn](https://linkedin.com/in/Ziad-M-Elmeligy)
