/**
 * Created by IntelliJ IDEA.
 * User: debnathsinha
 * Date: 6/18/11
 * Time: 1:08 PM
 * To change this template use File | Settings | File Templates.
 */
public class MyLinkedList {

    LinkedListNode head;

    MyLinkedList() {
        head = null;
    }

    public void insert(Object elem ) {
        LinkedListNode newNode = new LinkedListNode(elem,head);
        head = newNode;
    }

    public LinkedListNode pop() {
        LinkedListNode node = head;
        head = node.next;
        return head;
    }

    public String toString() {
        LinkedListNode tmpNode = head;
        String result = new String();
        while( tmpNode != null ) {
            result += tmpNode.toString();
            result += ",";
            tmpNode = tmpNode.next;
        }
        return result;

    }
}
