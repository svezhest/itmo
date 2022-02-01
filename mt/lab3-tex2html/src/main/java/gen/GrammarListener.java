// Generated from C:/Users/brodyaga/Desktop/lab-3/src/main/antlr4\Grammar.g4 by ANTLR 4.9.2
import org.antlr.v4.runtime.tree.ParseTreeListener;

/**
 * This interface defines a complete listener for a parse tree produced by
 * {@link GrammarParser}.
 */
public interface GrammarListener extends ParseTreeListener {
	/**
	 * Enter a parse tree produced by {@link GrammarParser#tex}.
	 * @param ctx the parse tree
	 */
	void enterTex(GrammarParser.TexContext ctx);
	/**
	 * Exit a parse tree produced by {@link GrammarParser#tex}.
	 * @param ctx the parse tree
	 */
	void exitTex(GrammarParser.TexContext ctx);
	/**
	 * Enter a parse tree produced by {@link GrammarParser#line}.
	 * @param ctx the parse tree
	 */
	void enterLine(GrammarParser.LineContext ctx);
	/**
	 * Exit a parse tree produced by {@link GrammarParser#line}.
	 * @param ctx the parse tree
	 */
	void exitLine(GrammarParser.LineContext ctx);
	/**
	 * Enter a parse tree produced by {@link GrammarParser#expression}.
	 * @param ctx the parse tree
	 */
	void enterExpression(GrammarParser.ExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link GrammarParser#expression}.
	 * @param ctx the parse tree
	 */
	void exitExpression(GrammarParser.ExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link GrammarParser#object}.
	 * @param ctx the parse tree
	 */
	void enterObject(GrammarParser.ObjectContext ctx);
	/**
	 * Exit a parse tree produced by {@link GrammarParser#object}.
	 * @param ctx the parse tree
	 */
	void exitObject(GrammarParser.ObjectContext ctx);
}