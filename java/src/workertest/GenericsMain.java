package workertest;

import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;

/**
 * Created by IntelliJ IDEA.
 * User: debnathsinha
 * Date: 6/23/11
 * Time: 12:43 PM
 * To change this template use File | Settings | File Templates.
 */
public class GenericsMain {

    public static class MyStack<T> {

        private T[] elems;
        private int top = 0;
        private final int maxSize;

        public MyStack(int n) {
            elems = (T[]) new Object[n];
            maxSize = n;
        }

        public void push( T elem ) {
            if( top < maxSize )
                elems[++top] = elem;
        }

        public T pop() {
            if( top > 0 )
                return elems[top--];
            else
                return null;
        }
    }

    public static void main( String[] args ) {
        MyStack<Integer> intStack = new MyStack<Integer>(10);
        intStack.push( new Integer(10));
        intStack.push( new Integer(20));
        System.out.println(intStack.pop());
        MyStack<String> stringMyStack = new MyStack<String>(10);
        stringMyStack.push("foo");
        stringMyStack.push("bar");
        System.out.println(stringMyStack.pop());
    }
}
