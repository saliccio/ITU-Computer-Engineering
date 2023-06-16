- init_convex:
    run: rm -f convex
    blocker: true

- build_convex:
    run: g++ -std=c++11 -Wall -Werror convex.cpp -o convex  # timeout: 2
    blocker: true

- init_prim:
    run: rm -f prim
    blocker: true

- build_prim:
    run: g++ -std=c++11 -Wall -Werror prim.cpp -o prim  # timeout: 2
    blocker: true

- run_convex00:
    run: ./convex cases/case00/input00.txt # timeout: 45
    blocker: true
    exit: 0

- diff_convex00:
    run: diff -rsZ convex.txt cases/case00/convex00.txt
    points: 1.9
    script:
        - expect: "Files convex.txt and cases/case00/convex00.txt are identical"
    exit: 0
- run_convex01:
    run: ./convex cases/case01/input01.txt # timeout: 45
    blocker: true
    exit: 0

- diff_convex01:
    run: diff -rsZ convex.txt cases/case01/convex01.txt
    points: 1.9
    script:
        - expect: "Files convex.txt and cases/case01/convex01.txt are identical"
    exit: 0
- run_convex02:
    run: ./convex cases/case02/input02.txt # timeout: 45
    blocker: true
    exit: 0

- diff_convex02:
    run: diff -rsZ convex.txt cases/case02/convex02.txt
    points: 1.9
    script:
        - expect: "Files convex.txt and cases/case02/convex02.txt are identical"
    exit: 0
- run_convex03:
    run: ./convex cases/case03/input03.txt # timeout: 45
    blocker: true
    exit: 0

- diff_convex03:
    run: diff -rsZ convex.txt cases/case03/convex03.txt
    points: 1.9
    script:
        - expect: "Files convex.txt and cases/case03/convex03.txt are identical"
    exit: 0
- run_convex04:
    run: ./convex cases/case04/input04.txt # timeout: 45
    blocker: true
    exit: 0

- diff_convex04:
    run: diff -rsZ convex.txt cases/case04/convex04.txt
    points: 1.9
    script:
        - expect: "Files convex.txt and cases/case04/convex04.txt are identical"
    exit: 0
- run_convex06:
    run: ./convex cases/case06/input06.txt # timeout: 45
    blocker: true
    exit: 0

- diff_convex06:
    run: diff -rsZ convex.txt cases/case06/convex06.txt
    points: 1.9
    script:
        - expect: "Files convex.txt and cases/case06/convex06.txt are identical"
    exit: 0
- run_convex07:
    run: ./convex cases/case07/input07.txt # timeout: 45
    blocker: true
    exit: 0

- diff_convex07:
    run: diff -rsZ convex.txt cases/case07/convex07.txt
    points: 1.9
    script:
        - expect: "Files convex.txt and cases/case07/convex07.txt are identical"
    exit: 0
- run_convex10:
    run: ./convex cases/case10/input10.txt # timeout: 45
    blocker: true
    exit: 0

- diff_convex10:
    run: diff -rsZ convex.txt cases/case10/convex10.txt
    points: 1.9
    script:
        - expect: "Files convex.txt and cases/case10/convex10.txt are identical"
    exit: 0
- run_convex11:
    run: ./convex cases/case11/input11.txt # timeout: 45
    blocker: true
    exit: 0

- diff_convex11:
    run: diff -rsZ convex.txt cases/case11/convex11.txt
    points: 1.9
    script:
        - expect: "Files convex.txt and cases/case11/convex11.txt are identical"
    exit: 0
- run_convex12:
    run: ./convex cases/case12/input12.txt # timeout: 45
    blocker: true
    exit: 0

- diff_convex12:
    run: diff -rsZ convex.txt cases/case12/convex12.txt
    points: 1.9
    script:
        - expect: "Files convex.txt and cases/case12/convex12.txt are identical"
    exit: 0





- run_prim00:
    run: ./prim cases/case00/input00.txt # timeout: 45
    blocker: true
    exit: 0

- diff_prim00:
    run: diff -rsZ prim.txt cases/case00/prim00.txt
    points: 2.1
    script:
        - expect: "Files prim.txt and cases/case00/prim00.txt are identical"
    exit: 0
- run_prim01:
    run: ./prim cases/case01/input01.txt # timeout: 45
    blocker: true
    exit: 0

- diff_prim01:
    run: diff -rsZ prim.txt cases/case01/prim01.txt
    points: 2.1
    script:
        - expect: "Files prim.txt and cases/case01/prim01.txt are identical"
    exit: 0
- run_prim02:
    run: ./prim cases/case02/input02.txt # timeout: 45
    blocker: true
    exit: 0

- diff_prim02:
    run: diff -rsZ prim.txt cases/case02/prim02.txt
    points: 2.1
    script:
        - expect: "Files prim.txt and cases/case02/prim02.txt are identical"
    exit: 0
- run_prim03:
    run: ./prim cases/case03/input03.txt # timeout: 45
    blocker: true
    exit: 0

- diff_prim03:
    run: diff -rsZ prim.txt cases/case03/prim03.txt
    points: 2.1
    script:
        - expect: "Files prim.txt and cases/case03/prim03.txt are identical"
    exit: 0
- run_prim04:
    run: ./prim cases/case04/input04.txt # timeout: 45
    blocker: true
    exit: 0

- diff_prim04:
    run: diff -rsZ prim.txt cases/case04/prim04.txt
    points: 2.1
    script:
        - expect: "Files prim.txt and cases/case04/prim04.txt are identical"
    exit: 0
- run_prim06:
    run: ./prim cases/case06/input06.txt # timeout: 45
    blocker: true
    exit: 0

- diff_prim06:
    run: diff -rsZ prim.txt cases/case06/prim06.txt
    points: 2.1
    script:
        - expect: "Files prim.txt and cases/case06/prim06.txt are identical"
    exit: 0
- run_prim07:
    run: ./prim cases/case07/input07.txt # timeout: 45
    blocker: true
    exit: 0

- diff_prim07:
    run: diff -rsZ prim.txt cases/case07/prim07.txt
    points: 2.1
    script:
        - expect: "Files prim.txt and cases/case07/prim07.txt are identical"
    exit: 0
- run_prim10:
    run: ./prim cases/case10/input10.txt # timeout: 45
    blocker: true
    exit: 0

- diff_prim10:
    run: diff -rsZ prim.txt cases/case10/prim10.txt
    points: 2.1
    script:
        - expect: "Files prim.txt and cases/case10/prim10.txt are identical"
    exit: 0
- run_prim11:
    run: ./prim cases/case11/input11.txt # timeout: 45
    blocker: true
    exit: 0

- diff_prim11:
    run: diff -rsZ prim.txt cases/case11/prim11.txt
    points: 2.1
    script:
        - expect: "Files prim.txt and cases/case11/prim11.txt are identical"
    exit: 0
- run_prim12:
    run: ./prim cases/case12/input12.txt # timeout: 45
    blocker: true
    exit: 0

- diff_prim12:
    run: diff -rsZ prim.txt cases/case12/prim12.txt
    points: 2.1
    script:
        - expect: "Files prim.txt and cases/case12/prim12.txt are identical"
    exit: 0