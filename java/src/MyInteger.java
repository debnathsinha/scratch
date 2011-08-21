/**
 * Created by IntelliJ IDEA.
 * User: debnathsinha
 * Date: 6/18/11
 * Time: 11:00 AM
 * To change this template use File | Settings | File Templates.
 */
public class MyInteger implements Comparable, Hashable {

    private int value;
    public MyInteger() {
        this(0);
    }
    MyInteger(int n) {
        value = n;
    }
    public int getValue() {
        return value;
    }
    public void putValue( int n ) {
        value = n;
    }
    public String toString() {
        return Integer.toString(value);
    }
    public int hash(int tableSize) {
        if( value >= 0 ) {
            return value%tableSize;
        } else {
            return (-value)%tableSize;
        }
    }
    public int compareTo(Comparable rhs) {

        return value < ((MyInteger)rhs).value ? -1 :
                value == ((MyInteger)rhs).value ? 0 : 1;
    }
    public boolean equals( Object rhs) {
        return ( rhs != null && value == ((MyInteger)rhs).value );
    }


}
