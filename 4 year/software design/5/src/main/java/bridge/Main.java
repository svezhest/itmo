package bridge;

import bridge.drawing.DrawingApi;
import bridge.drawing.DrawingAwt;
import bridge.drawing.DrawingJavaFx;
import bridge.graph.EdgeGraph;
import bridge.graph.Graph;
import bridge.graph.MatrixGraph;
import bridge.graphStructure.Edge;

import java.util.Arrays;
import java.util.List;
import java.util.Objects;

public class Main {
    public static void main(String[] args) {
        final DrawingApi drawingApi;
        final Graph graph;

        if (args.length < 2) {
            System.out.println("Not all arguments are given (drawingApi = awt | javafx, graphFormat = matrix | edges)\n" +
                    "Using defaults");
        }

        if (args.length >= 1 && Objects.equals(args[0], "awt")) {
            drawingApi = new DrawingAwt();
        } else {
            drawingApi = new DrawingJavaFx();
        }

//        пользовательский ввод графа не требуется в условии задачи! это несложно, конечно, но лень
        if (args.length >= 2 && Objects.equals(args[1], "matrix")) {
            List<List<Boolean>> matrix = Arrays.asList(
                    Arrays.asList(false, true, false, true),
                    Arrays.asList(false, false, true, true),
                    Arrays.asList(false, true, false, false),
                    Arrays.asList(true, true, false, false)
            );

            graph = new MatrixGraph(drawingApi, matrix);
        } else {
            List<Edge> edges = Arrays.asList(
                    new Edge(0, 1),
                    new Edge(0, 2),
                    new Edge(0, 3),
                    new Edge(1, 2),
                    new Edge(1, 6),
                    new Edge(2, 4),
                    new Edge(2, 5),
                    new Edge(2, 7),
                    new Edge(3, 4),
                    new Edge(3, 6),
                    new Edge(4, 5),
                    new Edge(4, 6),
                    new Edge(5, 6),
                    new Edge(6, 7)
            );

            graph = new EdgeGraph(drawingApi, edges);
        }

        graph.drawGraph();
    }
}