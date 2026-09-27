# Testing

## Test Categories

### 1. Valid IPv4 Addresses

These tests verify valid IPv4 addresses, including minimum and maximum octet values, addresses surrounded by garbage, and ordinary addresses.

| Test Case                          | Expected IPv4 Address | Expected Decimal Value | Expected Port | Expected |
| ---------------------------------- | --------------------- | ---------------------: | ------------- | -------- |
| `connecting to 192.168.1.1 now`    | `192.168.1.1`         |           `3232235777` | `none`        | Valid    |
| `hjdfjsjdjf255.255.255.255dhhfdfj` | `255.255.255.255`     |           `4294967295` | `none`        | Valid    |
| `0.0.0.0djfjkdhf`                  | `0.0.0.0`             |                    `0` | `none`        | Valid    |
| `hello 192.168.1.1 world`          | `192.168.1.1`         |           `3232235777` | `none`        | Valid    |
| `123.45.67.89`                     | `123.45.67.89`        |           `2066563929` | `none`        | Valid    |
| `0.1.0.255`                        | `0.1.0.255`           |                `65791` | `none`        | Valid    |

**Expected:** All valid.

**Actual:** All valid.

---

### 2. Valid IPv4 Addresses with Ports

These tests verify valid ports, including the minimum port (`0`), maximum port (`65535`), and a normal port.

| Test Case               | Expected IPv4 Address | Expected Decimal Value | Expected Port | Expected |
| ----------------------- | --------------------- | ---------------------: | ------------: | -------- |
| `1.2.3.4:0askjfjkf`     | `1.2.3.4`             |             `16909060` |           `0` | Valid    |
| `1.2.3.4:65535`         | `1.2.3.4`             |             `16909060` |       `65535` | Valid    |
| `server=10.0.0.1:8080`  | `10.0.0.1`            |            `167772161` |        `8080` | Valid    |
| `192.168.1.1:65535`     | `192.168.1.1`         |           `3232235777` |       `65535` | Valid    |
| `255.255.255.255:65535` | `255.255.255.255`     |           `4294967295` |       `65535` | Valid    |
| `0.0.0.0:0`             | `0.0.0.0`             |                    `0` |           `0` | Valid    |
| `1.2.3.4:12345`         | `1.2.3.4`             |             `16909060` |       `12345` | Valid    |

**Expected:** All valid.

**Actual:** All valid.

---

### 3. Out-of-Range Octets and Ports

These tests verify rejection of octets greater than `255` and ports greater than `65535`.

| Test Case            | Expected Result                                    |
| -------------------- | -------------------------------------------------- |
| `256.0.0.1dkjfkjdsf` | Invalid                                            |
| `1.256.3.4`          | Invalid                                            |
| `1.2.3.256`          | Invalid                                            |
| `1.2.3.4:65536`      | Invalid                                            |
| `1.2.3.4:99999x`     | Invalid                                            |
| `1.2.999.4x5.6.7.8`  | Valid → `5.6.7.8`, decimal `84281096`, port `none` |

**Expected:** First five invalid; last one valid.

**Actual:** First five invalid; last one valid.

---

### 4. Leading-Zero Violations

These tests verify that octets and ports cannot contain leading zeros unless the value is exactly `0`.

| Test Case       | Expected |
| --------------- | -------- |
| `01.2.3.4`      | Invalid  |
| `1.02.3.4`      | Invalid  |
| `1.2.03.4`      | Invalid  |
| `1.2.3.04`      | Invalid  |
| `1.2.3.4:01`    | Invalid  |
| `1.2.3.4:000`   | Invalid  |
| `1.2.3.4:00`    | Invalid  |
| `1.2.3.4:00000` | Invalid  |
| `1.2.3.4:00001` | Invalid  |

**Expected:** All invalid.

**Actual:** All invalid.

---

### 5. Invalid IPv4 Structure

These tests verify missing or extra octets, empty octets, and incorrect placement of separators.

| Test Case   | Expected |
| ----------- | -------- |
| `1.2.3`     | Invalid  |
| `1.2.3.4.5` | Invalid  |
| `1..2.3.4`  | Invalid  |
| `1.2..3.4`  | Invalid  |
| `1.2.3..4`  | Invalid  |
| `1.2.3:80`  | Invalid  |
| `1:2.3.4`   | Invalid  |

**Expected:** All invalid.

**Actual:** All invalid.

---

### 6. Invalid Ports and Colons

These tests verify missing ports, multiple colons, misplaced colons, and ports longer than five digits.

| Test Case        | Expected |
| ---------------- | -------- |
| `1.2.3.4:`       | Invalid  |
| `1.2.3.4::80`    | Invalid  |
| `1.2.3.4:80:90`  | Invalid  |
| `:1.2.3.4`       | Invalid  |
| `:1.2.3.4:80`    | Invalid  |
| `1.2.3.4:123456` | Invalid  |

**Expected:** All invalid.

**Actual:** All invalid.

---

### 7. Candidate-Token and Garbage Separation

These tests verify how garbage characters separate candidate tokens. Characters other than digits, `.`, and `:` terminate a candidate, allowing the program to continue searching for another candidate. These cases also test invalid candidates followed by valid candidates and multiple valid candidates.

|  # | Test Case                                                 | Expected Result                                          |
| -: | --------------------------------------------------------- | -------------------------------------------------------- |
|  1 | `192.168.1.1.`                                            | Invalid                                                  |
|  2 | `.192.168.1.1`                                            | Invalid                                                  |
|  3 | `192a168.1.1.1`                                           | Valid → `168.1.1.1`, decimal `2818638081`, port `none`   |
|  4 | `abc192.168.1.1xyzsdfjhdsjfkhjkhhhhhdsfhjhf1.1.1.1ghkjhf` | Valid → `192.168.1.1`, decimal `3232235777`, port `none` |
|  5 | `999.999.999.999 192.168.1.1`                             | Valid → `192.168.1.1`, decimal `3232235777`, port `none` |
|  6 | `192.168.01.1 10.20.30.40`                                | Valid → `10.20.30.40`, decimal `169090600`, port `none`  |
|  7 | `1.2.3.4x5.6.7.8`                                         | Valid → `1.2.3.4`, decimal `16909060`, port `none`       |
|  8 | `1.2.999.4x5.6.7.8`                                       | Valid → `5.6.7.8`, decimal `84281096`, port `none`       |
|  9 | `1.2.999.4.5.6.7.8`                                       | Invalid                                                  |
| 10 | `1.2.3.4x:80`                                             | Valid → `1.2.3.4`, decimal `16909060`, port `none`       |
| 11 | `1.2.3.4:80x5.6.7.8`                                      | Valid → `1.2.3.4`, decimal `16909060`, port `80`         |
| 12 | `1.2.3.4:99999x5.6.7.8`                                   | Valid → `5.6.7.8`, decimal `84281096`, port `none`       |
| 13 | `1.2.3.4: 80`                                             | Invalid                                                  |
| 14 | `1.2.3.4:80.`                                             | Invalid                                                  |
| 15 | `1.2.3.4abc:8080`                                         | Valid → `1.2.3.4`, decimal `16909060`, port `none`       |
| 16 | `999.999.999.999!192.168.1.1`                             | Valid → `192.168.1.1`, decimal `3232235777`, port `none` |
| 17 | `1.2.3.4:00 10.20.30.40`                                  | Valid → `10.20.30.40`, decimal `169090600`, port `none`  |
| 18 | `1.2.3.4 10.20.30.40`                                     | Valid → `1.2.3.4`, decimal `16909060`, port `none`       |

**Expected:**

* Invalid: Tests **1, 2, 9, 13, 14**
* Valid: Tests **3–8, 10–12, 15–18**

**Actual:** Matches all expected results.

---

### 8. No Valid IPv4 Address

These tests verify inputs containing no valid IPv4 address, including ordinary text, special characters, incomplete numeric strings, and punctuation-only candidates.

| Test Case                   | Expected |
| --------------------------- | -------- |
| `sjdbghjghjgfbhjbgf`        | Invalid  |
| `hello`                     | Invalid  |
| `abcdef`                    | Invalid  |
| `this is not an IP address` | Invalid  |
| `no number here`            | Invalid  |
| `!@#$%^&*()`                | Invalid  |
| `123`                       | Invalid  |
| `1`                         | Invalid  |
| `12`                        | Invalid  |
| `...`                       | Invalid  |
| `:::`                       | Invalid  |
| `:`                         | Invalid  |

**Expected:** All invalid.

**Actual:** All invalid.

---

### 9. Program Termination

| Test Case | Expected           |
| --------- | ------------------ |
| `END`     | Program terminates |

**Expected:** Program terminates and displays `Program terminated.`

**Actual:** Program terminates and displays `Program terminated.`
