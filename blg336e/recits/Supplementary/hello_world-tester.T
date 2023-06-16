- init:
    run: rm -f hello_world
    blocker: true

- build:
    run: g++ -std=c++11 -Wall -Werror hello_world.cpp -o hello_world  # timeout: 2
    blocker: true

- case_run1:
    run: ./hello_world
    # blocker: true
    points: 10
    script:
        - expect: "Hello World!*"
    exit: 0