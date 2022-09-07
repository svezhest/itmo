{-# LANGUAGE OverloadedStrings #-}

module HW3.Parser (parse)
where

import Control.Monad.Combinators.Expr
import Data.Functor.Identity (Identity)
import Data.Text (pack)
import Data.Void (Void)
import HW3.Base
import Data.Char (digitToInt, isAlphaNum, isAlpha, isSpace)
import Data.Text.Read(hexadecimal)
import Text.Megaparsec (sepBy1, satisfy, ParseErrorBundle, Parsec, between, choice, eof, many, manyTill, notFollowedBy, optional, runParser, sepBy, try, (<|>))
import Text.Megaparsec.Char (digitChar, hexDigitChar, char, letterChar, space1, string)
import Text.Megaparsec.Char.Lexer (hexadecimal, scientific, signed, skipBlockComment, skipLineComment, space, symbol)
import qualified Text.Megaparsec.Char.Lexer as L
import Text.Megaparsec.Internal (ParsecT)
import Data.Word (Word8)
import Data.ByteString.Internal (packBytes)
import Data.Map (fromList)


type Parser = Parsec Void String

sc :: Parser ()
sc = space space1 lineCmnt blockCmnt
  where
    lineCmnt = skipLineComment "//"
    blockCmnt = skipBlockComment "/*" "*/"


lexeme :: Parser a -> Parser a
lexeme = L.lexeme sc

parse :: String -> Either (ParseErrorBundle String Void) HiExpr
parse = runParser pLine ""

ssc :: [Char] -> Text.Megaparsec.Internal.ParsecT Void String Data.Functor.Identity.Identity [Char]
ssc = symbol sc

between' :: Parser open -> Parser close -> Parser a -> Parser a
between' l r = between (lexeme l) (r)

brackets = between' (char '(') $ char ')'

pNum :: Parser HiExpr
pNum = (HiExprValue . HiValueNumber . toRational) <$> (signed sc scientific)

pLine :: Parser HiExpr
pLine = (ssc "") *> lexeme pExpr <* eof

pExpr :: Parser HiExpr
pExpr = makeExprParser pOperand operators

pArgsList :: Parser [HiExpr]
pArgsList = pExpr `sepBy` (lexeme $ char ',')

pOperand :: Parser HiExpr
pOperand = do
  expression <- brackets pExpr <|> atom
  args <- lexeme pArgs
  return $ combine expression args

combine :: HiExpr -> [[HiExpr]] -> HiExpr
combine fun [] = fun
combine fun ([HiExprRun _] : rest) = combine (HiExprRun fun) rest
combine fun (first : rest) = combine (HiExprApply fun first) rest

pArgs :: Parser [[HiExpr]]
pArgs = many (pDotArg <|> try ((ssc "") *> brackets pArgsList) <|> (pActionSign))

pDotArg :: Parser [HiExpr]
pDotArg = do
  afterDot <- char '.' *> pID
  return $ [((HiExprValue . HiValueString . pack) afterDot)]

pID :: Parser String
pID = let
  word =  (:) <$> (satisfy isAlpha) <*> many (satisfy isAlphaNum)
  in try ((++) <$> word <*> ((:) <$> char '-' <*> pID)) <|>
    word

pActionSign :: Parser [HiExpr]
pActionSign = ([HiExprRun $ HiExprValue HiValueNull]) <$ (char '!')

atom :: Parser HiExpr
atom = choice [
  pDict,
  pBytes,
  pList,
  pNum,
  pBool,
  pString,
  (HiExprValue HiValueNull <$ string "null"),
  pFun
  ]

pDict :: Parser HiExpr
pDict = (between' (char '{') (char '}')) (HiExprDict <$>
  (((,) <$> (pExpr <* (lexeme $ char ':')) <*> pExpr) `sepBy` (lexeme $ char ',')))

pFun :: Parser HiExpr
pFun = do
  name <- pID
  case mapFunction name of
    Nothing -> case mapAction name of
       Nothing -> fail "No Such Function"
       Just act -> return (HiExprValue (HiValueAction act))
    Just fun -> return (HiExprValue (HiValueFunction fun))

pBool :: Parser HiExpr
pBool =
  let trueInput = ssc "true"
      falseInput = ssc "false"
   in (HiExprValue . HiValueBool) <$> (True <$ trueInput <|> False <$ falseInput)

pString :: Parser HiExpr
pString = (HiExprValue . HiValueString . pack) <$> (char '"' >> manyTill L.charLiteral (char '"'))

pList :: Parser HiExpr
pList = (HiExprApply (HiExprValue $ HiValueFunction HiFunList)) <$> (between' (char '[') $ char ']') pArgsList

funN :: String -> HiFun -> Operator Parser HiExpr
funN name f = InfixN (funApply f <$ lexeme (string name))

funL :: String -> HiFun -> Operator Parser HiExpr
funL name f = InfixL (funApply f <$ lexeme (string name))

funR :: String -> HiFun -> Operator Parser HiExpr
funR name f = InfixR (funApply f <$ lexeme (string name))

funApply :: HiFun -> HiExpr -> HiExpr -> HiExpr
funApply fun x y = HiExprApply (HiExprValue $ HiValueFunction fun) [x, y]

pBytes :: Parser HiExpr
pBytes = HiExprValue . HiValueBytes . packBytes . (map fromIntegral) <$> (between' (string "[#") (string "#]") $ lexeme byteSeq) where
  byteSeq :: Parser [Int]
  byteSeq = try ((:) <$> (hex <* (lexeme $ satisfy isSpace)) <*> byteSeq)
    <|> try ((:[]) <$> hex)
    <|> return []
  hex :: Parser Int
  hex = (\a b -> a * 16 + b) <$> (digitToInt <$> hexDigitChar) <*> (digitToInt <$> hexDigitChar)

operators :: [[Operator Parser HiExpr]]
operators =
  [[InfixL (funApply HiFunDiv <$ try (lexeme $ string "/" <* notFollowedBy (string "="))),
    funL "*" HiFunMul],
   [funL "+" HiFunAdd,
    funL "-" HiFunSub],
   [funN ">=" HiFunNotLessThan,
    funN "<=" HiFunNotGreaterThan,
    funN "<" HiFunLessThan,
    funN ">" HiFunGreaterThan,
    funN "==" HiFunEquals,
    funN "/=" HiFunNotEquals],
   [funR "&&" HiFunAnd],
   [funR "||" HiFunOr]]
   
mapFunction :: String -> Maybe HiFun
mapFunction "div" = Just HiFunDiv
mapFunction "mul" = Just HiFunMul
mapFunction "add" = Just HiFunAdd
mapFunction "sub" = Just HiFunSub
mapFunction "not" = Just HiFunNot
mapFunction "and" = Just HiFunAnd
mapFunction "or" = Just HiFunOr
mapFunction "less-than" = Just HiFunLessThan
mapFunction "greater-than" = Just HiFunGreaterThan
mapFunction "equals" = Just HiFunEquals
mapFunction "not-less-than" = Just HiFunNotLessThan
mapFunction "not-greater-than" = Just HiFunNotGreaterThan
mapFunction "not-equals" = Just HiFunNotEquals
mapFunction "if" = Just HiFunIf
mapFunction "length" = Just HiFunLength
mapFunction "to-upper" = Just HiFunToUpper
mapFunction "to-lower" = Just HiFunToLower
mapFunction "reverse" = Just HiFunReverse
mapFunction "trim" = Just HiFunTrim
mapFunction "list" = Just HiFunList
mapFunction "range" = Just HiFunRange
mapFunction "fold" = Just HiFunFold
mapFunction "pack-bytes" = Just HiFunPackBytes
mapFunction "unpack-bytes" = Just HiFunUnpackBytes
mapFunction "zip" = Just HiFunZip
mapFunction "unzip" = Just HiFunUnzip
mapFunction "encode-utf8" = Just HiFunEncodeUtf8
mapFunction "decode-utf8" = Just HiFunDecodeUtf8
mapFunction "serialise" = Just HiFunSerialise
mapFunction "deserialise" = Just HiFunDeserialise
mapFunction "read" = Just HiFunRead
mapFunction "write" = Just HiFunWrite
mapFunction "mkdir" = Just HiFunMkDir
mapFunction "cd" = Just HiFunChDir
mapFunction "parse-time" = Just HiFunParseTime
mapFunction "rand" = Just HiFunRand
mapFunction "echo" = Just HiFunEcho
mapFunction "count" = Just HiFunCount
mapFunction "keys" = Just HiFunKeys
mapFunction "values" = Just HiFunValues
mapFunction "invert" = Just HiFunInvert
mapFunction _ = Nothing

mapAction :: String -> Maybe HiAction
mapAction "cwd" = Just HiActionCwd
mapAction "now" = Just HiActionNow
mapAction _ = Nothing