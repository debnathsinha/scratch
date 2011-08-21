/**
 * Created by IntelliJ IDEA.
 * User: debnathsinha
 * Date: 6/18/11
 * Time: 1:44 PM
 * To change this template use File | Settings | File Templates.
 */
public class MyLinkedListIterator {

    LinkedListNode current;

    MyLinkedListIterator( LinkedListNode node ) {
        current = node;
    }

    public boolean hasNext() {
        return current != null;
    }

    public Object next() {
        LinkedListNode tmpNode = current;
        current = current.next;
        return tmpNode.data;
    }
}
