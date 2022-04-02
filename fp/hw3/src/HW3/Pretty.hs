module HW3.Pretty where

import HW3.Base 
import Data.Char (toLower)
import Data.Ratio (denominator, numerator)
import Data.Text (unpack)
import Prettyprinter (Doc, annotate, pretty)
import Prettyprinter.Internal (Pretty, viaShow)
import Prettyprinter.Render.Terminal (AnsiStyle, Color (..), bold, colorDull)
import Text.Printf (printf)
import Data.Sequence (Seq(Empty,(:<|)))
import qualified Data.ByteString as B
import Numeric (showHex)
import Data.List (sort)
import Data.Foldable (toList)
import qualified Data.Map as M

prettyValue :: HiValue -> Doc AnsiStyle
prettyValue (HiValueString s) = viaShow s
prettyValue (HiValueFunction fun) = annotate (colorDull Red <> bold) $ pretty $ funToStr fun
prettyValue other = annotate (colorDull Black) $ pretty $ toStr $ other
toStr (HiValueNumber x) =  (printNumber (numerator x) (denominator x) (fromRational x))
toStr (HiValueBool x) =  [toLower loweredString | loweredString <- show x]
toStr HiValueNull =  "null"
toStr (HiValueList list) =  ("[" ++ (listToStr $ toList list) ++ " ]")
toStr (HiValueBytes bytes) =  ("[# " ++ (bytesToStr bytes) ++ "#]")
toStr (HiValueTime time) = ("parse-time(" ++ "\"" ++ show time ++ "\"" ++ ")")
toStr (HiValueAction action) =  case action of
  HiActionRead file -> "read(" ++ "\"" ++ file ++ "\"" ++ ")"
  HiActionWrite file str ->  "write(" ++ "\"" ++ file ++ "\"" ++ ", " ++ (show $ prettyValue $ HiValueBytes $ str) ++ ")"
  HiActionMkDir file -> "mkdir(\"" ++ file ++ "\")"
  HiActionChDir file -> "cd(\"" ++ file ++ "\")"
  HiActionCwd -> "cwd"
  HiActionNow -> "now"
  HiActionRand i j -> "rand(" ++ (show i) ++ ", " ++ (show j) ++")"
  HiActionEcho str -> "echo(" ++ (show str) ++")"
toStr (HiValueDict dict) =  ("{" ++ (dictToStr dict) ++ " }")

simplify :: Integral a => a -> Bool
simplify 1 = True
simplify number
  | mod number 5 == 0 = simplify (div number 5)
  | mod number 2 == 0 = simplify (div number 2)
  | otherwise = False

printNumber :: (Show a, Integral a) => a -> a -> Double -> String
printNumber n d x
  | d == 1 = (show n)
  | simplify d =  (printf "%f" (x :: Double))
  | otherwise = (if n > d then
      setNumberSign n d " + "
    else if (-n) > d then
      "-" ++ setNumberSign (- n) d " - "
    else
      show n) ++ "/" ++ (show d)

setNumberSign :: (Show a, Integral a) => a -> a -> [Char] -> [Char]
setNumberSign n d sign = (show (div n d)) ++ sign ++ (show (mod n d))

listToStr :: [HiValue] -> String
listToStr [] = ""
listToStr (x:[]) = " " ++ (show $ prettyValue x)
listToStr (x:xs) = " " ++ (show $ prettyValue x) ++ "," ++ (listToStr xs)

bytesToStr :: B.ByteString -> String
bytesToStr byteString = B.foldr
  (\word string -> printf "%02x" word ++ " " ++ string)
  "" byteString

dictToStr :: M.Map HiValue HiValue -> String
dictToStr dict = let
    f [] = ""
    f [(key, val)] = " " ++ (show $ prettyValue key) ++ ": " ++ (show $ prettyValue val)
    f ((key, val) : dict) = " " ++ (show $ prettyValue key) ++ ": " ++ (show $ prettyValue val)
      ++ "," ++ (f dict)
  in f $ sort $ M.assocs dict

funToStr :: HiFun -> [Char]
funToStr fun
  | fun == HiFunDiv = "div"
  | fun == HiFunMul = "mul"
  | fun == HiFunAdd = "add"
  | fun == HiFunSub = "sub"
  | fun == HiFunNot = "not"
  | fun == HiFunAnd = "and"
  | fun == HiFunOr = "or"
  | fun == HiFunIf = "if"
  | fun == HiFunEquals = "equals"
  | fun == HiFunNotEquals = "not-equals"
  | fun == HiFunLessThan = "less-than"
  | fun == HiFunGreaterThan = "greater-than"
  | fun == HiFunNotLessThan = "not-less-than"
  | fun == HiFunNotGreaterThan = "not-greater-than"
  | fun == HiFunLength = "length"
  | fun == HiFunLength = "length"
  | fun == HiFunToUpper = "to-upper"
  | fun == HiFunToLower = "to-lower"
  | fun == HiFunReverse = "reverse"
  | fun == HiFunTrim = "trim"
  | fun == HiFunList = "list"
  | fun == HiFunRange = "range"
  | fun == HiFunFold = "fold"
  | fun == HiFunPackBytes = "pack-bytes"
  | fun == HiFunUnpackBytes = "unpack-bytes"
  | fun == HiFunZip = "zip"
  | fun == HiFunUnzip = "unzip"
  | fun == HiFunEncodeUtf8 = "encode-utf8"
  | fun == HiFunDecodeUtf8 = "decode-utf8"
  | fun == HiFunSerialise = "serialise"
  | fun == HiFunDeserialise = "deserialise"
  | fun == HiFunRead = "read"
  | fun == HiFunWrite = "write"
  | fun == HiFunMkDir = "mkdir"
  | fun == HiFunChDir = "cd"
  | fun == HiFunParseTime = "parse-time"
  | fun == HiFunRand = "rand"
  | fun == HiFunEcho = "echo"
  | fun == HiFunCount = "count"
  | fun == HiFunKeys = "keys"
  | fun == HiFunValues = "values"
  | fun == HiFunInvert = "invert"
  | otherwise = undefined