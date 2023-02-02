package bridge.graph;

import bridge.drawing.DrawingApi;
import bridge.graphStructure.Edge;

import java.util.ArrayList;
import java.util.List;

public class MatrixGraph extends Graph {
    private final List<Edge> edges;
    private final int size;

    /**
     * Requires matrix n x n
     */
    public MatrixGraph(DrawingApi drawingApi, List<List<Boolean>> matrix) {
        super(drawingApi);
        this.size = matrix.size();
        this.edges = new ArrayList<Edge>();
        for (int i = 0; i < size; i++) {
            for (int j = i + 1; j < size; j++) {
                if (matrix.get(i).get(j)) {
                    edges.add(new Edge(i, j));
                }
            }
        }
    }

    @Override
    protected int getNumberOfVertices() {
        return size;
    }

    @Override
    protected List<Edge> getEdges() {
        return edges;
    }
}
