package elevators;

/**
 * Created by IntelliJ IDEA.
 * User: debnathsinha
 * Date: 6/24/11
 * Time: 12:51 PM
 * To change this template use File | Settings | File Templates.
 */
public class Request {

    public int floor;
    //Change this to a proper time
    public int timestamp;


    public int timeToComplete;

    public Request(int inpfloor, int time) {
        floor = inpfloor;
        timestamp = time;
        //timeToComplete = inf;
    }
}
