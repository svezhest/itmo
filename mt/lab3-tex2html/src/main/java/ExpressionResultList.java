import java.util.ArrayList;
import java.util.List;

public class ExpressionResultList {
    private final List<ExpressionResult> expressionResultList;

    public ExpressionResultList() {
        expressionResultList = new ArrayList<ExpressionResult>();
    }

    public void insert(ExpressionResult expressionResult) {
        expressionResultList.add(expressionResult);
    }

    public double getValue(String name) {
        for (int i = expressionResultList.size() - 1; i >= 0; i--) {
            if (expressionResultList.get(i).getName().equals(name)) {
                return expressionResultList.get(i).getValue();
            }
        }
        try {
            throw new Exception(String.format("There is no variable named '%s' yet", name));
        } catch (Exception e) {
            e.printStackTrace();
        }
        return 0;
    }

    public boolean contains(String name) {
        for (ExpressionResult expressionResult : expressionResultList) {
            if (expressionResult.getName().equals(name)) {
                return true;
            }
        }

        return false;
    }

    public List<ExpressionResult> getExpressionResultList() {
        return expressionResultList;
    }

    @Override
    public String toString() {
        StringBuilder stringBuilder = new StringBuilder();

        for (ExpressionResult expressionResult : expressionResultList) {
            stringBuilder.append(expressionResult.toString());
            stringBuilder.append("\n");
        }

        return stringBuilder.toString();
    }
}
