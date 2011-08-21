import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

/**
 * Created by IntelliJ IDEA.
 * User: debnathsinha
 * Date: 6/22/11
 * Time: 3:06 PM
 * To change this template use File | Settings | File Templates.
 */
public class MysynchronizedQueueMain {


    public static class SyncQ {

        int data[] = new int[10];
        int front;
        int rear;
        int count = 0;
        final static Lock lock = new ReentrantLock();
        final static Condition notFull = lock.newCondition();
        final static Condition notEmpty = lock.newCondition();
        void put( int n ) {
            System.out.println("Putting" + n);
            lock.lock();
            try {
                while(count == 10)
                    notFull.await();
                data[rear] = n;
                rear = (rear + 1) %10;
                notEmpty.signal();
            } catch (InterruptedException e) {
                e.printStackTrace();  //To change body of catch statement use File | Settings | File Templates.
            } finally  {
                lock.unlock();
            }


        }

        int get() {
            System.out.println("Trying to get something");
            lock.lock();
            System.out.println("Acquired the lock");
            int n = -1;
            try {
                while( front == rear )
                    notEmpty.await();
                System.out.println("Done waiting");
                n = data[front];
                front = (front + 1)%10;

                notFull.signal();
            } catch (InterruptedException e) {
                e.printStackTrace();  //To change body of catch statement use File | Settings | File Templates.
            } finally {
                lock.unlock();
            }
            return n;
        }
        public SyncQ() {

        }
    }


    public static class Consumer implements Runnable {

        SyncQ q;
        public Consumer(SyncQ q) {
            this.q = q;
        }
        public void run() {
            System.out.println("Starting consumer");
            while(true) {
                try {
                    System.out.println("Got: " + q.get());
                } catch( Exception e) {
                    e.printStackTrace();
                }
            }
        }
    }

    public static class Producer implements Runnable {

        SyncQ q;
        public Producer(SyncQ q) {
            this.q = q;
        }

        public void run() {
            try {
            q.put(10);
            q.put(20);
            q.put(30);
            q.put(40);
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }

    public static void main( String[] args ) {
        SyncQ q = new SyncQ();
        ExecutorService es = Executors.newCachedThreadPool();
        es.submit( new Producer(q));
        es.submit( new Consumer(q));
        es.shutdown();
    }
}
