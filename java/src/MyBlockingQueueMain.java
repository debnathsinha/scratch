import java.lang.reflect.Array;
import java.util.LinkedList;
import java.util.List;
import java.util.concurrent.*;

/**
 * Created by IntelliJ IDEA.
 * User: debnathsinha
 * Date: 6/21/11
 * Time: 2:45 PM
 * To change this template use File | Settings | File Templates.
 */
public class MyBlockingQueueMain implements Callable {

    BlockingQueue<Integer> queue = new LinkedBlockingQueue<Integer>();
    private static final int MAX_WORKERS = 5;

    public static void main( String[] args ) {
        System.out.println("Hello World");
        MyBlockingQueueMain myQ = new MyBlockingQueueMain();
        ExecutorService es = Executors.newCachedThreadPool();
        List<Future<Integer>> futures = new LinkedList<Future<Integer>>();

        for( int i = 0; i < MAX_WORKERS; i++) {
            futures.add(es.submit(new MyBlockingQueueMain()));
        }
        es.shutdown();
        for( Future<Integer> future: futures) {
            if( future.isCancelled() ) {
                System.out.println("Future for" + Thread.currentThread() + "has been cancelled");
            } else {
                System.out.println("Future for" + Thread.currentThread() + "has not been cancelled");
            }
        }
        for( Future<Integer> future: futures ) {
            try {
                System.out.println(future.get());
            } catch (InterruptedException e) {
                e.printStackTrace();  //To change body of catch statement use File | Settings | File Templates.
            } catch (ExecutionException e) {
                e.printStackTrace();  //To change body of catch statement use File | Settings | File Templates.
            }
        }
    }

    public Integer call() {
        System.out.println("Hello world from callable thread" + Thread.currentThread());
        return 4;
    }
}
