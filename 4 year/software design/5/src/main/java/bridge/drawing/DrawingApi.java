package bridge.drawing;

import bridge.drawingStructure.Point;

public interface DrawingApi {
    long getDrawingAreaWidth();

    long getDrawingAreaHeight();

    void drawCircle(Point center, double radius);

    void drawLine(Point from, Point to);

    void render();
}
