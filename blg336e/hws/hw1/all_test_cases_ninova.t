- init:
    run: rm -f main

- build:
    run: g++ -std=c++11 -Wall -Werror main.cpp -o main  # timeout: 2



- clear_1:
    run: rm -f *.txt
    visible: false
- case_run1:
    run: ./main graphs/case1/input_1.txt
    exit: 0
- case_graph1:
    run: diff -rsZ graph.txt graphs/case1/graph_1.txt
    points: 0.7
    script:
        - expect: "Files graph.txt and graphs/case1/graph_1.txt are identical"
    exit: 0
- case_bfs1:
    run: diff -rsZ bfs.txt graphs/case1/bfs_1.txt
    points: 2.2
    script:
        - expect: "Files bfs.txt and graphs/case1/bfs_1.txt are identical"
    exit: 0
- case_dfs1:
    run: diff -rsZ dfs.txt graphs/case1/dfs_1.txt
    points: 2.1
    script:
        - expect: "Files dfs.txt and graphs/case1/dfs_1.txt are identical"
    exit: 0



- clear_2:
    run: rm -f *.txt
    visible: false
- case_run2:
    run: ./main graphs/case2/input_2.txt
    exit: 0
- case_graph2:
    run: diff -rsZ graph.txt graphs/case2/graph_2.txt
    points: 0.7
    script:
        - expect: "Files graph.txt and graphs/case2/graph_2.txt are identical"
    exit: 0
- case_bfs2:
    run: diff -rsZ bfs.txt graphs/case2/bfs_2.txt
    points: 2.2
    script:
        - expect: "Files bfs.txt and graphs/case2/bfs_2.txt are identical"
    exit: 0
- case_dfs2:
    run: diff -rsZ dfs.txt graphs/case2/dfs_2.txt
    points: 2.1
    script:
        - expect: "Files dfs.txt and graphs/case2/dfs_2.txt are identical"
    exit: 0



- clear_3:
    run: rm -f *.txt
    visible: false
- case_run3:
    run: ./main graphs/case3/input_3.txt
    exit: 0
- case_graph3:
    run: diff -rsZ graph.txt graphs/case3/graph_3.txt
    points: 0.7
    script:
        - expect: "Files graph.txt and graphs/case3/graph_3.txt are identical"
    exit: 0
- case_bfs3:
    run: diff -rsZ bfs.txt graphs/case3/bfs_3.txt
    points: 2.2
    script:
        - expect: "Files bfs.txt and graphs/case3/bfs_3.txt are identical"
    exit: 0
- case_dfs3:
    run: diff -rsZ dfs.txt graphs/case3/dfs_3.txt
    points: 2.1
    script:
        - expect: "Files dfs.txt and graphs/case3/dfs_3.txt are identical"
    exit: 0



- clear_4:
    run: rm -f *.txt
    visible: false
- case_run4:
    run: ./main graphs/case4/input_4.txt
    exit: 0
- case_graph4:
    run: diff -rsZ graph.txt graphs/case4/graph_4.txt
    points: 0.7
    script:
        - expect: "Files graph.txt and graphs/case4/graph_4.txt are identical"
    exit: 0
- case_bfs4:
    run: diff -rsZ bfs.txt graphs/case4/bfs_4.txt
    points: 2.2
    script:
        - expect: "Files bfs.txt and graphs/case4/bfs_4.txt are identical"
    exit: 0
- case_dfs4:
    run: diff -rsZ dfs.txt graphs/case4/dfs_4.txt
    points: 2.1
    script:
        - expect: "Files dfs.txt and graphs/case4/dfs_4.txt are identical"
    exit: 0



- clear_5:
    run: rm -f *.txt
    visible: false
- case_run5:
    run: ./main graphs/case5/input_5.txt
    exit: 0
- case_graph5:
    run: diff -rsZ graph.txt graphs/case5/graph_5.txt
    points: 0.7
    script:
        - expect: "Files graph.txt and graphs/case5/graph_5.txt are identical"
    exit: 0
- case_bfs5:
    run: diff -rsZ bfs.txt graphs/case5/bfs_5.txt
    points: 2.2
    script:
        - expect: "Files bfs.txt and graphs/case5/bfs_5.txt are identical"
    exit: 0
- case_dfs5:
    run: diff -rsZ dfs.txt graphs/case5/dfs_5.txt
    points: 2.1
    script:
        - expect: "Files dfs.txt and graphs/case5/dfs_5.txt are identical"
    exit: 0



- clear_6:
    run: rm -f *.txt
    visible: false
- case_run6:
    run: ./main graphs/case6/input_6.txt
    exit: 0
- case_graph6:
    run: diff -rsZ graph.txt graphs/case6/graph_6.txt
    points: 0.7
    script:
        - expect: "Files graph.txt and graphs/case6/graph_6.txt are identical"
    exit: 0
- case_bfs6:
    run: diff -rsZ bfs.txt graphs/case6/bfs_6.txt
    points: 2.2
    script:
        - expect: "Files bfs.txt and graphs/case6/bfs_6.txt are identical"
    exit: 0
- case_dfs6:
    run: diff -rsZ dfs.txt graphs/case6/dfs_6.txt
    points: 2.1
    script:
        - expect: "Files dfs.txt and graphs/case6/dfs_6.txt are identical"
    exit: 0



- clear_7:
    run: rm -f *.txt
    visible: false
- case_run7:
    run: ./main graphs/case7/input_7.txt
    exit: 0
- case_graph7:
    run: diff -rsZ graph.txt graphs/case7/graph_7.txt
    points: 0.7
    script:
        - expect: "Files graph.txt and graphs/case7/graph_7.txt are identical"
    exit: 0
- case_bfs7:
    run: diff -rsZ bfs.txt graphs/case7/bfs_7.txt
    points: 2.2
    script:
        - expect: "Files bfs.txt and graphs/case7/bfs_7.txt are identical"
    exit: 0
- case_dfs7:
    run: diff -rsZ dfs.txt graphs/case7/dfs_7.txt
    points: 2.1
    script:
        - expect: "Files dfs.txt and graphs/case7/dfs_7.txt are identical"
    exit: 0



- clear_8:
    run: rm -f *.txt
    visible: false
- case_run8:
    run: ./main graphs/case8/input_8.txt
    exit: 0
- case_graph8:
    run: diff -rsZ graph.txt graphs/case8/graph_8.txt
    points: 0.7
    script:
        - expect: "Files graph.txt and graphs/case8/graph_8.txt are identical"
    exit: 0
- case_bfs8:
    run: diff -rsZ bfs.txt graphs/case8/bfs_8.txt
    points: 2.2
    script:
        - expect: "Files bfs.txt and graphs/case8/bfs_8.txt are identical"
    exit: 0
- case_dfs8:
    run: diff -rsZ dfs.txt graphs/case8/dfs_8.txt
    points: 2.1
    script:
        - expect: "Files dfs.txt and graphs/case8/dfs_8.txt are identical"
    exit: 0



- clear_9:
    run: rm -f *.txt
    visible: false
- case_run9:
    run: ./main graphs/case9/input_9.txt
    exit: 0
- case_graph9:
    run: diff -rsZ graph.txt graphs/case9/graph_9.txt
    points: 0.7
    script:
        - expect: "Files graph.txt and graphs/case9/graph_9.txt are identical"
    exit: 0
- case_bfs9:
    run: diff -rsZ bfs.txt graphs/case9/bfs_9.txt
    points: 2.2
    script:
        - expect: "Files bfs.txt and graphs/case9/bfs_9.txt are identical"
    exit: 0
- case_dfs9:
    run: diff -rsZ dfs.txt graphs/case9/dfs_9.txt
    points: 2.1
    script:
        - expect: "Files dfs.txt and graphs/case9/dfs_9.txt are identical"
    exit: 0



- clear_10:
    run: rm -f *.txt
    visible: false
- case_run10:
    run: ./main graphs/case10/input_10.txt
    exit: 0
- case_graph10:
    run: diff -rsZ graph.txt graphs/case10/graph_10.txt
    points: 0.7
    script:
        - expect: "Files graph.txt and graphs/case10/graph_10.txt are identical"
    exit: 0
- case_bfs10:
    run: diff -rsZ bfs.txt graphs/case10/bfs_10.txt
    points: 2.2
    script:
        - expect: "Files bfs.txt and graphs/case10/bfs_10.txt are identical"
    exit: 0
- case_dfs10:
    run: diff -rsZ dfs.txt graphs/case10/dfs_10.txt
    points: 2.1
    script:
        - expect: "Files dfs.txt and graphs/case10/dfs_10.txt are identical"
    exit: 0



- clear_11:
    run: rm -f *.txt
    visible: false
- case_run11:
    run: ./main graphs/case11/input_11.txt
    exit: 0
- case_graph11:
    run: diff -rsZ graph.txt graphs/case11/graph_11.txt
    points: 0.7
    script:
        - expect: "Files graph.txt and graphs/case11/graph_11.txt are identical"
    exit: 0
- case_bfs11:
    run: diff -rsZ bfs.txt graphs/case11/bfs_11.txt
    points: 2.2
    script:
        - expect: "Files bfs.txt and graphs/case11/bfs_11.txt are identical"
    exit: 0
- case_dfs11:
    run: diff -rsZ dfs.txt graphs/case11/dfs_11.txt
    points: 2.1
    script:
        - expect: "Files dfs.txt and graphs/case11/dfs_11.txt are identical"
    exit: 0



- clear_12:
    run: rm -f *.txt
    visible: false
- case_run12:
    run: ./main graphs/case12/input_12.txt
    exit: 0
- case_graph12:
    run: diff -rsZ graph.txt graphs/case12/graph_12.txt
    points: 0.7
    script:
        - expect: "Files graph.txt and graphs/case12/graph_12.txt are identical"
    exit: 0
- case_bfs12:
    run: diff -rsZ bfs.txt graphs/case12/bfs_12.txt
    points: 2.2
    script:
        - expect: "Files bfs.txt and graphs/case12/bfs_12.txt are identical"
    exit: 0
- case_dfs12:
    run: diff -rsZ dfs.txt graphs/case12/dfs_12.txt
    points: 2.1
    script:
        - expect: "Files dfs.txt and graphs/case12/dfs_12.txt are identical"
    exit: 0



- clear_13:
    run: rm -f *.txt
    visible: false
- case_run13:
    run: ./main graphs/case13/input_13.txt
    exit: 0
- case_graph13:
    run: diff -rsZ graph.txt graphs/case13/graph_13.txt
    points: 0.7
    script:
        - expect: "Files graph.txt and graphs/case13/graph_13.txt are identical"
    exit: 0
- case_bfs13:
    run: diff -rsZ bfs.txt graphs/case13/bfs_13.txt
    points: 2.2
    script:
        - expect: "Files bfs.txt and graphs/case13/bfs_13.txt are identical"
    exit: 0
- case_dfs13:
    run: diff -rsZ dfs.txt graphs/case13/dfs_13.txt
    points: 2.1
    script:
        - expect: "Files dfs.txt and graphs/case13/dfs_13.txt are identical"
    exit: 0



- clear_14:
    run: rm -f *.txt
    visible: false
- case_run14:
    run: ./main graphs/case14/input_14.txt
    exit: 0
- case_graph14:
    run: diff -rsZ graph.txt graphs/case14/graph_14.txt
    points: 0.7
    script:
        - expect: "Files graph.txt and graphs/case14/graph_14.txt are identical"
    exit: 0
- case_bfs14:
    run: diff -rsZ bfs.txt graphs/case14/bfs_14.txt
    points: 2.2
    script:
        - expect: "Files bfs.txt and graphs/case14/bfs_14.txt are identical"
    exit: 0
- case_dfs14:
    run: diff -rsZ dfs.txt graphs/case14/dfs_14.txt
    points: 2.1
    script:
        - expect: "Files dfs.txt and graphs/case14/dfs_14.txt are identical"
    exit: 0