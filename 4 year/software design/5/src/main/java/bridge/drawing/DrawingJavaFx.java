package bridge.drawing;

import bridge.drawingStructure.Point;

import javafx.application.Application;
import javafx.scene.Group;
import javafx.scene.Scene;
import javafx.scene.paint.Paint;
import javafx.scene.shape.Circle;
import javafx.scene.shape.Line;
import javafx.scene.shape.Shape;
import javafx.stage.Stage;

import java.util.ArrayList;
import java.util.List;

public class DrawingJavaFx extends Application implements DrawingApi {
    private final long height = 800;
    private final long width = 800;

    private static final List<Shape> shapes = new ArrayList<>();

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
        shapes.add(new Circle(center.x(), center.y(), radius));
        if (radius - 2 > 0) {
            shapes.add(new Circle(center.x(), center.y(), radius - 2, Paint.valueOf("FFFFFF")));
        }
    }

    @Override
    public void drawLine(Point from, Point to) {
        shapes.add(new Line(from.x(), from.y(), to.x(), to.y()));
    }

    @Override
    public void render() {
        Application.launch(DrawingJavaFx.class);
    }

    @Override
    public void start(Stage stage) throws Exception {
        stage.setTitle("Graph");
        Group root = new Group();

        shapes.forEach(root.getChildren()::add);

        stage.setScene(new Scene(root, width, height));
        stage.show();
    }
}
