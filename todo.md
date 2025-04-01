# State Management in the tree

The biggest issue right now is updating the tree's node's heights as I go up the tree. The best solution to this will probably be trying to localize the problem to the subtrees such that it will work for any case.

The following might be implemented

1. Balance current node
2. Update heights in local tree
3. change current node to parent and repeat the steps
