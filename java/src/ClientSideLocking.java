import java.util.Iterator;
import java.util.Vector;

/**
 * Created by IntelliJ IDEA.
 * User: debnathsinha
 * Date: 6/23/11
 * Time: 5:13 PM
 * To change this template use File | Settings | File Templates.
 */
public class ClientSideLocking {

    private static void putIfAbsent(Vector<Integer>v, Integer n) {
        synchronized (v) {
            if( !v.contains(n))
                v.add(n);
        }
    }

    private static void printElems(Vector<Integer> v) {
        Iterator<Integer> it = v.iterator();
        while( it.hasNext())
            System.out.println(it.next());
    }

    public static void main( String[] args ) {
        Vector<Integer> v = new Vector<Integer>(10);
        v.add(new Integer(10));
        v.add(new Integer(20));
        v.add(new Integer(30));
        putIfAbsent(v,new Integer(40));
        printElems(v);
    }
}
