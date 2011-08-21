/**
 * Created by IntelliJ IDEA.
 * User: debnathsinha
 * Date: 6/18/11
 * Time: 10:49 AM
 * To change this template use File | Settings | File Templates.
 */
public class Main {

    public static void foo() {
        //ProducerConsumer pc = new ProducerConsumer();
        String[] dups = {"foo","bar","foo"};
        RemoveDuplicates.removeDuplicates(dups);
        MyInteger m1 = new MyInteger(11);
        MyInteger m2 = new MyInteger(20);
        System.out.println(m1.compareTo(m2));
        System.out.println(m1.hash(10));
        System.out.println(m1);

        MyLinkedList list = new MyLinkedList();
        list.insert(new Integer(10));
        list.insert(new Integer(20));
        list.insert(new Integer(30));
        System.out.println(list);
        System.out.println("Popping: " + list.pop());
        System.out.println(list);
        MyLinkedListIterator it = new MyLinkedListIterator(list.head);
        System.out.println("Iterating:");
        while(it.hasNext())
            System.out.println(it.next());
    }

    public static void main( String[] args ) {
        System.out.println("Hello World");


        int arr[] = {5,3,4,6,2,1,11,23,12,41,31,76,105,32};
        SlidingWindowMax windowMax = new SlidingWindowMax( arr );
        windowMax.printKMax();
    }
}