package bridge.drawing;

import bridge.drawingStructure.Point;

import java.awt.*;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.awt.geom.Arc2D;
import java.awt.geom.Line2D;
import java.util.ArrayList;
import java.util.List;

public class DrawingAwt extends Frame implements DrawingApi {
    private final long height = 800;
    private final long width = 800;
    final java.util.List<Arc2D> circles = new ArrayList<>();
    final List<Line2D> lines = new ArrayList<>();

    @Override
    public void paint(Graphics g) {
        Graphics2D graphics2D = (Graphics2D) g;
        graphics2D.setPaint(Color.black);
        graphics2D.setStroke(new BasicStroke(2));
        circles.forEach(graphics2D::draw);
        lines.forEach(graphics2D::draw);
    }

    @Override
    public long getDrawingAreaWidth() {
        return width;
    }

    @Override
    public long getDrawingAreaHeight() {
        return height;
    }

    @Override
    public void drawCircle(Point center, double radius) {
        circles.add(new Arc2D.Double(center.x() - radius, center.y() - radius, 2 * radius, 2 * radius, 0, 360, Arc2D.OPEN));
    }

    @Override
    public void drawLine(Point from, Point to) {
        lines.add(new Line2D.Double(from.x(), from.y(), to.x(), to.y()));
    }

    @Override
    public void render() {
        this.addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent we) {
                System.exit(0);
            }
        });
        this.setSize((int) width, (int) height);
        this.setVisible(true);
    }
}
