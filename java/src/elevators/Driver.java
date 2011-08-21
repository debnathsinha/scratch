package elevators;

import java.io.*;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;

/**
 * Created by IntelliJ IDEA.
 * User: debnathsinha
 * Date: 6/24/11
 * Time: 12:43 PM
 * To change this template use File | Settings | File Templates.
 */
public class Driver {


    public static void main( String[] args ) {

        Scheduler s = new Scheduler();
        List<Request> request = new LinkedList<Request>();

        try {
            BufferedReader reader = new BufferedReader(new FileReader("elev.inp"));

            String line;
            while( (line = reader.readLine() ) != null ) {
                String[] req = line.split(",");
                request.add(new Request(Integer.valueOf(req[0]), Integer.valueOf(req[1])));
            }
        } catch (FileNotFoundException e) {
            e.printStackTrace();  //To change body of catch statement use File | Settings | File Templates.
        } catch (IOException e) {
            e.printStackTrace();  //To change body of catch statement use File | Settings | File Templates.
        }

        for( Request r: request) {
            s.submit(r);

        }


    }
}
