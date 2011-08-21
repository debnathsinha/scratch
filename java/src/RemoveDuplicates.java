import java.util.HashSet;
import java.util.Hashtable;
import java.util.Iterator;
import java.util.Set;

/**
 * Created by IntelliJ IDEA.
 * User: debnathsinha
 * Date: 6/17/11
 * Time: 1:13 PM
 * To change this template use File | Settings | File Templates.
 */
public class RemoveDuplicates {

    public static void removeDuplicates( String[] args ) {
        Set<String> uniq = new HashSet<String>();
        Set<String> duplicates = new HashSet<String>();
        Set<String> stillDups = new HashSet<String>();
        duplicates.add("foo");
        duplicates.add("bar");
        duplicates.add("foo");

        stillDups = duplicates;
        if( stillDups.containsAll(duplicates))
            System.out.println("stillDups == Duplicates");
        for( String s: duplicates ) {
            if(! uniq.contains(s))
                uniq.add(s);
        }
        System.out.println(uniq);
        if( uniq.containsAll(duplicates))
            System.out.println("uniq == Duplicates");
        Iterator<String> sit = uniq.iterator();
        System.out.println(sit.next());
        while(sit.hasNext())
            System.out.println(sit.next());
    }
}
