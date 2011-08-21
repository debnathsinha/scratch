import java.util.*;

/**
 * Created by IntelliJ IDEA.
 * User: debnathsinha
 * Date: 6/21/11
 * Time: 4:59 PM
 * To change this template use File | Settings | File Templates.
 */
public class TicketOrder {

    public static void main( String[] args ) {
        Map<String, String> map = new HashMap<String,String>();
        map.put("sjc","pit");
        map.put("bos","nyc");
        map.put("pit","bos");
        Set<String> srcs = map.keySet();
        Set<String> dsts = new HashSet<String>();
        for( String src : srcs) {
            dsts.add(map.get(src));
        }
        for( String src: srcs )
            System.out.print(src + " ");
        System.out.println();
        for( String dst: dsts )
            System.out.print(dst + " ");

        String originSrc = null;
        for( String src: srcs ) {
            if( !dsts.contains(src) )
                originSrc = src;
        }
        String finalDst = null;
        for( String dst: dsts ) {
            if( !srcs.contains(dst))
                finalDst = dst;
        }
        System.out.println("Original src: " + originSrc + " final dst: " + finalDst);

        String src = originSrc;
        String dst = null;
        while( dst != finalDst ) {
            dst = map.get(src);
            System.out.println("Src: " + src + " Dst: " + dst);
            src = dst;
        }
    }
}
