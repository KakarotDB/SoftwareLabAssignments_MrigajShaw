# 🎓 Algorithm Lab Study Guide

## 1. 🗺️ Global Overview

- **Divide and Conquer Paradigm**: Extensively used across assignments, from classical sorting (Merge Sort, Quick Sort) to advanced order statistics (Quickselect, Median of Medians) and computational geometry (Closest Pair of Points in 2D).
- **Greedy Algorithms**: Dominates graph problems, specifically Minimum Spanning Trees (Prim's and Kruskal's) and Single-Source Shortest Paths (Dijkstra's).
- **Dynamic Programming**: Applied to overcome the overlapping subproblems and optimal substructure inherent in exponential recursive algorithms (Fibonacci, Matrix Chain Multiplication, 0/1 Knapsack).
- **Advanced Data Structures**: Custom implementations of **Disjoint Set Union (DSU)** for cycle detection/connectivity and **Min-Priority Queues (Min-Heap)** for efficient greedy choices.
- **Empirical Performance Analysis**: A strong recurring theme is benchmarking algorithms against pathological inputs (e.g., highly duplicated arrays, sorted arrays, negative weight cycles) to observe theoretical worst-case degradations in practice.
- **Space-Time Trade-offs**: Frequently explored, such as Adjacency Matrix vs. Adjacency List for dense/sparse graphs, or recursive stack overhead vs. in-place iterative algorithms.

---

## 2. 🛠️ Header Files & Core Utilities

### `DisjointSetUnion.h`

- **Purpose**: Abstracts the Union-Find data structure to manage disjoint sets, enabling efficient dynamic connectivity and cycle detection queries.
- **Key Functions**:
  - `createSet(int n)`: Initializes `parent` and `rank` arrays.
  - `find(DisjointSet *ds, int i)`: Returns the root representative of the set.
  - `unionSets(DisjointSet *ds, int a, int b)`: Merges two sets based on rank.
- **Pseudocode**:

  ```pseudocode
  function find(i):
      if parent[i] != i:
          parent[i] = find(parent[i])  // Path compression
      return parent[i]

  function unionSets(a, b):
      rootA = find(a), rootB = find(b)
      if rootA != rootB:
          if rank[rootA] < rank[rootB]: parent[rootA] = rootB
          else if rank[rootA] > rank[rootB]: parent[rootB] = rootA
          else: parent[rootB] = rootA; rank[rootA]++
          return true
      return false
  ```

- **Complexity**: Time: $\mathcal{O}(\alpha(N))$ amortized for `find` and `union`, where $\alpha$ is the Inverse Ackermann function. Space: $\mathcal{O}(N)$.
- **Usage Pattern**: Used in Assignment 5 (Social Networks, Road Connectivity) and Assignment 6 (Kruskal's Algorithm).

### `AdjacencyList.h`

- **Purpose**: Provides a memory-efficient representation of sparse graphs using linked lists.
- **Key Functions**:
  - `createAdjacencyList(int vertices)`: Allocates an array of node pointers.
  - `addEdgeAdjacencyListDirectedWithWeight(list, u, v, weight)`: Inserts a node at the head of `list[u]`.
- **Pseudocode**:

  ```pseudocode
  function addEdge(list, u, v, weight):
      newNode = allocate Node(v, weight)
      newNode.next = list[u]
      list[u] = newNode
  ```

- **Complexity**: Time: $\mathcal{O}(1)$ for insertion. Space: $\mathcal{O}(V + E)$.
- **Usage Pattern**: Used in Assignments 6 and 7 for Prim's, Dijkstra's, and overall graph representations.

### `MinHeap.h`

- **Purpose**: Implements a minimum priority queue to efficiently extract the minimum weight edge or distance.
- **Key Functions**:
  - `insertMinHeap(minHeap, u, v, weight)`: Bubbles up a new edge based on weight.
  - `extractMin(minHeap)`: Removes and returns the minimum element, then heapifies down.
  - `minHeapify(minHeap, idx)`: Maintains the min-heap property downwards.
- **Pseudocode**:

  ```pseudocode
  function extractMin(heap):
      if isEmpty(heap): return null
      root = heap.array[0]
      heap.array[0] = heap.array[heap.size - 1]
      heap.size--
      minHeapify(heap, 0)
      return root
  ```

- **Complexity**: Time: $\mathcal{O}(\log V)$ for insertion and extraction. Space: $\mathcal{O}(E)$ or $\mathcal{O}(V)$ depending on capacity.
- **Usage Pattern**: Critical for $\mathcal{O}(E \log V)$ implementations of Prim's (Assign 6) and Dijkstra's (Assign 7).

---

## 3. 📋 Assignment Breakdown

### Assignment 1 — `Searching and Sorting Basics`

| Field | Details |
|---|---|
| **Source File** | `Searching.c`, `Sorting.c` |
| **Depends On** | None |

- **Objective**: Implement and benchmark foundational searching (Linear vs. Binary) and sorting (Bubble, Insertion, Quick, Merge) algorithms on large datasets.
- **Algorithm & Pseudocode**:

  ```pseudocode
  function binarySearch(A, target):
      left = 0, right = n - 1
      while left <= right:
          mid = (left + right) / 2
          if A[mid] == target: return mid
          if A[mid] < target: left = mid + 1
          else: right = mid - 1
      return -1
  ```

- **Complexity Analysis**:
  - **Binary Search**: Time $\mathcal{O}(\log N)$, Space $\mathcal{O}(1)$.
  - **Merge Sort**: Time $\mathcal{O}(N \log N)$ (Best/Avg/Worst), Space $\mathcal{O}(N)$.
  - **Quick Sort**: Time $\mathcal{O}(N \log N)$ (Best/Avg), $\mathcal{O}(N^2)$ (Worst). Space $\mathcal{O}(\log N)$ stack.
- **Trade-offs & Design Choices**:
  - Binary Search requires the overhead of sorting first ($\mathcal{O}(N \log N)$), which is only amortized if multiple searches are performed.
  - In-place quicksort avoids the $\mathcal{O}(N)$ memory allocation overhead of Merge Sort, leading to better cache locality and lower constant factors.

> **Q: When would you prefer Linear Search over Binary Search?**
> **A:** When the array is unsorted and we only need to perform a single query. The $\mathcal{O}(N \log N)$ cost of sorting the array for Binary Search outweighs the $\mathcal{O}(N)$ cost of a single Linear Search.
> **Q: Why does Quicksort generally outperform Merge Sort in practice despite having a worse worst-case time complexity?**
> **A:** Quicksort operates in-place, yielding excellent CPU cache locality and lower constant factors, whereas Merge Sort requires $\mathcal{O}(N)$ auxiliary space and constant memory copying.

---

### Assignment 2 — `Order Statistics and Sets`

| Field | Details |
|---|---|
| **Source File** | `FourthGreatestThirdSmallest.c`, `MaxMinAlgorithm.c`, `PatternMatching.c`, `SetsAndSubsets.c`, `unionOfSets.c` |
| **Depends On** | None |

- **Objective**: Compute order statistics without full sorting, implement divide & conquer for Max-Min, and perform set operations.
- **Algorithm & Pseudocode** (Divide & Conquer Max-Min):

  ```pseudocode
  function recursiveMaxMin(A, low, high):
      if low == high: return (A[low], A[low])
      if high == low + 1: return (max(A[low], A[high]), min(A[low], A[high]))
      
      mid = (low + high) / 2
      left = recursiveMaxMin(A, low, mid)
      right = recursiveMaxMin(A, mid + 1, high)
      
      return (max(left.max, right.max), min(left.min, right.min))
  ```

- **Complexity Analysis**:
  - **Divide & Conquer Max-Min**: Time $\mathcal{O}(N)$ (specifically $\frac{3N}{2} - 2$ comparisons), Space $\mathcal{O}(\log N)$ for recursion stack.
  - **4th Largest / 3rd Smallest**: Time $\mathcal{O}(N)$ using a single pass with constant variables. Space $\mathcal{O}(1)$.
- **Trade-offs & Design Choices**:
  - The Divide & Conquer Max-Min optimally reduces the number of comparisons from $2N - 2$ (Naive) to $\frac{3N}{2} - 2$, demonstrating a pure algorithmic improvement in constant factors.
  - Set Union uses `qsort` ($\mathcal{O}(N \log N)$) followed by a linear scan to remove duplicates, favoring simplicity over a hash-based $\mathcal{O}(N)$ approach.

> **Q: How does the Divide and Conquer approach for Max-Min reduce the number of comparisons?**
> **A:** By pairing elements recursively, the algorithm compares pairs of maximums and pairs of minimums, effectively using 3 comparisons for every 2 elements, yielding $\frac{3N}{2}$ comparisons compared to the naive $2N$.
> **Q: Can you find the $k$-th largest element in exactly $\mathcal{O}(N)$ time?**
> **A:** Yes, using the Quickselect algorithm or the Median of Medians algorithm, avoiding the $\mathcal{O}(N \log N)$ cost of sorting.

---

### Assignment 3 — `Quicksort Variations & Duplicates`

| Field | Details |
|---|---|
| **Source File** | `RandomizedQuickSort.c`, `PerformanceComparisonQSort.c`, `QSortVMSort.c` |
| **Depends On** | None |

- **Objective**: Analyze the impact of pivot selection (Fixed vs. Randomized) and input distribution (duplicates, nearly sorted) on Quicksort and Merge Sort.
- **Algorithm & Pseudocode** (Randomized Partition):

  ```pseudocode
  function randomPartition(A, low, high):
      pivot_idx = random(low, high)
      swap(A[pivot_idx], A[high])
      return standardPartition(A, low, high)
  ```

- **Complexity Analysis**:
  - **Randomized Quicksort**: Expected Time $\mathcal{O}(N \log N)$. Space $\mathcal{O}(\log N)$.
  - **Pathological Case (90% Duplicates)**: Both Standard and Randomized Quicksort degrade to $\mathcal{O}(N^2)$ time and $\mathcal{O}(N)$ recursion depth because identical elements cause heavily unbalanced partitions.
- **Trade-offs & Design Choices**:
  - Randomization fixes the $\mathcal{O}(N^2)$ worst-case for *sorted* inputs by bypassing fixed pivot vulnerabilities, but fails against *duplicate* inputs.
  - Merge Sort is shown to perform strictly fewer comparisons than Quicksort on an 80% sorted array, but Quicksort still executes faster in absolute time due to in-place operations avoiding memory allocation overhead.

> **Q: Why does Randomized Quicksort fail to prevent $\mathcal{O}(N^2)$ degradation on arrays with 90% duplicate values?**
> **A:** Randomization only scrambles the pivot choice. If 90% of the elements are identical, any randomly chosen pivot will likely be that duplicate, resulting in an unbalanced partition where almost all elements fall to one side.
> **Q: How would you modify Quicksort to efficiently handle massive duplicates?**
> **A:** I would use Dijkstra's 3-way partitioning (Dutch National Flag algorithm), which groups elements into `< pivot`, `== pivot`, and `> pivot`, eliminating duplicates from future recursive calls.

---

### Assignment 4 — `Median Finding & Order Statistics`

| Field | Details |
|---|---|
| **Source File** | `MedianScore.c`, `MedianOfMedians.c`, `MedianOfTwoSortedArraysWithoutMerging.c` |
| **Depends On** | None |

- **Objective**: Compute the median using Quickselect (Expected $\mathcal{O}(N)$) and Median of Medians (Worst-case $\mathcal{O}(N)$), and find the median of two sorted arrays in $\mathcal{O}(\log N)$.
- **Algorithm & Pseudocode** (Median of Two Sorted Arrays):

  ```pseudocode
  function findMedianSortedArrays(A, B):
      if len(A) > len(B): swap(A, B)
      low = 0, high = len(A)
      
      while low <= high:
          partX = (low + high) / 2
          partY = (len(A) + len(B) + 1) / 2 - partX
          
          maxLeftX = A[partX - 1], minRightX = A[partX]
          maxLeftY = B[partY - 1], minRightY = B[partY]
          
          if maxLeftX <= minRightY and maxLeftY <= minRightX:
              return calculate_median()
          else if maxLeftX > minRightY: high = partX - 1
          else: low = partX + 1
  ```

- **Complexity Analysis**:
  - **Median of Medians**: Time $\mathcal{O}(N)$ worst-case. Space $\mathcal{O}(N)$ for recursive chunking.
  - **Median of Two Sorted Arrays**: Time $\mathcal{O}(\log(\min(N_1, N_2)))$ via binary search on partitions. Space $\mathcal{O}(1)$.
- **Trade-offs & Design Choices**:
  - Median of Medians provides a strict $\mathcal{O}(N)$ guarantee but carries a massive constant factor overhead due to recursively chunking arrays into groups of 5. Quickselect is faster on average.
  - The $\mathcal{O}(\log N)$ median solver explicitly avoids $\mathcal{O}(N)$ memory allocation, directly solving the strict memory constraint of merging two arrays.

> **Q: In the Median of Medians algorithm, why do we partition the array into groups of 5?**
> **A:** Groups of 5 guarantee that at least 30% of the elements are discarded in each recursive step, strictly satisfying the recurrence relation $T(N) \leq T(N/5) + T(7N/10) + \mathcal{O}(N)$, which yields a linear $\mathcal{O}(N)$ time. Groups of 3 would fail to bound the time linearly.
> **Q: How does the algorithm find the median of two sorted arrays in $\mathcal{O}(\log N)$ time without merging?**
> **A:** It performs a binary search on the smaller array to find a partition index such that all elements on the left of both partitions are smaller than all elements on the right.

---

### Assignment 5 — `Disjoint Set Union (DSU)`

| Field | Details |
|---|---|
| **Source File** | `DisjointSet.c`, `friendshipOperations.c`, `roadConstruction.c` |
| **Depends On** | `DisjointSetUnion.h` |

- **Objective**: Implement DSU with path compression and union by rank to solve dynamic connectivity problems (friend groups, road networks).
- **Algorithm & Pseudocode**: *(See Section 2 Header Files)*
- **Complexity Analysis**:
  - Time: $\mathcal{O}(M \alpha(N))$ for $M$ operations on $N$ elements. Effectively $\mathcal{O}(1)$ per operation.
  - Space: $\mathcal{O}(N)$ for the parent and rank arrays.
- **Trade-offs & Design Choices**:
  - **Path Compression**: Flattens the tree dynamically during `find` queries, drastically reducing future traversal times at the cost of a slight mutation overhead during reads.
  - Using DSU to check city road connectivity averts the need to run full Graph Traversals (BFS/DFS) which would cost $\mathcal{O}(V + E)$ per query, bringing it down to $\mathcal{O}(1)$.

> **Q: What is the difference between Path Compression and Union by Rank?**
> **A:** Union by Rank keeps the tree shallow by attaching the shorter tree under the root of the taller tree during a merge. Path Compression flattens the tree during a `find` operation by making all visited nodes point directly to the root.
> **Q: Why is DSU preferred over BFS/DFS for verifying dynamic road construction connectivity?**
> **A:** BFS/DFS require $\mathcal{O}(V + E)$ time to check connectivity. If roads are added dynamically, running BFS after every addition is $\mathcal{O}(M(V+E))$. DSU handles dynamic unions and queries in amortized $\mathcal{O}(1)$ time.

---

### Assignment 6 — `Minimum Spanning Trees (MST)`

| Field | Details |
|---|---|
| **Source File** | `RepresentationsOfGraph.c`, `primsAlgorithm.c`, `KruskallsAlgorithm.c`, `SmartCityPowerDistribution.c` |
| **Depends On** | `AdjacencyList.h`, `MinHeap.h`, `DisjointSetUnion.h` |

- **Objective**: Compare Adjacency List vs. Matrix, and implement Prim's and Kruskal's algorithms for generating MSTs.
- **Algorithm & Pseudocode** (Kruskal's):

  ```pseudocode
  function Kruskal(V, Edges):
      sort(Edges) by weight ascending
      dsu = createSet(V)
      mst_cost = 0
      
      for edge in Edges:
          if find(dsu, edge.u) != find(dsu, edge.v):
              unionSets(dsu, edge.u, edge.v)
              mst_cost += edge.weight
      return mst_cost
  ```

- **Complexity Analysis**:
  - **Prim's Algorithm (Adjacency List + Min-Heap)**: Time $\mathcal{O}(E \log V)$. Space $\mathcal{O}(V + E)$.
  - **Kruskal's Algorithm**: Time $\mathcal{O}(E \log E)$ due to sorting the edges. Space $\mathcal{O}(E + V)$.
- **Trade-offs & Design Choices**:
  - Kruskal's is mathematically optimal for **sparse graphs** since edge sorting ($\mathcal{O}(E \log E)$) is cheap.
  - Prim's shines on **dense graphs** since $\mathcal{O}(E \log V)$ outperforms Kruskal's sort overhead when $E \approx V^2$.
  - The "lazy" heap in Prim's intentionally pushes duplicate nodes rather than implementing a complex `decreaseKey` operation, prioritizing implementation simplicity over strict queue sizing.

> **Q: In your implementation of Prim's Algorithm, how do you handle nodes being added to the Min-Heap multiple times with different weights?**
> **A:** I use a boolean `visited` array. When a node is popped from the min-heap, if it is already marked as `visited`, I `continue` and ignore it. This "lazy deletion" avoids the complexity of writing a `decreaseKey` function.
> **Q: Why was Kruskal's chosen for the sparse graph and Prim's for the dense graph in the Smart City problem?**
> **A:** Kruskal's runs in $\mathcal{O}(E \log E)$ making it ideal when $E$ is small. Prim's runs in $\mathcal{O}(E \log V)$, which scales better natively for dense graphs where $E$ approaches $V^2$, avoiding massive edge-sorting overhead.

---

### Assignment 7 — `Single Source Shortest Paths (SSSP)`

| Field | Details |
|---|---|
| **Source File** | `SmartNavigationCity.c`, `DijkstraLimitationNegativeEdgeWeightCycle.c`, `ClosestPairOfPoints1D2D.c`, `BellmanFordAlgorithm.c` |
| **Depends On** | `AdjacencyList.h`, `MinHeap.h` |

- **Objective**: Implement Dijkstra's algorithm, demonstrate its failure on negative cycles, and implement Bellman-Ford to correctly detect negative cycles.
- **Algorithm & Pseudocode** (Bellman-Ford):

  ```pseudocode
  function BellmanFord(V, Edges, source):
      dist[source] = 0; all others = INF
      
      for i from 1 to V - 1:
          for edge in Edges:
              if dist[edge.u] + edge.weight < dist[edge.v]:
                  dist[edge.v] = dist[edge.u] + edge.weight
                  
      for edge in Edges:
          if dist[edge.u] + edge.weight < dist[edge.v]:
              print "Negative Weight Cycle Detected!"
  ```

- **Complexity Analysis**:
  - **Dijkstra**: Time $\mathcal{O}((V + E) \log V)$ with Adjacency List. Time $\mathcal{O}(V^2 + E \log V)$ with Matrix.
  - **Bellman-Ford**: Time $\mathcal{O}(V \times E)$. Space $\mathcal{O}(V)$.
- **Trade-offs & Design Choices**:
  - Dijkstra is greedy and finalizes nodes permanently. It achieves high speed but strictly requires non-negative weights.
  - Bellman-Ford sacrifices performance ($\mathcal{O}(VE)$ vs $\mathcal{O}(E \log V)$) by exhaustively relaxing all edges $V-1$ times to guarantee correctness in the presence of negative weights and to enable cycle detection.

> **Q: Why does Dijkstra's Algorithm fail when there are negative edge weights?**
> **A:** Dijkstra assumes that adding a new edge to a path strictly increases or maintains the total distance. If a negative edge exists, a finalized node might actually be reachable via a cheaper path later, but Dijkstra never revisits finalized nodes.
> **Q: How does Bellman-Ford mathematically guarantee it finds the shortest path?**
> **A:** A shortest path in a graph without negative cycles can have at most $V-1$ edges. By relaxing every edge exactly $V-1$ times, Bellman-Ford guarantees that the shortest paths of all possible lengths have propagated through the graph.

---

### Assignment 8 — `Dynamic Programming`

| Field | Details |
|---|---|
| **Source File** | `FibonacciDP.c`, `MatrixChainMultiplication.c`, `KnapSack01.c` |
| **Depends On** | None |

- **Objective**: Solve recursive overlapping subproblems using Memoization and Tabulation for Fibonacci, Matrix Chain Multiplication (MCM), and 0/1 Knapsack.
- **Algorithm & Pseudocode** (0/1 Knapsack DP):

  ```pseudocode
  function knapsackDP(values, weights, N, W):
      dp[N+1][W+1] = {0}
      for i from 1 to N:
          for w from 1 to W:
              if weights[i-1] > w:
                  dp[i][w] = dp[i-1][w]
              else:
                  dp[i][w] = max(dp[i-1][w], values[i-1] + dp[i-1][w - weights[i-1]])
      return dp[N][W]
  ```

- **Complexity Analysis**:
  - **Matrix Chain Multiplication**: Time $\mathcal{O}(N^3)$, Space $\mathcal{O}(N^2)$. Recursive is $\mathcal{O}(2^N)$.
  - **0/1 Knapsack**: Time $\mathcal{O}(N \cdot W)$, Space $\mathcal{O}(N \cdot W)$. Recursive is $\mathcal{O}(2^N)$.
- **Trade-offs & Design Choices**:
  - Dynamic programming trades memory ($\mathcal{O}(N \cdot W)$ or $\mathcal{O}(N^2)$) for massive polynomial-time speedups, averting catastrophic exponential $\mathcal{O}(2^N)$ stalling.
  - The DP Knapsack solution is *pseudo-polynomial*. If the weight capacity $W$ is astronomically large, the time and space complexity will degrade, requiring a different approach (like a Greedy fractional approximation or Branch and Bound).

> **Q: What is the optimal substructure in the Matrix Chain Multiplication problem?**
> **A:** The optimal cost of multiplying matrices $A_i \dots A_j$ is exactly the cost of optimally splitting them at some point $k$, plus the cost of multiplying $A_i \dots A_k$, plus the cost of multiplying $A_{k+1} \dots A_j$.
> **Q: Why is the DP solution for 0/1 Knapsack considered "pseudo-polynomial"?**
> **A:** The time complexity is $\mathcal{O}(N \cdot W)$. While $N$ is the number of items, $W$ is a numeric *value*. The number of bits required to represent $W$ is $\log W$. Thus, the time complexity relative to the input size is actually $\mathcal{O}(N \cdot 2^{\text{bits of } W})$, which is exponential with respect to the input representation size.

