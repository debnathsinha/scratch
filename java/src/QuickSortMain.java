/**
 * Created by IntelliJ IDEA.
 * User: debnathsinha
 * Date: 6/23/11
 * Time: 4:10 PM
 * To change this template use File | Settings | File Templates.
 */
public class QuickSortMain {

    private static int partition(int[] arr, int start, int end, int pivotPos) {

        int storeIndex = start;
        for( int i = start; i != end; i++ ) {
            if( arr[i] < arr[pivotPos]) {
                swaparr(arr,i,storeIndex++);
            }
        }

        swaparr(arr,storeIndex,pivotPos);
        return pivotPos;
    }
    private static void swaparr(int[] arr, int i, int j ) {
        int tmp = arr[j];
        arr[j] = arr[i];
        arr[i] = tmp;
    }

    private static void quickSort( int [] arr, int begin, int end ) {

        if( begin >= end )
            return;
        int pivotElemPos = partition(arr,begin,end,end);

        quickSort(arr,begin,pivotElemPos-1);
        quickSort(arr,pivotElemPos+1,end);


    }

    public static void main( String[] args ) {
        int[] arr = {5,15,10,35,20,25};
        quickSort(arr,0,arr.length-1);
        for(int i = 0; i < arr.length; i++) {
            System.out.println(arr[i]);
        }
    }
}
