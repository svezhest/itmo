{-# LANGUAGE BlockArguments #-}

module HW3.Evaluator
  ( eval,
  )
where

import Control.Monad.IO.Class (liftIO)
import Data.Time (UTCTime, NominalDiffTime, addUTCTime, diffUTCTime)
import Text.Read(readMaybe)
import Data.Text.Encoding
import Data.Ratio (denominator, numerator)
import Data.Semigroup (stimes)
import qualified Codec.Compression.Zlib as Z
import qualified Data.Sequence as Q
import qualified Data.Text as T
import qualified Data.ByteString as B
import Data.ByteString.Lazy(toStrict, fromStrict)
import Data.Foldable (toList)
import Data.Word (Word8)
import Data.ByteString.Internal (packBytes, unpackBytes)
import Data.Char (digitToInt, ord)
import Data.List (elemIndex)
import Data.Maybe (fromMaybe)
import Numeric (showHex)
import HW3.Base
import HW3.Action
import Control.Exception.Base
import Codec.Serialise (serialise, deserialiseOrFail)
import qualified Data.Map as M

eval :: HiMonad m => HiExpr -> m (Either HiError HiValue)
eval expr = case expr of
  (HiExprValue value) -> return $ Right value
  (HiExprDict args) -> let
    f :: HiMonad m => [(HiExpr, HiExpr)] -> m (Either HiError [(HiValue, HiValue)])
    f [] = return $ Right []
    f ((x,y):xs) = do
      ex <- eval x
      case ex of
        Right gx -> do
          ey <- eval y
          case ey of
            Right gy -> do
              cont <- f xs
              case cont of
                Left e -> return $ Left e
                Right gCont -> return $ Right $ (gx, gy) : gCont
            Left e -> return $ Left e
        Left e -> return $ Left e
    in do
      res <- f args
      case res of
        Left e -> return $ Left e
        Right list -> (return . Right . HiValueDict . M.fromList) list
  (HiExprApply function arguments) -> do
     case function of
      (HiExprValue hiValFun) -> case hiValFun of
        (HiValueNumber _) -> return $ Left HiErrorInvalidFunction
        (HiValueFunction hiFun) -> eFun hiFun arguments
        (HiValueString str) -> eListOp str arguments
        (HiValueList list) -> eListOpList list arguments
        (HiValueBytes bytes) -> eListOpBytes bytes arguments
        (HiValueDict dict) -> evalMapLookup dict arguments
        _ -> return $ Left HiErrorInvalidFunction
      (HiExprApply _ _) -> do
        funEval <- eval function
        case funEval of
          Right funEvalR -> eval (HiExprApply (HiExprValue funEvalR) arguments)
          Left e -> return $ Left e
      (HiExprDict dict) -> do
        dict' <- eval function
        case dict' of
          Left e -> return $ Left e
          Right (HiValueDict vDict) -> evalMapLookup vDict arguments
          Right _ -> return $ Left HiErrorInvalidFunction
      _ -> return $ Left HiErrorInvalidFunction
  (HiExprRun expr) -> do
    toRun <- eval expr
    case toRun of
      Right (HiValueAction action) -> do
        ans <- runAction action
        return $ Right ans
      Right _ -> do
        return $ Left HiErrorInvalidArgument
      Left e -> do
        return $ Left e

eFun :: HiMonad m => HiFun -> [HiExpr] -> m (Either HiError HiValue)
eFun hiFun = case hiFun of
  HiFunAdd -> arithmeticFunction hiFun (+)
  HiFunSub -> arithmeticFunction hiFun (-)
  HiFunMul -> arithmeticFunction hiFun (*)
  HiFunDiv -> arithmeticFunction hiFun (/)
  HiFunNot -> eNot
  HiFunAnd -> eAnd
  HiFunOr -> eOr
  HiFunLessThan -> evalEq (<)
  HiFunGreaterThan -> evalEq (>)
  HiFunEquals -> evalEq (==)
  HiFunNotLessThan -> evalEq (>=)
  HiFunNotGreaterThan -> evalEq (<=)
  HiFunNotEquals -> evalEq (/=)
  HiFunIf -> ifFunction
  HiFunLength -> eFunction f 1  where
    f [(HiValueString text)] = return $ Right $ HiValueNumber $ toRational $ T.length text
    f [(HiValueList list)] = return $ Right $ HiValueNumber $ toRational $ Q.length list
    f [(HiValueBytes bytes)] = return $ Right $ HiValueNumber $ toRational $ B.length bytes
    f _ = return $ Left HiErrorInvalidArgument
  HiFunToUpper -> eFunction f 1  where
    f [(HiValueString text)] = return $ Right $ HiValueString $ T.toUpper text
    f _ = return $ Left HiErrorInvalidArgument
  HiFunToLower -> eFunction f 1  where
    f [(HiValueString text)] = return $ Right $ HiValueString $ T.toLower text
    f _ = return $ Left HiErrorInvalidArgument
  HiFunReverse -> eFunction f 1  where
    f [(HiValueString text)] = return $ Right $ HiValueString $ T.reverse text
    f [(HiValueList list)] = return $ Right $ HiValueList $ Q.reverse list
    f [(HiValueBytes bytes)] = return $ Right $ HiValueBytes $ B.reverse bytes
    f _ = return $ Left HiErrorInvalidArgument
  HiFunTrim -> eFunction f 1  where
    f [(HiValueString text)] = return $ Right $ HiValueString $ T.strip text
    f _ = return $ Left HiErrorInvalidArgument
  HiFunList -> evalList
  HiFunRange -> eRange
  HiFunFold -> eFold
  HiFunPackBytes   -> ePackBytes
  HiFunUnpackBytes -> eUnpackBytes
  HiFunEncodeUtf8  -> eEncodeUtf8
  HiFunDecodeUtf8  -> eDecodeUtf8
  HiFunZip         -> eZip
  HiFunUnzip       -> eUnzip
  HiFunSerialise   -> eSerialise
  HiFunDeserialise -> eDeserialise
  HiFunRead -> eRead
  HiFunWrite -> eWrite
  HiFunMkDir -> eMkDir
  HiFunChDir -> eChDir
  HiFunParseTime -> eTime
  HiFunRand -> eRandAction
  HiFunEcho -> eEchoAction
  HiFunCount -> eCount
  HiFunKeys -> eKeys
  HiFunValues -> eValues
  HiFunInvert -> eInvert

eFunction :: HiMonad m => ([HiValue] -> m (Either HiError HiValue)) -> Int-> [HiExpr] -> m (Either HiError HiValue)
eFunction function arity args =
  if arity /= length args
    then return $ Left HiErrorArityMismatch
  else
    let
      f :: HiMonad m => [HiExpr] -> m (Either HiError [HiValue])
      f []  = return $ Right []
      f (x:xs) = do
        valOrErr <- eval x
        case valOrErr of
          Left e -> return $ Left e
          Right val -> do
            restOrErr <- f xs
            return $ case restOrErr of
               Left e -> Left e
               Right rest -> Right $ val : rest
    in
      do
        argValsOrErr <- f args
        case argValsOrErr of
          Left e -> return $ Left e
          Right argVals -> do
             res <- function argVals
             return $ res


arithmeticFunction :: HiMonad m => HiFun -> (Rational -> Rational -> Rational) -> [HiExpr] -> m (Either HiError HiValue)
arithmeticFunction hiFun fun =
  eFunction f 2 where
   f [((HiValueNumber rx)), (HiValueNumber ry)] = return $ case hiFun of
       HiFunDiv ->
         if ry == 0
           then Left HiErrorDivideByZero
           else Right (HiValueNumber (rx / ry))
       _ -> Right (HiValueNumber (fun rx ry))
   f [((HiValueNumber rx)), (HiValueString str1)] = return $ case hiFun of
       HiFunMul ->
         if 1 == denominator rx
           then Right $ HiValueString $ stimes (numerator rx) str1
           else exception
       (_) -> exception
   f [((HiValueNumber rx)), (HiValueList list1)] = return $ case hiFun of
        HiFunMul ->
          if 1 == denominator rx
            then Right $ HiValueList $ stimes (numerator rx) list1
            else exception
        _ -> exception
   f [((HiValueNumber rx)), (HiValueBytes bytes1)] = return $ case hiFun of
       HiFunMul ->
         if 1 == denominator rx && 0 < numerator rx
           then Right $ HiValueBytes $ packBytes $ stimes (numerator rx) $ unpackBytes bytes1
           else exception
       _ -> exception
   f [((HiValueNumber rx)), (HiValueTime time1)] = return $ case hiFun of
      HiFunAdd -> Right $ HiValueTime $ addUTCTime (fromRational rx :: NominalDiffTime) time1
      _ -> exception
   f [((HiValueString str0)), (HiValueString str1)] = return $ case hiFun of
     HiFunAdd -> Right $ HiValueString $ T.concat [str0, str1]
     HiFunDiv -> Right $ HiValueString $ T.concat [str0, T.pack "/", str1]
     _ -> exception
   f [((HiValueString str0)), (HiValueNumber rational1)] = return $ case hiFun of
      HiFunMul ->
        if 1 == denominator rational1 && 0 < numerator rational1
          then Right $ HiValueString $ stimes (numerator rational1) str0
          else exception
      _ -> exception
   f [((HiValueList list0)), (HiValueList list1)] = return $ case hiFun of
     HiFunAdd -> Right $ HiValueList $ list0 Q.>< list1
     _ -> exception
   f [((HiValueList list0)), (HiValueNumber rational1)] = return $ case hiFun of
     HiFunMul ->
       if 1 == denominator rational1 && 0 < numerator rational1
         then Right $ HiValueList $ stimes (numerator rational1) list0
         else exception
     _ -> exception
   f [((HiValueBytes bytes0)), (HiValueBytes bytes1)] = return $ case hiFun of
     HiFunAdd -> Right $ HiValueBytes $ packBytes $ unpackBytes bytes0 ++ unpackBytes bytes1
     _ -> exception
   f [((HiValueBytes bytes0)), (HiValueNumber rational1)] = return $ case hiFun of
       HiFunMul ->
         if 1 == denominator rational1 && 0 < numerator rational1
           then Right $ HiValueBytes $ packBytes $ stimes (numerator rational1) $ unpackBytes bytes0
           else exception
       _ -> exception
   f [((HiValueTime time0)), (HiValueNumber num)] = return $ case hiFun of
         HiFunAdd -> Right $ HiValueTime $ addUTCTime (fromRational num :: NominalDiffTime) time0
         _ -> exception
   f [((HiValueTime time0)), (HiValueTime time1)] = return $ case hiFun of
         HiFunSub -> Right $ HiValueNumber $ toRational $ diffUTCTime time0 time1
         _ -> exception
   f _ = return $ Left HiErrorInvalidArgument
   exception = Left HiErrorInvalidArgument



eNot :: HiMonad m => [HiExpr] -> m (Either HiError HiValue)
eNot = eFunction f 1 where
  f [(HiValueBool bool)] = return $ Right (HiValueBool (not bool))
  f _ = return $ Left HiErrorInvalidArgument

eAnd :: HiMonad m =>  [HiExpr] -> m (Either HiError HiValue)
eAnd values =
  if 2 /= length values
    then return $ Left HiErrorArityMismatch
  else
    do
      a <- eval $ head values
      case a of
        Right (HiValueBool False) -> return $ Right $ HiValueBool $ False
        Right (HiValueNull) -> return $ Right $ HiValueNull
        Right (HiValueBool True) -> eval $ values !! 1
        Right (_) -> eval $ values !! 1
        Left e -> return $ Left e

eOr :: HiMonad m =>  [HiExpr] -> m (Either HiError HiValue)
eOr values =
  if 2 /= length values
    then return $ Left HiErrorArityMismatch
  else
    do
      a <- eval $ head values
      case a of
        Right (HiValueBool False) -> eval $ values !! 1
        Right (HiValueNull) -> eval $ values !! 1
        Right (HiValueBool True) -> return $ Right $ HiValueBool $ True
        Right (_) -> return $ a
        Left e -> return $ Left e

evalEq ::
  HiMonad m =>  (HiValue -> HiValue -> Bool) ->
  [HiExpr] ->
  m (Either HiError HiValue)
evalEq fun values =
  if 2 == length values
    then do
      val0 <- eval $ head values
      val1 <- eval $ values !! 1
      return $ case val0 of
        Right arg0 -> case val1 of
          Right arg1 -> Right $ HiValueBool $ fun arg0 arg1
          Left e -> Left e
        Left e -> Left e
    else return $ Left HiErrorArityMismatch

ifFunction :: HiMonad m => [HiExpr] -> m (Either HiError HiValue)
ifFunction values =
  if length values /= 3
    then return $ Left HiErrorInvalidArgument
    else do
      expression <- eval $ head values
      case expression of
        Right (HiValueBool expr) -> case expr of
          True -> do
            trueAns <- eval $ values !! 1
            return $ case trueAns of
              Left e -> Left e
              Right (_) -> trueAns
          False -> do
            falseAns <- eval $ values !! 2
            return $ case falseAns of
              Left e -> Left e
              Right (_) -> falseAns
        Right (_) -> return $ Left HiErrorInvalidArgument
        Left e -> return $ Left e

eListOpGeneric :: HiMonad m => a -> (a -> Rational) -> (a -> Rational -> HiValue) -> (a -> Rational -> Rational -> HiValue) -> [HiExpr] -> m (Either HiError HiValue)
eListOpGeneric list lenFun getFun sliceFun values =
  let len = lenFun list
   in if 1 == length values
        then do
          val0 <- eval $ head values
          return $ case val0 of
            Right (HiValueNumber i) ->
              if i < 0 || i > len - (toRational 1)
                then Right HiValueNull
                else if 1 /= denominator i then Left HiErrorInvalidArgument else Right $ getFun list i
            Right _ -> Left HiErrorInvalidArgument
            Left e -> Left e
        else
          if 2 == length values
            then do
              val0 <- eval $ head values
              val1 <- eval $ values !! 1
              case val0 of
                Right HiValueNull -> case val1 of
                  Right j -> eListOpGeneric list lenFun getFun sliceFun [HiExprValue $ HiValueNumber $ toRational 0, HiExprValue $ j]
                  Left e -> return $ Left e
                Right (HiValueNumber i) -> case val1 of
                  Right HiValueNull ->
                    eListOpGeneric list lenFun getFun sliceFun [HiExprValue $ HiValueNumber i, HiExprValue $ HiValueNumber $ len]
                  Right (HiValueNumber j) ->
                    let i1 = if i < 0 then max 0 (i + len) else min i len
                        j1 = if j < 0 then max 0 (j + len) else min j len
                     in return $ if 1 /= denominator i1 || 1 /= denominator j1
                          then Left HiErrorInvalidArgument
                          else
                            Right $ sliceFun list i1 j1
                  Right _ -> return $ Left HiErrorInvalidArgument
                  Left e -> return $ Left e
                Right _ -> return $ Left HiErrorInvalidArgument
                Left e -> return $ Left e
            else return $ Left HiErrorArityMismatch


eListOp ::  HiMonad m => T.Text -> [HiExpr] -> m (Either HiError HiValue)
eListOp str = eListOpGeneric str
  (toRational . T.length)
  (\str i -> HiValueString $ T.pack [T.index str (fromInteger $ numerator i)])
  (\str i1 j1 -> HiValueString $ (T.drop (fromInteger $ numerator i1) . T.take (fromInteger $ numerator j1)) str)

eListOpBytes :: HiMonad m => B.ByteString -> [HiExpr] -> m (Either HiError HiValue)
eListOpBytes str = eListOpGeneric str
  (toRational . B.length)
  (\str i -> HiValueNumber $ fromIntegral $ B.index str (fromInteger $ numerator i))
  (\str i1 j1 -> HiValueBytes $ (B.drop (fromInteger $ numerator i1) . B.take (fromInteger $ numerator j1)) str)

eListOpList :: HiMonad m => Q.Seq HiValue -> [HiExpr] -> m (Either HiError HiValue)
eListOpList str = eListOpGeneric str
  (toRational . Q.length)
  (\str i -> Q.index str (fromInteger $ numerator i))
  (\str i1 j1 -> HiValueList $ (Q.drop (fromInteger $ numerator i1) . Q.take (fromInteger $ numerator j1)) str)

evalList :: HiMonad m => [HiExpr] -> m (Either HiError HiValue)
evalList values =
  let f :: HiMonad m => [HiExpr] -> m (Either HiError (Q.Seq HiValue))
      f [] = return $ Right Q.Empty
      f (val : values) = do
        evaledVal <- eval val
        case evaledVal of
          Right smth -> do
            next <- f values
            case next of
              Right cont -> return $ Right (smth Q.:<| cont)
              Left e -> return $ Left e
          Left e -> return $ Left e
   in do
    res <- f values
    case res of
      Right smth -> return $ Right $ HiValueList smth
      Left e -> return $ Left e

eRange :: HiMonad m => [HiExpr] -> m (Either HiError HiValue)
eRange = eFunction f 2 where
  f [(HiValueNumber i), (HiValueNumber j)] = return $ Right $ HiValueList $ Q.fromList $ map (HiValueNumber) [i .. j]
  f _ = return $ Left HiErrorInvalidArgument

eFold :: HiMonad m => [HiExpr] -> m (Either HiError HiValue)
eFold = eFunction f 2 where
 f [fun, (HiValueList list)] = case list of
  Q.Empty -> return $ Right HiValueNull
  (acc Q.:<| cont) ->
    let f :: HiMonad m => HiValue -> Q.Seq HiValue -> m (Either HiError HiValue)
        f acc Q.Empty = return $ Right acc
        f acc (el Q.:<| cont) = do
          newAcc <-
            eval
              ( HiExprApply
                  (HiExprValue $ fun)
                  [HiExprValue $ acc, HiExprValue $ el]
              )
          case newAcc of
            Right newAcc' -> f newAcc' cont
            Left e -> return $ Left e
     in f acc cont
 f _ = return $ Left HiErrorInvalidArgument

mapWithErrors :: (a -> (Either HiError b)) -> [a] -> (Either HiError [b])
mapWithErrors f [] = Right []
mapWithErrors f (x:xs) = case f x of
  Right first -> case mapWithErrors f xs of
    Right rest -> Right $ first : rest
    Left e -> Left e
  Left e -> Left e

ePackBytes :: HiMonad m => [HiExpr] -> m (Either HiError HiValue)
ePackBytes = eFunction f 1 where
  f [(HiValueList hList)] = let
    list =  toList hList
    loop = mapWithErrors (\x -> case x of
      HiValueNumber num -> if 1 /= denominator num || 0 > numerator num || 255 < numerator num then
       Left HiErrorInvalidArgument
       else Right (numerator num)
      _ -> Left HiErrorInvalidArgument)
    in
      return $ case loop list of
        Right tList -> Right $ HiValueBytes $
          B.pack (map fromIntegral tList)
        Left e -> Left e
  f _ = return $ Left HiErrorInvalidArgument

eUnpackBytes :: HiMonad m => [HiExpr] -> m (Either HiError HiValue)
eUnpackBytes = eFunction f 1 where
  f [(HiValueBytes bytes)] = return $ Right $ HiValueList $ Q.fromList $ map (HiValueNumber . toRational) $ unpackBytes bytes
  f _ = return $ Left HiErrorInvalidArgument

eEncodeUtf8 :: HiMonad m => [HiExpr] -> m (Either HiError HiValue)
eEncodeUtf8 = eFunction f 1 where
  f [(HiValueString str)] = return $ Right $ HiValueBytes $ encodeUtf8 str
  f _ = return $ Left HiErrorInvalidArgument

eDecodeUtf8 :: HiMonad m => [HiExpr] -> m (Either HiError HiValue)
eDecodeUtf8 = eFunction f 1 where
  f [(HiValueBytes bytes)] = return $ case decodeUtf8' bytes of
    Right str -> Right $ HiValueString str
    Left _ -> Right $ HiValueNull
  f _ = return $ Left HiErrorInvalidArgument

eZip :: HiMonad m => [HiExpr] -> m (Either HiError HiValue)
eZip = eFunction f 1 where
  f [(HiValueBytes bytes)] = return $ Right $ HiValueBytes $ toStrict $ Z.compressWith
     (Z.defaultCompressParams {Z.compressLevel = Z.bestCompression }) (fromStrict bytes)
  f _ = return $ Left HiErrorInvalidArgument

eUnzip :: HiMonad m => [HiExpr] -> m (Either HiError HiValue)
eUnzip = eFunction f 1 where
  f [(HiValueBytes bytes)] = return $ Right $ HiValueBytes $ toStrict $ Z.decompressWith
    (Z.defaultDecompressParams) (fromStrict bytes)
  f _ = return $ Left HiErrorInvalidArgument

eSerialise :: HiMonad m => [HiExpr] -> m (Either HiError HiValue)
eSerialise = eFunction f 1 where
  f [value] = return $ Right $ HiValueBytes $ toStrict $ serialise value
  f _ = return $ Left HiErrorInvalidArgument

eDeserialise :: HiMonad m => [HiExpr] -> m (Either HiError HiValue)
eDeserialise = eFunction f 1 where
  f [(HiValueBytes bytes)] = return $ case deserialiseOrFail $ fromStrict bytes of
    Right res -> Right res
    Left _ -> Left HiErrorInvalidArgument
  f _ = return $ Left HiErrorInvalidArgument

eRead :: HiMonad m => [HiExpr] -> m (Either HiError HiValue)
eRead = eFunction f 1 where
  f [(HiValueString file)] = return $ Right $ HiValueAction $ HiActionRead $ T.unpack file
  f _ = return $ Left HiErrorInvalidArgument

eChDir :: HiMonad m => [HiExpr] -> m (Either HiError HiValue)
eChDir = eFunction f 1 where
  f [(HiValueString file)] = return $ Right $ HiValueAction $ HiActionChDir $ T.unpack file
  f _ = return $ Left HiErrorInvalidArgument

eMkDir :: HiMonad m => [HiExpr] -> m (Either HiError HiValue)
eMkDir = eFunction f 1 where
  f [(HiValueString file)] = return $ Right $ HiValueAction $ HiActionMkDir $ T.unpack file
  f _ = return $ Left HiErrorInvalidArgument

eWrite :: HiMonad m => [HiExpr] -> m (Either HiError HiValue)
eWrite = eFunction f 2 where
  f [(HiValueString file), (HiValueString text)] = return $ Right $ HiValueAction $ HiActionWrite (T.unpack file) (encodeUtf8 text)
  f [(HiValueString file), (HiValueBytes bytes)] = return $ Right $ HiValueAction $ HiActionWrite (T.unpack file) bytes
  f _ = return $ Left HiErrorInvalidArgument

eTime :: HiMonad m => [HiExpr] -> m (Either HiError HiValue)
eTime = eFunction f 1 where
  f [(HiValueString text)] = return $ Right $ case (readMaybe . T.unpack) text :: Maybe UTCTime of
   Nothing -> HiValueNull
   Just time ->  HiValueTime time
  f _ = return $ Left HiErrorInvalidArgument

eRandAction :: HiMonad m => [HiExpr] -> m (Either HiError HiValue)
eRandAction = eFunction f 2 where
  f [(HiValueNumber num0), (HiValueNumber num1)] = return $ if 1 /= denominator num1 || num0 > num1
    || (num0) /= toRational (fromInteger $ numerator num0 :: Int)
    || (num1) /= toRational (fromInteger $ numerator num1 :: Int)
    then Left HiErrorInvalidArgument
    else Right $ HiValueAction $ HiActionRand (fromInteger $ numerator num0) (fromInteger $ numerator num1)
  f _ = return $ Left HiErrorInvalidArgument

eEchoAction :: HiMonad m => [HiExpr] -> m (Either HiError HiValue)
eEchoAction = eFunction f 1 where
  f [(HiValueString text)] = return $ Right $ HiValueAction $ HiActionEcho text
  f _ = return $ Left HiErrorInvalidArgument

evalMapLookup :: HiMonad m => (M.Map HiValue HiValue) -> [HiExpr] -> m (Either HiError HiValue)
evalMapLookup dict' values = if 1 == length values then do
   val0 <- eval $ values !! 0
   return $ case val0 of
     Right input -> Right $ case M.lookup input dict' of
       Just value -> value
       Nothing -> HiValueNull
     Left e -> Left e
   else
     return $ Left HiErrorArityMismatch

eCount :: HiMonad m => [HiExpr] -> m (Either HiError HiValue)
eCount = eFunction f 1 where
  f [(HiValueString str)] = return $ Right $ HiValueDict $ count $ map (\x -> HiValueString $ T.pack $ [x]) $ T.unpack str
  f [(HiValueList list)] = return $ Right $ HiValueDict $ count $ toList list
  f [(HiValueBytes bytes)] = return $ Right $ HiValueDict $ count $ map (HiValueNumber . toRational) $ unpackBytes bytes
  f _ = return $ Left HiErrorInvalidArgument
  count :: [HiValue] -> M.Map HiValue HiValue
  count [] = M.empty
  count (x:xs) = M.insertWith (\(HiValueNumber a) (HiValueNumber b) -> HiValueNumber $ a + b) x (HiValueNumber 1) (count xs)

eKeys :: HiMonad m => [HiExpr] -> m (Either HiError HiValue)
eKeys = eFunction f 1 where
  f [(HiValueDict dict)] = return $ Right $ HiValueList $ Q.fromList $ M.keys dict
  f _ = return $ Left HiErrorInvalidArgument

eValues :: HiMonad m => [HiExpr] -> m (Either HiError HiValue)
eValues = eFunction f 1 where
  f [(HiValueDict dict)] = return $ Right $ HiValueList $ Q.fromList $ M.elems dict
  f _ = return $ Left HiErrorInvalidArgument

eInvert :: HiMonad m => [HiExpr] -> m (Either HiError HiValue)
eInvert = eFunction f 1 where
  f [(HiValueDict dict)] = return $ Right $ HiValueDict $
    M.unionsWith (\(HiValueList a) (HiValueList b) -> HiValueList $ b Q.>< a)
      $ map (\(x,y) -> M.fromList([(y, (HiValueList . Q.singleton) x)])) $ M.toList dict
  f _ = return $ Left HiErrorInvalidArgument