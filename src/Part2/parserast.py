import nltk
from nltk import Tree

# This function parses an indented text representation into an nltk.Tree.
def parse_tree(text):
    lines = text.splitlines()
    # Stack will hold tuples (level, tree) where level is the indent level.
    stack = []
    root = None
    for line in lines:
        # Skip empty lines.
        if not line.strip():
            continue
        
        # Determine the current indent level (assumes 2 spaces per level).
        indent = len(line) - len(line.lstrip())
        level = indent // 2
        
        # Create a tree node with the stripped line as its label.
        node = Tree(line.strip(), [])
        
        if level == 0:
            # This is the root node.
            root = node
            stack = [(level, node)]
        else:
            # Pop from the stack until finding a parent with a lower indent level.
            while stack and stack[-1][0] >= level:
                stack.pop()
            if stack:
                parent = stack[-1][1]
                parent.append(node)
            # Push the current node onto the stack.
            stack.append((level, node))
    return root

def main():
    # Read input from output.txt.
    with open('output.txt', 'r') as file:
        tree_text = file.read()
    
    # Parse the text into an nltk.Tree.
    tree = parse_tree(tree_text)
    
    # Print a textual "pretty" representation of the tree.
    tree.pretty_print()
    
    # Graphically display the tree in a new window.
    tree.draw()

if __name__ == '__main__':
    main()