# Algorithm Analysis
### 1. DNA Subsequence
- __Dynamic Programming__ is used
- There are 2 penalties:
  1. delta: comp w/ _blank_ and a letter
  2. alpha: comp w/ two diff letters
- ex) XX-Y w/ XXYX = 1 d + 1 a

### 2. Kosaraju's Algorithm
- To find __Strongly Connected Components__ 
- Steps:
  1. Topological sort on vertices.
  2. Reverse edges.
  3. Run DFS to find the _source_
  4. Re-reverse edges and now _source_ becomes _sink_
  5. Run BFS from _sink_ 
