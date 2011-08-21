package workertest;

/**
 * Created by IntelliJ IDEA.
 * User: debnathsinha
 * Date: 6/23/11
 * Time: 9:45 AM
 * To change this template use File | Settings | File Templates.
 */
public class WorkerTestMain {

    public static class TestJob implements Job {

        private final int startNumber;
        private final int endNumber;

        public TestJob(int start, int end) {
            startNumber = start;
            endNumber = end;
        }
        public void job() {
            for( int i = startNumber; i < endNumber; i++ ) {
                //Brutally slow prime finder
                for( int j = 2; j < i; j++ ) {
                    if( i %j == 0) {
                        return;
                    }
                }
            }

        }

    }

    public static void main( String[] args ) {

        Scheduler scheduler = new Scheduler();
        TestWorker worker = new TestWorker();
        TestListener listener = new TestListener();

    }
}
