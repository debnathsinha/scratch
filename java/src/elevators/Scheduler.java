package elevators;

import java.util.Collections;
import java.util.List;
import java.util.Queue;

/**
 * Created by IntelliJ IDEA.
 * User: debnathsinha
 * Date: 6/24/11
 * Time: 12:41 PM
 * To change this template use File | Settings | File Templates.
 */
public class Scheduler {

    Queue<Request> openRequests;

    //Move number of elevators out of schduler
    Elevator[] elevs;

    public Scheduler() {

        elevs = new Elevator[4];
    }

    public void submit(Request request) {
        int[] times = new int[4];
        int i = 0, minElev = 0, minTime = 0;
        for( i = 0; i < 4 ; i++) {
            times[i] = elevs[i].timeToServiceReq(request);
            if( times[i] < minTime ) {
                minElev = i;
                minTime = times[i];
            }
        }
        List<Request> renegeList = elevs[minElev].enqueueRequest(request);
        processRenegeList(renegeList);
    }

    private void processRenegeList(List<Request> renegeList) {
        //Though this function is recursive without a terminating condition,
        // it will converge because at some time we will not need to reschedule another
        // request to accomodate one of these, although it will take a lot of time
        //Possible optimization is to just enqueue into openRequest and come back
        // to them in a review
        // and then service the request in some time
        for( Request req: renegeList)
            submit(req);
    }
}
