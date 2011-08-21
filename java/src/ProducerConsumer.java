/**
 * Created by IntelliJ IDEA.
 * User: debnathsinha
 * Date: 6/17/11
 * Time: 8:27 AM
 * To change this template use File | Settings | File Templates.
 */
public class ProducerConsumer {

    class Q {
        int n = 0;
        boolean valueSet = false;
        synchronized int get() {
            if( !valueSet ) {
                try {
                    wait();
                } catch( InterruptedException e ) {
                    System.out.println("Interrupted exception caught");
                }

            }
            System.out.println("Got" + n);
            valueSet = false;
            notify();
            return n;
        }
        synchronized void put( int n ) {
            if( valueSet ) {
                try {
                    wait();
                } catch( InterruptedException e) {
                    System.out.println("Caught interrupted exception in producer");
                }

            }
            this.n = n;
            System.out.println("Put" + n);
            valueSet = true;
            notify();

        }

    }

    class Producer implements Runnable {
        Q q;
        Producer(Q q) {
            this.q = q;
            new Thread(this,"Producer").start();
        }
        public void run() {
            int i = 0;
            System.out.println("Starting producer");
            while(true) {
                q.put(i++);
            }
        }
    }

    class Consumer implements Runnable {
        Q q;
        Consumer( Q q ) {
            this.q = q;
            new Thread(this,"Consumer").start();
        }
        public void run() {
            System.out.println("Starting consumer");
            while(true) {
                q.get();
            }
        }
    }

    ProducerConsumer() {
        Q q = new Q();
        Producer p = new Producer(q);
        Consumer c = new Consumer(q);
    }

}
