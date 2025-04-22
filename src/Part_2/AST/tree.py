from nltk.tree import *

# Corrected tree representation with explicit binary structure
from nltk.tree import Tree

# Input AST in parentheses notation
text = """
(program
  (stmts
    (expr (:= x (+ y (5))))
    (expr (:= y (10)))
  )
)
"""

# Parse the AST string into an NLTK Tree
tree = Tree.fromstring(text)

# Pretty print the tree with Unicode lines
tree.pretty_print(unicodelines=True, nodedist=5)



