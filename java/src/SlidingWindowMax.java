import java.util.*;

/**
 * Created by IntelliJ IDEA.
 * User: debnathsinha
 * Date: 6/18/11
 * Time: 11:19 AM
 * To change this template use File | Settings | File Templates.
 */
public class SlidingWindowMax {

    private List<Integer> myArr;
    private List<Integer> kList;
    int arr_[];

    public SlidingWindowMax(int[] arr ) {
        myArr = new ArrayList<Integer>();
        arr_ = arr;
        for( int item : arr) {
            myArr.add(item);
        }
    }
    public void printKMax() {
        Iterator it = myArr.listIterator();
        kList = new LinkedList<Integer>();
        kList.add(new Integer( arr_[0] ));
        kList.add(new Integer( arr_[1] ));
        kList.add(new Integer( arr_[2] ));
        kList.add(new Integer( arr_[3] ));
        kList.add(new Integer( arr_[4] ));
        kList.add(new Integer( arr_[5] ));
        kList.add(new Integer( arr_[6] ));
        kList.add(new Integer( arr_[7] ));

        for( int i = 8; i < arr_.length; i++ ) {
            Integer elementDroppingOut = new Integer( arr_[i-8] );
            Integer elementComingIn = new Integer( arr_[i] );
            Boolean addElemComingIn = false;
            if( kList.contains( elementDroppingOut) )
                kList.remove(kList.indexOf(elementDroppingOut));
            try {
                List<Integer> removeList = new LinkedList<Integer>();

                for( Integer elem: kList ) {
                    if( elem < elementComingIn ) {
                        removeList.add(kList.indexOf(elem));
                        addElemComingIn = true;
                    }
                }
                kList.add(elementComingIn);
                int k = 0;
                //System.out.print("Remove list: ");
                for( Integer elem: removeList) {
                    //System.out.print(elem + " ");
                    kList.remove(elem - k++);
                }
                //System.out.println();
            } catch( ConcurrentModificationException e) {
                e.printStackTrace();
            }

            System.out.print("The elements I am looking at are: ");
            for( int j = 0; j < 8; j++ )
                System.out.print(arr_[i - 8 + j] + " ");

            System.out.print("      And the elements in the list are: ");
            for( Integer elem: kList )
                System.out.print(elem + " ");
            System.out.println();
            System.out.println("The max so far is: " + Collections.max(kList));
        }
    }

}
