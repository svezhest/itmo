package bridge.graph;

import bridge.Main;
import bridge.drawing.DrawingApi;
import bridge.graphStructure.Edge;

import java.util.List;

public class EdgeGraph extends Graph {
    private final List<Edge> edges;
    private final int size;

    public EdgeGraph(DrawingApi drawingApi, List<Edge> edges) {
        super(drawingApi);
        this.edges = edges;
        int max = 0;
        for (Edge edge : edges) {
            max = Math.max(edge.to(), Math.max(edge.from(), max));
        }
        this.size = max + 1;
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
