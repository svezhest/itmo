package bridge.graph;

import bridge.drawing.DrawingApi;
import bridge.drawingStructure.Point;
import bridge.graphStructure.Edge;

import java.util.ArrayList;
import java.util.List;

public abstract class Graph {
    private final double pointRadius = 20;
    /**
     * Bridge to drawing api
     */
    private final DrawingApi drawingApi;

    public Graph(DrawingApi drawingApi) {
        this.drawingApi = drawingApi;
    }

    protected abstract int getNumberOfVertices();

    /**
     * Required numeration from 0 and that maximum used index is less than numberOfVertices
     */
    protected abstract List<Edge> getEdges();

    public void drawGraph() {
        long height = drawingApi.getDrawingAreaHeight();
        long width = drawingApi.getDrawingAreaWidth();
        int size = getNumberOfVertices();

        Point center = new Point(width / 2., height / 2.);

        // free space equals extra half a point on each side
        double radius = Math.min(height, width) / 2. - pointRadius * 4;

        ArrayList<Point> points = new ArrayList<>();
        for (int i = 0; i < size; i++) {
            double angle = 2 * i * Math.PI / size;
            Point point = new Point(
                    radius * Math.cos(angle) + center.x(),
                    radius * Math.sin(angle) + center.y()
            );

            points.add(point);
            drawingApi.drawCircle(point, pointRadius);
        }

        List<Edge> edges = getEdges();
        edges.forEach(edge -> drawingApi.drawLine(points.get(edge.from()), points.get(edge.to())));
        drawingApi.render();
    }
}
