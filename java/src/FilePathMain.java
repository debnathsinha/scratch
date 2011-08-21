import com.sun.tools.javac.util.Pair;
import sun.tools.tree.ThisExpression;

import java.util.*;

/**
 * Created by IntelliJ IDEA.
 * User: debnathsinha
 * Date: 6/22/11
 * Time: 12:44 AM
 * To change this template use File | Settings | File Templates.
 */
public class FilePathMain {

    public static PathTree tree = new PathTree();
    public static class PathTreeNode {
        String path;
        List<PathTreeNode> children;
        private PathTreeNode addNode(String str) {
            PathTreeNode newNode = new PathTreeNode(str);
            children.add(newNode);
            return newNode;

        }
        private void addList(List<String> strList) {
            PathTreeNode nodeAdded = addNode(strList.remove(0));
            if( !strList.isEmpty() )
                nodeAdded.addList(strList);
        }

        public void printNode() {
            System.out.println(path + " ");
            if( children != null ) {
                for( PathTreeNode child: children )
                    child.printNode();
            }
        }
        //public PathTreeNode() {
        //    this.path = null;
        //    this.children = null;
        //}
        public PathTreeNode(String name) {
            this.path = name;
            this.children = new LinkedList<PathTreeNode>();
        }
    }

    public static class PathTree {
        PathTreeNode root;

        PathTree() {
            root = new PathTreeNode("");
        }
        void addPath(String path) {
            String[] tokens = tokenize(path);
            addTokens(tokens);
        }

        Pair<PathTreeNode,List<String>> findLongestMatch(String[] tokens) {
            PathTreeNode curNode = root;

            int i = 0;
            if( curNode.children == null ) {
                return new Pair<PathTreeNode, List<String>>(curNode,new LinkedList<String>(Arrays.asList(tokens)));
            }
            for( i = 1; i < tokens.length; i++ ) {
                boolean foundMatch = false;
                for( PathTreeNode child: curNode.children ) {
                    if( tokens[i].equals(child.path) ) {
                        curNode = child;
                        foundMatch = true;
                        break;
                    }
                }
                if( foundMatch == false )
                    break;
            }
            List<String> list = new LinkedList<String>();
            for(; i < tokens.length; i++ ) {
                list.add(tokens[i]);
            }
            return new Pair<PathTreeNode,List<String>>(curNode,list);


        }

        private void addTokens(String[] tokens) {

            Pair<PathTreeNode,List<String>> longestMatch = findLongestMatch(tokens);
            longestMatch.fst.addList(longestMatch.snd);
        }

        private String[] tokenize(String str ) {
            String tokens[] = str.split("/");
            return tokens;
        }

        public void printTree() {
            PathTreeNode curNode = root;
            root.printNode();
        }

    }



    public static void main( String[] args ) {
        List<String> paths = new LinkedList<String>();
        paths.add("/usr/bin");
        paths.add("/usr/local/bin");
        paths.add("/home/deb");
        for( String path: paths)
            tree.addPath(path);
        tree.printTree();

    }
}
