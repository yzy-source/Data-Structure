public void iterativeInorderTraverse()
{
    StackInterface<BinaryNodeInterface<T>> nodeStack = new LinkedStack<>();
    BinaryNode<T> currentNode = root;
    while (!nodeStack.isEmpty() || (currentNode != null))
    {
        // Find leftmost node with no left child
        while (currentNode != null)
        {
            nodeStack.push(currentNode);
            currentNode = currentNode.getLeftChild();
        } // end while
        // Visit leftmost node, then traverse its right subtree
        if (!nodeStack.isEmpty())
        {
            BinaryNode<T> nextNode = nodeStack.pop();
            assert nextNode != null;    // Since node Stack was not empty
                            // before the pop
            System.out.println(nextNode.getData());
            currentNode = nextNode.getRightChild();
        } // end if
    } // end while
} // end iterativeInorderTraverse

