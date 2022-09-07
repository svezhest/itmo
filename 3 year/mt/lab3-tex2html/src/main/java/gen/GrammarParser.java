// Generated from C:/Users/brodyaga/Desktop/lab-3/src/main/antlr4\Grammar.g4 by ANTLR 4.9.2
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.misc.*;
import org.antlr.v4.runtime.tree.*;
import java.util.List;
import java.util.Iterator;
import java.util.ArrayList;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast"})
public class GrammarParser extends Parser {
	static { RuntimeMetaData.checkVersion("4.9.2", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		T__0=1, T__1=2, T__2=3, T__3=4, T__4=5, T__5=6, T__6=7, T__7=8, MulOrDiv=9, 
		Whitespace=10, Number=11, Variable=12, OPEN_BRACKET=13, CLOSE_BRACKET=14, 
		BEGIN=15, END=16, UP=17, DOWN=18;
	public static final int
		RULE_tex = 0, RULE_line = 1, RULE_expression = 2, RULE_object = 3;
	private static String[] makeRuleNames() {
		return new String[] {
			"tex", "line", "expression", "object"
		};
	}
	public static final String[] ruleNames = makeRuleNames();

	private static String[] makeLiteralNames() {
		return new String[] {
			null, "'$'", "'='", "'\\'", "'('", "')'", "'+'", "'-'", "'\\frac'", null, 
			null, null, null, "'{'", "'}'", null, null, "'^'", "'_'"
		};
	}
	private static final String[] _LITERAL_NAMES = makeLiteralNames();
	private static String[] makeSymbolicNames() {
		return new String[] {
			null, null, null, null, null, null, null, null, null, "MulOrDiv", "Whitespace", 
			"Number", "Variable", "OPEN_BRACKET", "CLOSE_BRACKET", "BEGIN", "END", 
			"UP", "DOWN"
		};
	}
	private static final String[] _SYMBOLIC_NAMES = makeSymbolicNames();
	public static final Vocabulary VOCABULARY = new VocabularyImpl(_LITERAL_NAMES, _SYMBOLIC_NAMES);

	/**
	 * @deprecated Use {@link #VOCABULARY} instead.
	 */
	@Deprecated
	public static final String[] tokenNames;
	static {
		tokenNames = new String[_SYMBOLIC_NAMES.length];
		for (int i = 0; i < tokenNames.length; i++) {
			tokenNames[i] = VOCABULARY.getLiteralName(i);
			if (tokenNames[i] == null) {
				tokenNames[i] = VOCABULARY.getSymbolicName(i);
			}

			if (tokenNames[i] == null) {
				tokenNames[i] = "<INVALID>";
			}
		}
	}

	@Override
	@Deprecated
	public String[] getTokenNames() {
		return tokenNames;
	}

	@Override

	public Vocabulary getVocabulary() {
		return VOCABULARY;
	}

	@Override
	public String getGrammarFileName() { return "Grammar.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public ATN getATN() { return _ATN; }

	public GrammarParser(TokenStream input) {
		super(input);
		_interp = new ParserATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	public static class TexContext extends ParserRuleContext {
		public String value;
		public LineContext next;
		public TerminalNode BEGIN() { return getToken(GrammarParser.BEGIN, 0); }
		public LineContext line() {
			return getRuleContext(LineContext.class,0);
		}
		public TexContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_tex; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof GrammarListener ) ((GrammarListener)listener).enterTex(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof GrammarListener ) ((GrammarListener)listener).exitTex(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof GrammarVisitor ) return ((GrammarVisitor<? extends T>)visitor).visitTex(this);
			else return visitor.visitChildren(this);
		}
	}

	public final TexContext tex() throws RecognitionException {
		TexContext _localctx = new TexContext(_ctx, getState());
		enterRule(_localctx, 0, RULE_tex);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(8);
			match(BEGIN);
			setState(9);
			((TexContext)_localctx).next = line();

			     ((TexContext)_localctx).value =  "<html> <head> <title> Tex2HTML </title> </head> <body>\n" + ((TexContext)_localctx).next.value + "</body> </html>";
			   
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class LineContext extends ParserRuleContext {
		public String value;
		public ExpressionContext expr1;
		public ExpressionContext expr2;
		public LineContext next;
		public ExpressionContext expr;
		public Token s;
		public List<ExpressionContext> expression() {
			return getRuleContexts(ExpressionContext.class);
		}
		public ExpressionContext expression(int i) {
			return getRuleContext(ExpressionContext.class,i);
		}
		public LineContext line() {
			return getRuleContext(LineContext.class,0);
		}
		public TerminalNode Variable() { return getToken(GrammarParser.Variable, 0); }
		public TerminalNode END() { return getToken(GrammarParser.END, 0); }
		public LineContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_line; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof GrammarListener ) ((GrammarListener)listener).enterLine(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof GrammarListener ) ((GrammarListener)listener).exitLine(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof GrammarVisitor ) return ((GrammarVisitor<? extends T>)visitor).visitLine(this);
			else return visitor.visitChildren(this);
		}
	}

	public final LineContext line() throws RecognitionException {
		LineContext _localctx = new LineContext(_ctx, getState());
		enterRule(_localctx, 2, RULE_line);
		try {
			setState(40);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,0,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(12);
				match(T__0);
				setState(13);
				((LineContext)_localctx).expr1 = expression(0);
				setState(14);
				match(T__1);
				setState(15);
				((LineContext)_localctx).expr2 = expression(0);
				setState(16);
				match(T__0);
				setState(17);
				((LineContext)_localctx).next = line();

				     ((LineContext)_localctx).value =  "<math displaystyle=\"true\"> <mrow> " + ((LineContext)_localctx).expr1.value + " <mo> = </mo> " + ((LineContext)_localctx).expr2.value + " </mrow>  </math>\n" + ((LineContext)_localctx).next.value;
				   
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(20);
				match(T__0);
				setState(21);
				((LineContext)_localctx).expr = expression(0);
				setState(22);
				match(T__0);
				setState(23);
				((LineContext)_localctx).next = line();

				     ((LineContext)_localctx).value =  "<math displaystyle=\"true\"> <mrow> " + ((LineContext)_localctx).expr.value + " </mrow> </math>\n" + ((LineContext)_localctx).next.value;
				   
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(26);
				match(T__0);
				setState(27);
				match(T__2);
				setState(28);
				((LineContext)_localctx).s = match(Variable);
				setState(29);
				match(T__0);
				setState(30);
				((LineContext)_localctx).next = line();

				     ((LineContext)_localctx).value =  "<div class=\"" + (((LineContext)_localctx).s!=null?((LineContext)_localctx).s.getText():null) + "\"></div>\n" + ((LineContext)_localctx).next.value;
				   
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(33);
				match(T__0);
				setState(34);
				match(T__0);
				setState(35);
				((LineContext)_localctx).next = line();

				     ((LineContext)_localctx).value =  ((LineContext)_localctx).next.value;
				   
				}
				break;
			case 5:
				enterOuterAlt(_localctx, 5);
				{
				setState(38);
				match(END);

				     ((LineContext)_localctx).value =  "";
				   
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ExpressionContext extends ParserRuleContext {
		public String value;
		public ExpressionContext expr1;
		public ExpressionContext expr;
		public ExpressionContext expr2;
		public ObjectContext s;
		public Token sign;
		public ExpressionContext expr3;
		public List<ExpressionContext> expression() {
			return getRuleContexts(ExpressionContext.class);
		}
		public ExpressionContext expression(int i) {
			return getRuleContext(ExpressionContext.class,i);
		}
		public List<TerminalNode> OPEN_BRACKET() { return getTokens(GrammarParser.OPEN_BRACKET); }
		public TerminalNode OPEN_BRACKET(int i) {
			return getToken(GrammarParser.OPEN_BRACKET, i);
		}
		public List<TerminalNode> CLOSE_BRACKET() { return getTokens(GrammarParser.CLOSE_BRACKET); }
		public TerminalNode CLOSE_BRACKET(int i) {
			return getToken(GrammarParser.CLOSE_BRACKET, i);
		}
		public ObjectContext object() {
			return getRuleContext(ObjectContext.class,0);
		}
		public TerminalNode MulOrDiv() { return getToken(GrammarParser.MulOrDiv, 0); }
		public TerminalNode UP() { return getToken(GrammarParser.UP, 0); }
		public TerminalNode DOWN() { return getToken(GrammarParser.DOWN, 0); }
		public ExpressionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expression; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof GrammarListener ) ((GrammarListener)listener).enterExpression(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof GrammarListener ) ((GrammarListener)listener).exitExpression(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof GrammarVisitor ) return ((GrammarVisitor<? extends T>)visitor).visitExpression(this);
			else return visitor.visitChildren(this);
		}
	}

	public final ExpressionContext expression() throws RecognitionException {
		return expression(0);
	}

	private ExpressionContext expression(int _p) throws RecognitionException {
		ParserRuleContext _parentctx = _ctx;
		int _parentState = getState();
		ExpressionContext _localctx = new ExpressionContext(_ctx, _parentState);
		ExpressionContext _prevctx = _localctx;
		int _startState = 4;
		enterRecursionRule(_localctx, 4, RULE_expression, _p);
		int _la;
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(64);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case T__3:
				{
				setState(43);
				match(T__3);
				setState(44);
				((ExpressionContext)_localctx).expr = expression(0);
				setState(45);
				match(T__4);

				     ((ExpressionContext)_localctx).value =  "<mrow> " + "<mo> ( </mo> " + ((ExpressionContext)_localctx).expr.value + " <mo> ) </mo>" + " </mrow>";
				   
				}
				break;
			case T__6:
				{
				setState(48);
				match(T__6);
				setState(49);
				((ExpressionContext)_localctx).expr = expression(3);

				     ((ExpressionContext)_localctx).value =  "<mo> - </mo> " + ((ExpressionContext)_localctx).expr.value;
				   
				}
				break;
			case T__7:
				{
				setState(52);
				match(T__7);
				setState(53);
				match(OPEN_BRACKET);
				setState(54);
				((ExpressionContext)_localctx).expr1 = expression(0);
				setState(55);
				match(CLOSE_BRACKET);
				setState(56);
				match(OPEN_BRACKET);
				setState(57);
				((ExpressionContext)_localctx).expr2 = expression(0);
				setState(58);
				match(CLOSE_BRACKET);

				     ((ExpressionContext)_localctx).value =  "<mfrac> " + "<mrow>" + ((ExpressionContext)_localctx).expr1.value + "</mrow>" + " " + "<mrow>" + ((ExpressionContext)_localctx).expr2.value + "</mrow>" + "</mfrac>";
				   
				}
				break;
			case Number:
			case Variable:
				{
				setState(61);
				((ExpressionContext)_localctx).s = object();

				     ((ExpressionContext)_localctx).value =  ((ExpressionContext)_localctx).s.value;
				   
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
			_ctx.stop = _input.LT(-1);
			setState(107);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,3,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					if ( _parseListeners!=null ) triggerExitRuleEvent();
					_prevctx = _localctx;
					{
					setState(105);
					_errHandler.sync(this);
					switch ( getInterpreter().adaptivePredict(_input,2,_ctx) ) {
					case 1:
						{
						_localctx = new ExpressionContext(_parentctx, _parentState);
						_localctx.expr1 = _prevctx;
						_localctx.expr1 = _prevctx;
						pushNewRecursionContext(_localctx, _startState, RULE_expression);
						setState(66);
						if (!(precpred(_ctx, 8))) throw new FailedPredicateException(this, "precpred(_ctx, 8)");
						setState(67);
						((ExpressionContext)_localctx).sign = match(MulOrDiv);
						setState(68);
						((ExpressionContext)_localctx).expr2 = expression(9);

						               ((ExpressionContext)_localctx).value =  "<mrow> " + ((ExpressionContext)_localctx).expr1.value + " <mo> " + (((ExpressionContext)_localctx).sign!=null?((ExpressionContext)_localctx).sign.getText():null) + " </mo> " + ((ExpressionContext)_localctx).expr2.value + " </mrow>";
						             
						}
						break;
					case 2:
						{
						_localctx = new ExpressionContext(_parentctx, _parentState);
						_localctx.expr1 = _prevctx;
						_localctx.expr1 = _prevctx;
						pushNewRecursionContext(_localctx, _startState, RULE_expression);
						setState(71);
						if (!(precpred(_ctx, 7))) throw new FailedPredicateException(this, "precpred(_ctx, 7)");
						setState(72);
						((ExpressionContext)_localctx).sign = _input.LT(1);
						_la = _input.LA(1);
						if ( !(_la==T__5 || _la==T__6) ) {
							((ExpressionContext)_localctx).sign = (Token)_errHandler.recoverInline(this);
						}
						else {
							if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
							_errHandler.reportMatch(this);
							consume();
						}
						setState(73);
						((ExpressionContext)_localctx).expr2 = expression(8);

						               ((ExpressionContext)_localctx).value =  "<mrow> " + ((ExpressionContext)_localctx).expr1.value + " <mo> " + (((ExpressionContext)_localctx).sign!=null?((ExpressionContext)_localctx).sign.getText():null) + " </mo> " + ((ExpressionContext)_localctx).expr2.value + " </mrow>";
						             
						}
						break;
					case 3:
						{
						_localctx = new ExpressionContext(_parentctx, _parentState);
						_localctx.expr1 = _prevctx;
						_localctx.expr1 = _prevctx;
						pushNewRecursionContext(_localctx, _startState, RULE_expression);
						setState(76);
						if (!(precpred(_ctx, 6))) throw new FailedPredicateException(this, "precpred(_ctx, 6)");
						setState(77);
						match(UP);
						setState(78);
						match(OPEN_BRACKET);
						setState(79);
						((ExpressionContext)_localctx).expr2 = expression(0);
						setState(80);
						match(CLOSE_BRACKET);
						setState(81);
						match(DOWN);
						setState(82);
						match(OPEN_BRACKET);
						setState(83);
						((ExpressionContext)_localctx).expr3 = expression(0);
						setState(84);
						match(CLOSE_BRACKET);

						               ((ExpressionContext)_localctx).value =  "<msubsup> " + ((ExpressionContext)_localctx).expr1.value + " " + ((ExpressionContext)_localctx).expr3.value + " " + ((ExpressionContext)_localctx).expr2.value + " </msubsup>";
						             
						}
						break;
					case 4:
						{
						_localctx = new ExpressionContext(_parentctx, _parentState);
						_localctx.expr1 = _prevctx;
						_localctx.expr1 = _prevctx;
						pushNewRecursionContext(_localctx, _startState, RULE_expression);
						setState(87);
						if (!(precpred(_ctx, 5))) throw new FailedPredicateException(this, "precpred(_ctx, 5)");
						setState(88);
						match(DOWN);
						setState(89);
						match(OPEN_BRACKET);
						setState(90);
						((ExpressionContext)_localctx).expr2 = expression(0);
						setState(91);
						match(CLOSE_BRACKET);
						setState(92);
						match(UP);
						setState(93);
						match(OPEN_BRACKET);
						setState(94);
						((ExpressionContext)_localctx).expr3 = expression(0);
						setState(95);
						match(CLOSE_BRACKET);

						               ((ExpressionContext)_localctx).value =  "<msubsup> " + ((ExpressionContext)_localctx).expr1.value + " " + ((ExpressionContext)_localctx).expr2.value + " " + ((ExpressionContext)_localctx).expr3.value + " </msubsup>";
						             
						}
						break;
					case 5:
						{
						_localctx = new ExpressionContext(_parentctx, _parentState);
						_localctx.expr1 = _prevctx;
						_localctx.expr1 = _prevctx;
						pushNewRecursionContext(_localctx, _startState, RULE_expression);
						setState(98);
						if (!(precpred(_ctx, 4))) throw new FailedPredicateException(this, "precpred(_ctx, 4)");
						setState(99);
						((ExpressionContext)_localctx).sign = _input.LT(1);
						_la = _input.LA(1);
						if ( !(_la==UP || _la==DOWN) ) {
							((ExpressionContext)_localctx).sign = (Token)_errHandler.recoverInline(this);
						}
						else {
							if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
							_errHandler.reportMatch(this);
							consume();
						}
						setState(100);
						match(OPEN_BRACKET);
						setState(101);
						((ExpressionContext)_localctx).expr2 = expression(0);
						setState(102);
						match(CLOSE_BRACKET);

						               if ((((ExpressionContext)_localctx).sign!=null?((ExpressionContext)_localctx).sign.getText():null).equals("^")) {
						                  ((ExpressionContext)_localctx).value = "<msup> " + ((ExpressionContext)_localctx).expr1.value + " " + ((ExpressionContext)_localctx).expr2.value + " </msup>";
						               } else {
						                  ((ExpressionContext)_localctx).value = "<msub> " + ((ExpressionContext)_localctx).expr1.value + " " + ((ExpressionContext)_localctx).expr2.value + " </msub>";
						               }
						             
						}
						break;
					}
					} 
				}
				setState(109);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,3,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			unrollRecursionContexts(_parentctx);
		}
		return _localctx;
	}

	public static class ObjectContext extends ParserRuleContext {
		public String value;
		public Token s;
		public TerminalNode Number() { return getToken(GrammarParser.Number, 0); }
		public TerminalNode Variable() { return getToken(GrammarParser.Variable, 0); }
		public ObjectContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_object; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof GrammarListener ) ((GrammarListener)listener).enterObject(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof GrammarListener ) ((GrammarListener)listener).exitObject(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof GrammarVisitor ) return ((GrammarVisitor<? extends T>)visitor).visitObject(this);
			else return visitor.visitChildren(this);
		}
	}

	public final ObjectContext object() throws RecognitionException {
		ObjectContext _localctx = new ObjectContext(_ctx, getState());
		enterRule(_localctx, 6, RULE_object);
		try {
			setState(114);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case Number:
				enterOuterAlt(_localctx, 1);
				{
				setState(110);
				((ObjectContext)_localctx).s = match(Number);

				     ((ObjectContext)_localctx).value =  "<mn> " + (((ObjectContext)_localctx).s!=null?((ObjectContext)_localctx).s.getText():null) +" </mn>";
				   
				}
				break;
			case Variable:
				enterOuterAlt(_localctx, 2);
				{
				setState(112);
				((ObjectContext)_localctx).s = match(Variable);

				     ((ObjectContext)_localctx).value =  "<mi> " + (((ObjectContext)_localctx).s!=null?((ObjectContext)_localctx).s.getText():null) +" </mi>";
				   
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public boolean sempred(RuleContext _localctx, int ruleIndex, int predIndex) {
		switch (ruleIndex) {
		case 2:
			return expression_sempred((ExpressionContext)_localctx, predIndex);
		}
		return true;
	}
	private boolean expression_sempred(ExpressionContext _localctx, int predIndex) {
		switch (predIndex) {
		case 0:
			return precpred(_ctx, 8);
		case 1:
			return precpred(_ctx, 7);
		case 2:
			return precpred(_ctx, 6);
		case 3:
			return precpred(_ctx, 5);
		case 4:
			return precpred(_ctx, 4);
		}
		return true;
	}

	public static final String _serializedATN =
		"\3\u608b\ua72a\u8133\ub9ed\u417c\u3be7\u7786\u5964\3\24w\4\2\t\2\4\3\t"+
		"\3\4\4\t\4\4\5\t\5\3\2\3\2\3\2\3\2\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3"+
		"\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3"+
		"\3\3\3\5\3+\n\3\3\4\3\4\3\4\3\4\3\4\3\4\3\4\3\4\3\4\3\4\3\4\3\4\3\4\3"+
		"\4\3\4\3\4\3\4\3\4\3\4\3\4\3\4\3\4\5\4C\n\4\3\4\3\4\3\4\3\4\3\4\3\4\3"+
		"\4\3\4\3\4\3\4\3\4\3\4\3\4\3\4\3\4\3\4\3\4\3\4\3\4\3\4\3\4\3\4\3\4\3\4"+
		"\3\4\3\4\3\4\3\4\3\4\3\4\3\4\3\4\3\4\3\4\3\4\3\4\3\4\3\4\3\4\7\4l\n\4"+
		"\f\4\16\4o\13\4\3\5\3\5\3\5\3\5\5\5u\n\5\3\5\2\3\6\6\2\4\6\b\2\4\3\2\b"+
		"\t\3\2\23\24\2\177\2\n\3\2\2\2\4*\3\2\2\2\6B\3\2\2\2\bt\3\2\2\2\n\13\7"+
		"\21\2\2\13\f\5\4\3\2\f\r\b\2\1\2\r\3\3\2\2\2\16\17\7\3\2\2\17\20\5\6\4"+
		"\2\20\21\7\4\2\2\21\22\5\6\4\2\22\23\7\3\2\2\23\24\5\4\3\2\24\25\b\3\1"+
		"\2\25+\3\2\2\2\26\27\7\3\2\2\27\30\5\6\4\2\30\31\7\3\2\2\31\32\5\4\3\2"+
		"\32\33\b\3\1\2\33+\3\2\2\2\34\35\7\3\2\2\35\36\7\5\2\2\36\37\7\16\2\2"+
		"\37 \7\3\2\2 !\5\4\3\2!\"\b\3\1\2\"+\3\2\2\2#$\7\3\2\2$%\7\3\2\2%&\5\4"+
		"\3\2&\'\b\3\1\2\'+\3\2\2\2()\7\22\2\2)+\b\3\1\2*\16\3\2\2\2*\26\3\2\2"+
		"\2*\34\3\2\2\2*#\3\2\2\2*(\3\2\2\2+\5\3\2\2\2,-\b\4\1\2-.\7\6\2\2./\5"+
		"\6\4\2/\60\7\7\2\2\60\61\b\4\1\2\61C\3\2\2\2\62\63\7\t\2\2\63\64\5\6\4"+
		"\5\64\65\b\4\1\2\65C\3\2\2\2\66\67\7\n\2\2\678\7\17\2\289\5\6\4\29:\7"+
		"\20\2\2:;\7\17\2\2;<\5\6\4\2<=\7\20\2\2=>\b\4\1\2>C\3\2\2\2?@\5\b\5\2"+
		"@A\b\4\1\2AC\3\2\2\2B,\3\2\2\2B\62\3\2\2\2B\66\3\2\2\2B?\3\2\2\2Cm\3\2"+
		"\2\2DE\f\n\2\2EF\7\13\2\2FG\5\6\4\13GH\b\4\1\2Hl\3\2\2\2IJ\f\t\2\2JK\t"+
		"\2\2\2KL\5\6\4\nLM\b\4\1\2Ml\3\2\2\2NO\f\b\2\2OP\7\23\2\2PQ\7\17\2\2Q"+
		"R\5\6\4\2RS\7\20\2\2ST\7\24\2\2TU\7\17\2\2UV\5\6\4\2VW\7\20\2\2WX\b\4"+
		"\1\2Xl\3\2\2\2YZ\f\7\2\2Z[\7\24\2\2[\\\7\17\2\2\\]\5\6\4\2]^\7\20\2\2"+
		"^_\7\23\2\2_`\7\17\2\2`a\5\6\4\2ab\7\20\2\2bc\b\4\1\2cl\3\2\2\2de\f\6"+
		"\2\2ef\t\3\2\2fg\7\17\2\2gh\5\6\4\2hi\7\20\2\2ij\b\4\1\2jl\3\2\2\2kD\3"+
		"\2\2\2kI\3\2\2\2kN\3\2\2\2kY\3\2\2\2kd\3\2\2\2lo\3\2\2\2mk\3\2\2\2mn\3"+
		"\2\2\2n\7\3\2\2\2om\3\2\2\2pq\7\r\2\2qu\b\5\1\2rs\7\16\2\2su\b\5\1\2t"+
		"p\3\2\2\2tr\3\2\2\2u\t\3\2\2\2\7*Bkmt";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}