/**
 * Created by IntelliJ IDEA.
 * User: debnathsinha
 * Date: 6/17/11
 * Time: 3:42 PM
 * To change this template use File | Settings | File Templates.
 */
public class MyHeap {

    private final int MaxHeapSize = 10;
    private int[] heap = new int[MaxHeapSize];
    private int top = 0;

    public void insert( int n ) {
        if( top < MaxHeapSize )
            heap[top++] = n;
        bubbleUp();
    }

    private int parent(int pos ) {
        return pos/2;
    }


    private void swapWithParent(int childPos) {
        int tmp = heap[childPos];
        heap[childPos] = heap[parent(childPos)];
        heap[parent(childPos)] = tmp;
    }

    private void bubbleUp() {
        int i = top;
        while (i != 0 ) {
                if( heap[i] < heap[parent(i)])
                    swapWithParent(i);
        }
    }

    MyHeap() {
        MyHeapDriver heapDriver = new MyHeapDriver();
    }

    public class MyHeapDriver {
        MyHeapDriver() {
            MyHeap myHeap = new MyHeap();
            myHeap.insert(10);
            myHeap.insert(20);
            myHeap.insert(30);
        }
    }

}
