#include <iostream>
#include <string>

/*
Extracts a valid IPv4 address and optional port from the input string.

Inputs: 
    - str is the input string
    - outAddress stores the extracted IPv4 address
    - outPort stores the extracted port

Returns:
    - true if a valid IPv4 address is found and false otherwise

Author:
    - AI (ChatGPT GPT-5.6 Luna): created the initial code and slight adjustments and refinement were made.
*/
bool extractIPv4(const std::string& str,
                 unsigned long& outAddress,
                 int& outPort)
{
    // Initialize the outputs to their default.
    outAddress = 0;
    outPort = -1;

    size_t i = 0; // Start iteration through the string

    while (i < str.length())
    {
        // Skip garbage until we reach a digit, period, or colon.
        if (str[i] != '.' && str[i] != ':' &&
            (str[i] < '0' || str[i] > '9'))
        {
            ++i;
            continue;
        }

        // Find the end of this complete candidate token.
        size_t start = i;
        size_t end = i;

        // Find the complete candidate.
        while (end < str.length() &&
               (str[end] == '.' || str[end] == ':' ||
                (str[end] >= '0' && str[end] <= '9')))
        {
            ++end;
        }

        // A valid candidate must begin with a digit.
        if (str[start] < '0' || str[start] > '9')
        {
            i = end;
            continue;
        }

        size_t pos = start; // where we currently are inside the candidate
        unsigned long octets[4] = {0, 0, 0, 0}; // create storage for the octets
        bool valid = true; // assume candidate to be valid

        // Parse the four octets.
        for (int octet = 0; octet < 4; ++octet)
        {
            // Each octet must contain at least one digit.
            if (pos >= end ||
                str[pos] < '0' || str[pos] > '9')
            {
                valid = false;
                break;
            }

            // No leading zero unless the octet is exactly 0.
            if (str[pos] == '0' &&
                pos + 1 < end &&
                str[pos + 1] >= '0' &&
                str[pos + 1] <= '9')
            {
                valid = false;
                break;
            }

            unsigned long value = 0; // value of octet
            int digits = 0; // number of digits

            // Keep reading digits of the octet
            while (pos < end &&
                   str[pos] >= '0' &&
                   str[pos] <= '9')
            {
                // Confirm there are not more than 3 digits.
                if (digits == 3)
                {
                    valid = false;
                    break;
                }

                value = value * 10 + (str[pos] - '0'); // add digit to the number
                ++digits;
                ++pos;
            }

            // Check whether the octet was invalid
            if (!valid || value > 255)
            {
                valid = false;
                break;
            }

            octets[octet] = value; // save the octet

            // The first three octets must be followed by '.'.
            if (octet < 3)
            {
                if (pos >= end || str[pos] != '.')
                {
                    valid = false;
                    break;
                }

                ++pos;
            }
        }

        // Confirm 4 octets are valid
        if (!valid)
        {
            i = end;
            continue;
        }

        // Check for an optional port.
        if (pos < end)
        {
            // Check if whatever is left is a port
            if (str[pos] != ':')
            {
                i = end;
                continue;
            }

            ++pos; // move past the ':'

            // A colon must be followed by at least one digit.
            if (pos >= end ||
                str[pos] < '0' || str[pos] > '9')
            {
                i = end;
                continue;
            }

            // No leading zero unless the port is exactly 0.
            if (str[pos] == '0' &&
                pos + 1 < end &&
                str[pos + 1] >= '0' &&
                str[pos + 1] <= '9')
            {
                i = end;
                continue;
            }

            int port = 0; // initialize port number
            int digits = 0; // initialize number of port digits

            // Keep reading characters while there are digits remaining.
            while (pos < end &&
                   str[pos] >= '0' &&
                   str[pos] <= '9')
            {
                // Max number of digits is 5
                if (digits == 5)
                {
                    valid = false;
                    break;
                }

                port = port * 10 + (str[pos] - '0'); // convert the digit characters to a number
                ++digits;
                ++pos;
            }

            // Test for invalid ports.
            if (!valid || port > 65535 || pos != end)
            {
                i = end;
                continue;
            }

            outPort = port;
        }
        else
        {
            outPort = -1; // address has no port
        }

        // The entire candidate must have been consumed.
        if (pos != end)
        {
            i = end;
            continue;
        }

        // Construct the 32-bit decimal IPv4 value manually.
        outAddress =
            ((octets[0] * 256 + octets[1]) * 256 + octets[2]) * 256
            + octets[3];

        return true;
    }

    return false;
}

/*
Prompts the user for a string and displays the result and information regarding the IPv4 address.

Input: a string will be entered by the user.

Output: the extracted IPv4 address and port, an error message, or the program terminates.

Author:
    - AI (ChatGPT GPT-5.6 Luna): created the initial code and slight adjustments and refinement were made.
*/
int main()
{
    std::string input; // create input variable

    // Keep asking the user for input
    while (true)
    {
        std::cout << "Enter a string (or 'END' to quit): ";
        std::getline(std::cin, input);

        if (input == "END")
        {
            std::cout << "Program terminated." << std::endl;
            break;
        }

        // Receive results from the 'extractIPv4'
        unsigned long address; 
        int port;

        if (extractIPv4(input, address, port))
        {
            // Recover the four octets from the 32-bit address.
            // Shift desired octet right and use '&' to keep only 8 bits.
            unsigned long a = (address >> 24) & 255; // 1st octet
            unsigned long b = (address >> 16) & 255; // 2nd octet
            unsigned long c = (address >> 8) & 255; // 3rd octet
            unsigned long d = address & 255; // 4th octet

            // Output the IPv4 address
            std::cout << "Extracted IPv4 address: "
                      << a << "."
                      << b << "."
                      << c << "."
                      << d
                      << " (decimal value: "
                      << address
                      << ", port: ";

            // Check if there is a port
            if (port == -1)
            {
                std::cout << "none";
            }

            // There is a port
            else
            {
                std::cout << port;
            }

            std::cout << ")" << std::endl;
        }

        // Otherwise, there is not a valid address
        else
        {
            std::cout << "Invalid input: no valid IPv4 address found"
                      << std::endl;
        }
    }

    return 0;
}