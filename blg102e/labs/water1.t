- init:
    run: rm -f water
    blocker: true

- build:
    run: gcc -std=c99 -Wall -Werror water1.c -o water  # timeout: 2
    blocker: true

- case_67_C:
    run: ./water
    points: 1
    script:
        - expect: "Enter temperature \\(end with F for Fahrenheit or C for Celsius\\): "  # timeout: 2
        - send: "67 C"
        - expect: "Water is Liquid at 67.00 degrees Celsius\r\n"                   # timeout: 2
        - expect: _EOF_  # timeout: 2
    exit: 0

- case_19_2_F:
    run: ./water
    points: 1
    script:
        - expect: "Enter temperature \\(end with F for Fahrenheit or C for Celsius\\): "  # timeout: 2
        - send: "19.2 F"
        - expect: "Water is Solid \\(Ice\\) at 19.20 degrees Fahrenheit\r\n"                   # timeout: 2
        - expect: _EOF_  # timeout: 2
    exit: 0

- case_180_C:
    run: ./water
    points: 1
    script:
        - expect: "Enter temperature \\(end with F for Fahrenheit or C for Celsius\\): "  # timeout: 2
        - send: "180 C"
        - expect: "Water is Gas \\(Vapor\\) at 180.00 degrees Celsius\r\n"                   # timeout: 2
        - expect: _EOF_  # timeout: 2
    exit: 0

- case_input_error:
    run: ./water
    points: 1
    script:
        - expect: "Enter temperature \\(end with F for Fahrenheit or C for Celsius\\): "  # timeout: 2
        - send: "67 K"
        - expect: "Please enter temperature unit as either C or F.\r\n"                  # timeout: 2
        - expect: _EOF_                                # timeout: 2
    exit: 1
