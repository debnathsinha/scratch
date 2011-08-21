package elevators;

import java.util.LinkedList;
import java.util.List;
import java.util.Queue;

/**
 * Created by IntelliJ IDEA.
 * User: debnathsinha
 * Date: 6/24/11
 * Time: 12:41 PM
 * To change this template use File | Settings | File Templates.
 */
public class Elevator {

    private Queue<Request> serviceList;

    public Elevator() {

    }

    public int timeToServiceReq(Request request) {
        //Put in the elevator algorithm into this
        //This logic is garbage
        return request.timestamp;
    }

    public List<Request> enqueueRequest( Request request ) {

        List<Request> renegeList = new LinkedList<Request>();  //The list the elevator cannot
                                                               //deliver as promised in order to
                                                               //enqueue this request
        for( Request req: serviceList) {
            if( req.timeToComplete < request.timeToComplete ) {
                renegeList.add(req);
            }
        }
        return renegeList;
    }
}
