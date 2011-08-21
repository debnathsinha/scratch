/**
 * Created by IntelliJ IDEA.
 * User: debnathsinha
 * Date: 6/18/11
 * Time: 1:05 PM
 * To change this template use File | Settings | File Templates.
 */
public class LinkedListNode {

    Object data;
    LinkedListNode next;

    public LinkedListNode(LinkedListNode ln) {
        this.data = ln.data;
        this.next = ln.next;
    }

    public LinkedListNode() {
        this.data = null;
        this.next = null;
    }

    public LinkedListNode(Object elem, LinkedListNode next) {
        this.data = elem;
        this.next = next;
    }

    public String toString() {
        return data.toString();
    }
}
