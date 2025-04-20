from nltk.tree import *

# Corrected tree representation with explicit binary structure
from nltk.tree import Tree

# Input AST in parentheses notation
text = """
( ( ( (number) (int)) ( (sum) (int)) ( (a) (int)) ( (b) (int)) ( (a[6]) (char))) ( ( ( (:= (number) ((3, 10)))) ( (:= (sum) ((0, 10)))) (while (> (number) ((0, 10))) ( ( ( (:= (sum) (+ (sum) (number)))) ( (:= (number) (- (number) ((1, 10)))))))) ( (:= (b) ((20, 10)))) (for (:= (a) ((10, 8))) (+ (b) ( ((10, 2)))) ((1, 10)) ( ( (print (Thevalueofa=@) (args (a)))))))))
"""

# Parse the AST string into an NLTK Tree
tree = Tree.fromstring(text)

# Pretty print the tree with Unicode lines
tree.pretty_print(unicodelines=True, nodedist=5)



