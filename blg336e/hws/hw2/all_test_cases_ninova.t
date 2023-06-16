
- init_convex:
    run: rm -f convex
    
- build_convex:
    run: g++ -std=c++11 -Wall -Werror convex.cpp -o convex  # timeout: 10

- init_prim:
    run: rm -f prim

- build_prim:
    run: g++ -std=c++11 -Wall -Werror prim.cpp -o prim  # timeout: 10



- clear_00:
    run: rm -f *.txt
    visible: false
-  run_convex00:
    run: /bin/sh -c 'if [ -f "convex" ]; then ./convex ./all_cases/case00/input00.txt; fi' # timeout: 45
    exit: 0
-  diff_convex00:
    run: diff -rsZ convex.txt ./all_cases/case00/convex00.txt
    points: 1.9
    script:
        - expect: "Files convex.txt and ./all_cases/case00/convex00.txt are identical"
    exit: 0
-  run_prim00:
    run: /bin/sh -c 'if [ -f "prim" ]; then ./prim ./all_cases/case00/input00.txt; fi' # timeout: 45
    exit: 0
-  diff_prim00:
    run: diff -rsZ prim.txt ./all_cases/case00/prim00.txt
    points: 2.1
    script:
        - expect: "Files prim.txt and ./all_cases/case00/prim00.txt are identical"
    exit: 0



- clear_01:
    run: rm -f *.txt
    visible: false
-  run_convex01:
    run: /bin/sh -c 'if [ -f "convex" ]; then ./convex ./all_cases/case01/input01.txt; fi' # timeout: 45
    exit: 0
-  diff_convex01:
    run: diff -rsZ convex.txt ./all_cases/case01/convex01.txt
    points: 1.9
    script:
        - expect: "Files convex.txt and ./all_cases/case01/convex01.txt are identical"
    exit: 0
-  run_prim01:
    run: /bin/sh -c 'if [ -f "prim" ]; then ./prim ./all_cases/case01/input01.txt; fi' # timeout: 45
    exit: 0
-  diff_prim01:
    run: diff -rsZ prim.txt ./all_cases/case01/prim01.txt
    points: 2.1
    script:
        - expect: "Files prim.txt and ./all_cases/case01/prim01.txt are identical"
    exit: 0



- clear_02:
    run: rm -f *.txt
    visible: false
-  run_convex02:
    run: /bin/sh -c 'if [ -f "convex" ]; then ./convex ./all_cases/case02/input02.txt; fi' # timeout: 45
    exit: 0
-  diff_convex02:
    run: diff -rsZ convex.txt ./all_cases/case02/convex02.txt
    points: 1.9
    script:
        - expect: "Files convex.txt and ./all_cases/case02/convex02.txt are identical"
    exit: 0
-  run_prim02:
    run: /bin/sh -c 'if [ -f "prim" ]; then ./prim ./all_cases/case02/input02.txt; fi' # timeout: 45
    exit: 0
-  diff_prim02:
    run: diff -rsZ prim.txt ./all_cases/case02/prim02.txt
    points: 2.1
    script:
        - expect: "Files prim.txt and ./all_cases/case02/prim02.txt are identical"
    exit: 0



- clear_03:
    run: rm -f *.txt
    visible: false
-  run_convex03:
    run: /bin/sh -c 'if [ -f "convex" ]; then ./convex ./all_cases/case03/input03.txt; fi' # timeout: 45
    exit: 0
-  diff_convex03:
    run: diff -rsZ convex.txt ./all_cases/case03/convex03.txt
    points: 1.9
    script:
        - expect: "Files convex.txt and ./all_cases/case03/convex03.txt are identical"
    exit: 0
-  run_prim03:
    run: /bin/sh -c 'if [ -f "prim" ]; then ./prim ./all_cases/case03/input03.txt; fi' # timeout: 45
    exit: 0
-  diff_prim03:
    run: diff -rsZ prim.txt ./all_cases/case03/prim03.txt
    points: 2.1
    script:
        - expect: "Files prim.txt and ./all_cases/case03/prim03.txt are identical"
    exit: 0



- clear_04:
    run: rm -f *.txt
    visible: false
-  run_convex04:
    run: /bin/sh -c 'if [ -f "convex" ]; then ./convex ./all_cases/case04/input04.txt; fi' # timeout: 45
    exit: 0
-  diff_convex04:
    run: diff -rsZ convex.txt ./all_cases/case04/convex04.txt
    points: 1.9
    script:
        - expect: "Files convex.txt and ./all_cases/case04/convex04.txt are identical"
    exit: 0
-  run_prim04:
    run: /bin/sh -c 'if [ -f "prim" ]; then ./prim ./all_cases/case04/input04.txt; fi' # timeout: 45
    exit: 0
-  diff_prim04:
    run: diff -rsZ prim.txt ./all_cases/case04/prim04.txt
    points: 2.1
    script:
        - expect: "Files prim.txt and ./all_cases/case04/prim04.txt are identical"
    exit: 0



- clear_05:
    run: rm -f *.txt
    visible: false
-  run_convex05:
    run: /bin/sh -c 'if [ -f "convex" ]; then ./convex ./all_cases/case05/input05.txt; fi' # timeout: 45
    exit: 0
-  diff_convex05:
    run: diff -rsZ convex.txt ./all_cases/case05/convex05.txt
    points: 2.5
    script:
        - expect: "Files convex.txt and ./all_cases/case05/convex05.txt are identical"
    exit: 0
-  run_prim05:
    run: /bin/sh -c 'if [ -f "prim" ]; then ./prim ./all_cases/case05/input05.txt; fi' # timeout: 45
    exit: 0
-  diff_prim05:
    run: diff -rsZ prim.txt ./all_cases/case05/prim05.txt
    points: 2.5
    script:
        - expect: "Files prim.txt and ./all_cases/case05/prim05.txt are identical"
    exit: 0



- clear_06:
    run: rm -f *.txt
    visible: false
-  run_convex06:
    run: /bin/sh -c 'if [ -f "convex" ]; then ./convex ./all_cases/case06/input06.txt; fi' # timeout: 45
    exit: 0
-  diff_convex06:
    run: diff -rsZ convex.txt ./all_cases/case06/convex06.txt
    points: 1.9
    script:
        - expect: "Files convex.txt and ./all_cases/case06/convex06.txt are identical"
    exit: 0
-  run_prim06:
    run: /bin/sh -c 'if [ -f "prim" ]; then ./prim ./all_cases/case06/input06.txt; fi' # timeout: 45
    exit: 0
-  diff_prim06:
    run: diff -rsZ prim.txt ./all_cases/case06/prim06.txt
    points: 2.1
    script:
        - expect: "Files prim.txt and ./all_cases/case06/prim06.txt are identical"
    exit: 0



- clear_07:
    run: rm -f *.txt
    visible: false
-  run_convex07:
    run: /bin/sh -c 'if [ -f "convex" ]; then ./convex ./all_cases/case07/input07.txt; fi' # timeout: 45
    exit: 0
-  diff_convex07:
    run: diff -rsZ convex.txt ./all_cases/case07/convex07.txt
    points: 1.9
    script:
        - expect: "Files convex.txt and ./all_cases/case07/convex07.txt are identical"
    exit: 0
-  run_prim07:
    run: /bin/sh -c 'if [ -f "prim" ]; then ./prim ./all_cases/case07/input07.txt; fi' # timeout: 45
    exit: 0
-  diff_prim07:
    run: diff -rsZ prim.txt ./all_cases/case07/prim07.txt
    points: 2.1
    script:
        - expect: "Files prim.txt and ./all_cases/case07/prim07.txt are identical"
    exit: 0



- clear_08:
    run: rm -f *.txt
    visible: false
-  run_convex08:
    run: /bin/sh -c 'if [ -f "convex" ]; then ./convex ./all_cases/case08/input08.txt; fi' # timeout: 45
    exit: 0
-  diff_convex08:
    run: diff -rsZ convex.txt ./all_cases/case08/convex08.txt
    points: 2.5
    script:
        - expect: "Files convex.txt and ./all_cases/case08/convex08.txt are identical"
    exit: 0
-  run_prim08:
    run: /bin/sh -c 'if [ -f "prim" ]; then ./prim ./all_cases/case08/input08.txt; fi' # timeout: 45
    exit: 0
-  diff_prim08:
    run: diff -rsZ prim.txt ./all_cases/case08/prim08.txt
    points: 2.5
    script:
        - expect: "Files prim.txt and ./all_cases/case08/prim08.txt are identical"
    exit: 0



- clear_09:
    run: rm -f *.txt
    visible: false
-  run_convex09:
    run: /bin/sh -c 'if [ -f "convex" ]; then ./convex ./all_cases/case09/input09.txt; fi' # timeout: 45
    exit: 0
-  diff_convex09:
    run: diff -rsZ convex.txt ./all_cases/case09/convex09.txt
    points: 2.5
    script:
        - expect: "Files convex.txt and ./all_cases/case09/convex09.txt are identical"
    exit: 0
-  run_prim09:
    run: /bin/sh -c 'if [ -f "prim" ]; then ./prim ./all_cases/case09/input09.txt; fi' # timeout: 45
    exit: 0
-  diff_prim09:
    run: diff -rsZ prim.txt ./all_cases/case09/prim09.txt
    points: 2.5
    script:
        - expect: "Files prim.txt and ./all_cases/case09/prim09.txt are identical"
    exit: 0



- clear_10:
    run: rm -f *.txt
    visible: false
-  run_convex10:
    run: /bin/sh -c 'if [ -f "convex" ]; then ./convex ./all_cases/case10/input10.txt; fi' # timeout: 45
    exit: 0
-  diff_convex10:
    run: diff -rsZ convex.txt ./all_cases/case10/convex10.txt
    points: 1.9
    script:
        - expect: "Files convex.txt and ./all_cases/case10/convex10.txt are identical"
    exit: 0
-  run_prim10:
    run: /bin/sh -c 'if [ -f "prim" ]; then ./prim ./all_cases/case10/input10.txt; fi' # timeout: 45
    exit: 0
-  diff_prim10:
    run: diff -rsZ prim.txt ./all_cases/case10/prim10.txt
    points: 2.1
    script:
        - expect: "Files prim.txt and ./all_cases/case10/prim10.txt are identical"
    exit: 0



- clear_11:
    run: rm -f *.txt
    visible: false
-  run_convex11:
    run: /bin/sh -c 'if [ -f "convex" ]; then ./convex ./all_cases/case11/input11.txt; fi' # timeout: 45
    exit: 0
-  diff_convex11:
    run: diff -rsZ convex.txt ./all_cases/case11/convex11.txt
    points: 1.9
    script:
        - expect: "Files convex.txt and ./all_cases/case11/convex11.txt are identical"
    exit: 0
-  run_prim11:
    run: /bin/sh -c 'if [ -f "prim" ]; then ./prim ./all_cases/case11/input11.txt; fi' # timeout: 45
    exit: 0
-  diff_prim11:
    run: diff -rsZ prim.txt ./all_cases/case11/prim11.txt
    points: 2.1
    script:
        - expect: "Files prim.txt and ./all_cases/case11/prim11.txt are identical"
    exit: 0



- clear_12:
    run: rm -f *.txt
    visible: false
-  run_convex12:
    run: /bin/sh -c 'if [ -f "convex" ]; then ./convex ./all_cases/case12/input12.txt; fi' # timeout: 45
    exit: 0
-  diff_convex12:
    run: diff -rsZ convex.txt ./all_cases/case12/convex12.txt
    points: 1.9
    script:
        - expect: "Files convex.txt and ./all_cases/case12/convex12.txt are identical"
    exit: 0
-  run_prim12:
    run: /bin/sh -c 'if [ -f "prim" ]; then ./prim ./all_cases/case12/input12.txt; fi' # timeout: 45
    exit: 0
-  diff_prim12:
    run: diff -rsZ prim.txt ./all_cases/case12/prim12.txt
    points: 2.1
    script:
        - expect: "Files prim.txt and ./all_cases/case12/prim12.txt are identical"
    exit: 0



- clear_13:
    run: rm -f *.txt
    visible: false
-  run_convex13:
    run: /bin/sh -c 'if [ -f "convex" ]; then ./convex ./all_cases/case13/input13.txt; fi' # timeout: 45
    exit: 0
-  diff_convex13:
    run: diff -rsZ convex.txt ./all_cases/case13/convex13.txt
    points: 2.5
    script:
        - expect: "Files convex.txt and ./all_cases/case13/convex13.txt are identical"
    exit: 0
-  run_prim13:
    run: /bin/sh -c 'if [ -f "prim" ]; then ./prim ./all_cases/case13/input13.txt; fi' # timeout: 45
    exit: 0
-  diff_prim13:
    run: diff -rsZ prim.txt ./all_cases/case13/prim13.txt
    points: 2.5
    script:
        - expect: "Files prim.txt and ./all_cases/case13/prim13.txt are identical"
    exit: 0



- clear_14:
    run: rm -f *.txt
    visible: false
-  run_convex14:
    run: /bin/sh -c 'if [ -f "convex" ]; then ./convex ./all_cases/case14/input14.txt; fi' # timeout: 45
    exit: 0
-  diff_convex14:
    run: diff -rsZ convex.txt ./all_cases/case14/convex14.txt
    points: 2.5
    script:
        - expect: "Files convex.txt and ./all_cases/case14/convex14.txt are identical"
    exit: 0
-  run_prim14:
    run: /bin/sh -c 'if [ -f "prim" ]; then ./prim ./all_cases/case14/input14.txt; fi' # timeout: 45
    exit: 0
-  diff_prim14:
    run: diff -rsZ prim.txt ./all_cases/case14/prim14.txt
    points: 2.5
    script:
        - expect: "Files prim.txt and ./all_cases/case14/prim14.txt are identical"
    exit: 0



- clear_15:
    run: rm -f *.txt
    visible: false
-  run_convex15:
    run: /bin/sh -c 'if [ -f "convex" ]; then ./convex ./all_cases/case15/input15.txt; fi' # timeout: 45
    exit: 0
-  diff_convex15:
    run: diff -rsZ convex.txt ./all_cases/case15/convex15.txt
    points: 2.5
    script:
        - expect: "Files convex.txt and ./all_cases/case15/convex15.txt are identical"
    exit: 0
-  run_prim15:
    run: /bin/sh -c 'if [ -f "prim" ]; then ./prim ./all_cases/case15/input15.txt; fi' # timeout: 45
    exit: 0
-  diff_prim15:
    run: diff -rsZ prim.txt ./all_cases/case15/prim15.txt
    points: 2.5
    script:
        - expect: "Files prim.txt and ./all_cases/case15/prim15.txt are identical"
    exit: 0
