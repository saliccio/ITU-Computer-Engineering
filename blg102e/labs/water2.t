- init:
    run: rm -f water
    blocker: true

- build:
    run: gcc -std=c99 -Wall -Werror water2.c -o water  # timeout: 2
    blocker: true

- case_67_C:
    run: ./water
    points: 1
    script:
        - expect: "Enter temperature \\(end with F for Fahrenheit or C for Celsius\\): "  # timeout: 2
        - send: "67 C"
        - expect: "Enter altitude in meters: " # timeout: 2
        - send: "100"
        - expect: "Water is Liquid at 67.00 degrees Celsius\r\n"                   # timeout: 2
        - expect: _EOF_  # timeout: 2
    exit: 0

- case_19_2_F:
    run: ./water
    points: 1
    script:
        - expect: "Enter temperature \\(end with F for Fahrenheit or C for Celsius\\): "  # timeout: 2
        - send: "19.2 F"
        - expect: "Enter altitude in meters: " # timeout: 2
        - send: "100"
        - expect: "Water is Solid \\(Ice\\) at 19.20 degrees Fahrenheit\r\n"                   # timeout: 2
        - expect: _EOF_  # timeout: 2
    exit: 0

- case_99_C_100:
    run: ./water
    points: 1
    script:
        - expect: "Enter temperature \\(end with F for Fahrenheit or C for Celsius\\): "  # timeout: 2
        - send: "99 C"
        - expect: "Enter altitude in meters: " # timeout: 2
        - send: "100"
        - expect: "Water is Liquid at 99.00 degrees Celsius\r\n"                   # timeout: 2
        - expect: _EOF_  # timeout: 2
    exit: 0

- case_99_C_500:
    run: ./water
    points: 1
    script:
        - expect: "Enter temperature \\(end with F for Fahrenheit or C for Celsius\\): "  # timeout: 2
        - send: "99 C"
        - expect: "Enter altitude in meters: " # timeout: 2
        - send: "500"
        - expect: "Water is Gas \\(Vapor\\) at 99.00 degrees Celsius\r\n"                   # timeout: 2
        - expect: _EOF_  # timeout: 2
    exit: 0

- case_input_error:
    run: ./water
    points: 1
    script:
        - expect: "Enter temperature \\(end with F for Fahrenheit or C for Celsius\\): "  # timeout: 2
        - send: "67 K"
        - expect: "Enter altitude in meters: " # timeout: 2
        - send: "500"
        - expect: "Please enter temperature unit as either C or F.\r\n"                  # timeout: 2
        - expect: _EOF_                                # timeout: 2
    exit: 1
