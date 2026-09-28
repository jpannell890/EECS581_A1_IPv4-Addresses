# AI Usage and Disclosure

## General Disclosure

* **GAI Tool:** ChatGPT
* **Version:** GPT-5.6 Luna
* **Date(s) Consulted:** 9/25/26, 9/26/26, 9/27/26

## Code Attribution

### Prompt 1

> Act as an experienced C++ programmer and parser expert that must focus on minimizing bugs and testing all edge cases before coming up with a solution. Carefully implement the IPv4 parser and do not assume your first implementation is successful and meets all requirements.
>
> Write a C++ program that implements the IPv4 parser described:
>
> The program must read a line of text and extract a single valid IPv4 address with a potential port number anywhere in the text with garbage characters skipped.
>
> The following are the requirements:
>
> * Only digits, periods, and colons are ever part of a valid token.
> * Characters that do not represent the accepted set of characters are considered garbage and skipped.
> * To match an address, the token must be fully correct with no partial matches or truncating to find a valid piece.
> * An acceptable address must be 4 octets that follows this form: `octet.octet.octet.octet`.
> * Each octet is 1–3 digits.
> * Each octet has a value of 0–255.
> * No leading zeros unless the value is exactly 0.
> * Optionally, a port may be included that follows the fourth octet: `:port`.
>
>   * The port must be 1–5 digits.
>   * The port must have a value of 0–65535.
>   * The port cannot have leading zeros unless the value is exactly 0.
>   * If a colon is used to indicate a port, the port must be fully valid or the entire match is rejected.
> * Exactly one valid address can be extracted per input line, and all else in the line is skipped or part of a token that fails validation.
> * Reject anything that does not exactly match the requirements.
>
>   * Examples include a wrong octet count, empty octet, out-of-range octet or port, a disallowed leading zero, a second colon, a colon not immediately after the fourth octet, or a stray period/colon directly adjacent to an otherwise-valid address.
> * On success, print:
>   `Extracted IPv4 address: A.B.C.D (decimal value: N, port: P)`
>   where `N` is the 32-bit decimal value and `P` is the port number or the literal text `none`.
>
> ### Programming Requirements
>
> The following requirements were provided in the assignment:
>
> * The function prototype is:
>
>  ```cpp
>  bool extractIPv4(const std::string& str, unsigned long& outAddress, int& outPort);
>  ```
>
> * The `extractIPv4` function must:
>
>  * Return `true` if a valid address was found and otherwise return `false`.
>  * On success, `outAddress` holds the 32-bit value.
>  * On success, `outPort` holds the port number, or `-1` if no port was present.
>  * On failure, `outAddress` is set to `0` and `outPort` is set to `-1`.
>  * Perform all digit accumulation manually.
>
> * The `main` function must:
>
>  * Continue to prompt the user for input until the user enters `END`.
>  * Print `Program terminated.` and exit when `END` is entered.
>  * Display the result received from `extractIPv4` using the required format.
>
>### Important Restrictions
>
> The following functions and libraries may not be used:
>
> 1. **String-to-number conversion functions**
>
>   * `atoi`
>   * `atol`
>   * `atoll`
>   * `strtol`
>   * `strtoul`
>   * `strtod`
>   * `stoi`
>   * `stol`
>   * `stoul`
>   * `sscanf`
>   * `scanf` with numeric conversions
>
> 2. **Address-parsing library functions**
>
>   * `inet_aton`
>   * `inet_pton`
>   * `inet_addr`
>   * Equivalent address-parsing functions
>
> 3. **Regular-expression facilities**
>
>   * `std::regex`
>   * `regex.h`
>   * Similar regular-expression libraries
>
>*The parsing and validation logic must be implemented using character-by-character code rather than a pattern-matching library.*
>
> *Standard character-classification functions such as `isdigit` are permitted.*
>
> ### Sample Runs
>
> The following sample runs were provided by the professor:
>
> ```text
> Enter a string (or 'END' to quit): connecting to 192.168.1.1 now
> Extracted IPv4 address: 192.168.1.1 (decimal value: 3232235777, port: none)
>
> Enter a string (or 'END' to quit): server=10.0.0.255:8080end
> Extracted IPv4 address: 10.0.0.255 (decimal value: 167772415, port: 8080)
>
> Enter a string (or 'END' to quit): 192a168.1.1.1
> Extracted IPv4 address: 168.1.1.1 (decimal value: 2818638081, port: none)
>
> Enter a string (or 'END' to quit): 192.168.1.1.
> Invalid input: no valid IPv4 address found
>
> Enter a string (or 'END' to quit): Connection from 192.168.1.1 refused
> Extracted IPv4 address: 192.168.1.1 (decimal value: 3232235777, port: none)
>
> Enter a string (or 'END' to quit): 192.168.01.1
> Invalid input: no valid IPv4 address found
>
> Enter a string (or 'END' to quit): 1.2.3.4:99999
> Invalid input: no valid IPv4 address found
>
> Enter a string (or 'END' to quit): 12.34.56
> Invalid input: no valid IPv4 address found
>
> Enter a string (or 'END' to quit): no number here
> Invalid input: no valid IPv4 address found
>
> Enter a string (or 'END' to quit): END
> Program terminated.
> ```

## Documentation

The whole code was initially developed using AI generation. After further discussion and review, the code was modified to fulfill the assignment requirements. The code was primarily run, tested, and reviewed by me.

* Each function contains comments describing its purpose, behavior, and author.
* The code was reviewed to make sure I understood how each part works.

## Modifications

1. **Simplified the work performed by `main`**

   * The original code had `main` parse the address a second time to reconstruct the decimal display.
   * This was unnecessary because `extractIPv4` already returns the parsed address and port through its output parameters.
   * I changed `main` to use the information returned by `extractIPv4` rather than having `main` repeat the parsing work.

2. **Added explanatory comments**

   * I added comments throughout the code to demonstrate my understanding of the implementation.
   * The comments explain the purpose of important variables, conditions, parsing steps, and output operations.

## Verification Statement

1. **Code Review**

   * I reviewed the code line by line to understand how it works.
   * Comments were added throughout the code to document my understanding of the implementation and the reasoning behind important sections.
   * AI was also used to discuss confusing parts of the implementation and clarify how different parsing and validation techniques work.

2. **Testing**

   * The code passed all of the assignment's provided test cases.
   * Additional valid, invalid, boundary, malformed-input, and stress test cases were also created and tested.
   * Testing included cases involving leading zeros, out-of-range octets and ports, extra periods and colons, invalid candidate tokens, and multiple possible addresses in the same input.

3. **Known Bugs and Limitations**

   * As of the date of this disclosure, no known correctness bugs were found during testing.
   * All tested assignment and additional test cases produced the expected results.
