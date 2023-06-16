- init:
    run: rm -f main
    blocker: true

- build:
    run: g++ -std=c++11 -Wall -Werror main.cpp -o main  # timeout: 2
    blocker: true

- case_run1:
    run: ./main graphs/case1/input_1.txt
    blocker: true
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


- case_run2:
    run: ./main graphs/case2/input_2.txt
    blocker: true
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


- case_run3:
    run: ./main graphs/case3/input_3.txt
    blocker: true
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


- case_run6:
    run: ./main graphs/case6/input_6.txt
    blocker: true
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


- case_run7:
    run: ./main graphs/case7/input_7.txt
    blocker: true
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


- case_run9:
    run: ./main graphs/case9/input_9.txt
    blocker: true
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


- case_run11:
    run: ./main graphs/case11/input_11.txt
    blocker: true
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


- case_run13:
    run: ./main graphs/case13/input_13.txt
    blocker: true
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
